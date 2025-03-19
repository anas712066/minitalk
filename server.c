/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:08:38 by mumajeed          #+#    #+#             */
/*   Updated: 2025/03/18 22:08:39 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	process_signal(int sig, char *c, int *bit)
{
	if (sig == SIGUSR1)
		*c |= (0b10000000 >> *bit);
	else if (sig == SIGUSR2)
		*c &= ~(0x80 >> *bit);
	(*bit)++;
}

static void	handle_char(char *c, pid_t goku, int *bit)
{
	if (*bit == CHAR_BIT)
	{
		*bit = 0;
		if (*c == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			Kill(goku, SIGUSR2);
		}
		else
			write(STDOUT_FILENO, c, 1);
		*c = 0;
	}
	Kill(goku, SIGUSR1);
}

static void	handler(int sig, siginfo_t *info, void *more_info)
{
	static char	c;
	static int	bit;
	static pid_t goku;

	(void)more_info;
	if (!goku && info->si_pid)
		goku = info->si_pid;
	process_signal(sig, &c, &bit);
	handle_char(&c, goku, &bit);
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		fputs("Usage: ./server\n", stderr);
		return (EXIT_FAILURE);
	}
	ft_printf("Server PID: %d\n", getpid());
	Signal(SIGUSR1, NULL, handler, true);
	Signal(SIGUSR2, NULL, handler, true);
	while (1337)
		pause();
	return (EXIT_SUCCESS);
}

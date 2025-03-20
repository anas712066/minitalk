/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:59:55 by mumajeed          #+#    #+#             */
/*   Updated: 2025/03/18 21:59:57 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_kingkai = BUSY;

static void	end_handler(int sig)
{
	(void)sig;
	fputs("\n\t✅ Message received ✅\n", stdout);
	g_kingkai = READY;
	exit(EXIT_SUCCESS);
}

static void	ack_handler(int sig)
{
	(void)sig;
	g_kingkai = READY;
}

static void	send_char(char c, pid_t kingkai)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if (c & (0x80 >> bit))
			send_signal(kingkai, SIGUSR1);
		else
			send_signal(kingkai, SIGUSR2);
		bit++;
		while (BUSY == g_kingkai)
			usleep(42);
		g_kingkai = BUSY;
	}
}

int	main(int ac, char **av)
{
	pid_t	kingkai;
	char	*message;
	int		i;

	if (ac != 3)
	{
		fputs("Usage: ./client <kingkai> \"message\"\n", stderr);
		return (EXIT_FAILURE);
	}
	kingkai = ft_atoi(av[1]);
	message = av[2];
	signal_setup(SIGUSR1, ack_handler, NULL, false);
	signal_setup(SIGUSR2, end_handler, NULL, false);
	i = 0;
	while (message[i])
		send_char(message[i++], kingkai);
	send_char('\0', kingkai);
	return (EXIT_SUCCESS);
}

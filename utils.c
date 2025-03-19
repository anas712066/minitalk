/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:11:49 by mumajeed          #+#    #+#             */
/*   Updated: 2025/03/18 22:11:50 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	Signal(int sig, void (*handler)(int), void (*siginfo_handler)
	(int, siginfo_t *, void *), bool use_siginfo)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (use_siginfo)
	{
		sa.sa_sigaction = siginfo_handler;
		sa.sa_flags = SA_SIGINFO;
	}
	else
	{
		sa.sa_handler = handler;
		sa.sa_flags = 0;
	}
	if (sigaction(sig, &sa, NULL) < 0)
	{
		perror("Signal handler setup failed");
		exit(EXIT_FAILURE);
	}
}

void	Kill(pid_t pid, int signum)
{
	if (kill(pid, signum) < 0)
	{
		perror("Signal transmission failed");
		exit(EXIT_FAILURE);
	}
}

void	print_pending_signals(void)
{
	sigset_t	pending;
	int			i;

	if (sigpending(&pending) == -1)
	{
		perror("sigpending");
		exit(EXIT_FAILURE);
	}
	ft_printf("\n=== Pending Signals ===\n");
	i = 1;
	while (i < NSIG)
	{
		if (sigismember(&pending, i))
			ft_printf("Signal %d (%s) is pending\n", i, strsignal(i));
		i++;
	}
	printf("=======================\n\n");
}

void	print_blocked_signals(void)
{
	sigset_t	blocked;
	int			i;

	if (sigprocmask(SIG_BLOCK, NULL, &blocked) == -1)
	{
		perror("sigprocmask");
		exit(EXIT_FAILURE);
	}
	ft_printf("\n=== Blocked Signals ===\n");
	i = 1;
	while (i < NSIG)
	{
		if (sigismember(&blocked, i))
			ft_printf("Signal %d (%s) is blocked\n", i, strsignal(i));
		i++;
	}
	ft_printf("=======================\n");
}

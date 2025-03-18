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

void	signal_handler(int sig, void *handler, bool use_siginfo)
{
	sigaction	sa;

	sa.sa_mask = 0;
	if (use_siginfo)
	{
		sa.sa_sigaction = handler;
		sa.sa_flags = SA_SIGINFO;
	}
	else
		sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(sig, &sa, NULL) < 0)
	{
		perror("Signal handler setup failed");
		exit(EXIT_FAILURE);
	}
}

void	kill_process(pid_t pid, int signum)
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
	printf("\n=== Pending Signals ===\n");
	i = 1;
	while (i < NSIG)
	{
		if (sigismember(&pending, i))
			printf("Signal %d (%s) is pending\n", i, strsignal(i));
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
	printf("\n=== Blocked Signals ===\n");
	i = 1;
	while (i < NSIG)
	{
		if (sigismember(&blocked, i))
			printf("Signal %d (%s) is blocked\n", i, strsignal(i));
		i++;
	}
	printf("=======================\n");
}

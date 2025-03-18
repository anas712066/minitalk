/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:46:12 by mumajeed          #+#    #+#             */
/*   Updated: 2025/03/14 12:47:14 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>

# define BUSY 0
# define READY 1

void	Signal(int nsig, void *handler, bool use_siginfo);
void	Kill(pid_t pid, int signum);

#endif

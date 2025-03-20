/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:07:56 by mumajeed          #+#    #+#             */
/*   Updated: 2025/03/18 22:07:58 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include "ft_printf/includes/ft_printf.h"
# include "libft/libft.h"

# define BUSY	0
# define READY	1

void	signal_setup(int sig, void (*handler)(int),
			void (*siginfo_handler)
			(int, siginfo_t *, void *), bool use_siginfo);
void	send_signal(pid_t pid, int signum);

#endif

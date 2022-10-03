/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:13:25 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/09 12:46:27 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_ctl_c(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler_fork(int sig_num)
{
	if (sig_num == SIGINT)
		rl_on_new_line();
	else if (sig_num == SIGQUIT)
		ft_putstr_fd("", 1);
}

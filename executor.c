/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:01:04 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/09 12:34:43 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	this_is_buitlin(t_info *data)
{
	if (!ft_strncmp(data->reserved_words[0], data->cmd_list->args[0], 5))
		return (ft_echo(data));
	if (!ft_strncmp(data->reserved_words[1], data->cmd_list->args[0], 4))
		return (ft_pwd(data));
	if (!ft_strncmp(data->reserved_words[2], data->cmd_list->args[0], 3))
		return (ft_cd(data));
	if (!ft_strncmp(data->reserved_words[3], data->cmd_list->args[0], 7))
		return (ft_export(data));
	if (!ft_strncmp(data->reserved_words[4], data->cmd_list->args[0], 6))
		return (ft_unset(data, 1));
	if (!ft_strncmp(data->reserved_words[5], data->cmd_list->args[0], 4))
		return (ft_env(data));
	if (!ft_strncmp(data->reserved_words[6], data->cmd_list->args[0], 5))
		return (ft_exit(data));
	return (0);
}

int	check_builtin(t_info *data)
{
	int		i;

	i = -1;
	while (++i < 7)
	{
		if (!ft_strcmp(data->reserved_words[i], data->cmd_list->args[0]))
			return (OK);
	}
	return (ERROR);
}

int	just_do_it(t_info *data)
{
	int		tmpin;
	int		tmpout;
	int		fdin;
	t_cmd	*tmp;

	tmpin = dup(0);
	tmpout = dup(1);
	fdin = dup(tmpin);
	tmp = data->cmd_list;
	while (data->cmd_list)
	{
		do_pipe_or_not(data, fdin, tmpout);
		if (ft_redirects(data, tmpin, tmpout) == ERROR)
			return (ERROR);
		ft_fork(tmpin, tmpout, fdin, data);
		data->cmd_list = data->cmd_list->next;
	}
	data->cmd_list = tmp;
	dup2 (tmpin, 0);
	dup2 (tmpout, 1);
	close(tmpin);
	close(tmpout);
	ft_waitpid(data);
	return (OK);
}

int	executor(t_info *data)
{
	int		i;

	ft_reenv_arr(data);
	i = -1;
	if (data->cmd_list->args != NULL)
	{
		while (++i < 7 && !data->cmd_list->next)
		{
			if (!ft_strcmp(data->reserved_words[i], data->cmd_list->args[0]))
			{
				this_is_buitlin(data);
				break ;
			}
		}
	}
	if ((!data->cmd_list->next && i == 7) || data->cmd_list->next
		|| data->cmd_list->redir)
		just_do_it(data);
	return (OK);
}

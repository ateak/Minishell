/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:25:59 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/08 17:08:46 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_exit(t_info *data)
{
	ft_putstr_fd("exit\n", 1);
	data->exit_status = 0;
	exit(0);
}

void	error_exit(int er_num, char *str)
{
	char	*error_msg;

	if (str != NULL)
	{
		error_msg = strerror(er_num);
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "\n", 1);
	}
	exit(er_num);
}

void	fail_execve(t_info *data, char *path)
{
	if (!path)
	{
		data->exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd_list->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		error_exit(data->exit_status, NULL);
	}
	if (access(path, F_OK))
	{
		data->exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd_list->args[0], 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		error_exit(data->exit_status, NULL);
	}
	if (path && access(path, X_OK))
	{
		data->exit_status = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd_list->args[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		error_exit(data->exit_status, NULL);
	}
}

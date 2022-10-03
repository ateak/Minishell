/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:28:24 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/06 20:09:56 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_error(t_info *data, char *str, int flag)
{
	data->exit_status = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str, 2);
	if (flag == 1)
		ft_putstr_fd(" : No such file or directory\n", 2);
	if (flag == 2)
		ft_putstr_fd(" : Not a directory\n", 2);
}

void	env_after_cd(t_info **data)
{
	t_envp	*tmp;
	t_envp	*tmp1;

	tmp = (*data)->envp_list;
	tmp1 = (*data)->envp_list;
	while (tmp && ft_strcmp(tmp->name, "PWD"))
		tmp = tmp->next;
	while (tmp1 && ft_strcmp(tmp1->name, "OLDPWD"))
		tmp1 = tmp1->next;
	if (tmp && tmp1)
	{
		free(tmp1->value);
		tmp1->value = ft_strdup(tmp->value);
		free(tmp->value);
		tmp->value = getcwd(NULL, 0);
		if (!tmp->value)
			error_exit(errno, "getcwd");
	}
	ft_reenv_arr(*data);
}

int	cd_without_args(t_info	*data, char **path)
{
	t_envp	*tmp;

	tmp = data->envp_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "HOME"))
		{
			*path = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		write (2, "Error: HOME does not exist\n", 28);
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

char	*get_path(t_info *data)
{
	char	*path;
	char	*pwd;

	path = NULL;
	path = getcwd(path, 0);
	if (!path)
		error_exit(errno, "getcwd");
	pwd = ft_strjoin(path, "/");
	free(path);
	path = ft_strjoin(pwd, data->cmd_list->args[1]);
	free(pwd);
	return (path);
}

int	ft_cd(t_info *data)
{
	char	*path;

	if (!data->cmd_list->args[1])
	{
		if (cd_without_args(data, &path))
			return (1);
	}
	else
	{
		if (data->cmd_list->args[1][0] == '/')
			path = ft_strdup(data->cmd_list->args[1]);
		else
			path = get_path(data);
	}
	if (!access(path, F_OK))
	{
		if (chdir(path) != 0)
			cd_error(data, data->cmd_list->args[1], 2);
		else
			env_after_cd(&data);
	}
	else
		cd_error(data, data->cmd_list->args[1], 1);
	free(path);
	return (0);
}

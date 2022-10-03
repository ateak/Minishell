/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_do_it.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:48:42 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/09 12:45:03 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_full_path(char **cmd_path, char	**arr_cmd)
{
	char	*full_cmd_path;
	int		true_path;
	int		i;
	char	*tmp;

	i = 0;
	true_path = -1;
	while (cmd_path[i] && (true_path == -1))
	{
		full_cmd_path = (ft_strjoin(cmd_path[i], "/"));
		tmp = full_cmd_path;
		full_cmd_path = ft_strjoin(tmp, arr_cmd[0]);
		free(tmp);
		tmp = NULL;
		true_path = access(full_cmd_path, F_OK);
		i++;
	}
	if (true_path == -1)
		return (NULL);
	return (full_cmd_path);
}

char	*ft_find_path(char **arr_cmd, t_info *data)
{
	int		i;
	char	**cmds_path;
	char	*full_cmd_path;

	i = 0;
	if (ft_strchr(data->cmd_list->args[0], '/'))
		return (data->cmd_list->args[0]);
	while (data->envp[i] && ft_strncmp(data->envp[i], "PATH", 4))
		i++;
	if (!data->envp[i])
		error_exit(2, "PATH does not exist");
	cmds_path = ft_split(data->envp[i] + 5, ':');
	if (!cmds_path)
		error_exit(12, "malloc");
	full_cmd_path = ft_full_path(cmds_path, arr_cmd);
	return (full_cmd_path);
}

void	ft_fork(int tmpin, int tmpout, int fdin, t_info *data)
{
	char	*full_path_cmd;
	pid_t	pid;

	signal(SIGINT, handler_fork);
	signal(SIGQUIT, handler_fork);
	pid = fork();
	if (pid == -1)
		error_exit(errno, "fork");
	if (pid == 0)
	{
		close(tmpin);
		close(tmpout);
		close(fdin);
		if (check_builtin(data) == OK)
		{
			data->num_cmd = 1;
			exit (this_is_buitlin(data));
		}
		full_path_cmd = ft_find_path(data->cmd_list->args, data);
		if (execve(full_path_cmd, data->cmd_list->args, data->envp) == -1)
			fail_execve(data, full_path_cmd);
	}
}

void	do_pipe_or_not(t_info *data, int fdin, int tmpout)
{
	int		fdpipe[2];
	int		fdout;

	dup2 (fdin, 0);
	close (fdin);
	if (!data->cmd_list->next)
		fdout = dup (tmpout);
	else
	{
		if (pipe(fdpipe) == -1)
			error_exit(errno, "pipe");
		fdout = fdpipe[1];
		fdin = fdpipe[0];
	}
	dup2(fdout, 1);
	close(fdout);
}

void	ft_waitpid(t_info *data)
{
	t_cmd	*tmp;
	int		status;

	tmp = data->cmd_list;
	while (tmp)
	{
		waitpid (-1, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else
			data->exit_status = status + 128;
		tmp = tmp->next;
	}
}

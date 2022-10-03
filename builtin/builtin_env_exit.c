/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:02:43 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/08 16:02:24 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_info *data)
{
	t_envp	*tmp;

	if (data->cmd_list->args[1])
	{
		printf("%s: %s: No such file or directory\n",
			data->cmd_list->args[0], data->cmd_list->args[1]);
		data->exit_status = 1;
		return (1);
	}
	tmp = data->envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->sep, "=") == 0)
			printf("%s%s%s\n", tmp->name, tmp->sep, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_chek_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_er_in_exit(int num_er, char **arr_str, t_info *data)
{
	char	*shell;

	if (num_er == 1)
	{
		shell = ft_substr(data->shell_name, 0, 10);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("exit:", 2);
		ft_putstr_fd("too many arguments\n", 2);
		free(shell);
	}
	else if (num_er == 2)
	{
		shell = ft_substr(data->shell_name, 0, 10);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("exit :", 2);
		ft_putstr_fd(arr_str[1], 2);
		ft_putstr_fd(":", 2);
		ft_putstr_fd("numeric argument required\n", 2);
		free(shell);
	}
}

int	ft_exit(t_info *data)
{
	int		status;

	if (data->num_cmd == 1)
		printf("exit\n");
	if (data->cmd_list->args[1] && data->cmd_list->args[2])
	{
		ft_print_er_in_exit(1, data->cmd_list->args, data);
		return (1);
	}
	else if (data->cmd_list->args[1])
	{
		if (!ft_chek_digit(data->cmd_list->args[1]))
			status = ft_atoi(data->cmd_list->args[1]);
		else
		{
			status = 255;
			ft_print_er_in_exit(2, data->cmd_list->args, data);
		}
		error_exit(status, NULL);
	}
	else
		error_exit(0, NULL);
	return (0);
}

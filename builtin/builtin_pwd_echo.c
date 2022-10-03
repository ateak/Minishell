/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:41:14 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/08 16:02:52 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_echo(char **arr_str, int i)
{
	while (arr_str[++i])
	{
		if (arr_str[i + 1])
			printf("%s ", arr_str[i]);
		else
			printf("%s", arr_str[i]);
	}
}

int	ft_echo(t_info *data)
{
	int	flag;
	int	i;

	if (data->cmd_list->args[1])
		flag = ft_strcmp(data->cmd_list->args[1], "-n");
	if (data->cmd_list->args[1] && !flag)
	{
		i = 1;
		ft_print_echo(data->cmd_list->args, i);
	}
	else if (data->cmd_list->args[1] && flag)
	{
		i = 0;
		ft_print_echo(data->cmd_list->args, i);
		printf("\n");
	}
	else
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_pwd(t_info *data)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
		error_exit(errno, "getcwd");
	printf("%s\n", pwd);
	free(pwd);
	data->exit_status = 0;
	return (0);
}

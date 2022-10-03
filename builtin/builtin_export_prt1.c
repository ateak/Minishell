/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_prt1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:57:28 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/06 20:04:26 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_just_print(t_envp *tmp)
{
	while (tmp)
	{
		if (tmp->sep && tmp->value)
		{
			printf("declare -x %s%s\"%s\"\n", tmp->name, \
				tmp->sep, tmp->value);
		}
		else
			printf("declare -x %s%s\n", tmp->name, \
				tmp->sep);
		tmp = tmp->next;
	}
	return (0);
}

static void	print_unvalid_id(t_info *data, int i)
{
	data->exit_status = 1;
	if (!ft_strcmp(data->cmd_list->args[i], "?"))
	{
		printf ("%s: %s: '%s': not a valid identifier\n",
			ft_substr(data->shell_name, 0, 10), data->cmd_list->args[0], "1");
	}
	else
	{
		printf ("%s: %s: '%s': not a valid identifier\n",
			ft_substr(data->shell_name, 0, 10), data->cmd_list->args[0],
			data->cmd_list->args[i]);
	}
}

static void	check_id(t_info *data, int i)
{
	t_envp	*new;
	int		j;
	int		flag;

	new = NULL;
	j = 0;
	flag = 0;
	while (data->cmd_list->args[i][j] != '='
		&& data->cmd_list->args[i][j] != '\0')
	{
		if (!(ft_isalnum(data->cmd_list->args[i][j]))
			&& data->cmd_list->args[i][j] != '_')
		{
			flag = 1;
			break ;
		}
		j++;
	}
	if (flag == 0)
	{
		new = ft_put_env_into_list(data->cmd_list->args[i]);
		ft_check_dup_export(&(data->envp_list), new);
	}
	else
		print_unvalid_id(data, i);
}

int	ft_export(t_info *data)
{
	int		i;

	data->exit_status = 0;
	if (!data->cmd_list->args[1])
		return (ft_just_print(data->envp_list));
	i = 1;
	while (data->cmd_list->args[i])
	{
		if (ft_isalpha(data->cmd_list->args[i][0])
			|| data->cmd_list->args[i][0] == '_')
			check_id(data, i);
		else
			print_unvalid_id(data, i);
		i++;
	}
	ft_reenv_arr(data);
	return (data->exit_status);
}

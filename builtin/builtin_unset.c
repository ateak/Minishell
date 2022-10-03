/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:17:19 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/06 20:04:16 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_args(char *str)
{
	while (*str)
		if (!ft_isalnum(*str++))
			return (1);
	return (0);
}

int	ft_check_first(t_envp **envp, char *str)
{
	t_envp	*tmp;

	tmp = *envp;
	if (ft_strcmp(str, tmp->name) == 0)
	{
		*envp = (*envp)->next;
		free_node_envp(tmp);
		return (1);
	}
	return (0);
}

void	ft_check_other_nodes(t_envp *tmp, char *str)
{
	t_envp	*del_node;

	while (tmp->next)
	{
		if (!ft_strcmp(str, tmp->next->name))
		{
			del_node = tmp->next;
			tmp->next = tmp->next->next;
			free_node_envp(del_node);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_print_er_unset(t_info *data, int i)
{
	ft_putstr_fd(data->shell_name, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(data->cmd_list->args[0], 2);
	ft_putstr_fd(":`", 2);
	ft_putstr_fd(data->cmd_list->args[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_unset(t_info *data, int i)
{
	t_envp	*tmp;

	if (!data->cmd_list->args[1])
		return (1);
	i = 1;
	while (data->cmd_list->args[i])
	{
		tmp = data->envp_list;
		if (!ft_check_args(data->cmd_list->args[i]))
		{
			if (!ft_check_first(&data->envp_list, data->cmd_list->args[i]))
				ft_check_other_nodes(data->envp_list, data->cmd_list->args[i]);
		}
		else
			ft_print_er_unset(data, i);
		i++;
	}
	ft_reenv_arr(data);
	return (0);
}

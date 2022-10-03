/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_prt2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:57:28 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/06 14:15:29 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_envp	*check_lines_env(t_envp *tmp, t_envp *new)
{
	t_envp	*tmp2;

	while (tmp->next)
	{
		if (!ft_strcmp(tmp->next->name, new->name))
		{
			if (new->sep[0] != 0)
			{
				tmp2 = tmp->next;
				tmp->next = new;
				tmp->next->next = tmp2->next;
				free_node_envp(tmp2);
			}
			break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_check_dup_export(t_envp **env, t_envp *new)
{
	t_envp	*tmp;

	tmp = *env;
	if (!ft_strcmp(tmp->name, new->name))
	{
		if (new->sep[0] != 0)
		{
			new->next = tmp->next;
			*env = new;
			free_node_envp(tmp);
		}
		return ;
	}
	tmp = check_lines_env(tmp, new);
	if (!tmp->next)
		ft_envp_list_add_back(&tmp, new);
}

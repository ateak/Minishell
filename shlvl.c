/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:18:47 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/08 16:31:14 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_add_shlvl(t_envp *tmp)
{
	int	lvl;

	if (!tmp->value[0])
	{
		free(tmp->sep);
		tmp->sep = ft_strdup("=");
		free(tmp->value);
		tmp->value = ft_strdup("1");
	}
	else
	{
		lvl = ft_atoi(tmp->value) + 1;
		free(tmp->value);
		tmp->value = ft_itoa(lvl);
	}
}

void	ft_check_shell_lvl(t_info *data)
{
	t_envp	*tmp;
	t_envp	*new;

	tmp = data->envp_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "SHLVL"))
		{
			ft_add_shlvl(tmp);
			ft_reenv_arr(data);
			return ;
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_envp));
	if (new == NULL)
		error_exit(errno, "malloc");
	new->name = "SHLVL";
	new->sep = "=";
	new->value = "1";
	ft_envp_list_add_back(&data->envp_list, new);
	ft_reenv_arr(data);
}

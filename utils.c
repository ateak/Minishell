/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:19:12 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/08 16:14:30 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array_dup(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_node_envp(t_envp *tmp)
{
	free(tmp->name);
	free(tmp->sep);
	free(tmp->value);
	free(tmp);
}

char	**ft_recreate_arr_env(char **envp, t_envp *tmp, int *i)
{
	char	*str;
	char	*str1;

	str = ft_strjoin(tmp->name, tmp->sep);
	if (tmp->value)
	{
		str1 = ft_strjoin(str, tmp->value);
		envp[*i] = ft_strdup(str1);
		free(str);
		free(str1);
	}
	else
	{
		envp[*i] = ft_strdup(str);
		free(str);
	}
	return (envp);
}

void	ft_reenv_arr(t_info *data)
{
	int		i;
	t_envp	*tmp;

	free_array_dup(data->envp);
	data->envp = 0;
	tmp = data->envp_list;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	data->envp = (char **)malloc(sizeof(char *) * (i + 1));
	tmp = data->envp_list;
	i = 0;
	while (tmp)
	{
		if (tmp->sep[0])
		{
			data->envp = ft_recreate_arr_env(data->envp, tmp, &i);
			i++;
		}
		tmp = tmp->next;
	}
	data->envp[i] = NULL;
}

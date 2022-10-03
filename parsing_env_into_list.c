/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_into_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:44:14 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/08 16:27:42 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_current_path(t_info *data)
{
	t_envp	*tmp;
	char	*pwd;
	char	*tmp_path;
	char	*new_path;

	tmp = data->envp_list;
	while (ft_strcmp("PWD", tmp->name))
		tmp = tmp->next;
	pwd = tmp->value;
	tmp = data->envp_list;
	while (ft_strcmp("PATH", tmp->name))
		tmp = tmp->next;
	tmp_path = ft_strjoin(tmp->value, ":");
	new_path = ft_strjoin(tmp_path, pwd);
	free(tmp_path);
	free(tmp->value);
	tmp->value = ft_strdup(new_path);
	free(new_path);
}

static t_envp	*ft_envp_list_find_last(t_envp *list)
{
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_envp_list_add_back(t_envp **envp_list, t_envp *new)
{
	t_envp	*tmp;

	if (*envp_list != NULL)
	{
		tmp = ft_envp_list_find_last(*envp_list);
		tmp->next = new;
	}
	else
		*envp_list = new;
}

t_envp	*ft_put_env_into_list(char *env)
{
	t_envp	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_envp));
	if (!new)
		error_exit(errno, "malloc");
	while (env[i] && env[i] != '=')
		i++;
	new->name = ft_substr(env, 0, i);
	if (!new->name)
		error_exit(errno, "malloc");
	new->sep = ft_substr(env, i, 1);
	if (!new->sep)
		error_exit(errno, "malloc");
	if (env[i])
	{
		new->value = ft_substr(env, i + 1, ft_strlen(env) - i);
		if (!new->value)
			error_exit(errno, "malloc");
	}
	else
		new->value = 0;
	new->next = NULL;
	return (new);
}

void	ft_parse_env(char **env, t_envp **envp_list, t_info *data)
{
	int		i;
	t_envp	*tmp;

	i = 0;
	while (env[i] != NULL)
	{
		tmp = ft_put_env_into_list(env[i]);
		ft_envp_list_add_back(envp_list, tmp);
		i++;
		data->envp_y++;
	}
	add_current_path(data);
	ft_create_envp_arr(data, env);
}

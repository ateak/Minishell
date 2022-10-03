/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:07:18 by ateak             #+#    #+#             */
/*   Updated: 2022/09/08 17:09:18 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data(t_info *data)
{
	t_envp	*tmp;

	while (data->envp_list)
	{
		tmp = data->envp_list;
		if (data->envp_list->name)
			free(data->envp_list->name);
		if (data->envp_list->sep)
			free(data->envp_list->sep);
		if (data->envp_list->value)
			free(data->envp_list->value);
		data->envp_list = data->envp_list->next;
		if (tmp)
			free(tmp);
	}
}

void	free_token_list(t_info *data)
{
	t_token	*tmp;

	while (data->token_list != NULL)
	{
		tmp = data->token_list;
		if (data->token_list->value)
		{
			free (data->token_list->value);
			data->token_list->value = NULL;
		}
		data->token_list = data->token_list->next;
		free(tmp);
	}
}

void	free_redir_list(t_redir *redir_list)
{
	t_redir	*tmp;

	while (redir_list)
	{
		tmp = redir_list;
		if (redir_list->file)
			free (redir_list->file);
		redir_list = redir_list->next;
		if (tmp)
			free(tmp);
	}
}

void	free_cmd_list(t_info *data)
{
	t_cmd	*tmp;

	while (data->cmd_list)
	{
		tmp = data->cmd_list;
		if (data->cmd_list->args)
			free_array_dup(data->cmd_list->args);
		if (data->cmd_list->redir)
			free_redir_list(data->cmd_list->redir);
		data->cmd_list = data->cmd_list->next;
		if (tmp)
			free(tmp);
	}
}

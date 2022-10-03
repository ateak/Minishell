/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_create_cmd_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:04:53 by ateak             #+#    #+#             */
/*   Updated: 2022/09/08 16:10:05 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	put_tokens_to_cmd_args(t_info *data, t_cmd **cmd, t_token **tmp,
		int i)
{
	if (ft_strchr((*tmp)->value, '$'))
		dollar_handler(&(*tmp), &data->dol_info, data);
	(*cmd)->args[i] = ft_strdup((*tmp)->value);
	i++;
	data->args_amount--;
	*tmp = (*tmp)->next;
	if (*tmp)
	{
		while ((*tmp)->type == SEP && (*tmp)->next)
			(*tmp) = (*tmp)->next;
	}
	return (i);
}

static	char	*join_tokens(t_info *data, t_token **tmp)
{
	char	*str;
	char	*new_value;

	str = NULL;
	new_value = NULL;
	while ((*tmp)->join_flag == 1 && (*tmp)->next)
	{
		if (ft_strchr((*tmp)->next->value, '$'))
			dollar_handler(&(*tmp)->next, &data->dol_info, data);
		if (!new_value)
			new_value = ft_strjoin((*tmp)->value, (*tmp)->next->value);
		else
		{
			str = ft_strjoin(new_value, (*tmp)->next->value);
			free_func(&new_value);
			new_value = ft_strdup(str);
			free_func(&str);
		}
		(*tmp)->join_flag = 0;
		(*tmp) = (*tmp)->next;
	}
	return (new_value);
}

static int	put_joined_tokens_to_cmd_args(t_info *data, t_cmd **cmd,
		t_token **tmp, int i)
{
	char	*new_value;

	new_value = NULL;
	new_value = join_tokens(data, &(*tmp));
	(*cmd)->args[i] = ft_strdup(new_value);
	if (new_value)
		free_func(&new_value);
	i++;
	data->args_amount--;
	(*tmp) = (*tmp)->next;
	return (i);
}

static void	redir(t_cmd **cmd, t_token **tmp)
{
	t_token	*tmp2;

	tmp2 = NULL;
	while ((*tmp)->type == SEP && (*tmp)->next)
		*tmp = (*tmp)->next;
	while ((*tmp)->type >= REDIR_OUT && (*tmp)->type <= REDIR_HEREDOC && *tmp)
	{
		tmp2 = *tmp;
		tmp2 = redir_handler(cmd, &tmp2);
		while (((*tmp)->type < WORD || (*tmp)->type > EXP_FIELD) && *tmp)
		{
			*tmp = (*tmp)->next;
			if ((*tmp)->type == PIPE)
				break ;
		}
		*tmp = (*tmp)->next;
		while ((*tmp)->type == SEP && (*tmp)->next)
			*tmp = (*tmp)->next;
	}
}

t_token	*create_cmd_args(t_info *data, t_cmd *cmd, t_token *tmp)
{
	int		i;

	i = 0;
	while (data->args_amount != 0)
	{
		if (ft_strchr(tmp->value, '$'))
			dollar_handler(&tmp, &data->dol_info, data);
		if (tmp)
			redir(&cmd, &tmp);
		if (tmp->join_flag == 1 && tmp->next)
			i = put_joined_tokens_to_cmd_args(data, &cmd, &tmp, i);
		else
			i = put_tokens_to_cmd_args(data, &cmd, &tmp, i);
	}
	cmd->args[i] = NULL;
	return (tmp);
}

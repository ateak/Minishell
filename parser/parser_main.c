/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:27:43 by ateak             #+#    #+#             */
/*   Updated: 2022/09/08 15:30:25 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*tokens_handler(t_info *data, t_cmd *cmd, t_token *tmp,
		t_token	*tmp2)
{
	if (!tmp->next)
		data->args_amount++;
	else
	{
		tmp2 = tmp;
		find_joining_tokens(data, tmp2);
	}
	cmd->args = (char **)malloc(sizeof(char *) * (data->args_amount + 1));
	if (!(cmd->args))
		error_exit(MALLOC_ERR, "malloc");
	tmp = create_cmd_args(data, cmd, tmp);
	return (tmp);
}

static void	parser(t_info *data, t_cmd **cmd, t_token **tmp, t_token **tmp2)
{
	while ((*tmp)->type != PIPE && *tmp)
	{
		if (*tmp)
		{
			if ((*tmp)->type == SEP)
			{
				if ((*tmp)->next == NULL)
					break ;
				(*tmp) = (*tmp)->next;
			}
			else if ((*tmp)->type == REDIR_IN || (*tmp)->type == REDIR_OUT
				|| (*tmp)->type == REDIR_APPEND
				|| (*tmp)->type == REDIR_HEREDOC)
				*tmp = redir_handler(cmd, tmp);
			else if ((*tmp)->type == WORD || (*tmp)->type == FIELD
				|| (*tmp)->type == EXP_FIELD)
				*tmp = tokens_handler(data, *cmd, *tmp, *tmp2);
			if (!(*tmp))
				break ;
		}
		else
			break ;
	}
}

t_token	*parser_main(t_info *data, t_cmd **cmd, t_token **tmp, t_token **tmp2)
{
	while (*tmp != NULL)
	{
		parser(data, cmd, tmp, tmp2);
		break ;
	}
	return (*tmp);
}

static void	init_cmd_list(t_info *data)
{
	data->cmd_list = (t_cmd *) malloc(sizeof(t_cmd));
	if (!(data->cmd_list))
		error_exit(MALLOC_ERR, "malloc");
	data->cmd_list->args = NULL;
	data->cmd_list->redir = NULL;
	data->cmd_list->next = NULL;
	data->args_amount = 0;
	data->num_cmd = 0;
}

void	put_tokens_to_cmd(t_info *data)
{
	t_cmd		*cmd;
	t_token		*tmp;
	t_token		*tmp2;

	init_cmd_list(data);
	cmd = data->cmd_list;
	tmp = data->token_list;
	tmp2 = NULL;
	while (cmd != NULL)
	{
		data->num_cmd++;
		tmp = parser_main(data, &cmd, &tmp, &tmp2);
		if (tmp)
		{
			if (tmp->type == SEP && !tmp->next)
				break ;
			if (tmp->type == PIPE)
				tmp = tmp->next;
			cmd_push_back(&data->cmd_list);
		}
		cmd = cmd->next;
	}
}

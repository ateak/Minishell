/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:27:25 by ateak             #+#    #+#             */
/*   Updated: 2022/09/06 15:13:34 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	word_tokens(t_info *data, t_token **tmp2)
{
	(*tmp2)->join_flag = 1;
	data->args_amount--;
	*tmp2 = (*tmp2)->next;
}

static void	sep_tokens(t_token **tmp2)
{
	*tmp2 = (*tmp2)->next;
	while ((*tmp2)->type == SEP && (*tmp2)->next)
		*tmp2 = (*tmp2)->next;
}

static	void	tokens(t_info *data, t_token **tmp2)
{
	if ((*tmp2)->next->type == SEP)
		sep_tokens(tmp2);
	else if ((*tmp2)->next->type >= WORD && (*tmp2)->next->type <= EXP_FIELD)
		word_tokens(data, tmp2);
}

static	void	redir_tokens(t_token **tmp2)
{
	while ((*tmp2)->type >= REDIR_OUT
		&& (*tmp2)->type <= REDIR_HEREDOC && (*tmp2))
	{
		while (((*tmp2)->type < WORD || (*tmp2)->type > EXP_FIELD) && (*tmp2))
		{
			*tmp2 = (*tmp2)->next;
			if ((*tmp2)->type == PIPE)
				break ;
		}
		*tmp2 = (*tmp2)->next;
		if (*tmp2)
		{
			while ((*tmp2)->type == SEP && (*tmp2)->next)
				*tmp2 = (*tmp2)->next;
			if ((*tmp2)->type == SEP && !((*tmp2)->next))
				break ;
		}
		else
			break ;
	}
}

void	find_joining_tokens(t_info *data, t_token	*tmp2)
{
	while (tmp2->type != PIPE && tmp2)
	{
		if (tmp2->type == SEP && !tmp2->next)
			break ;
		redir_tokens(&tmp2);
		if (tmp2 && tmp2->type != PIPE)
		{
			if (tmp2->type == SEP && !tmp2->next)
				break ;
			data->args_amount++;
			if (tmp2->next)
			{
				if (tmp2->next->type >= SEP && tmp2->next->type <= EXP_FIELD)
					tokens(data, &tmp2);
				else
					break ;
			}
			else
				break ;
		}
		else
			break ;
	}
}

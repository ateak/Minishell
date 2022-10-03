/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:11:23 by ateak             #+#    #+#             */
/*   Updated: 2022/09/08 14:43:40 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redir_push_back(t_redir **redir, t_token **token)
{
	t_redir	*new_element;
	t_redir	*tmp;

	new_element = (t_redir *) malloc(sizeof(t_redir));
	if (!new_element)
		error_exit(MALLOC_ERR, "malloc");
	new_element->type = (*token)->type;
	(*token) = (*token)->next;
	if (*token)
	{
		while ((*token)->type == SEP && (*token)->next)
			(*token) = (*token)->next;
	}
	new_element->file = ft_strdup((*token)->value);
	if (!new_element->file)
		error_exit(MALLOC_ERR, "malloc");
	new_element->next = NULL;
	tmp = *redir;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_element;
}

static void	init_redir_list(t_redir **redir, t_token **tmp)
{
	*redir = (t_redir *) malloc(sizeof(t_redir));
	if (!(*redir))
		error_exit(MALLOC_ERR, "malloc");
	(*redir)->type = (*tmp)->type;
	(*tmp) = (*tmp)->next;
	if (*tmp)
	{
		while ((*tmp)->type == SEP && (*tmp)->next)
			(*tmp) = (*tmp)->next;
	}
	(*redir)->file = ft_strdup((*tmp)->value);
	if (!((*redir)->file))
		error_exit(MALLOC_ERR, "malloc");
	(*redir)->next = NULL;
}

t_token	*redir_handler(t_cmd **cmd, t_token **tmp)
{	
	if (!(*cmd)->redir)
		init_redir_list(&(*cmd)->redir, &(*tmp));
	else
		redir_push_back(&(*cmd)->redir, &(*tmp));
	*tmp = (*tmp)->next;
	return (*tmp);
}

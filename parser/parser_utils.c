/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:45:56 by ateak             #+#    #+#             */
/*   Updated: 2022/09/08 16:10:36 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*cmd_get_last(t_cmd *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	cmd_push_back(t_cmd **head)
{
	t_cmd	*last;
	t_cmd	*tmp;

	last = cmd_get_last(*head);
	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!tmp)
		error_exit(MALLOC_ERR, "malloc");
	tmp->args = NULL;
	tmp->redir = NULL;
	tmp->next = NULL;
	last->next = tmp;
}

void	free_func(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	ft_isdelim(char *s)
{
	if (!ft_strncmp(s, "|", 1) || !ft_strncmp(s, "<", 1) || \
		!ft_strncmp(s, ">", 1))
		return (1);
	else
		return (0);
}

int	ms_isspace(int c)
{
	return (c == '\f' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:20:46 by ateak             #+#    #+#             */
/*   Updated: 2022/08/30 15:21:47 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*ft_token_list_find_last(t_token *list)
{
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_token_list_add_back(t_token **token_list, t_token *new)
{
	t_token	*tmp;

	if (*token_list != NULL)
	{
		tmp = ft_token_list_find_last(*token_list);
		tmp->next = new;
	}
	else
		*token_list = new;
}

t_token	*ft_create_token_list(char *str, int start, t_info *data)
{
	t_token	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_token));
	if (!new)
		error_exit(MALLOC_ERR, "malloc");
	new->len = data->token_len;
	new->value = ft_substr(str, start, data->token_len);
	new->next = NULL;
	return (new);
}

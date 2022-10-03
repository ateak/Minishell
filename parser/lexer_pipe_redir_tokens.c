/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pipe_redir_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:10:21 by ateak             #+#    #+#             */
/*   Updated: 2022/08/30 15:27:30 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	token_of_redir_in_type(char *str, int i, t_info *data)
{
	int		start;
	t_token	*token_head;

	start = i;
	data->token_len = 0;
	while (str[i] == '<' && str[i] != '\0')
	{
		data->token_len++;
		i++;
	}
	token_head = ft_create_token_list(str, start, data);
	if (data->token_len == 2)
		token_head->type = REDIR_HEREDOC;
	else
		token_head->type = REDIR_IN;
	ft_token_list_add_back(&data->token_list, token_head);
	return (i);
}

static int	token_of_redir_out_type(char *str, int i, t_info *data)
{
	int		start;
	t_token	*token_head;

	start = i;
	data->token_len = 0;
	while (str[i] == '>' && str[i] != '\0')
	{
		data->token_len++;
		i++;
	}
	token_head = ft_create_token_list(str, start, data);
	if (data->token_len == 2)
		token_head->type = REDIR_APPEND;
	else
		token_head->type = REDIR_OUT;
	ft_token_list_add_back(&data->token_list, token_head);
	return (i);
}

static int	token_of_pipe_type(char *str, int i, t_info *data)
{
	int		start;
	t_token	*token_head;

	start = i;
	data->token_len = 0;
	while (str[i] == '|' && str[i] != '\0')
	{
		data->token_len++;
		i++;
	}
	token_head = ft_create_token_list(str, start, data);
	token_head->type = PIPE;
	ft_token_list_add_back(&data->token_list, token_head);
	return (i);
}

int	token_of_pipe_redir_type(char *str, int i, t_info *data)
{
	while (ft_isdelim(&str[i]) && str[i] != '\0')
	{
		if (str[i] == '|')
			i = token_of_pipe_type(str, i, data);
		else if (str[i] == '>')
			i = token_of_redir_out_type(str, i, data);
		else if (str[i] == '<')
			i = token_of_redir_in_type(str, i, data);
	}
	return (i);
}

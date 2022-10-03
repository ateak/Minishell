/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:12:12 by ateak             #+#    #+#             */
/*   Updated: 2022/08/30 15:23:42 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_of_sep_type(char *str, int i, t_info *data)
{
	int		start;
	t_token	*token_head;

	start = i;
	data->token_len = 0;
	while (ft_isspace(str[i]) && str[i] != '\0')
	{
		data->token_len++;
		i++;
	}
	token_head = ft_create_token_list(str, start, data);
	token_head->type = SEP;
	token_head->join_flag = 0;
	ft_token_list_add_back(&data->token_list, token_head);
	return (i);
}

int	token_of_word_type(char *str, int i, t_info *data)
{
	int		start;
	t_token	*token_head;

	start = i;
	data->token_len = 0;
	while (!ft_isspace(str[i]) && !ft_isdelim(&str[i])
		&& str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
	{
		data->token_len++;
		i++;
	}
	token_head = ft_create_token_list(str, start, data);
	token_head->type = WORD;
	token_head->join_flag = 0;
	ft_token_list_add_back(&data->token_list, token_head);
	return (i);
}

int	token_in_double_quotes(char *str, int i, t_info *data)
{
	int		start;
	t_token	*token_head;

	i++;
	start = i;
	data->token_len = 0;
	while (str[i] != '\"' && str[i] != '\0')
	{
		data->token_len++;
		i++;
	}
	i++;
	token_head = ft_create_token_list(str, start, data);
	token_head->type = EXP_FIELD;
	token_head->join_flag = 0;
	ft_token_list_add_back(&data->token_list, token_head);
	return (i);
}

int	token_in_single_quotes(char *str, int i, t_info *data)
{
	int		start;
	t_token	*token_head;

	i++;
	start = i;
	data->token_len = 0;
	while (str[i] != '\'' && str[i] != '\0')
	{
		data->token_len++;
		i++;
	}
	i++;
	token_head = ft_create_token_list(str, start, data);
	token_head->type = FIELD;
	token_head->join_flag = 0;
	ft_token_list_add_back(&data->token_list, token_head);
	return (i);
}

void	divide_into_tokens(char *str, t_info *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]) && !ft_isdelim(&str[i]))
		{
			if (str[i] == '\'')
				i = token_in_single_quotes(str, i, data);
			else if (str[i] == '\"')
				i = token_in_double_quotes(str, i, data);
			else
				i = token_of_word_type(str, i, data);
		}
		else
		{
			if (ft_isspace(str[i]))
				i = token_of_sep_type(str, i, data);
			else if (ft_isdelim(&str[i]))
				i = token_of_pipe_redir_type(str, i, data);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:03:20 by ateak             #+#    #+#             */
/*   Updated: 2022/09/07 17:12:32 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(t_info *data)
{
	data->ret_val = SYNTAX_ERR;
	data->exit_status = SYNTAX_ERR;
	printf(ERRSYNTAX);
	return (ERROR);
}

void	ft_syntax_err(t_info *data)
{
	data->ret_val = SYNTAX_ERR;
	data->exit_status = SYNTAX_ERR;
	printf(ERRSYNTAX);
}

int	preparser(t_info *data, char *line)
{
	data->ret_val = OK;
	if (check_eve_quotes(line) == ERROR)
		return (syntax_error(data));
	while (ms_isspace(*line))
		line++;
	if (*line == '|')
		return (syntax_error(data));
	while (*line)
	{
		if (*line == '\"' || *line == '\'')
			line = check_quotes(line);
		else if (*line == '>' || *line == '<' || *line == '|')
			line = check_redirect_and_pipe(data, line);
		if (data->ret_val != OK)
			return (ERROR);
		if (!(*line))
			break ;
		else if (*line != '\"' && *line != '\'')
			line++;
	}
	return (OK);
}

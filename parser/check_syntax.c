/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:51:49 by ateak             #+#    #+#             */
/*   Updated: 2022/08/31 18:36:42 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_pipe(t_info *data, char *line)
{
	if (*line == *(line + 1))
	{
		ft_syntax_err(data);
		return (line);
	}
	line++;
	while (1)
	{
		if (*line == '\n' || *line == '|' || (!*line))
		{
			ft_syntax_err(data);
			return (line);
		}
		if (!ms_isspace(*line))
			return (line);
		line++;
	}
	return (line);
}

static char	*check_redirect(t_info *data, char *line)
{
	if (*line == *(line + 1))
		line++;
	line++;
	while (1)
	{
		if (*line == '\n' || *line == '|' || *line == '<'
			|| *line == '>' || (!*line))
		{
			ft_syntax_err(data);
			return (line);
		}
		if (!ms_isspace(*line))
			return (line);
		if (!(*line))
			return (line);
		line++;
	}
	return (line);
}

char	*check_redirect_and_pipe(t_info *data, char *line)
{
	while (*line == '<' || *line == '>' || *line == '|')
	{
		if (data->ret_val != OK)
			return (NULL);
		if (*line == '<' || *line == '>')
			line = check_redirect(data, line);
		else if (*line == '|')
			line = check_pipe(data, line);
		else
			return (line);
	}
	return (line);
}

char	*check_quotes(char *line)
{
	char	c;

	c = *line;
	line++;
	while (*line != c)
	{
		if (!(*line))
			return (line);
		line++;
	}
	line++;
	return (line);
}

int	check_eve_quotes(char *str)
{
	int	count_one;
	int	count_double;
	int	i;

	i = 0;
	count_one = 0;
	count_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && count_double % 2 == 0)
			count_one++;
		if (str[i] == '\"' && count_one % 2 == 0)
			count_double++;
		i++;
	}
	if (count_double % 2 == 0 && count_one % 2 == 0)
		return (OK);
	else
		return (ERROR);
}

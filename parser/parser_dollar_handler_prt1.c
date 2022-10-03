/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_handler_prt1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:26:48 by ateak             #+#    #+#             */
/*   Updated: 2022/08/28 15:44:26 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	find_another_symbols(t_token **tmp,
				t_dollar **dol_info)
{
	(*dol_info)->len = 0;
	(*dol_info)->between_dollar_len = (*dol_info)->i;
	while ((*tmp)->value[(*dol_info)->i] != '$'
		&& (*tmp)->value[(*dol_info)->i])
	{
		(*dol_info)->i++;
		(*dol_info)->len++;
	}
	(*dol_info)->dollar = (*dol_info)->i;
	(*dol_info)->tmp1 = ft_substr((*tmp)->value,
			(*dol_info)->between_dollar_len, (*dol_info)->len);
	if (!((*dol_info)->new_value) && (*dol_info)->tmp2)
		(*dol_info)->tmp2 = ft_strjoin((*dol_info)->tmp2, (*dol_info)->tmp1);
	else if ((*dol_info)->new_value && !((*dol_info)->tmp2))
		(*dol_info)->tmp2 = ft_strjoin((*dol_info)->new_value,
				(*dol_info)->tmp1);
	else
		(*dol_info)->tmp2 = ft_strdup((*dol_info)->tmp1);
}

void	dollar_parser(t_token **tmp, t_dollar **dol_info, t_info *data)
{
	while ((*tmp)->value[(*dol_info)->i])
	{
		find_another_symbols(tmp, dol_info);
		free_func(&(*dol_info)->tmp1);
		free_func(&(*dol_info)->new_value);
		if ((*tmp)->value[(*dol_info)->i] == '\0')
		{
			(*dol_info)->new_value = ft_strdup((*dol_info)->tmp2);
			free_func(&(*dol_info)->tmp2);
			break ;
		}
		dollar_expansion(tmp, dol_info, data);
		if (!((*dol_info)->new_value))
		{
			free_func(&(*dol_info)->tmp3);
			if ((*tmp)->value[(*dol_info)->i] == '\0')
			{
				(*dol_info)->new_value = ft_strdup((*dol_info)->tmp2);
				free_func(&(*dol_info)->tmp2);
			}
		}
	}	
}

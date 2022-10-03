/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_handler_main.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:17:48 by ateak             #+#    #+#             */
/*   Updated: 2022/09/08 15:30:48 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_dollar_struct(t_info *data)
{
	data->dol_info = (t_dollar *) malloc(sizeof(t_dollar));
	if (!data->dol_info)
		error_exit(MALLOC_ERR, "malloc");
	data->dol_info->new_value = NULL;
	data->dol_info->tmp1 = NULL;
	data->dol_info->tmp2 = NULL;
	data->dol_info->tmp3 = NULL;
	data->dol_info->between_dollar_len = 0;
	data->dol_info->dollar = 0;
	data->dol_info->i = 0;
	data->dol_info->number_flag = 0;
	data->dol_info->null_flag = 0;
}

void	dollar_handler(t_token **tmp, t_dollar **dol_info,
		t_info *data)
{
	init_dollar_struct(data);
	if ((*tmp)->type == EXP_FIELD || (*tmp)->type == WORD)
	{
		dollar_parser(tmp, &data->dol_info, data);
		free ((*tmp)->value);
		(*tmp)->value = ft_strdup((*dol_info)->new_value);
		(*tmp)->len = ft_strlen((*tmp)->value);
		free ((*dol_info)->new_value);
		(*dol_info)->new_value = NULL;
	}
	free(data->dol_info);
}

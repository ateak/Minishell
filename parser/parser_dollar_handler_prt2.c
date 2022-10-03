/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_handler_prt2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:42:58 by ateak             #+#    #+#             */
/*   Updated: 2022/08/31 18:04:31 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	dollar_replace(t_token **tmp, t_dollar **dol_info, t_info *data)
{
	t_envp	*env_tmp;

	(*dol_info)->tmp3 = ft_substr((*tmp)->value, (*dol_info)->dollar + 1,
			(*dol_info)->len);
	env_tmp = data->envp_list;
	while (env_tmp != NULL)
	{
		if (!ft_strncmp((*dol_info)->tmp3, env_tmp->name, (*dol_info)->len)
			&& (*dol_info)->len == ft_strlen(env_tmp->name))
		{
			(*dol_info)->new_value = ft_strjoin((*dol_info)->tmp2,
					env_tmp->value);
			free_func(&(*dol_info)->tmp2);
			free_func(&(*dol_info)->tmp3);
			break ;
		}
		env_tmp = env_tmp->next;
	}
}

static void	find_dollar_value(t_token **tmp, t_dollar **dol_info, t_info *data)
{
	if ((*dol_info)->len == 0)
	{
		(*dol_info)->new_value = ft_strjoin((*dol_info)->tmp2, "$");
		free_func(&(*dol_info)->tmp2);
	}
	else
		dollar_replace(tmp, dol_info, data);
}

static void	number_after_dollar(t_token **tmp, t_dollar **dol_info)
{
	if ((*dol_info)->null_flag > 0)
	{
		(*dol_info)->tmp3 = ft_strjoin("Minishell", (ft_substr((*tmp)->value,
						(*dol_info)->dollar + 2, (*dol_info)->len - 1)));
		(*dol_info)->null_flag = 0;
	}
	else
	{
		(*dol_info)->tmp3 = ft_substr((*tmp)->value, (*dol_info)->dollar + 2,
				(*dol_info)->len - 1);
	}
	(*dol_info)->new_value = ft_strjoin((*dol_info)->tmp2, (*dol_info)->tmp3);
	free_func(&(*dol_info)->tmp2);
	free_func(&(*dol_info)->tmp3);
	(*dol_info)->number_flag = 0;
}

static	void	dollar_question_handler(t_dollar **dol_info,
				t_info *data)
{
	char	*nbr;

	nbr = ft_itoa(data->exit_status);
	(*dol_info)->new_value = ft_strjoin((*dol_info)->tmp2, nbr);
	free_func(&(*dol_info)->tmp2);
	free_func(&nbr);
	(*dol_info)->i++;
}

void	dollar_expansion(t_token **tmp, t_dollar **dol_info,
				t_info *data)
{
	(*dol_info)->i++;
	if (ft_isdigit((*tmp)->value[(*dol_info)->i]))
	{
		(*dol_info)->number_flag++;
		if ((*tmp)->value[(*dol_info)->i] == '0')
			(*dol_info)->null_flag++;
	}
	(*dol_info)->len = 0;
	while (ft_isalnum((*tmp)->value[(*dol_info)->i])
		|| (*tmp)->value[(*dol_info)->i] == '_')
	{
		(*dol_info)->i++;
		(*dol_info)->len++;
	}
	if ((*tmp)->value[(*dol_info)->i - 1] == '$'
		&& (*tmp)->value[(*dol_info)->i] == '?')
		dollar_question_handler(dol_info, data);
	else if ((*dol_info)->number_flag > 0)
		number_after_dollar(tmp, dol_info);
	else
		find_dollar_value(tmp, dol_info, data);
}

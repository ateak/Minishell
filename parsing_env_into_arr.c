/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_into_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:55:26 by ateak             #+#    #+#             */
/*   Updated: 2022/09/08 16:19:30 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill_envp_arr(t_info *data, char **env)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (env[y])
	{
		x = 0;
		while (env[y][x])
		{
			data->envp[y][x] = env[y][x];
			x++;
		}
		data->envp[y][x] = '\0';
		y++;
	}
}

void	ft_create_envp_arr(t_info *data, char **env)
{
	int	y;

	data->envp = (char **)malloc(sizeof(char *) * (data->envp_y + 1));
	if (data->envp == NULL)
		error_exit(MALLOC_ERR, "malloc");
	y = 0;
	while (env[y])
	{
		data->envp[y] = (char *)malloc(sizeof(char) * (ft_strlen(env[y]) + 1));
		if (data->envp[y] == NULL)
			error_exit(MALLOC_ERR, "malloc");
		y++;
	}
	data->envp[y] = NULL;
	ft_fill_envp_arr(data, env);
}

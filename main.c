/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:42:22 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/09 12:27:22 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_info *data, char *str)
{
	if (preparser(data, str) != ERROR)
	{
		divide_into_tokens(str, data);
		put_tokens_to_cmd(data);
		executor(data);
	}
}

char	*ft_readline(char *prompt)
{
	char	*str;

	str = readline(prompt);
	if (str)
		add_history(str);
	return (str);
}

void	ft_init_data(t_info *data)
{
	data->reserved_words[0] = "echo";
	data->reserved_words[1] = "pwd";
	data->reserved_words[2] = "cd";
	data->reserved_words[3] = "export";
	data->reserved_words[4] = "unset";
	data->reserved_words[5] = "env";
	data->reserved_words[6] = "exit";
	data->envp = NULL;
	data->envp_list = NULL;
	data->envp_y = 0;
	data->exit_status = 0;
	data->shell_name = "minishell$ ";
	data->token_list = NULL;
	data->cmd_list = NULL;
	data->cmd_name = 0;
	data->args_amount = 0;
	data->ret_val = 0;
	data->token_len = 0;
	data->dol_info = NULL;
	data->num_cmd = 0;
}

static int	check_num_args(int argc)
{
	if (argc > 1)
	{
		printf ("Error: argument not allowed!\n");
		return (ERROR);
	}
	return (OK);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_info	data;

	(void) argv;
	if (check_num_args(argc))
		return (0);
	ft_init_data(&data);
	ft_parse_env(env, &data.envp_list, &data);
	ft_check_shell_lvl(&data);
	while (1)
	{
		signal(SIGINT, handler_ctl_c);
		signal(SIGQUIT, SIG_IGN);
		str = ft_readline(data.shell_name);
		if (str == NULL)
			norm_exit(&data);
		if (str[0] != '\0')
			minishell(&data, str);
		free_token_list(&data);
		free_cmd_list(&data);
		free(str);
	}
	free_data(&data);
	return (0);
}

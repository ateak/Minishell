/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:25:33 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/08 19:39:17 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_stop(char *tmp, char *file)
{
	if (!ft_strcmp(tmp, file))
	{
		free(tmp);
		return (1);
	}
	return (0);
}

void	ft_write_in_pipe(int tmpin, int tmpout, int fdhere, t_redir *p)
{
	char	*heredoc ;
	char	*tmp;
	char	*tmp1;

	while (1)
	{
		write (tmpout, "> ", 3);
		heredoc = get_next_line(tmpin);
		if (heredoc == NULL)
			return ;
		tmp = ft_strtrim(heredoc, "\n");
		if (heredoc)
			free(heredoc);
		if (check_stop(tmp, p->file) == 1)
			break ;
		tmp1 = ft_strjoin(tmp, "\n");
		if (tmp)
			free(tmp);
		write (fdhere, tmp1, ft_strlen(tmp1));
		if (tmp1)
			free(tmp1);
	}
}

void	ft_heredoc(t_redir *p, int tmpin, int tmpout)
{
	int		fdhere[2];

	if (pipe(fdhere) == -1)
		error_exit(errno, "pipe");
	dup2(fdhere[0], 0);
	close(fdhere[0]);
	ft_write_in_pipe(tmpin, tmpout, fdhere[1], p);
	close(fdhere[1]);
}

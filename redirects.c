/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:26:54 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/08 16:48:45 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_error(t_redir *p, t_info *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(p->file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	data->exit_status = 126;
	return (ERROR);
}

int	redir_out(t_redir *p, t_info *data, int flag)
{
	int		fdredout;

	if (flag == 1)
	{
		fdredout = open(p->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fdredout == -1)
			return (ft_redir_error(p, data));
	}
	if (flag == 2)
	{
		fdredout = open(p->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fdredout == -1)
			return (ft_redir_error(p, data));
	}
	dup2(fdredout, 1);
	close(fdredout);
	return (OK);
}

int	redir_in(t_redir *p, t_info *data)
{
	int		fdredin;

	fdredin = open(p->file, O_RDONLY, 0644);
	if (fdredin == -1)
		return (ft_redir_error(p, data));
	dup2(fdredin, 0);
	close(fdredin);
	return (OK);
}

int	ft_redirects(t_info *data, int tmpin, int tmpout)
{
	t_redir	*p;

	p = data->cmd_list->redir;
	while (p)
	{
		if (p->type == REDIR_HEREDOC)
			ft_heredoc(p, tmpin, tmpout);
		if (p->type == REDIR_IN)
		{
			if (redir_in(p, data) == ERROR)
				return (ERROR);
		}
		if (p->type == REDIR_OUT)
		{
			if (redir_out(p, data, 1) == ERROR)
				return (ERROR);
		}
		if (p->type == REDIR_APPEND)
		{
			if (redir_out(p, data, 2) == ERROR)
				return (ERROR);
		}
		p = p->next;
	}
	return (OK);
}

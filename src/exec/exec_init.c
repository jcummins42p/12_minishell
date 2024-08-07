/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:46:05 by akretov           #+#    #+#             */
/*   Updated: 2024/08/09 17:07:42 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pid(t_pipex *pipex, int n_pipes)
{
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * (n_pipes + 1));
	if (!pipex->pid)
	{
		msg("Memory allocation error");
		return (0);
	}
	return (1);
}

void	pipex_init(t_mshell *msh)
{
	msh->pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (msh->pipex == NULL)
	{
		msg(ERR_MEMORY);
		exit(1);
	}
	msh->pipex->fd_in = dup(STDIN_FILENO);
	msh->pipex->fd_out = dup(STDOUT_FILENO);
	// Arguments for execve
	msh->pipex->cmd_paths = ft_split(*msh->path, ':');
	if (!msh->pipex->cmd_paths)
	{
		// add error handler
		return ;
	}
	msh->pipex->status = 0;
	msh->pipex->cmd = NULL;
	msh->pipex->cmd_args = NULL;
	msh->pipex->pid = NULL;
}

void	ft_exec_init(t_mshell *msh)
{
	ft_exec_cmd(msh);
	free_pipex(msh->pipex);
}

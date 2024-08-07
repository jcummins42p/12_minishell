/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:50:45 by akretov           #+#    #+#             */
/*   Updated: 2024/08/09 19:05:11 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// delete?
void	cleanup(t_mshell *msh, t_pipex *pipex, int n_pipes)
{
	int		i;
	char	*status;

	i = 0;
	while (i < n_pipes + 1)
	{
		waitpid(pipex->pid[i], &pipex->status, 0);
		i++;
	}
	status = ft_itoa(pipex->status);
	env_set(&msh->envlist, "?", status, SHLVAR);
	close(pipex->fd_in);
	close(pipex->fd_out);
	free(status);
	free_pipex(pipex);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	if (!pipex)
		return ;
	i = 0;
	if (pipex->cmd_args)
	{
		while (pipex->cmd_args[i])
		{
			free(pipex->cmd_args[i]);
			i++;
		}
		free(pipex->cmd_args);
	}
	i = 0;
	if (pipex->cmd_paths)
	{
		while (pipex->cmd_paths[i])
		{
			free(pipex->cmd_paths[i]);
			i++;
		}
		free(pipex->cmd_paths);
	}
	free(pipex->cmd);
	free(pipex->pid);
	free(pipex);
}

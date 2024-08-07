/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:01 by akretov           #+#    #+#             */
/*   Updated: 2024/08/09 19:19:04 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_file(const char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
		write(STDERR_FILENO, "Couldn't open the file\n", 23);
	return (fd);
}

void ft_handle_heredoc(t_pipex *pipex, const char *delimiter)
{
	char *line;

	if (pipe(pipex->fd_pipe) == -1)
	{
		write(STDERR_FILENO, "Couldn't create pipe\n", 23);
		return;
	}

	while (1)
	{
		line = readline("> ");
		if (!line)
			break;

		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0) {
			free(line);
			break;
		}

		write(pipex->fd_pipe[1], line, ft_strlen(line));
		write(pipex->fd_pipe[1], "\n", 1);
		free(line);
	}
	close(pipex->fd_pipe[1]);
}

void	ft_handle_redirection(t_pipex *pipex, t_tokenlist **tokens)
{
	if (*tokens == NULL)
		return ;
	if ((*tokens)->mtctype == RDIN)
	{
		*tokens = (*tokens)->next;
		if (*tokens)
			pipex->fd_in = ft_open_file((*tokens)->token, O_RDONLY, 0);
	}
	else if ((*tokens)->mtctype == RDOUT)
	{
		*tokens = (*tokens)->next;
		if (*tokens)
			pipex->fd_out = ft_open_file((*tokens)->token,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if ((*tokens)->mtctype == RDAPP)
	{
		*tokens = (*tokens)->next;
		if (*tokens)
			pipex->fd_out = ft_open_file((*tokens)->token,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if ((*tokens)->mtctype == DELIMIT)
	{
		*tokens = (*tokens)->next;
		if (*tokens)
		{
			ft_handle_heredoc(pipex, (*tokens)->token);
			pipex->fd_in = dup(pipex->fd_pipe[0]);
			close(pipex->fd_pipe[0]);
		}
	}
	if (*tokens)
		*tokens = (*tokens)->next;
}

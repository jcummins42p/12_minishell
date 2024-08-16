/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:51:39 by akretov           #+#    #+#             */
/*   Updated: 2024/08/15 13:04:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	populate_args(t_pipex *pipex, t_tokenlist **tokens, char **arg[])
{
	int	i;

	i = 0;
	(void)pipex;
	while (*tokens && (*tokens)->mtctype != PIPE)
	{
		if ((*tokens)->mtctype >= RDIN)
			*tokens = (*tokens)->next->next;
		else
		{
			(*arg)[i++] = ft_strdup((*tokens)->expand);
			*tokens = (*tokens)->next;
		}
	}
	(*arg)[i] = NULL;
}

int	count_args(t_tokenlist *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->mtctype != PIPE)
	{
		if (tokens->mtctype < RDIN)
			count++;
		else
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (count);
}

char	**ft_get_arg(t_pipex *pipex, t_tokenlist **tokens)
{
	char		**arg;
	int			i;
	t_tokenlist	*ptr;

	ptr = *tokens;
	i = 0;
	if ((*tokens)->mtctype == PIPE)
	{
		*tokens = (*tokens)->next;
		ptr = ptr->next;
	}
	i = count_args(ptr);
	arg = malloc(sizeof(char *) * (i + 1));
	if (!arg)
	{
		write(STDERR_FILENO, "Memory allocation failed\n", 25);
		return (NULL);
	}
	populate_args(pipex, tokens, &arg);
	return (arg);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

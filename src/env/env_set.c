/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:31:31 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/14 15:15:45 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	free function for dynamically allocated env char **
void	env_unset_string(char **env[])
{
	int	i;

	i = 0;
	while ((*env)[i])
		free ((*env)[i++]);
	free (*env);
}

//	recreates the env in original char **format suitable for execve
void	env_set_string(t_envlist **envlist, char **env[])
{
	t_envlist	*curr;
	int			line;
	int			size;

	if (*env)
		env_unset_string(env);
	curr = *envlist;
	line = 0;
	size = env_list_size(envlist);
	*env = malloc(sizeof (char *) * (size + 1));
	while (curr)
	{
		if (curr->scope == ENVVAR)
			(*env)[line++] = ft_strchrjoin(curr->param, curr->value, '=');
		curr = curr->next;
	}
	(*env)[line] = NULL;
}

//	deletes env node from linked list based on search parameter
void	env_unset(t_envlist **envlist, const char *search)
{
	t_envlist	*find;

	find = env_search(envlist, search);
	if (find)
		env_del(&find);
}

//	checks that an environment variable name is valid before creating it
bool	env_valid(const char *search)
{
	int	i;

	i = 0;
	if (ft_isalpha(search[i]) || search[i] == '_' || search[i] == '$' \
			|| search[i] == '?')
		i++;
	else
		return (false);
	while (search[i])
	{
		if (ft_isalnum(search[i]) || search[i] == '_')
			i++;
		else
			return (false);
	}
	return (true);
}

//	either updates search env variable to newval, or creates new node if input
//	is valid
void	env_set(t_envlist **envlist, const char *search, const char *newval, \
		t_vscope scope)
{
	t_envlist	*find;

	if (!envlist || !search || !newval)
		return ;
	find = env_search(envlist, search);
	if (find)
	{
		free (find->value);
		find->value = ft_strdup(newval);
		if (scope == ENVVAR)
			find->scope = ENVVAR;
	}
	else
	{
		if (env_valid(search))
			env_new(envlist, search, newval, scope);
		else
			ft_printf("export: not valid in this context: %s\n", search);
	}
}

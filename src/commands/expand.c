/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:10:23 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 15:28:33 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**expand_variable(t_envlist **envlist, char *param)
{
	char	**expand;

	expand = env_get_val(envlist, param);
	if (expand)
		printf("%s\n", *expand);
	else
		printf("\n");
	return (expand);
}

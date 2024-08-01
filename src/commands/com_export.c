/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:21:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/01 14:02:27 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_var(t_mshell *msh, t_vscope scope)
{
	t_tokenlist	*token;

	token = msh->tokens;
	if (token->comtype == EXPORT)
		token = token->next;
	while (token && token->mtctype != PIPE)
	{
		env_from_str(&msh->envlist, token->token, scope);
		token = token->next;
	}
	env_set_string(&msh->envlist, &msh->env);
}

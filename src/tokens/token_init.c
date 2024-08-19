/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:40:26 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/19 18:06:57 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_set_validity(t_mshell *msh, char quote)
{
	if (quote == '\"')
		msh->valid_input = NO_DQUOTE;
	else if (quote == '\'')
		msh->valid_input = NO_SQUOTE;
}

void	token_init(t_mshell *msh, t_tokenlist *new, char *newtoken, int pos)
{
	new->token = ft_strdup(newtoken);
	new->comtype = is_builtin(newtoken);
	new->mtctype = is_metachar(newtoken);
	if (new->comtype)
		new->tokentype = COMMAND;
	else if (new->mtctype)
		new->tokentype = METACHAR;
	else
		new->tokentype = GENERIC;
	if (new->mtctype >= ASS)
		new->expand = ft_strdup(new->token);
	else if (new->mtctype == SQUOTE)
		new->expand = expand_string_sq(newtoken);
	else
		new->expand = expand_string_dq(msh, newtoken);
	if (new->comtype != C_ASSIGN && new->comtype != C_EXPORT)
		new->comtype = is_builtin(new->expand);
	new->pos = pos;
	new->next = NULL;
}

void	token_append(t_tokenlist **tokens, t_tokenlist **new)
{
	t_tokenlist	*curr;
	int			index;

	curr = *tokens;
	index = 0;
	if (curr == NULL)
	{
		*tokens = *new;
		(*new)->prev = NULL;
		(*new)->index = index;
	}
	else
	{
		index++;
		while (curr->next)
		{
			curr = curr->next;
			index++;
		}
		curr->next = *new;
		(*new)->index = index;
		(*new)->prev = curr;
	}
}

//	creates new node in tokenlist based on token (metachar or command) and the
//	variable following that token, such as $VARIABLE
int	token_new(t_mshell *msh, char *newtoken, int pos, bool trail_space)
{
	t_tokenlist	*new;

	new = malloc(sizeof(t_tokenlist));
	if (new == NULL)
		return (0);
	new->trail_space = trail_space;
	token_init(msh, new, newtoken, pos);
	token_append(&msh->tokens, &new);
	msh->valid_input = VALID_IN;
	return (ft_strlen(newtoken));
}

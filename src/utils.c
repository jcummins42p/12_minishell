/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:19:05 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/08 13:04:04 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_trailspace(char c)
{
	if (c == '\t'	|| c == ' ' || c == '\0')
		return (true);
	else
		return (false);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else
		return (false);
}

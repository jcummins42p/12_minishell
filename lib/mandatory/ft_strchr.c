/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:37:43 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/25 17:30:30 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		else
			s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

/*int	main(void)*/
/*{*/
	/*const char		*str = "The quick brown fox jumps over the lazy dog!";*/
	/*unsigned char	c = '|';*/

	/*printf("Found %c at \"%s\" in the string.\n", c, ft_strchr(str, c));*/
/*}*/

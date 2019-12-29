/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 01:51:50 by fgeruss           #+#    #+#             */
/*   Updated: 2019/04/08 01:51:52 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;
	char	*p;

	p = (char *)s2;
	if (*p == '\0')
		return ((char *)s1);
	while (*((char *)s1) != '\0')
	{
		i = 0;
		s2 = p;
		while (*((char *)s2) == *(((char *)s1) + i))
		{
			if (*((char *)s2 + 1) == '\0')
				return ((char *)s1);
			i++;
			s2++;
		}
		s1++;
	}
	return (NULL);
}

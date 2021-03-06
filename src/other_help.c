/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:04:25 by asusan            #+#    #+#             */
/*   Updated: 2019/11/22 16:04:27 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

size_t	ft_tabpos(const char *line, char ch)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ch)
			return (i);
		i++;
	}
	return (i);
}


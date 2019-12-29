/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norm_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:00:16 by fgeruss           #+#    #+#             */
/*   Updated: 2019/11/18 16:00:18 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		not_exit_room(char *line, t_room *room)
{
	char	*str1;
	char	*str2;
	int		bool;

	bool = 0;
	str1 = ft_strsub(line, 0, ft_tabpos(line, '-'));
	str2 = ft_strsub(line, ft_tabpos(line, '-') + 1, ft_tabpos(line, '\0'));
	while (room->next != NULL)
	{
		if (ft_strcmp(room->room, str1) == 0)
			bool++;
		if (ft_strcmp(room->room, str2) == 0)
			bool++;
		room = room->next;
	}
	if (bool != 2)
		return (0);
	ft_strdel(&str1);
	ft_strdel(&str2);
	return (1);
}

int		for_norm_2(t_room *room, t_ants *ants, char **unique)
{
	int		bool;
	int		i;

	bool = 0;
	while ((room = room->next) && room->next != NULL)
	{
		i = -1;
		while (++i < ants->count_rooms)
		{
			if (i != 0 && unique[i] == NULL)
			{
				unique[i] = (unique[i] == NULL) ? ft_strdup(room->room) : NULL;
				break ;
			}
			bool = (i != 0 && ft_strcmp(unique[i], room->room) == 0) ? 1 : 0;
			if (bool == 1)
				return (0);
		}
	}
	return (1);
}

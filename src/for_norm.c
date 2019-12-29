/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:18:19 by fgeruss           #+#    #+#             */
/*   Updated: 2019/11/18 14:18:20 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Цикл,в котором записываем количество
** соседей у каждой комнаты
** и записываем имя самого соседа
*/

int		loop(t_room *room, char *str1, char *str2)
{
	int 	i;

	while (room->next)
	{
		if (!(ft_strcmp(room->room, str1) && ft_strcmp(room->room, str2)))
		{
			if (!ft_strcmp(room->room, str2))
			{
				i = -1;
				while (++i < room->count_neigh)
				{
					if (!ft_strcmp(room->neight[i], str2))
						return (0);
				}
				room->neight[room->count_neigh++] = ft_strdup(str1);
			}
			else if (!ft_strcmp(room->room, str1))
			{
				i = -1;
				while (++i < room->count_neigh)
				{
					if (!ft_strcmp(room->neight[i], str2))
						return (0);
				}
				room->neight[room->count_neigh++] = ft_strdup(str2);
			}
		}
		room = room->next;
	}
	return (1);
}

/*
** Проверка на дублирование координат
*/

int		check_dublicate_coord(t_room *room)
{
	t_room	*point;

	point = room->next;
	while (room->next->next != NULL)
	{
		if (room->x == point->x)
			if (room->y == point->y)
				return (0);
		point = point->next;
		if (point->next == NULL)
		{
			room = room->next;
			point = room->next;
		}
	}
	return (1);
}

/*
** Инициализация координат
*/

int		for_norm_1(char *str, char **dig1, char **dig2)
{
	int		i;

	i = 0;
	if ((*dig1 = ft_strsub(str + 1, 0, for_norm_count(str + 1, ' '))) != NULL)
	{
		while (*dig1[i] && *dig1[i] != ' ')
			if (!ft_isdigit(*dig1[i++]))
			{
				free(*dig1);
				return (0);
			}
		if ((*dig2 = ft_strstr(str + 1 + ft_strlen(*dig1), "\0") + 1) != NULL)
		{
			i = 0;
			while (*dig2[i] && *dig2[i] != '\0')
				if (!ft_isdigit(*dig2[i++]))
					return (0);
		}
	}
	return (1);
}

int		for_norm_count(char *str, char pr)
{
	int		c;

	c = 0;
	while (*str++ != pr)
		c++;
	return (c);
}

void	for_norm(t_room *room, char *line)
{
	room->room = NULL;
	room->room = ft_strsub(line, 0, ft_tabpos(line, ' '));
	room->real = NULL;
	if (room->is_start == 1 || room->is_end == 1)
		room->real = ft_strsub(line, 0, ft_tabpos(line, ' '));
}

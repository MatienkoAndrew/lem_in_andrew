/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:58:14 by fgeruss           #+#    #+#             */
/*   Updated: 2019/09/11 18:58:30 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Экстренное завершение программы
*/

void	error(char *str)
{
	ft_printf("%s", str);
	exit(1);
}

/*
** Очистка памяти
*/

void	freer(t_room *room)
{
	int		i;
	t_room	*tmp;

	while (room)
	{
		i = -1;
		while (++i < room->count_neigh)
			ft_strdel(&room->neight[i]);
		free(room->neight);
		room->neight = NULL;
		if (room->is_start == 1 || room->is_end == 1)
			ft_strdel(&room->real);
		ft_strdel(&room->room);
		tmp = room->next;
		room->next = NULL;
		free(room);
		room = NULL;
		room = tmp;
	}
}

/*
** Выделяется память под двумерный массив
** в который будем записывать соседей
*/

void	create_neighbours(t_room *room, t_ants *ants)
{
	ants->count_rooms = nbr_rooms(room);
	while (room->next)
	{
		if (!(room->neight = (char **)malloc(sizeof(char *) \
				* ants->count_rooms)))
			error("Not allocated memory");
		room = room->next;
	}
}

/*
** Подсчитывает количество комнат
*/

int		nbr_rooms(t_room *start)
{
	t_room	*tmp;
	int		count;

	count = 0;
	tmp = start;
	while (start->next)
	{
		count++;
		start = start->next;
	}
	return (count);
}

/*
** Инициализация переменных
*/

void	init_val(t_ants *ants)
{
	(*ants).count_road = NULL;
	(*ants).count_road_variable = 0;
	(*ants).count_rooms = 0;
	(*ants).helper = 0;
	(*ants).lem_count = 0;
	(*ants).s_top = NULL;
	(*ants).lem_in_house = 0;
	(*ants).min_road = 0;
	(*ants).reverse_lem = 0;
	(*ants).roads = NULL;
	(*ants).special_for_end = NULL;
	(*ants).special_for_end_int = 0;
	(*ants).special_for_end = NULL;
	(*ants).reverse_lem = 0;
	(*ants).length_road = NULL;
}

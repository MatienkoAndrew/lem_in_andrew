/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:05:59 by fgeruss           #+#    #+#             */
/*   Updated: 2019/09/11 19:12:28 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Проверка на дублирование комнат
*/

int		check_dublicate(t_room *room, t_ants *ants)
{
	char	**unique;
	int		i;
	int		bool;

	bool = 0;
	unique = NULL;
	if (!(unique = (char **)malloc(sizeof(char *) * ants->count_rooms)))
		error("Not allocated memory");
	i = -1;
	while (++i < ants->count_rooms)
		unique[i] = NULL;
	unique[0] = ft_strdup(room->room);
	for_norm_2(room, ants, unique);
	i = -1;
	while (++i < ants->count_rooms)
		ft_strdel(&unique[i]);
	free(unique);
	unique = NULL;
	return (1);
}

/*
** Выделяем память в массиве структур
** для двумерного массива, в котором
** запишем имена соседей
*/

void	mem_neight(t_room *start, t_ants *ants)
{
	int		i;

	i = -1;
	while (++i < ants->count_rooms)
	{
		if (!((ants->s_top[i]).neighbours = \
				(char **)malloc(sizeof(char *) * start->count_neigh)))
			error("Not allocated memory");
		start = start->next;
	}
}

/*
** Функция перезаписывает информацию из листов(комнат)
** в массив структур
*/

void	rewriting(t_room *start, t_ants *ants)
{
	t_norm	a;
	t_room	*first;

	first = start;
	if (!(ants->s_top = (t_top *)malloc(sizeof(t_top) * ants->count_rooms)))
		error("Not allocated memory!");
	a.i = -1;
	while (++a.i < ants->count_rooms)
		initialize_s_top(&ants->s_top[a.i]);
	mem_neight(start, ants);
	start = first;
	a.i = -1;
	while (++a.i < ants->count_rooms)
	{
		a.j = -1;
		(ants->s_top[a.i]).room_name = ft_strdup(start->room);
		if (start->is_start == 1 || start->is_end == 1)
			(ants->s_top[a.i].real_name) = ft_strdup(start->real);
		(ants->s_top[a.i]).start = start->is_start;
		(ants->s_top[a.i]).end = start->is_end;
		(ants->s_top[a.i]).count_neigh = start->count_neigh;
		while (++a.j < start->count_neigh)
			(ants->s_top[a.i]).neighbours[a.j] = ft_strdup(start->neight[a.j]);
		start = start->next;
	}
}

void	initialize_s_top(t_top *top)
{
	top->helper = 0;
	top->real_name = NULL;
	top->room_name = NULL;
	top->count_neigh = 0;
	top->weight = 0;
	top->bellman_was_here = 0;
	top->end = 0;
	top->for_bell = 0;
	top->for_in_out = 0;
	top->from_to = 0;
	top->his_road = NULL;
	top->mark = 0;
	top->start = 0;
	top->name_ant_in_flat = NULL;
	top->input = 0;
	top->output = 0;
	top->forward_to = NULL;
	top->forwarders = 0;
	top->part_of_road = NULL;
	top->what_ant = 0;
	top->in_house = 0;
}

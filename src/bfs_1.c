/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:04:06 by asusan            #+#    #+#             */
/*   Updated: 2019/11/22 16:04:08 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

char	*search_startroom(t_ants *ants)
{
	char	*room_name;
	int		i;

	i = -1;
	room_name = NULL;
	while (++i < ants->count_rooms)
		if ((ants->s_top[i]).start == 1)
			return (room_name = (ants->s_top[i]).room_name);
	return (room_name);
}

char	*search_endroom(t_ants *ants)
{
	int	i;

	i = -1;
	while (++i < ants->count_rooms)
		if ((ants->s_top[i]).end == 1)
			return (ants->s_top[i].room_name);
	return (NULL);
}

void	mark_to_null(t_ants *ants)
{
	int		i;

	i = -1;
	while (++i < ants->count_rooms)
		ants->s_top[i].mark = 0;
}

void	weight_to_null(t_ants *ants)
{
	int	i;

	i = -1;
	while (++i != ants->count_rooms)
		ants->s_top[i].weight = -1;
}

void	init(t_queue *q)
{
	int		i;

	(*q).first = 0;
	(*q).end = -1;
	i = -1;
	while (++i < 100000 - 1)
		q->qu[i] = NULL;
}

void	push(t_queue *q, char *x)
{
	if (q->end < 100000 - 1)
	{
		q->end++;
		q->qu[q->end] = ft_strdup(x);
	}
	else
		ft_printf("Queue Is full");
}

int		is_empty_(t_queue *q)
{
	if (q->end < q->first)
		return (1);
	else
		return (0);
}

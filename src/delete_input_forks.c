/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_input_forks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 14:58:17 by fgeruss           #+#    #+#             */
/*   Updated: 2019/12/28 14:58:19 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		ft_rewrite_forward_to_1(t_ants *ants, int i, char **temp, int k)
{
	int 	m;

	m = -1;
	while (++m < (ants->s_top[i]).forwarders)
		ft_strdel(&(ants->s_top[i]).forward_to[m]);
	free((ants->s_top[i]).forward_to);
	(ants->s_top[i]).forwarders = k;
	(ants->s_top[i]).forward_to = (char **)malloc(sizeof(char *) * (ants->s_top[i]).forwarders);
	m = -1;
	while (++m < (ants->s_top[i]).forwarders)
		(ants->s_top[i]).forward_to[m] = ft_strdup(temp[m]);
}


/*
** Переписываем массив
*/

void		ft_rewrite_forward_to(t_ants *ants, int i)
{
	char 	**temp;
	int 	k;
	int 	m;

	temp = (char **)malloc(sizeof(char *) * (ants->s_top[i]).forwarders);
	k = 0;
	m = -1;
	while (++m < (ants->s_top[i]).forwarders)
	{
		if ((ants->s_top[i]).forward_to[m] == NULL)
			continue ;
		temp[k] = ft_strdup((ants->s_top[i]).forward_to[m]);
		k++;
	}
	ft_rewrite_forward_to_1(ants, i, temp, k);
	m = -1;
	while (++m < (ants->s_top[i]).forwarders)
		ft_strdel(&temp[m]);
	free(temp);
}

void	delete_forward_to(t_ants *ants, int i, int j)
{
	int 	k;

	k = -1;
	while (++k < (ants->s_top[i]).forwarders)
		if (ft_strcmp((ants->s_top[i]).forward_to[k], (ants->s_top[j]).room_name) == 0)
			ft_strdel(&(ants->s_top[i]).forward_to[k]);
	ft_rewrite_forward_to(ants, i);
	//Delete second
	k = -1;
	while (++k < (ants->s_top[j]).forwarders)
		if (ft_strcmp((ants->s_top[j]).forward_to[k], (ants->s_top[i]).room_name) == 0)
			ft_strdel(&(ants->s_top[j]).forward_to[k]);
	ft_rewrite_forward_to(ants, j);
}

int 	has_forward_to(t_ants *ants, int i, int j)
{
	int 	k;

	k = -1;
	while (++k < (ants->s_top[i]).forwarders)
		if (ft_strcmp((ants->s_top[i]).forward_to[k], (ants->s_top[j]).room_name) == 0)
			return (1);
	return (0);
}

void	delete_links(t_ants *ants, int point)
{
	int 	i;
	int 	point_new;

	i = -1;
	while (++i < (ants->s_top[point]).count_neigh)
	{
		point_new = search(ants, (ants->s_top[point]).neighbours[i]);
		if ((ants->s_top[point_new]).output > 1 && has_forward_to(ants, point_new, point))
		{
			delete_forward_to(ants, point_new, point);
			delete(ants, point_new, point);
			(ants->s_top[point_new]).output -= 1;
			(ants->s_top[point]).input -= 1;
		}
	}
}

void	delete_input_forks(t_ants *ants)
{
	int 	i;
	int 	j;
	t_queue queue;

	init(&queue);
	mark_to_null(ants);
	(ants->s_top[search(ants, search_startroom(ants))]).mark = 1;

	//засунули соседей в очередь
	i = -1;
	while (++i < (ants->s_top[search(ants, search_startroom(ants))]).count_neigh)
	{
		push(&queue, (ants->s_top[search(ants, search_startroom(ants))]).neighbours[i]);
		ants->s_top[search(ants, (ants->s_top[search(ants, search_startroom(ants))]).neighbours[i])].mark = 1;
	}
	//расставляем веса
	while (!is_empty_(&queue))
	{
		j = search(ants, pop(&queue));
		i = -1;
		while (++i < ((ants->s_top[j]).count_neigh))
		{
			int 	k = search(ants, (ants->s_top[j]).neighbours[i]);
			if ((ants->s_top[k]).mark == 0 && ft_strcmp((ants->s_top[j]).room_name, (ants->s_top[search(ants, search_endroom(ants))]).room_name))
			{
				(ants->s_top[k]).mark = 1;
				push(&queue, (ants->s_top[j]).neighbours[i]);
				if ((ants->s_top[k]).input > 1 && ft_strcmp((ants->s_top[k]).room_name, (ants->s_top[search(ants, search_endroom(ants))]).room_name))
					delete_links(ants, k);
			}
		}
	}

	//Free
	i = -1;
	while (queue.qu[++i] != NULL)
		ft_strdel(&queue.qu[i]);


//	Print
	ft_printf("\n\nStep 7:\n");
	i = -1;
	while (++i < ants->count_rooms)
	{
		ft_printf("\nRoom: %-6s  Neighbours: ", (ants->s_top[i]).room_name);
		j = -1;
		while (++j < (ants->s_top[i]).count_neigh)
			ft_printf("%-6s ", (ants->s_top[i]).neighbours[j]);
	}

	ft_printf("\n\n");
	i = -1;
	while (++i < ants->count_rooms)
		ft_printf("Room: %-6s  Input: %-2d  Output: %-2d\n", (ants->s_top[i]).room_name, (ants->s_top[i]).input, (ants->s_top[i]).output);


	i = -1;
	while (++i < ants->count_rooms)
	{
		ft_printf("\nRoom: %-6s  forward_to: ", (ants->s_top[i]).room_name);
		j = -1;
		while (++j < (ants->s_top[i]).forwarders)
			ft_printf("%-6s ", (ants->s_top[i]).forward_to[j]);
	}
}


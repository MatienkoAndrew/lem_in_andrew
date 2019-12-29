/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_output_forks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 16:55:43 by fgeruss           #+#    #+#             */
/*   Updated: 2019/12/28 16:55:44 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 	find_min_dist(int *len_dist, int size)
{
	int 	i;
	int 	min;
	int 	index;

	index = 0;
	min = len_dist[index];
	i = -1;
	while (++i < size)
	{
		if (len_dist[i] < min)
		{
			index = i;
			min = len_dist[i];
		}
	}
	return (index);
}

void	delete_some_links(t_ants *ants, int point)
{
	int 	i;
	int 	point_new;
	char 	**distances;
	int 	*len_dist;

	if (!(len_dist = (int *)malloc(sizeof(int) * (ants->s_top[point]).forwarders)))
		error("Not allocated memory");
	i = -1;
	while (++i < (ants->s_top[point]).forwarders)
		len_dist[i] = 1;


	distances = NULL;
	if (!(distances = (char **)malloc(sizeof(char *) * (ants->s_top[point]).forwarders)))
		error("Not allocated memory");
	i = -1;
	while (++i < (ants->s_top[point]).forwarders)
	{
		distances[i] = NULL;
		distances[i] = ft_strdup((ants->s_top[point]).room_name);
	}


//	Ищет пути от разветвления до конца
//	len_dist - длина пути от разветвления
//	distances - сами пути
	i = -1;
	while (++i < (ants->s_top[point]).forwarders)
	{
		point_new = search(ants, (ants->s_top[point]).forward_to[i]);
		while (ft_strcmp((ants->s_top[point_new]).room_name, (ants->s_top[search(ants, search_endroom(ants))]).room_name))
		{
//			LEAKS!!!!!!!!!!!!
			distances[i] = ft_strjoin(distances[i], "/");
			distances[i] = ft_strjoin(distances[i], (ants->s_top[point_new]).room_name);
			len_dist[i] += 1;
			point_new = search(ants, (ants->s_top[point_new]).forward_to[0]);
		}
		distances[i] = ft_strjoin(distances[i], "/");
		distances[i] = ft_strjoin(distances[i], (ants->s_top[search(ants, search_endroom(ants))]).room_name);
	}

//	Индекс минимального пути
	int min_dist = find_min_dist(len_dist, (ants->s_top[point]).forwarders);
	char 	*str1;
	char 	*str2;
	str2 = NULL;
	i = -1;
	while (++i < (ants->s_top[point]).forwarders)
	{
		if (i == min_dist)
			continue ;
		else
		{
			while (ft_strcmp(distances[i], (ants->s_top[search(ants, search_endroom(ants))]).room_name))
			{
				str1 = ft_strsub(distances[i], 0, for_norm_count(distances[i], '/'));
				str2 = ft_strsub(distances[i] + ft_strlen(str1) + 1, 0, for_norm_count(distances[i], '/'));
				delete(ants, search(ants, str1), search(ants, str2));
				delete_forward_to(ants, search(ants, str1), search(ants, str2));
				(ants->s_top[search(ants, str1)]).output -= 1;
				(ants->s_top[search(ants, str2)]).input -= 1;
				distances[i] = ft_strstr(distances[i], "/") + 1;
			}
		}
	}
}

void	delete_output_forks(t_ants *ants)
{
	int 	i;
	int 	j;
	t_queue queue;

	init(&queue);
	mark_to_null(ants);
	(ants->s_top[search(ants, search_endroom(ants))]).mark = 1;

	//засунули соседей в очередь
	i = -1;
	while (++i < (ants->s_top[search(ants, search_endroom(ants))]).count_neigh)
	{
		push(&queue, (ants->s_top[search(ants, search_endroom(ants))]).neighbours[i]);
		ants->s_top[search(ants, (ants->s_top[search(ants, search_endroom(ants))]).neighbours[i])].mark = 1;
	}
	//расставляем веса
	while (!is_empty_(&queue))
	{
		j = search(ants, pop(&queue));
		i = -1;
		while (++i < ((ants->s_top[j]).count_neigh))
		{
			int 	k = search(ants, (ants->s_top[j]).neighbours[i]);
			if ((ants->s_top[k]).mark == 0 && ft_strcmp((ants->s_top[j]).room_name, (ants->s_top[search(ants, search_startroom(ants))]).room_name))
			{
				(ants->s_top[k]).mark = 1;
				push(&queue, (ants->s_top[j]).neighbours[i]);
				if ((ants->s_top[k]).output > 1 && ft_strcmp((ants->s_top[k]).room_name, (ants->s_top[search(ants, search_startroom(ants))]).room_name))
					delete_some_links(ants, k);
			}
		}
	}

	//Free
	i = -1;
	while (queue.qu[++i] != NULL)
		ft_strdel(&queue.qu[i]);




	//	Print
	ft_printf("\n\nStep 8:\n");
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

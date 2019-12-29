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

//
//void	helper_for_search_road_228(t_ants *ants,
//								   int i, char **distance, char **room_name)
//{
//	int		j;
//	char	*temp;
//	char	*temp_1;
//	int		m;
//
//	j = -1;
//	while (++j < (ants->s_top[i]).count_neigh)
//	{
//		m = search(ants, (ants->s_top[i]).neighbours[j]);
//		if (ants->s_top[i].from_to[j] == -1)
//		{
//			ft_strdel(room_name);
//			*room_name = (ants->s_top[m]).room_name;
//			temp = ft_strdup(*distance);
//			ft_strdel(distance);
//			temp_1 = ft_strjoin("/", temp);
//			ft_strdel(&temp);
//			ants->s_top[i].for_bell = 1;
//			*distance = ft_strjoin(*room_name, temp_1);
//			(ants->s_top[m]).mark++;
//			ft_strdel(&temp);
//			ft_strdel(&temp_1);
//			break ;
//		}
//	}
//}

char 	*for_leaks(char *distance, t_ants *ants, int point_new)
{
	char 	*temp;
	char 	*temp_1;

	temp = ft_strdup(distance);
	ft_strdel(&distance);
	temp_1 = ft_strjoin(temp, "/");
	ft_strdel(&temp);
	distance = ft_strjoin(temp_1, (ants->s_top[point_new]).room_name);
	ft_strdel(&temp_1);
	return (distance);
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
			distances[i] = for_leaks(distances[i], ants, point_new);
//
//			distances[i] = ft_strjoin(distances[i], "/");
//			distances[i] = ft_strjoin(distances[i], (ants->s_top[point_new]).room_name);
//

			len_dist[i] += 1;
			if ((ants->s_top[point_new]).forward_to[0] == NULL)
				break ;
			point_new = search(ants, (ants->s_top[point_new]).forward_to[0]);
		}
		distances[i] = for_leaks(distances[i], ants, search(ants, search_endroom(ants)));
//		distances[i] = ft_strjoin(distances[i], "/");
//		distances[i] = ft_strjoin(distances[i], (ants->s_top[search(ants, search_endroom(ants))]).room_name);
	}

//	Индекс минимального пути
	int min_dist = find_min_dist(len_dist, (ants->s_top[point]).forwarders);
	char 	*str1;
	char 	*str2;
	str2 = NULL;


//	FOR LEAKS
	char 	*temp;
	int 	temp_forwarders = (ants->s_top[point]).forwarders;

	i = -1;
	while (++i < (ants->s_top[point]).forwarders)
	{
		if (i == min_dist)
			continue ;
		else
		{
			temp = distances[i];
//			while (ft_strcmp(distances[i], (ants->s_top[search(ants, search_endroom(ants))]).room_name))
			while (ft_strcmp(temp, (ants->s_top[search(ants, search_endroom(ants))]).room_name))
			{
				str1 = ft_strsub(distances[i], 0, for_norm_count(distances[i], '/'));
				str2 = ft_strsub(distances[i] + ft_strlen(str1) + 1, 0, for_norm_count(distances[i], '/'));
				delete_forward_to(ants, search(ants, str1), search(ants, str2));
				delete(ants, search(ants, str1), search(ants, str2), 1);
				(ants->s_top[search(ants, str1)]).output -= 1;
				(ants->s_top[search(ants, str2)]).input -= 1;

				temp = ft_strstr(temp, "/") + 1;
//				distances[i] = ft_strstr(distances[i], "/") + 1;

				ft_strdel(&str1);
				ft_strdel(&str2);
			}
		}
	}

	i = -1;
	while (++i < temp_forwarders)//(ants->s_top[point]).forwarders)
		ft_strdel(&distances[i]);
	free(distances);
	ft_strdel_int(&len_dist);


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
			int 	k = -1;
			if ((ants->s_top[j]).neighbours != NULL && (ants->s_top[j]).neighbours[i] != NULL)
				k = search(ants, (ants->s_top[j]).neighbours[i]);
			if (k != -1 && (ants->s_top[k]).mark == 0 && ft_strcmp((ants->s_top[j]).room_name, (ants->s_top[search(ants, search_startroom(ants))]).room_name))
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

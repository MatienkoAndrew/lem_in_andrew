/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 19:07:33 by fgeruss           #+#    #+#             */
/*   Updated: 2019/12/28 19:07:34 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Массив с индексами неуникальных значений
*/

int 	*find_min_index(int *len_dist, int new, int min, int size)
{
	int 	i;
	int 	j;
	int 	*new_ar;

	if (!(new_ar = (int *)malloc(sizeof(int) * new)))
		error("Not allocated memory");
	i = -1;
	j = -1;
	while (++i < size)
		if (len_dist[i] == min)
		{
			new_ar[++j] = i;
			len_dist[i] = -1;
		}
	return (new_ar);
}

/*
** Ищет количество минимальных чисел в массиве int
*/

int 	count_min_num(int *len_dist, int min, int size)
{
	int 	i;
	int 	count;

	count = 0;
	i = -1;
	while (++i < size)
		if (len_dist[i] == min)
			count++;
	return (count);
}

/*
** Ищет минимальное число в массиве int
*/

int 	min_num(int *len_dist, int size)
{
	int 	i;
	int 	min;

	min = 100000000;
	i = -1;
	while (++i < size)
		if (len_dist[i] != -1 && len_dist[i] < min)
			min = len_dist[i];
	return (min);
}

/*
** Количество дорог без повторений по длине
*/

int 	unique(int *len_dist, t_ants *ants)
{
	int 	uniq;
	int 	size;
	int 	i;
	int 	j;

	size = (ants->s_top[search(ants, search_startroom(ants))]).forwarders;
	uniq = size;
	i = -1;
	while (++i < size)
	{
		j = i;
		while (++j < size)
			if (len_dist[i] == len_dist[j])
			{
				uniq -= 1;
				break ;
			}
	}
//	ft_printf("\nUnique:  %i\n", uniq);
	return (uniq);
}

void	ft_write_roads(t_ants *ants, char **distances, int *len_dist)
{
	int 	forks;
	int 	size;
	int 	*index_min;
	index_min = NULL;

	size = (ants->s_top[search(ants, search_startroom(ants))]).forwarders;
	forks = unique(len_dist, ants);

	if (!(ants->roads = (char ***)malloc(sizeof(char **) * forks)))
		error("Not allocated memory");
	ants->count_road_variable = forks;
	int 	i;
	i = -1;
	while (++i < forks)
		ants->roads[i] = NULL;

//	Длина каждого пути
	if (!(ants->length_road = (int *)malloc(sizeof(int) * size)))
		error("Not allocated memory");

//	Количесво дорог на стороне кубика
	if (!(ants->count_road = (int *)malloc(sizeof(int) * size)))
		error("Not allocated memory");

	int remind = 0;

	i = -1;
	while (++i < forks)
	{
		int 	min = min_num(len_dist, size);
		int 	count_min = count_min_num(len_dist, min, size);
		if (!(ants->roads[i] = (char **)malloc(sizeof(char *) * count_min)))
			error("Not allocated memory");

		ants->count_road[i] = count_min;

		index_min = find_min_index(len_dist, count_min, min, size);
		int 	k = -1;
		while (++k < count_min)
		{
			ants->roads[i][k] = NULL;
			remind = index_min[k];
			ants->roads[i][k] = ft_strdup(distances[remind]);
			ants->length_road[i + k] = min;
//			ft_printf("\nDistance %i: %s  Length: %i", i + 1, ants->roads[i][k], ants->length_road[i + k]);
		}
		ft_strdel_int(&index_min);
	}
}

void	form_paths(t_ants *ants)
{
	int 	i;
	char 	**distances;

	distances = NULL;
	if (!(distances = (char **)malloc(sizeof(char *) * (ants->s_top[search(ants, search_startroom(ants))]).forwarders)))
		error("Not allocated memory");
	i = -1;
	while (++i < (ants->s_top[search(ants, search_startroom(ants))]).forwarders)
	{
 		distances[i] = NULL;
		distances[i] = ft_strdup((ants->s_top[search(ants, search_startroom(ants))]).room_name);
	}

	char 	*str;

	str = NULL;
	int 	*len_dist;
	len_dist = NULL;
	if (!(len_dist = (int *)malloc(sizeof(int) * (ants->s_top[search(ants, search_startroom(ants))].forwarders))))
		error("Not allocated memory");
	i = -1;
	while (++i < (ants->s_top[search(ants, search_startroom(ants))].forwarders))
		len_dist[i] = 2;

	int 	point_new;
	i = -1;

	while (++i < (ants->s_top[search(ants, search_startroom(ants))].forwarders))
	{
		str = ft_strdup((ants->s_top[search(ants, search_startroom(ants))]).room_name);
		point_new = search(ants, (ants->s_top[search(ants, search_startroom(ants))]).forward_to[i]);
		while ((ants->s_top[point_new]).forward_to[0] != NULL)
		{
			distances[i] = for_leaks(distances[i], ants, point_new);
			point_new = search(ants, (ants->s_top[point_new]).forward_to[0]);
			ft_strdel(&str);
			str = ft_strdup((ants->s_top[point_new]).room_name);
			len_dist[i] += 1;
		}
		distances[i] = for_leaks(distances[i], ants, search(ants, search_endroom(ants)));
		ft_strdel(&str);

		/*
		while (ft_strcmp(str, (ants->s_top[search(ants, search_endroom(ants))].room_name)))
		{
			distances[i] = for_leaks(distances[i], ants, point_new);
			if ((ants->s_top[point_new]).forward_to[0] != NULL)
				point_new = search(ants, (ants->s_top[point_new]).forward_to[0]);
			ft_strdel(&str);
			str = ft_strdup((ants->s_top[point_new]).room_name);
			len_dist[i] += 1;
		}
		distances[i] = for_leaks(distances[i], ants, search(ants, search_endroom(ants)));
		ft_strdel(&str);
		 */
	}


//	ft_printf("\n\nStep 9:\n");
	ft_write_roads(ants, distances, len_dist);
	i = -1;
	while (++i < (ants->s_top[search(ants, search_startroom(ants))].forwarders))
		ft_strdel(&distances[i]);
	free(distances);
	ft_strdel_int(&len_dist);

//	i = -1;
//	while (++i < (ants->s_top[search(ants, search_startroom(ants))].forwarders))
//		ft_printf("\nDistance %i: %s  Length: %i", i + 1, distances[i], len_dist[i]);

}

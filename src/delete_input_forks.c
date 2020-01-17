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

void	delete_forward_to(t_ants *ants, int i, int j) {
	int k;

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

//int		check_to_start(t_ants *ants, int point_before, int point_after)
//{
//	int 	i;
//	while (ft_strcmp(ants->s_top[point_before].room_name, "start"))
//	{
//		if ((ants->s_top[point_before]).output > 1)
//			return (1);
//		else
//		{
//			i = -1;
//			int 	neight = (ants->s_top[point_before]).count_neigh;
//			while (++i < neight)
//			{
//				int 	point;
//				point = search(ants, (ants->s_top[point_before]).neighbours[i]);
//				int 	c;
//				c = -1;
//				while (++c < (ants->s_top[point]).forwarders)
//					if (!ft_strcmp((ants->s_top[point]).forward_to[c], (ants->s_top[point_before]).room_name))
//						point_before = search(ants, (ants->s_top[point]).room_name);
//			}
//		}
//	}
//	return (0);
//}

char 	*for_leaks_vice(char *distance, t_ants *ants, int point_new)
{
	char 	*temp;
	char 	*temp_1;

	temp = ft_strdup(distance);
	ft_strdel(&distance);
	temp_1 = ft_strjoin("/", temp);
	ft_strdel(&temp);
	distance = ft_strjoin((ants->s_top[point_new]).room_name, temp_1);
	ft_strdel(&temp_1);
	return (distance);
}

/*
 * point_cur - текущая комната
 * point_before - комната, которую надо найти. Она должна быть соседом point_cur
 * и указывать на него. И was_here дб = 0, чтобы несколько раз не заходить в нее
 */

int 	check_neight(t_ants *ants, int point_before, int bool)
{
	int 	i;

	i = -1;
	while (++i < (ants->s_top[point_before]).count_neigh)
	{
		if ((ants->s_top[point_before]).neighbours[i] != NULL)
		{
			if (has_forward_to(ants, search(ants, (ants->s_top[point_before]).neighbours[i]), point_before) &&
					(ants->s_top[search(ants, (ants->s_top[point_before]).neighbours[i])]).was_here == 0)
			{
				point_before = search(ants, (ants->s_top[point_before]).neighbours[i]);
				if(bool == 1)
					(ants->s_top[point_before]).was_here = 1;
//				if (ft_strcmp((ants->s_top[point]).neighbours[i], search_startroom(ants)))
//					(ants->s_top[point_before]).was_here = 1;
				return (point_before);
			}
		}
	}
	return (-1);
}

//int 	check_neight(t_ants *ants, int point_cur, int *point_before)
//{
//	int 	i;
//	//Ищем соседа
//	i = -1;
//	while (++i < (ants->s_top[point_cur]).count_neigh)
//	{
//		if ((ants->s_top[point_cur]).neighbours[i] != NULL)
//		{
//			if (has_forward_to(ants, search(ants, (ants->s_top[point_cur]).neighbours[i]), point_cur)
//				&& (ants->s_top[search(ants, (ants->s_top[point_cur]).neighbours[i])]).was_here == 0)
//			{
//				*point_before = search(ants, (ants->s_top[point_cur]).neighbours[i]);
//				if (ft_strcmp((ants->s_top[point_cur]).neighbours[i], search_startroom(ants)))
//					(ants->s_top[*point_before]).was_here = 1;
//				return (1);
//			}
//		}
//	}
//	return (0);
//}

int 	find_min_dist_1(int *len_dist, int size)
{
	int 	i;
	int 	min;
	int 	index;

	index = 0;
	min = 10000000;
	i = -1;
	while (++i < size)
	{
		if (len_dist[i] < min && len_dist[i] != -1)
		{
			index = i;
			min = len_dist[i];
		}
	}
	return (index);
}


//void	delete_links(t_ants *ants, int point)
//{
//	int 	i;
//	int	point_new;
//	i = -1;
//
//	while (++i < (ants->s_top[point]).count_neigh)
//	{
//		if ((ants->s_top[point]).neighbours[i] == NULL)
//			continue ;
//		point_new = search(ants, (ants->s_top[point]).neighbours[i]);
//		if ((ants->s_top[point_new]).output > 1 && has_forward_to(ants, point_new, point))// && check_to_start(ants, point_new, point))
//		{
//			delete_forward_to(ants, point_new, point);
//			delete(ants, point_new, point, 0);
//			(ants->s_top[point_new]).output -= 1;
//			(ants->s_top[point]).input -= 1;
//		}
//	}
//
//
//	if ((ants->s_top[point]).input > 1)
//	{
//		while ((ants->s_top[point]).input > 1)
//		{
//			i = -1;
//			while (++i < (ants->s_top[point]).count_neigh)
//			{
//				point_new = search(ants, (ants->s_top[point]).neighbours[i]);
//				if (ft_strcmp((ants->s_top[point_new]).room_name, search_endroom(ants)))
//				{
//					delete_forward_to(ants, point_new, point);
//					delete(ants, point_new, point, 0);
//					(ants->s_top[point_new]).output -= 1;
//					(ants->s_top[point]).input -= 1;
//				}
//			}
//		}
//	}
//}

void	null_was_here(t_ants *ants)
{
	int i = -1;
	while (++i < ants->count_rooms)
		ants->s_top[i].was_here = 0;
}

void	delete_links(t_ants *ants, int point_cur)
{
	int 	i;
	int 	point_before;


	int 	input = (ants->s_top[point_cur]).input;
	int 	*len_dist; //Длина пути
	len_dist = NULL;
	if (!(len_dist = (int *)malloc(sizeof(int) * input))) //Длин столько сколько input'ов
		error("Not good!");

	char 	**distances; //Пути
	distances = NULL;
	if (!(distances = (char **)malloc(sizeof(char *) * input)))
		error("Not good!");

	i = -1;
	while (++i < input)
	{
		distances[i] = NULL;
		distances[i] = ft_strdup((ants->s_top[point_cur]).room_name);
		len_dist[i] = 1;
	}

	int 	save = point_cur;

//	if (!ft_strcmp((ants->s_top[point_cur]).room_name, "Nf_2"))
//		ft_printf("adw");

	null_was_here(ants);
//	ants->s_top[search(ants, search_startroom(ants))].was_here = 1;

	int 	bool = 0;
	i = -1;
	while (++i < input)
	{
		point_cur = save;
		point_before = check_neight(ants, point_cur, 1);
//		check_neight(ants, point_cur, &point_before);
		while (ft_strcmp(ants->s_top[point_before].room_name, search_startroom(ants)) && (ants->s_top[point_before]).input > 0)
		{
			if ((ants->s_top[point_before]).output > 1)
			{
				delete_forward_to(ants, point_before, point_cur);
				delete(ants, point_before, point_cur, 0);
				(ants->s_top[point_before]).output -= 1;
				(ants->s_top[point_cur]).input -= 1;

				len_dist[i] = -1;

				bool = 1;
				break ;
			}
			else
			{
				distances[i] = for_leaks_vice(distances[i], ants, point_before);
				len_dist[i] += 1;

				point_cur = point_before;
				point_before = check_neight(ants, point_before, 0);


//				check_neight(ants, point_before, &point_cur);
//				point_before = point_cur;
			}
		}
	}

	if (bool == 1 && (ants->s_top[save]).input <= 1)
	{
		i = -1;
		while (++i < input)
			ft_strdel(&distances[i]);
		free(distances);
		ft_strdel_int(&len_dist);
		return ;
	}
	int 	min_dist = find_min_dist_1(len_dist, input);

	char 	*temp;
	temp = NULL;

	char 	*str1;
	char 	*str2;

	i = -1;
	while (++i < input)
	{
		if (i == min_dist || len_dist[i] == 1 || len_dist[i] == -1)
			continue ;
		else
		{
			temp = distances[i];
			point_cur = save;
			while (ft_strcmp(temp, (ants->s_top[point_cur]).room_name))
			{
				str1 = ft_strsub(temp, 0, for_norm_count(temp, '/'));
				str2 = ft_strsub(temp + ft_strlen(str1) + 1, 0, for_norm_count(temp, '/'));
				delete_forward_to(ants, search(ants, str1), search(ants, str2));
				delete(ants, search(ants, str1), search(ants, str2), 1);
				(ants->s_top[search(ants, str1)]).output -= 1;
				(ants->s_top[search(ants, str2)]).input -= 1;
				temp = ft_strstr(temp, "/") + 1;
				ft_strdel(&str1);
				ft_strdel(&str2);
			}
		}
	}

	i = -1;
	while (++i < input)
		ft_strdel(&distances[i]);
	free(distances);
	ft_strdel_int(&len_dist);

}

void	delete_input_loop(t_ants *ants, t_queue *queue)
{
	int 	i;
	int 	j;
	int 	k;

	while (!is_empty_(queue))
	{
		j = search(ants, pop(queue));
		i = -1;
		while (++i < ((ants->s_top[j]).count_neigh))
		{
			if ((ants->s_top[j]).neighbours[i] == NULL)
				continue;
			k = search(ants, (ants->s_top[j]).neighbours[i]);
			if ((ants->s_top[k]).mark == 0 && ft_strcmp((ants->s_top[j]).room_name, (ants->s_top[search(ants, search_endroom(ants))]).room_name))
			{
				(ants->s_top[k]).mark = 1;
				push(queue, (ants->s_top[j]).neighbours[i]);

				if ((ants->s_top[k]).input > 1 && ft_strcmp((ants->s_top[k]).room_name, (ants->s_top[search(ants, search_endroom(ants))]).room_name))
					delete_links(ants, k);
			}
		}
	}
}

void	bfs_11(t_ants *ants, t_queue *queue)
{
	int 	i;

	(ants->s_top[search(ants, search_startroom(ants))]).mark = 1;
	i = -1;
	while (++i < (ants->s_top[search(ants, search_startroom(ants))]).count_neigh)
	{
		push(queue, (ants->s_top[search(ants, search_startroom(ants))]).neighbours[i]);
		ants->s_top[search(ants, (ants->s_top[search(ants, search_startroom(ants))]).neighbours[i])].mark = 1;
	}
}

void	delete_input_forks(t_ants *ants)
{
	int 	i;
	t_queue queue;

	init(&queue);
	mark_to_null(ants);
	bfs_11(ants, &queue);
	//расставляем веса
	delete_input_loop(ants, &queue);
	i = -1;
	while (queue.qu[++i] != NULL)
		ft_strdel(&queue.qu[i]);

//	Print
//	ft_printf("\n\nStep 7:\n");
//	i = -1;
//	int 	j;
//	while (++i < ants->count_rooms)
//	{
//		ft_printf("\nRoom: %-6s  Neighbours: ", (ants->s_top[i]).room_name);
//		j = -1;
//		while (++j < (ants->s_top[i]).count_neigh)
//			ft_printf("%-6s ", (ants->s_top[i]).neighbours[j]);
//	}
//
//	ft_printf("\n\n");
//	i = -1;
//	while (++i < ants->count_rooms)
//		ft_printf("Room: %-6s  Input: %-2d  Output: %-2d\n", (ants->s_top[i]).room_name, (ants->s_top[i]).input, (ants->s_top[i]).output);
//
//
//	i = -1;
//	while (++i < ants->count_rooms)
//	{
//		ft_printf("\nRoom: %-6s  forward_to: ", (ants->s_top[i]).room_name);
//		j = -1;
//		while (++j < (ants->s_top[i]).forwarders)
//			ft_printf("%-6s ", (ants->s_top[i]).forward_to[j]);
//	}
}


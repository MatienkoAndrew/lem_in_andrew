/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:04:29 by fgeruss           #+#    #+#             */
/*   Updated: 2019/09/11 18:57:25 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Создаем последующие комнаты
*/

t_room	*new_list(t_room **room)
{
	t_room	*n_list;

	n_list = NULL;
	if (!(n_list = (t_room *)malloc(sizeof(t_room))))
		error("Memory hasn't allocated");
	(*room)->next = n_list;
	n_list->is_start = 0;
	n_list->is_end = 0;
	n_list->count_neigh = 0;
	n_list->neight = NULL;
	n_list->room = NULL;
	n_list->next = NULL;
	return (n_list);
}

/*
** Создаем комнату - первый лист
*/

t_room	*new_room(t_room **room)
{
	if (!(*room = (t_room *)malloc(sizeof(t_room))))
		error("Memory hasn't allocated");
	(*room)->is_end = 0;
	(*room)->is_start = 0;
	(*room)->count_neigh = 0;
	(*room)->neight = NULL;
	(*room)->room = NULL;
	(*room)->next = NULL;
	return (*room);
}

/*
** Проверка комнат
** под каждую комнату создаем лист
** в комнату записываем название
** является ли она началом или концом
** и соседей каждой комнаты
*/

//int		valid_rooms(char *line, t_ants *ants, t_room *room)
int		valid_rooms(char *line, t_ants *ants, t_room *room, int fd)
{
	t_room	*start;

	start = room;
//	while (get_next_line(0, &line) > 0)
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n", line);
		while (line != NULL && line[0] == '#')
			check_sharp(&line, room, fd);
		if (line == NULL)
			return (1);
		if (parsing_room(line, room))
			for_norm(room, line);
		else if (parsing_tube(line) && not_exit_room(line, start))
		{
			if (!(nbr_neight(start, room, line, ants, fd)))
				return (0);
			break ;
		}
		else
			return (0);
		room = new_list(&room);
		ft_strdel(&line);
	}
	return (1);
}

/*
** Проверка на первую строчку
** в ней должно содержаться количество муравьев
*/

//int		valid_ants(char *line, t_ants *ants)
int		valid_ants(char *line, t_ants *ants, int fd)
{
	int			i;
	intmax_t	nbr;

	i = 0;
	nbr = 0;
//	get_next_line(0, &line);
	get_next_line(fd, &line);
	if (line[0] == '\0')
		return (0);
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) || line[i] == ' ' \
				|| (line[i] == '+' && line[i + 1] != '\0'
				&& ft_isdigit(line[i + 1])) \
				|| (i != 0 && ft_isdigit(line[i]) && ft_isdigit(line[i - 1])))
			i++;
		else
			return (0);
	}
	if ((nbr = ft_atoi_for_f(line)) > 2147483647)
		return (0);
	else
		ants->lem_count = nbr;
	ft_printf("%s\n", line);
	ft_strdel(&line);
	return (1);
}

int		validate(t_ants *ants, int fd)
{
	t_room	*room;
	char	*line;

	line = NULL;
	room = NULL;
	if (!valid_ants(line, ants, fd))
		return (0);
	room = new_room(&room);
	if (!valid_rooms(line, ants, room, fd))
		return (0);
	if (!check_dublicate(room, ants))
		error("Error: Dublicate room");
	if (!check_dublicate_coord(room))
		error("Dublicate coordinates");
	rewriting(room, ants);
	freer(room);
	room = NULL;
	ft_strdel(&line);
	return (1);
}

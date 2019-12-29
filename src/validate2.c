/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:03:22 by fgeruss           #+#    #+#             */
/*   Updated: 2019/09/11 19:00:29 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Соседи для первой строки
*/

int		first_attempt(t_room *start, t_room *room, char *line, int fd)
{
	char	*str1;
	char	*str2;

	while (*line == '#')
		check_sharp(&line, room, fd);
	if (parsing_tube(line) == 0 || not_exit_room(line, start) == 0)
		return (0);
	str1 = ft_strsub(line, 0, ft_tabpos(line, '-'));
	str2 = ft_strdup(ft_strchr(line, '-') + 1);
	room = start;
	while (room->next)
	{
		if (!(ft_strcmp(room->room, str1) && ft_strcmp(room->room, str2)))
		{
			if (!ft_strcmp(room->room, str2))
				room->neight[room->count_neigh++] = ft_strdup(str1);
			else if (!ft_strcmp(room->room, str1))
				room->neight[room->count_neigh++] = ft_strdup(str2);
		}
		room = room->next;
	}
	ft_strdel(&line);
	ft_strdel(&str1);
	ft_strdel(&str2);
	return (1);
}

/*
** Количество соседей
** и соседей записываем в двумерный массив
*/

int		nbr_neight(t_room *start, t_room *room, char *line, t_ants *ants, int fd)
{
	char	*str1;
	char	*str2;

	create_neighbours(start, ants);
	if (!(first_attempt(start, room, line, fd)))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n", line);
		while (line != NULL && *line == '#')
			check_sharp(&line, room, fd);
		if (line == NULL)
			return (1);
		if (parsing_tube(line) == 0 || not_exit_room(line, start) == 0)
			return (0);
		str1 = ft_strsub(line, 0, ft_tabpos(line, '-'));
		str2 = ft_strdup(ft_strchr(line, '-') + 1);
		if (!loop(start, str1, str2))
			return (0);
		ft_strdel(&line);
		ft_strdel(&str1);
		ft_strdel(&str2);
	}
	return (1);
}

/*
** Parsing "%s-%s"
*/

int		parsing_tube(char *line)
{
	char	*str;
	int		i;

	i = 0;
	if (ft_strstr(line, "-") == NULL)
		return (0);
	while (line[i] && line[i] != '-')
		if (ft_isalnum(line[i]) || line[i] == '_')
			i++;
		else
			return (0);
	if ((str = ft_strstr(line, "-") + 1) != NULL)
	{
		i = 0;
		while (str[i])
			if (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			else
				return (0);
	}
	else
		return (0);
	return (1);
}

/*
** Parsing "%s %d %d"
*/

int		parsing_room(char *line, t_room *room)
{
	char	*str;
	char	*dig1;
	char	*dig2;

	if ((str = ft_strstr(line, " ")) != NULL)
		for_norm_1(str, &dig1, &dig2);
	else
		return (0);
	room->x = ft_atoi(dig1);
	room->y = ft_atoi(dig2);
	free(dig1);
	return (1);
}

/*
** Проверка на #
*/

void	check_sharp(char **line, t_room *room, int fd)
{
	if (*(*line + 1) == '#')
	{
		if (ft_strstr(*line, "##start"))
			room->is_start = 1;
		else if (ft_strstr(*line, "##end"))
			room->is_end = 1;
	}
	else
	{
		ft_strdel(line);
		get_next_line(fd, line);
		ft_printf("%s\n", *line);
		return ;
	}
	ft_strdel(line);
	if (get_next_line(fd, line) <= 0)
		error("Invalid file");
	ft_printf("%s\n", *line);
}

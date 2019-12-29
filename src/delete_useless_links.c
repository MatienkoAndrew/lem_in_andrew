/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_useless_links.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 20:27:18 by fgeruss           #+#    #+#             */
/*   Updated: 2019/12/27 20:27:19 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		ft_rewrite_1(t_ants *ants, int i, char **temp, int k)
{
	int 	m;

	m = -1;
	while (++m < (ants->s_top[i]).count_neigh)
		ft_strdel(&(ants->s_top[i]).neighbours[m]);
	free((ants->s_top[i]).neighbours);
	(ants->s_top[i]).count_neigh = k;
	(ants->s_top[i]).neighbours = (char **)malloc(sizeof(char *) * (ants->s_top[i]).count_neigh);
	m = -1;
	while (++m < (ants->s_top[i]).count_neigh)
		(ants->s_top[i]).neighbours[m] = ft_strdup(temp[m]);
}


/*
** Переписываем массив
*/

void		ft_rewrite(t_ants *ants, int i)
{
	char 	**temp;
	int 	k;
	int 	m;

	temp = (char **)malloc(sizeof(char *) * (ants->s_top[i]).count_neigh);
	k = 0;
	m = -1;
	while (++m < (ants->s_top[i]).count_neigh)
	{
		if ((ants->s_top[i]).neighbours[m] == NULL)
			continue ;
		temp[k] = ft_strdup((ants->s_top[i]).neighbours[m]);
		k++;
	}
	ft_rewrite_1(ants, i, temp, k);
	m = -1;
	while (++m < (ants->s_top[i]).count_neigh)
		ft_strdel(&temp[m]);
	free(temp);
}

int 	has_neigh(t_ants *ants, int i, int j)
{
	int 	k;

	k = -1;
	while (++k < (ants->s_top[i]).count_neigh)
	{
		if ((ants->s_top[i]).neighbours[k] == NULL)
			continue ;
		if (ft_strcmp((ants->s_top[i]).neighbours[k], (ants->s_top[j]).room_name) == 0)
			return (1);
	}
	return (0);
}

void	delete(t_ants *ants, int i, int j, int bool)
{
	int 	k;

	k = -1;
	while (++k < (ants->s_top[i]).count_neigh)
	{
		if ((ants->s_top[i]).neighbours[k] == NULL)
			continue ;
		if (ft_strcmp((ants->s_top[i]).neighbours[k], (ants->s_top[j]).room_name) == 0)
			ft_strdel(&(ants->s_top[i]).neighbours[k]);
	}
	if (bool == 1)
		ft_rewrite(ants, i);
	//Delete second
	k = -1;
	while (++k < (ants->s_top[j]).count_neigh)
	{
		if ((ants->s_top[j]).neighbours[k] == NULL)
			continue ;
		if (ft_strcmp((ants->s_top[j]).neighbours[k], (ants->s_top[i]).room_name) == 0)
			ft_strdel(&(ants->s_top[j]).neighbours[k]);
	}
	ft_rewrite(ants, j);
}

void	delete_useless_links(t_ants *ants)
{
	int 	i;
	int 	j;

	i = -1;
	while (++i < ants->count_rooms)
	{
		j = -1;
		while (++j < ants->count_rooms)
			if (i != j && ((ants->s_top[i]).weight == (ants->s_top[j]).weight) && has_neigh(ants, i, j))
				delete(ants, i, j, 1);
	}


//	Print
	ft_printf("\nStep 3:\n");
	i = -1;
	while (++i < ants->count_rooms)
	{
		ft_printf("\nRoom: %-6s  Neighbours: ", (ants->s_top[i]).room_name);
		j = -1;
		while (++j < (ants->s_top[i]).count_neigh)
			ft_printf("%-6s ", (ants->s_top[i]).neighbours[j]);
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_dead_ends.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 21:58:13 by fgeruss           #+#    #+#             */
/*   Updated: 2019/12/27 21:58:14 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	delete_dead_ends(t_ants *ants)
{
	int 	i;
	int 	j;

	i = -1;
	while (++i < ants->count_rooms)
	{
		if ((((ants->s_top[i]).input == 0 && (ants->s_top[i]).output != 0) ||
			((ants->s_top[i]).output == 0 && (ants->s_top[i]).input != 0)) && \
			ft_strcmp((ants->s_top[i]).room_name, search_startroom(ants)) && \
			ft_strcmp((ants->s_top[i]).room_name, search_endroom(ants)))
		{
			int 	count = (ants->s_top[i]).count_neigh;
			j = -1;
			while (++j < count)
			{
				if ((ants->s_top[i]).neighbours[j] == NULL)
					continue ;
				if ((ants->s_top[search(ants, (ants->s_top[i]).neighbours[j])]).room_name != NULL)
					(ants->s_top[search(ants, (ants->s_top[i]).neighbours[j])]).output -= 1;
				delete_forward_to(ants, i, search(ants, (ants->s_top[i]).neighbours[j]));
				delete(ants, i, search(ants, (ants->s_top[i]).neighbours[j]), 0);
				(ants->s_top[i]).input -= 1;
			}
//			ft_rewrite(ants, i);
			(ants->s_top[i]).count_neigh -= j;
//			Отправляемся обратно с новыми данными
			i = -1;
		}
	}

//	Print
//	ft_printf("\nStep 6:\n");
//	i = -1;
//	while (++i < ants->count_rooms)
//	{
//		ft_printf("\nRoom: %-6s  Neighbours: ", (ants->s_top[i]).room_name);
//		j = -1;
//		while (++j < (ants->s_top[i]).count_neigh)
//		{
//			ft_printf("%-6s ", (ants->s_top[i]).neighbours[j]);
//		}
//	}
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
//
//	ft_printf("\n\n");
}

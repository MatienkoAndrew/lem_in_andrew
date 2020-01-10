/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 21:05:13 by fgeruss           #+#    #+#             */
/*   Updated: 2019/12/27 21:05:14 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
 * Если у соседа вес больше на единицу
 * то у соседа input += 1
 * а у самой комнаты output += 1
 */

void 	align_links(t_ants *ants)
{
	int 	i;
	int 	j;

	i = -1;
	while (++i < ants->count_rooms)
	{
		j = -1;
		while (++j < (ants->s_top[i]).count_neigh)
		{
			if ((ants->s_top[i]).neighbours[j] == NULL)
				continue ;
			if (((ants->s_top[search(ants, (ants->s_top[i]).neighbours[j])]).weight > (ants->s_top[i]).weight) \
				&& (ants->s_top[i]).weight != -1)// == 1)
			{
				(ants->s_top[search(ants, (ants->s_top[i]).neighbours[j])]).input += 1;
				(ants->s_top[i]).output += 1;
			}
		}
	}



//	Print
//	ft_printf("\n\nStep 5: \n\nOutput/Input:\n");
//	i = -1;
//	while (++i < ants->count_rooms)
//		ft_printf("Room: %-6s  Input: %-2d  Output: %-2d\n", (ants->s_top[i]).room_name, (ants->s_top[i]).input, (ants->s_top[i]).output);
}

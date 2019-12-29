/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientir_graph.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 21:34:34 by fgeruss           #+#    #+#             */
/*   Updated: 2019/12/27 21:34:35 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	orientir_graph(t_ants *ants)
{
	int 	i;
	int 	j;
	int 	k;

	i = -1;
	while (++i < ants->count_rooms)
	{
		if (!((ants->s_top[i]).forward_to = (char **)malloc(sizeof(char *) * (ants->s_top[i]).count_neigh)))
			error("Not allocated memory");
		j = -1;
		while (++j < (ants->s_top[i]).count_neigh)
			(ants->s_top[i]).forward_to[j] = NULL;
		k = 0;
		j = -1;
		while (++j < (ants->s_top[i]).count_neigh)
		{
			if (((ants->s_top[search(ants, (ants->s_top[i]).neighbours[j])]).weight > (ants->s_top[i]).weight) \
					&& (ants->s_top[i]).weight != -1)
				(ants->s_top[i]).forward_to[k++] = ft_strdup((ants->s_top[search(ants, (ants->s_top[i]).neighbours[j])]).room_name);
		}
		(ants->s_top[i]).forwarders = k;
	}


	//	Print
	ft_printf("\n\nStep 4: \n\nOrientir graph:\n");
	i = -1;
	while (++i < ants->count_rooms)
	{
		ft_printf("\nRoom: %-6s  forward_to: ", (ants->s_top[i]).room_name);
		j = -1;
		while (++j < (ants->s_top[i]).forwarders)
			ft_printf("%-6s ", (ants->s_top[i]).forward_to[j]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_memory_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:43:04 by asusan            #+#    #+#             */
/*   Updated: 2019/11/22 16:43:05 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_info(t_ants *ants)
{
	int	i;
	int	j;

	i = -1;
	while (++i != ants->count_rooms)
	{
		j = -1;
		while (++j != ants->s_top[i].count_neigh)
			ft_strdel(&ants->s_top[i].neighbours[j]);
		free(ants->s_top[i].neighbours);
		ants->s_top[i].neighbours = NULL;
		j = -1;
		while (++j < ants->s_top[i].forwarders)
			ft_strdel(&ants->s_top[i].forward_to[j]);
		free(ants->s_top[i].forward_to);
		ants->s_top[i].forward_to = NULL;
		ft_strdel(&ants->s_top[i].room_name);
		ft_strdel(&ants->s_top[i].real_name);
		ft_strdel(&ants->s_top[i].name_ant_in_flat);
		ft_strdel(&ants->s_top[i].his_road);
		ft_strdel_int(&ants->s_top[i].from_to);
	}
	free(ants->s_top);
	ants->s_top = NULL;
	//free_road(ants);
	i = -1;
	while (++i != ants->special_for_end_int)
		free(ants->special_for_end[i]);
	free(ants->special_for_end);
	free(ants->count_road);
}

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

	char 	*str = ft_strdup((ants->s_top[search(ants, search_startroom(ants))]).room_name);
	int 	point_new;
	i = -1;
	while (++i < (ants->s_top[search(ants, search_startroom(ants))].forwarders))
	{
		str = ft_strdup((ants->s_top[search(ants, search_startroom(ants))]).room_name);
		point_new = search(ants, (ants->s_top[search(ants, search_startroom(ants))]).forward_to[i]);
		while (ft_strcmp(str, (ants->s_top[search(ants, search_endroom(ants))].room_name)))
		{
			distances[i] = ft_strjoin(distances[i], "/");
			distances[i] = ft_strjoin(distances[i], (ants->s_top[point_new]).room_name);
			if ((ants->s_top[point_new]).forward_to[0] != NULL)
				point_new = search(ants, (ants->s_top[point_new]).forward_to[0]);
			str = ft_strdup((ants->s_top[point_new]).room_name);
		}
		distances[i] = ft_strjoin(distances[i], "/");
		distances[i] = ft_strjoin(distances[i], (ants->s_top[search(ants, search_endroom(ants))]).room_name);
		ft_strdel(&str);
	}


	ft_printf("\n\nStep 9:\n");
	i = -1;
	while (++i < (ants->s_top[search(ants, search_startroom(ants))].forwarders))
		ft_printf("\nDistance %i: %s", i, distances[i]);

}

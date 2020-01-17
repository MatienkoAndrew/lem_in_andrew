/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:38:14 by fgeruss           #+#    #+#             */
/*   Updated: 2019/08/31 17:39:26 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void   change_real_name_1(t_ants *ants, char *start, char *end, int i)
{
	if (ft_strcmp(ants->s_top[i].room_name, end) == 0)
	{
		free(ants->s_top[i].room_name);
		ants->s_top[i].room_name = ft_strdup("end");
	}
	else if (ft_strcmp(ants->s_top[i].room_name, start) == 0)
	{
		free(ants->s_top[i].room_name);
		ants->s_top[i].room_name = ft_strdup("start");
	}
}
void   change_real_name(t_ants *ants)
{
	t_norm a;
	a.end = ft_strdup(search_endroom(ants));
	a.start = ft_strdup(search_startroom(ants));
	a.i = -1;
	while (++a.i != ants->count_rooms)
	{
		change_real_name_1(ants, a.start, a.end, a.i);
		a.j = -1;
		while (++a.j != (ants->s_top[a.i]).count_neigh)
		{
			if (ft_strcmp(ants->s_top[a.i].neighbours[a.j], a.end) == 0)
			{
				free(ants->s_top[a.i].neighbours[a.j]);
				ants->s_top[a.i].neighbours[a.j] = ft_strdup("end");
			}
			else if (ft_strcmp(ants->s_top[a.i].neighbours[a.j], a.start) == 0)
			{
				free(ants->s_top[a.i].neighbours[a.j]);
				ants->s_top[a.i].neighbours[a.j] = ft_strdup("start");
			}
		}
	}
	ft_strdel(&a.end);
	ft_strdel(&a.start);
}

int		main(int argc, char **argv)
{
	t_ants	ants;

//	argv = 0;
	argc = 0;

	int fd = open(argv[1], O_RDONLY);

	init_val(&ants);
	if (!validate(&ants, fd))
//	if (!validate(&ants, 0))
		error("Input isn't valid!");
	ft_printf("\n");

	change_real_name(&ants);

//	Step_2
	bfs(&ants);
//	Step 3
	delete_useless_links(&ants);
//	Step 4
	orientir_graph(&ants);
//	Step 5
	align_links(&ants);
//	Step 6
	delete_dead_ends(&ants);
//	Step 7
	delete_input_forks(&ants);

	delete_dead_ends(&ants);
//	Step 8
	delete_output_forks(&ants);

//	delete_dead_ends(&ants);
//	Step 9
	form_paths(&ants);
//	ft_printf("\n\n");
//	Step 10
	move_ants(&ants);

	free_info(&ants);
	return (0);
}

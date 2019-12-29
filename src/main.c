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

int		main(int argc, char **argv)
{
	t_ants	ants;
//	int		stat;

//	argv = 0;
	argc = 0;

	int fd = open(argv[1], O_RDONLY);

	init_val(&ants);
	if (!validate(&ants, fd))
		error("Input isn't valid!");
	ft_printf("\n");

//	Step_2
	bfs(&ants);
//	Step_3D
	delete_useless_links(&ants);
//	Step 4
	orientir_graph(&ants);
//	Step 5
	align_links(&ants);
//	Step 6
	delete_dead_ends(&ants);
//	Step 7
	delete_input_forks(&ants);
//	Step 8
	delete_output_forks(&ants);
//	Step 9
	form_paths(&ants);

//	for_functions(&ants, &stat);
	free_info(&ants);
	return (0);
}

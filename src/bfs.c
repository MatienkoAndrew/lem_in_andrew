/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:40:46 by fgeruss           #+#    #+#             */
/*   Updated: 2019/09/15 14:40:48 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**  Поиск в ширину
*/

void        bfs(t_ants *ants)
{
    t_queue		queue;
    int 		i = -1;

    init(&queue);

    weight_to_null(ants);

	(ants->s_top[search(ants, search_startroom(ants))]).weight = 0;
	(ants->s_top[search(ants, search_startroom(ants))]).mark = 1;

    //засунули соседей в очередь
    while (++i < (ants->s_top[search(ants, search_startroom(ants))]).count_neigh)
    {
        push(&queue, (ants->s_top[search(ants, search_startroom(ants))]).neighbours[i]);
        ants->s_top[search(ants, (ants->s_top[search(ants, search_startroom(ants))]).neighbours[i])].weight = 1;
		ants->s_top[search(ants, (ants->s_top[search(ants, search_startroom(ants))]).neighbours[i])].mark = 1;
    }

    //расставляем веса
    while (!is_empty_(&queue))
    {
        int 	j = search(ants, pop(&queue));
        i = -1;
        while (++i < ((ants->s_top[j]).count_neigh))
        {
            int 	k = search(ants, (ants->s_top[j]).neighbours[i]);
            if ((ants->s_top[k]).mark == 0 && ft_strcmp((ants->s_top[j]).room_name, (ants->s_top[search(ants, search_endroom(ants))]).room_name))
            {
                int 	m = search(ants, (ants->s_top[j]).neighbours[i]);
                (ants->s_top[m]).mark = 1;
                (ants->s_top[m]).weight = (ants->s_top[j]).weight + 1;
                push(&queue, (ants->s_top[j]).neighbours[i]);
            }
        }
    }
	i = -1;
	while (queue.qu[++i] != NULL)
		ft_strdel(&queue.qu[i]);

	//End = INF
	ants->s_top[search(ants, search_endroom(ants))].weight = 100000000;

    ft_printf("\nStep 2:\n");
    i = -1;
	while (++i < ants->count_rooms)
		ft_printf("Room: %-6s  \tWeight: %-6i\n", (ants->s_top[i]).room_name, (ants->s_top[i]).weight);
}

char	*pop(t_queue *q)
{
	char	*x;

	if (is_empty_(q) == 1)
		ft_printf("Queue is null");
	x = q->qu[q->first];
	q->first++;
	return (x);
}

int		search(t_ants *ants, char *room_name)
{
	int	i;

	i = -1;
	while (++i < ants->count_rooms)
		if (ft_strcmp((ants->s_top[i]).room_name, room_name) == 0)
			return (i);
	return (0);
}

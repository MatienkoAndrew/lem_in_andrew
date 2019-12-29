/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 14:53:15 by fgeruss           #+#    #+#             */
/*   Updated: 2019/11/15 18:26:20 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/ft_printf.h"
# include <fcntl.h>

typedef struct		s_top
{
	char			*real_name;
	char			*room_name;
	char			**neighbours;
	int				*from_to;
	int				count_neigh;
	int				start;
	int				end;
	int				for_bell;
	int				helper;
	int				for_in_out;
	char			*name_ant_in_flat;
	char			*his_road;
	int				weight;
	int				mark;
	int				bellman_was_here;


	int 			input;
	int 			output;
	char 			**forward_to;
	int 			forwarders;
}					t_top;

typedef	struct		s_ants
{
	int				reverse_lem;
	char			**special_for_end;
	int				special_for_end_int;
	t_top			*s_top;
	int				lem_count;
	int				count_rooms;
	char			***road;
	int				count_road_variable;
	int				*count_road;
	int				min_road;
	int				lem_in_house;
	int				helper;
	int				gl_help;
	int				gl_help_1;
	int				gl_help_2;
}					t_ants;

typedef struct		s_queue
{
	char			*qu[100000];
	int				first;
	int				end;
}					t_queue;

typedef struct		s_three_int
{
	int				i;
	int				j;
	int				count;
	int				k;
	int				ch;
	int				x;
	int				y;
	int				twins;
	int				m;
	int				mk;
	int				for_roading;
	int				count_func;
	char			*room_name;
}					t_three_int;

typedef struct		s_zaeb
{
	int				number;
	struct s_zaeb	*next;
}					t_zaeb;

typedef struct		s_room
{
	char			*room;
	char			*real;
	int				is_start;
	int				is_end;
	int				count_neigh;
	int				x;
	int				y;
	char			**neight;
	struct s_room	*next;
}					t_room;

typedef struct		s_norm
{
	int				i;
	int				j;
	int				k;
	int				m;
	int				res;
	int				bool;
	char			*end;
	char			*start;
}					t_norm;

/*
**=================File validate.c===========================
*/

t_room				*new_list(t_room **room);
t_room				*new_room(t_room **room);
//int					valid_rooms(char *line, t_ants *ants, t_room *room);
int		valid_rooms(char *line, t_ants *ants, t_room *room, int fd);
//int					valid_ants(char *line, t_ants *ants);
//int					validate(t_ants *ants);
int		valid_ants(char *line, t_ants *ants, int fd);
int		validate(t_ants *ants, int fd);
/*
**===========================================================
*/

/*
**=================File validate1.c===========================
*/

void				error(char *str);
void				freer(t_room *room);
void				create_neighbours(t_room *room, t_ants *ants);
int					nbr_rooms(t_room *start);
void				init_val(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File validate2.c===========================
*/

//int					first_attempt(t_room *start, t_room *room, char *line);
int		first_attempt(t_room *start, t_room *room, char *line, int fd);
//int					nbr_neight(t_room *start, t_room *room, char *line,
//		t_ants *ants);

int		nbr_neight(t_room *start, t_room *room, char *line, t_ants *ants, int fd);
int					parsing_tube(char *line);
int					parsing_room(char *line, t_room *room);
//void				check_sharp(char **line, t_room *room);
void	check_sharp(char **line, t_room *room, int fd);

/*
**===========================================================
*/

/*
**=================File validate3.c===========================
*/

int					check_dublicate(t_room *room, t_ants *ants);
void				mem_neight(t_room *start, t_ants *ants);
void				rewriting(t_room *start, t_ants *ants);
void				initialize_s_top(t_top *top);

/*
**===========================================================
*/

/*
**=================File bfs.c===========================
*/

void				bfs(t_ants *ants);
char				*pop(t_queue *q);
int					search(t_ants *ants, char *room_name);

/*
**===========================================================
*/

/*
**=================File for_norm.c===========================
*/

//void				loop(t_room *room, char *str1, char *str2);
int					loop(t_room *room, char *str1, char *str2);
int					check_dublicate_coord(t_room *room);
int					for_norm_1(char *str, char **dig1, char **dig2);
int					for_norm_count(char *str, char pr);
void				for_norm(t_room *room, char *line);

/*
**===========================================================
*/

/*
**=================File for_norm_1.c===========================
*/

int					not_exit_room(char *line, t_room *room);
int					for_norm_2(t_room *room, t_ants *ants, char	**unique);





/*
**=================File bfs_1.c===========================
*/

void				weight_to_null(t_ants *ants);
void				init(t_queue *q);
void				push(t_queue *q, char *x);
int					is_empty_(t_queue *q);

/*
**===========================================================
*/

/*
**=================File bfs_up.c===========================
*/

char				*search_startroom(t_ants *ants);
char				*search_endroom(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File for_memory_2.c===========================
*/

void				free_info(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File other_help.c===========================
*/

size_t				ft_tabpos(const char *line, char ch);

/*
**===========================================================
*/

/*
**=================File reverse_road.c===========================
*/

void				mark_to_null(t_ants *ants);

/*
**===========================================================
*/


void				delete_useless_links(t_ants *ants);
void 				align_links(t_ants *ants);
void				orientir_graph(t_ants *ants);
void				delete_dead_ends(t_ants *ants);
void				delete(t_ants *ants, int i, int j, int bool);
void				delete_input_forks(t_ants *ants);
int 				has_neigh(t_ants *ants, int i, int j);
void				delete_forward_to(t_ants *ants, int i, int j);
void				delete_output_forks(t_ants *ants);
void				form_paths(t_ants *ants);

#endif

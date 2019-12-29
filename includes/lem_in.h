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


//Delete
#include "stdio.h"

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
void				installer_bfs(int *i, int *j, int val_1, int val_2);
void				helper_for_bfs(t_three_int t, t_ants *ants, t_queue *queue);

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
**===========================================================
*/

/*
**=================File change_real_name.c===========================
*/

void				change_real_name_1(t_ants *ants, char *start,
		char *end, int i);
void				change_real_name(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File algos.c===========================
*/

int					helper(t_ants *ants);
void				print_dist_2(t_ants *ants, int *i, int *j);
void				print_dist_1(t_ants *ants, int **ptr, int *c);
void				print_dist(t_ants *ants);
void				algos(t_ants *ants, int *stat);

/*
**===========================================================
*/

/*
**=================File algos_1.c===========================
*/

int					function_help_1(t_ants *ants, t_norm *a);
int					function_help(t_ants *ants, t_norm *a);
void				function_4_1(t_ants *ants, t_norm *a);
void				for_functions(t_ants *ants, int *stat);
void				algos_1(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File suurballe.c===========================
*/

void				suurballe(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File another_rev.c===========================
*/

void				another_rev(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File bell_ford.c===========================
*/

int					bell_ford(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File bfs_1.c===========================
*/

void				weight_to_null(t_ants *ants);
void				bfs_1(t_ants *ants, int index);
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
void				helper_for_bfs_up(t_ants *ants,
		t_queue *queue, t_three_int t);
void				helper_for_bfs_up_1(t_ants *ants,
		t_queue *queue, t_three_int t);
void				bfs_up(t_ants *ants);

/*
**===========================================================
*/

///*
//**=================File copy.c===========================
//*/
//
//int					*copy_int(const int *arr, int max);
//void				copy(int **res, const int *res_two, int i);
//char				**copy_double(char **arr, int count);
//void				instal(int *i, int *temp);
//char				**ft_copy(char **arr, int count);

/*
**===========================================================
*/

/*
**=================File counters.c===========================
*/

int					count(t_ants *ants);
int					next_lvl_count(const int *ptr, int val);
int					count_dist(t_ants *ants, t_top array);
int					count_dist_228(t_ants *ants, int ind);
void				new_count(int **arr, int val, int variable);

/*
**===========================================================
*/

/*
**=================File double_arr.c===========================
*/

void				inst_for_fresh(int *i, char ****temp, t_ants *ants);
void				func_for_fresh_double(t_ants *ants, char *road);
void				free_double(char ***arr, int count);
char				**fresh_memory_road(char **arr, char *temp, int road_count);

/*
**===========================================================
*/

/*
**=================File find_road.c===========================
*/

int					local_helper(int **ptr, int **temp,
		t_ants *ants, t_three_int t);
int					helper_for_find_road(int **ptr, int **temp,
		t_ants *ants, t_three_int t);
void				installer_for_find_road(int **ptr,
								t_three_int *t, t_three_int a, t_ants *ants);
int					find_norm_road(t_ants *ants, t_three_int a, int **ptr);
int					logic_val_for_search(t_ants *ants, t_three_int *t);

/*
**===========================================================
*/

/*
**=================File finders.c===========================
*/

int					find_last_slash(char *stack);
int					find_count_slash(const char *arr);
int					find_this_line(char **arr, char *temp, int count_rown);
int					find_neigh_with_helper(t_ants *ants, int index);
int					finder_more_weight(t_ants *ants, int m, int weight);

/*
**===========================================================
*/

/*
**=================File foo.c===========================
*/

int					helper_for_foo(t_ants *ants, t_three_int t,
		char **temp, char *road);
int					helper_for_foo_1(char *road, t_three_int t,
		t_ants *ants, char **temp);
int					helper_for_foo_2(char *road, t_three_int t,
		t_ants *ants, char **temp);
int					is_check_foo(t_ants *ants, t_three_int t,
					const char *temp, const char *road);
int					foo(t_ants *ants, char *road);

/*
**===========================================================
*/

/*
**=================File for_memory.c===========================
*/

void				inst_for_fresh_memory_3(t_three_int *t,
		t_ants *ants, int number_1);
void				fresh_memory_road3(t_ants *ants,
		int number_1, int number_2);
void				helper_for_free_road(t_three_int *t);
int					helper_for_free_road_1(t_three_int *t,
		int **ptr, t_ants *ants);
void				func_for_free_road(t_ants *ants, int *ptr);

/*
**===========================================================
*/

/*
**=================File for_memory_1.c===========================
*/

void				ft_free(char ***arr, int count);
char				**new_install(char **arr, int j);
void				to_null(t_ants *ants);
char				*ret(char *arr);
void				base_setup_for_helper(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File for_memory_2.c===========================
*/

void				free_info(t_ants *ants);
void				free_for_search_1(char ***roads,
		t_three_int *t, char **distance, char **temping);
void				helper_to_null(t_ants *ants);
int					not_null_pos(char **arr, int count);
void				free_temp(char ***temp, t_ants *ants);

/*
**===========================================================
*/

/*
**=================File for_memory_3.c===========================
*/

void				free_road(t_ants *ants);
char				**inst_for_search_228(t_three_int *t, int i, t_ants *ants);
void				little_helper_for_search_228(t_three_int *t,
		t_ants *ants, char **distance);
void				bellman_to_null(t_ants *ants);
int					logic_func_for_foo(t_ants *ants,
		t_three_int t, const char *road);

/*
**===========================================================
*/

/*
**=================File go_ants.c===========================
*/

void				inst_for_go_ants(t_three_int *t, int index,
		int **reserved_two, int c);
void				cycle_inst(t_three_int *t, t_ants ants, int index);
void				for_go_ants(t_ants *ants, t_three_int *t,
		int **ptr, int index);
void				inside_go_ants(t_ants *ants, t_three_int *t,
		int **ptr, int **reserved_two);
int					go_ants(t_ants ants, int index, int **ptr, int c);

/*
**===========================================================
*/

/*
**=================File minimum_roads.c===========================
*/

void				minimum_roads(t_ants *ants, int *stat);

/*
**===========================================================
*/

/*
**=================File other_help.c===========================
*/

size_t				ft_tabpos(const char *line, char ch);
char				*reter_1(t_ants *ants, char *stack);
char				*little_help(int *tmp, t_ants *ants,
		char *stack, int count_slash);
void				inst_zero(int **remember, int count, int val);
void				inst_is_twins_two(t_three_int *t,
		const char **s1, const char **s2);

/*
**===========================================================
*/

/*
**=================File other_help_1.c===========================
*/

int					helper_for_is_twins(const char *s1,
		const char *s2, t_three_int *t);
int					is_twins_two(const char *s1, const char *s2);
int					cont(const int *arr, int c);
int					return_count_road(const int *arr, int i);
int					foo_2(const char *arr);

/*
**===========================================================
*/

/*
**=================File other_help_2.c===========================
*/

void				inst_in_t_three(t_three_int *t);
void				helper_for_is_not_good_road(t_three_int *t,
									t_ants ants, char **temp, int index);
int					is_not_good_road(t_ants ants, int index);
int					return_count_slash(t_ants ants, int i);
int					helper_for_record_2(t_ants *ants,
		t_three_int t, char **temp, const char *next_info);

/*
**===========================================================
*/

/*
**=================File other_help_3.c===========================
*/

int					is_empty(t_ants ants, const char *road);
int					is_after(const char *road, const char *room_name);
char				*ft_strstr_up(char *s1, char *s2);
void				first_inst_for_foo(t_three_int *t);
char				*counter_for_foo(t_three_int *t, const char *road);

/*
**===========================================================
*/

/*
**=================File other_help_4.c===========================
*/

int					you_can(t_ants *ants, int mm);
int					my_neigh_is_start(t_ants *ants, int m);
void				install_t_all_elem(t_three_int *t);
int					check_lem(t_ants *ants, const int *ptr);
int					is_twins_four(t_ants *ants, const int *ptr, int x, int y);

/*
**===========================================================
*/

/*
**=================File other_help_5.c===========================
*/

int					dont_find_one(t_ants *ants, int m);
void				ff(char **roads, t_ants *ants, char ***temp, t_three_int t);
void				fff(t_three_int *t, t_ants *ants,
		char **roads, char ***temp);
int					neigh_up(t_ants *ants, int m, int index);
void				inst_for_finder(t_three_int *t, t_ants *ants, int m);

/*
**===========================================================
*/

/*
**=================File other_help_6.c===========================
*/

int					helper_for_tresh_triple(char **roads, int count);
char				***reter_triple(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File record.c===========================
*/

int					helper_for_record(t_ants *ants,
		const char *next_info, char **temp, char ***doble);
void				installer_for_record(char **temp,
		char *position, t_three_int *t, const char **road);
int					helper_for_record_1(t_ants *ants,
		const char *road, t_three_int t, char **temp);
void				little(char **arr, const char *next_info);
int					record(t_ants *ants, const char *road,
		char *position, const char *next_info);

/*
**===========================================================
*/

/*
**=================File reverse_road.c===========================
*/

void				mark_to_null(t_ants *ants);
void				inst_way(t_ants *ants);
void				installer_for_reverce_min_road(t_three_int *t,
		t_ants *ants, t_zaeb **zaeb, t_zaeb **temp);
void				logic_for_reverse(t_ants *ants,
		t_three_int t, int k, t_zaeb **zaeb);
void				reverse_min_road(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File road_to_end.c===========================
*/

void				helper_for_road_to_end(char *temp,
		t_ants *ants, int count_slash, int tmp);
void				helper_for_road_to_end_1(char ***dobl,
		t_ants *ants, char *temp);
int					f(char *stack, t_ants *ants, int *tmp, char **temp);
int					f_1(t_ants *ants, char *temp, int tmp);
char				*road_to_end(t_ants *ants, char *arr,
		char *stack, int count_slash);

/*
**===========================================================
*/

/*
**=================File search_road_1.c===========================
*/

void				little_help_search_1(t_three_int *t, char *distance);
char				**installer_search_1(t_three_int *t,
		char **temping, char *distance, t_ants *ants);
void				little_help_search_1_1(t_ants *ants,
		t_three_int *t, char **distance, char *temping);
void				little_help_search_1_2(int *i,
		t_ants *ants, t_three_int *t);
void				search_some_roads_1(t_ants *ants,
		char *distance, int i);

/*
**===========================================================
*/

/*
**=================File search_road_1_2.c===========================
*/

void				installer_for_search_road_1(t_three_int *t,
									t_ants *ants, char **distance);

void				helper_for_memory_search_roads_2(t_ants *ants,
		char *distance);
void				helper_f_search_1(t_ants *ants,
		t_three_int *t, char **distance, char *temping);
int					helper_for_search_1(t_ants *ants,
		t_three_int *t, char **distance, char ***roads);
void				helper_for_memory_search_roads_1(t_ants *ants,
		char **roads, int count_branching);

/*
**===========================================================
*/

/*
**=================File search_road_1_3.c===========================
*/

int					helper_for_search_road_1(t_ants *ants,
		t_three_int *t, char **distance);
void				helper_for_helper_memory(int *tr,
		t_ants *ants, int i, char *distance);
int					helper_for_search_road_1_1(t_ants *ants,
		t_three_int *t, char **distance);
void				helper_for_search_road_1_2(t_three_int *t,
		t_ants *ants, char **distance);
int					search_road_1(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File search_road_228.c===========================
*/

void				free_for_search_228(t_three_int *t,
		char ***roads, char **distance, char **temping);
void				helper_for_search_228_2(t_ants *ants,
		t_three_int *t, char **distance, char *temping);
void				free_for_search_228_1(t_three_int *t,
		char ***roads, char **distance, char **temping);
void				helper_for_search_228_3(t_three_int *t,
		char **distance, char **temping);
void				search_some_roads_228(t_ants *ants,
		char **distance, int i);

/*
**===========================================================
*/

/*
**=================File search_road_228_1.c===========================
*/

void				helper_for_search_228(t_three_int *t,
		t_ants *ants, char **distance, char ***roads);
void				helper_for_search_228_1(t_three_int *t,
		char **distance, t_ants *ants, char ***roads);
void				helper_for_search_road_228(t_ants *ants,
		int i, char **distance, char **room_name);
int					search_road_228(t_ants *ants);

/*
**===========================================================
*/

/*
**=================File triple_arr.c===========================
*/

void				func_for_fresh_triple(t_ants *ants,
		char **roads, int count);
void				inst_for_copy_triple(int *i, int *j);
char				***reter_triple_arr(t_ants *ants, int pos);
void				free_triple(char ****arr,
		int count_road_variable, const int *count_road);
void				copy_triple_arr(t_ants *ants, int pos);

/*
**===========================================================
*/

/*
**=================File main.c===========================
*/

int					find_neigh(t_ants *ants, int from, char *neigh);
void				only_reverse_road(t_ants *ants);

/*
**===========================================================
*/



void				delete_useless_links(t_ants *ants);
void 				align_links(t_ants *ants);
void				orientir_graph(t_ants *ants);
void				delete_dead_ends(t_ants *ants);
void				delete(t_ants *ants, int i, int j);
void				delete_input_forks(t_ants *ants);
int 				has_neigh(t_ants *ants, int i, int j);
void				delete_forward_to(t_ants *ants, int i, int j);
void				delete_output_forks(t_ants *ants);
void				form_paths(t_ants *ants);

#endif

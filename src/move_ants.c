/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 20:56:36 by fgeruss           #+#    #+#             */
/*   Updated: 2019/12/29 20:56:38 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int find_count_slash(const char *arr)
{
	int i = 0;
	int count = 0;
	while (arr[i] != '\0')
	{
		if (arr[i] == '/')
			count++;
		i++;
	}
	return (count);
}
void inst_zero(int **remember, int count, int val)
{
	int i = 0;
	while (i != count)
		(*remember)[i++] = val;
}
int cont(const int* arr, int c)
{
	int i = 0;
	int count = 0;
	while (i != c)
	{
		if (arr[i] == 1)
			count++;
		i++;
	}
	return (count);
}
int go_ants(t_ants ants, int **ptr, int c)
{
	int i;
	int x = 0;
	int m;
	int count = 0;
	if (ants.lem_in_house < 0)
		return (0);
	int *temp = (int*)malloc(sizeof(int) * c);
	inst_zero(&temp, c, -1);
	int sum = 0;
	int j;
	i = 0;
	ants.lem_in_house--;
	while (i != ants.count_road_variable)
	{
		m = find_count_slash(ants.roads[i][0]);
		x = 0;
		while (x != ants.count_road[i])
		{
			j = 0;
			sum = 0;
			if (i == 0)
				(*ptr)[count++] = 1;
			else
				while (temp[j] != -1)
				{
					sum += (m - temp[j]);
					j++;
				}
			if (sum <= ants.lem_in_house && i != 0)
			{
				ants.lem_in_house--;
				(*ptr)[count++] = 1;
			}
			x++;
		}
		temp[i] = m;
		i++;
	}
	free(temp);
	return (cont(*ptr, c));
}
int foo_2(const char *arr)
{
	int i = 0;
	++i;
	while (arr[i] != '/' && arr[i] != '\0')
		i++;
	return (i);
}
char **ft_copy(char **arr, int count)
{
	int i = 0;
	char **new_arr;
	int temp = 0;
	while (i != count)
		if (arr[i++] == NULL)
			temp++;
	new_arr = (char**)malloc(sizeof(char*) * (count - temp));
	temp = 0;
	i = 0;
	while (i != count)
	{
		if (arr[i] != NULL)
		{
			new_arr[temp] = ft_strdup(arr[i]);
			temp++;
		}
		i++;
	}
	return (new_arr);
}
void ft_free(char ***arr, int count)
{
	int i = 0;
	while (i != count)
		free((*arr)[i++]);
	free(*arr);
}
char **new_install(char **arr, int j)
{
	char **temp;
	int i = 0;
	temp = (char**)malloc(sizeof(char*) * j);
	while (i != j - 1)
	{
		temp[i] = ft_strdup(arr[i]);
		i++;
	}
	return (temp);
}
int     helper_for_record(t_ants *ants,
						  const char *next_info, char **temp, char ***doble)
{
	if (ants->special_for_end == NULL)
	{
		ants->special_for_end_int = 1;
		ants->special_for_end = NULL;
		ants->special_for_end = (char**)malloc(sizeof(char*));
		ants->special_for_end[0] = NULL;
		ants->special_for_end[0] = ft_strdup(next_info);
	}
	else if (next_info)
	{
		*doble = ft_copy(ants->special_for_end, ants->special_for_end_int);
		ft_free(&ants->special_for_end, ants->special_for_end_int);
		ants->special_for_end_int++;
		ants->special_for_end = new_install(*doble, ants->special_for_end_int);
		ft_free(doble, ants->special_for_end_int - 1);
		ants->special_for_end[ants->special_for_end_int - 1] =
				ft_strdup(next_info);
	}
	ft_strdel(temp);
	if (!next_info)
	{
		ft_strdel(temp);
		return (0);
	}
	return (1);
}
void    installer_for_record(char **temp,
							 char *position, t_three_int *t, const char **road)
{
	t->i = -1;
	*road += ft_strlen(position) + 1;
	*temp = ft_strsub(*road, 0, foo_2(*road));
}
int     record(t_ants *ants, const char *road,
			   char *position, const char *next_info);
int     helper_for_record_1(t_ants *ants,
							const char *road, t_three_int t, char **temp)
{
	if (record(ants, road, *temp, ants->s_top[t.i].name_ant_in_flat) == 1)
	{
		if (ants->s_top[t.i].name_ant_in_flat != NULL)
			free(ants->s_top[t.i].name_ant_in_flat);
		ants->s_top[t.i].name_ant_in_flat = NULL;
		ft_strdel(temp);
		return (1);
	}
	if (ants->s_top[t.i].name_ant_in_flat != NULL)
		free(ants->s_top[t.i].name_ant_in_flat);
	ants->s_top[t.i].name_ant_in_flat = NULL;
	ft_strdel(temp);
	return (0);
}
void    little(char **arr, const char *next_info)
{
	if (*arr != NULL)
		free(*arr);
	*arr = ft_strdup(next_info);
}
int     helper_for_record_2(t_ants *ants,
							t_three_int t, char **temp, const char *next_info)
{
	if (ants->s_top[t.i].name_ant_in_flat != NULL)
		free(ants->s_top[t.i].name_ant_in_flat);
	ants->s_top[t.i].name_ant_in_flat = ft_strdup(next_info);
	ft_strdel(temp);
	return (0);
}
int     record(t_ants *ants, const char *road,
			   char *position, const char *next_info)
{
	char        *temp;
	t_three_int t;
	char        **doble;
	installer_for_record(&temp, position, &t, &road);
	if (ft_strcmp(temp, "end") == 0)
		return (helper_for_record(ants, next_info, &temp, &doble));
	while (++t.i != ants->count_rooms)
		if (ft_strcmp(temp, ants->s_top[t.i].room_name) == 0)
		{
			if (next_info == NULL)
				return (helper_for_record_1(ants, road, t, &temp));
			else if (ants->s_top[t.i].name_ant_in_flat)
			{
				t.j = record(ants, road,
							 temp, ants->s_top[t.i].name_ant_in_flat);
				little(&ants->s_top[t.i].name_ant_in_flat, next_info);
				ft_strdel(&temp);
				return (t.j);
			}
			else
				return (helper_for_record_2(ants, t, &temp, next_info));
		}
	ft_strdel(&temp);
	return (0);
}
int is_empty(t_ants ants, const char *road)
{
	road += 6;
	int i  = 0;
	while (i != ants.count_rooms)
	{
		if (ft_strstr(road, ants.s_top[i].room_name) && ants.s_top[i].name_ant_in_flat)
			return (0);
		i++;
	}
	return (1);
}
int is_after(const char *road, const char *room_name)
{
	int i = 0;
	int j;
	int count = 0;
	road += 6;
	while (road[i] != '\0')
	{
		j = 0;
		while (room_name[j] != '\0')
		{
			if (road[i + j] == room_name[j])
				count++;
			j++;
		}
		if (count == (int)ft_strlen(room_name))
			return (1);
		else
			return (0);
		i++;
	}
	return (0);
}
void    first_inst_for_foo(t_three_int *t)
{
	t->x = 0;
	t->i = 0;
	t->k = 0;
	t->j = 6;
}
char    *counter_for_foo(t_three_int *t, const char *road)
{
	t->k = 0;
	while (road[t->j + t->k] != '/')
		t->k++;
	t->j += t->k;
	t->i -= 1;
	return (ft_strsub(road, t->j - t->k, t->k));
}
int helper_for_foo(t_ants *ants, t_three_int t, char **temp, char *road)
{
	*temp = ft_itoa(++ants->reverse_lem);
	if (ants->s_top[t.i].name_ant_in_flat != NULL)
		free(ants->s_top[t.i].name_ant_in_flat);
	ants->s_top[t.i].name_ant_in_flat = ft_strjoin("L", *temp);
	if (ants->s_top[t.i].his_road)
		free(ants->s_top[t.i].his_road);
	ants->s_top[t.i].his_road = ft_strdup(road);
	free(*temp);
	if (ft_strcmp("start/end", road) == 0)
		return (1);
	return (0);
}
int helper_for_foo_1(char *road, t_three_int t, t_ants *ants, char **temp)
{
	if (ft_strcmp(road, "start/end") == 0)
	{
		*temp = ft_itoa(++ants->reverse_lem);
		if (ants->s_top[t.i].name_ant_in_flat != NULL)
			free(ants->s_top[t.i].name_ant_in_flat);
		t.x += record(ants, road, "start",
					  (ants->s_top[t.i].name_ant_in_flat = ft_strjoin("L", *temp)));
		free(*temp);
	}
	else
	{
		t.x += record(ants, road, "start", NULL);
		*temp = ft_itoa(++ants->reverse_lem);
		if (ants->s_top[t.i].name_ant_in_flat != NULL)
			free(ants->s_top[t.i].name_ant_in_flat);
		ants->s_top[t.i].name_ant_in_flat = ft_strjoin("L", *temp);
		free(*temp);
	}
	return (t.x);
}
int helper_for_foo_2(char *road, t_three_int t, t_ants *ants, char **temp)
{
	if (ft_strcmp(road, "start/end") == 0 && ants->reverse_lem < ants->helper)
	{
		if (ants->s_top[t.i].name_ant_in_flat != NULL)
			free(ants->s_top[t.i].name_ant_in_flat);
		*temp = ft_itoa(++ants->reverse_lem);
		ants->s_top[t.i].name_ant_in_flat = ft_strjoin("L", *temp);
		t.x += record(ants, road, "start", ants->s_top[t.i].name_ant_in_flat);
		free(*temp);
	}
	else if (ft_strcmp(road + 6, "end"))
		t.x += record(ants, road, "start", NULL);
	return (t.x);
}
int is_check_foo(t_ants *ants, t_three_int t,
				 const char *temp, const char *road)
{
	if (ft_strcmp(ants->s_top[t.i].room_name, temp) == 0
		&& ft_strcmp(ants->s_top[t.i].room_name, "start") != 0
		&& (ft_strcmp(ants->s_top[t.i].room_name, "end") != 0
			|| ft_strcmp("start/end", road) == 0))
		return (1);
	return (0);
}
int     logic_func_for_foo(t_ants *ants, t_three_int t, const char *road)
{
	if (!(ants->s_top[t.i].name_ant_in_flat && ants->s_top[t.i].his_road)
		&& ants->reverse_lem < ants->helper
		&& is_after(road, ants->s_top[t.i].room_name)
		&& ants->reverse_lem < ants->helper)
		return (1);
	return (0);
}
int foo(t_ants *ants, char *road)
{
	char        *temp;
	t_three_int t;
	first_inst_for_foo(&t);
	while (road[t.j] != '\0')
	{
		temp = counter_for_foo(&t, road);
		while (++t.i != ants->count_rooms)
			if (is_check_foo(ants, t, temp, road))
			{
				ft_strdel(&temp);
				if (logic_func_for_foo(ants, t, road))
					return (helper_for_foo(ants, t, &temp, road));
				else if (ants->reverse_lem < ants->helper &&
						 is_after(road, ants->s_top[t.i].room_name)
						 && ants->reverse_lem < ants->helper)
					return (helper_for_foo_1(road, t, ants, &temp));
				else if (is_empty(*ants, road) == 0
						 && is_after(road, ants->s_top[t.i].room_name))
					return (helper_for_foo_2(road, t, ants, &temp));
			}
	}
	return (t.x);
}
int check_lem(t_ants *ants, const int *ptr)
{
	int i = 0;
	int j;
	int delete_ants = 0;
	int k = 0;
	if (ants->special_for_end)
		ft_free(&ants->special_for_end, ants->special_for_end_int);
	ants->special_for_end = NULL;
	while (i != ants->count_road_variable)
	{
		j = 0;
		while (j != ants->count_road[i])
		{
			if (ptr[k] == 1)
				delete_ants += foo(ants, ants->roads[i][j]);
			else if (is_empty(*ants, ants->roads[i][j]) == 0)
				delete_ants += record(ants, ants->roads[i][j], "start", NULL);
			k++;
			j++;
		}
		i++;
	}
	return (delete_ants);
}
void to_null(t_ants *ants)
{
	int i = 0;
	while (i != ants->count_rooms)
	{
		ants->s_top[i].name_ant_in_flat = NULL;
		ants->s_top[i].his_road = NULL;
		i++;
	}
}
void    move_ants(t_ants *ants)
{
	int     i;
	int     j;
	int c = 0;
	i = 0;
	while (i != ants->count_road_variable)
		c += ants->count_road[i++];
	to_null(ants);
	ants->helper = ants->lem_count;
	ants->special_for_end = NULL;
	ants->reverse_lem = 0;
	ants->lem_in_house = ants->lem_count;
//  ft_printf("\n\n");
	int count = 0;
	int *ptr = (int *) malloc(sizeof(int) * c);
	while (ants->lem_count > 0) {
		inst_zero(&ptr, c, 0);
		go_ants(*ants, &ptr, c);
		ants->lem_in_house -= cont(ptr, c);
		ants->lem_count -= check_lem(ants, ptr);
		i = 0;
		j = 0;
		while (i != ants->count_rooms) {
			if (ants->s_top[i].name_ant_in_flat && ants->s_top[i].end != 1) {
				ft_printf("%s-%s ", ants->s_top[i].name_ant_in_flat, ants->s_top[i].room_name);
			} else if (ants->special_for_end && ants->s_top[i].end == 1) {
				while (j != ants->special_for_end_int)
					ft_printf("%s-%s ", ants->special_for_end[j++], ants->s_top[i].real_name);
			} else if (ants->s_top[i].end == 1 && ants->s_top[i].name_ant_in_flat)
				ft_printf("%s-%s ", ants->s_top[i].name_ant_in_flat, ants->s_top[i].real_name);
			i++;
		}
		count++;
		write(1, "\n", 1);
	}
	free(ptr);
//  ft_printf("%d\n", count);
}

/*
int 	count_slash(t_ants *ants, int i, int j)
{
	int 	count;
	int 	k;

	if (j == -1)
		return (0);
	count = 0;
	k = -1;
	while (ants->roads[i][j][++k] != '\0')
		if (ants->roads[i][j][k] == '/')
			count += 1;
	return (count + 1);
}

int 	condition_to_go(t_ants *ants, int i, int j)
{
	int 	difference;
	int 	sum;

	sum = 0;
	difference = 0;
	int 	count = 0;
	int 	k = j;
	int 	m = i;
	while (m != 0 || k != 0)
	{
		k -= 1;
		if (k <= 0)
		{
			m -= 1;
			k = ants->count_road[m] - 1;
		}
		sum += count_slash(ants, m, k);
		count += 1;
	}
//	while (i + k != 0)
//	{
//		sum += count_slash(ants, i, i + k - 1);//ants->length_road[i + k - 1];
//		k -= 1;
//		count += 1;
//	}
	difference = count_slash(ants, i, j) * count - sum;
	if (ants->lem_in_start > difference)
		return (1);
	else
		return (0);
}

char 	*cutting(char *str)
{
	int 	i;
	int 	j;
	char 	*str_new;

	str_new = ft_strdup(str);
	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '/')
		i--;
	j = i;
	i--;
	while (str[i] != '/' && i != -1)
		i--;
	str_new = ft_strsub(str, i + 1, for_norm_count(str, '/'));
	return (str_new);
}

void	moving_1(t_ants *ants, char *str1)
{
	ants->s_top[search(ants, str1)].in_house = 0;
	ants->s_top[search(ants, ants->s_top[search(ants, str1)].forward_to[0])].in_house = 1;

	int 	point = search(ants, str1);
	int		point_new = search(ants, (ants->s_top[point]).forward_to[0]);
	ants->s_top[point_new].what_ant = ants->s_top[point].what_ant;
	ft_printf("L%i-%s ", ants->s_top[point].what_ant,
			  ants->s_top[point].forward_to[0]);
	if (!ft_strcmp(ants->s_top[point].forward_to[0], search_endroom(ants)))
		ants->lem_in_end += 1;
}

void	moving(t_ants *ants, int i, int j)
{
	int 	length;
	char 	*str1;

	char 	*str2;
	char 	*str3;
	char 	*temp = ft_strdup(ants->roads[i][j]);

	length = 0;
	int length_road = count_slash(ants, i, j);
	while (length != length_road - 1)//ants->length_road[i + j] - 1)
	{
		str1 = ft_strdup(cutting(temp));
		if (ants->s_top[search(ants, str1)].in_house)
		{
			moving_1(ants, str1);
		}
		if (!ft_strcmp(str1, (ants->s_top[search(ants, search_startroom(ants))]).room_name) && ants->lem_in_start > 0)
		{
			str2 = ft_strsub(ants->roads[i][j], 0, for_norm_count(ants->roads[i][j], '/'));
			str3 = ft_strsub(ants->roads[i][j] + ft_strlen(str1) + 1, 0, for_norm_count(ants->roads[i][j], '/'));
			(ants->s_top[search(ants, str3)]).what_ant = ants->lem_count - ants->lem_in_start + 1;
			ft_printf("L%i-%s ", (ants->s_top[search(ants, str3)]).what_ant, str3);
			(ants->s_top[search(ants, str3)]).in_house = 1;
			ants->lem_in_start -= 1;
		}
		length++;
		temp = ft_strsub(temp, 0, ft_strlen(temp) - ft_strlen(str1) - 1);
	}
}

void	move_ants(t_ants *ants)
{
	int		i;
	int 	j;

	ants->lem_in_start = ants->lem_count;

	while (ants->lem_in_end != ants->lem_count)
	{
		i = -1;
		while (++i < ants->count_road_variable)
		{
			j = -1;
			while (++j < ants->count_road[i])
			{
//				ft_printf("\n%s", ants->roads[i][j]);
//				if (i == 0 && j == 0 && (ants->lem_in_start > 0))
//					moving(ants, i, j);
				if (condition_to_go(ants, i, j))
					moving(ants, i, j);
				else
					moving(ants, i, j);
			}
		}

		ft_printf("\n");
	}
}
*/
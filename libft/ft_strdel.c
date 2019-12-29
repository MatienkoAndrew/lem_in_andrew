/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:50:56 by fgeruss           #+#    #+#             */
/*   Updated: 2019/04/11 19:45:43 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_strdel(char **as)
{
	if (!as || !*as)
		return ;
	else
	{
		free(*as);
		*as = NULL;
	}
}

void	ft_strdel_int(int **as)
{
	if (!as || !*as)
		return ;
	else
	{
		free(*as);
		*as = NULL;
	}
}
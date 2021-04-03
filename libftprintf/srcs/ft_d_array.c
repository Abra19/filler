/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:28:54 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 18:28:57 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** create dynamic array char
*/

char	*create_da(t_ptf *pr, unsigned size)
{
	pr->buff = (char *)ft_memalloc(sizeof(char) * size);
	pr->buff[size - 1] = '\0';
	return (pr->buff);
}

/*
** copy data in array of new size
*/

void	ft_copy(char *to, char *from, unsigned size)
{
	unsigned		i;

	i = 0;
	while (i < size)
	{
		to[i] = from[i];
		i++;
	}
	to[i] = '\0';
}

int		resize_da(t_ptf *pr)
{
	char			*arr;
	unsigned long	new_size;

	arr = (char *)ft_memalloc(sizeof(char) * pr->size);
	arr[pr->size - 1] = '\0';
	ft_copy(arr, pr->buff, pr->size);
	ft_strdel(&pr->buff);
	new_size = pr->size * 2;
	pr->buff = (char *)ft_memalloc(sizeof(char) * new_size);
	pr->buff[new_size - 1] = '\0';
	ft_copy(pr->buff, arr, pr->size);
	ft_strdel(&arr);
	pr->size = new_size;
	return (1);
}

void	ft_copycut(char *to, char *from, unsigned start, unsigned size)
{
	unsigned		i;

	i = 0;
	while (i < size)
	{
		to[i] = from[i + start];
		i++;
	}
	to[i] = '\0';
}

/*
** create dynamic array int
*/

int		*create_da_int(unsigned size)
{
	int				*arr;

	arr = (int *)ft_memalloc(sizeof(int) * size);
	return (arr);
}

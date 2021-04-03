/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:21:00 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:44:05 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	copy_map(t_graf *graf)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	init_copy_map(graf);
	alloc_map_color(graf);
	while (i < graf->filler.height)
	{
		j = 0;
		while (j < graf->filler.width)
		{
			k = 0;
			while (k < graf->mult)
			{
				multiply_map(graf, i, j, k);
				k++;
			}
			j++;
		}
		i++;
	}
}

int		found_sizes_d(char *line, int *height, int *width)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = line;
	while (ft_isdigit(tmp[i]) != 1)
		i++;
	tmp = tmp + i;
	*height = ft_atoi(tmp);
	tmp = line;
	while (tmp[i] != ':')
		i++;
	i--;
	while (ft_isdigit(tmp[i]) == 1)
		i--;
	tmp = tmp + i;
	*width = ft_atoi(tmp);
	if (*height <= 0 || *width <= 0)
		return (0);
	return (1);
}

void	alloc_graf_map(t_graf *graf)
{
	graf->filler.map = (char **)ft_memalloc((graf->filler.height + 1) *\
	sizeof(char *));
	graf->filler.map[graf->filler.height] = 0;
	ft_bzero(graf->filler.map, graf->filler.height);
}

void	handle_map(t_graf *graf, char *line, int i)
{
	int		j;

	j = 4;
	graf->filler.map[i] = (char *)ft_memalloc((graf->filler.width + 1)\
			* sizeof(char));
	graf->filler.map[i][graf->filler.width] = '\0';
	while (j < graf->filler.width + 4)
	{
		graf->filler.map[i][j - 4] = line[j];
		j++;
	}
}

int		start_map(t_graf *graf, char *line)
{
	int		i;
	int		res;

	i = 0;
	alloc_graf_map(graf);
	while (i < graf->filler.height)
	{
		if ((res = get_next_line(0, &line)) <= 0)
		{
			clean_up_map_d((void **)graf->filler.map, i - 1);
			return (0);
		}
		if (res > 0)
		{
			handle_map(graf, line, i);
			ft_strdel(&line);
		}
		i++;
	}
	return (1);
}

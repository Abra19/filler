/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:21:00 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:45:35 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	clean_up_map_d(void **map, int height)
{
	int		i;

	i = 0;
	while (i < height)
	{
		ft_memdel(&map[i]);
		i++;
	}
	free(map);
}

int		min(int a, int b)
{
	int		min;

	min = (a <= b) ? a : b;
	return (min);
}

void	multiply_map(t_graf *graf, int i, int j, int k)
{
	int		l;

	l = 0;
	while (l < graf->mult)
	{
		if (graf->filler.map[i][j] == 'X')
			graf->map.color[graf->mult * i + k][graf->mult * j + l] = XCOL;
		else if (graf->filler.map[i][j] == 'x')
			graf->map.color[graf->mult * i + k][graf->mult * j + l] = SXCOL;
		else if (graf->filler.map[i][j] == 'O')
			graf->map.color[graf->mult * i + k][graf->mult * j + l] = OCOL;
		else if (graf->filler.map[i][j] == 'o')
			graf->map.color[graf->mult * i + k][graf->mult * j + l] = SOCOL;
		else
			graf->map.color[graf->mult * i + k][graf->mult * j + l] = ECOL;
		if ((graf->mult * i + k) % graf->mult == 0 ||\
			(graf->mult * j + l) % graf->mult == 0)
			graf->map.color[graf->mult * i + k][graf->mult * j + l] = BORD;
		l++;
	}
}

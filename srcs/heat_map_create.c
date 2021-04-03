/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:19:13 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:24:51 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	touch_map(t_filler *filler, int i, int j)
{
	if (j + 1 < filler->width && ((i - 1 >= 0 && \
		filler->heat_map[i - 1][j + 1] == RFIG) || \
		filler->heat_map[i][j + 1] == RFIG ||\
		(i + 1 < filler->height && \
		filler->heat_map[i + 1][j + 1] == RFIG)))
		filler->heat_map[i][j] = 1;
	if (j - 1 >= 0 && ((i - 1 >= 0 && \
		filler->heat_map[i - 1][j - 1] == RFIG) || \
		filler->heat_map[i][j - 1] == RFIG ||\
		(i + 1 < filler->height && \
		filler->heat_map[i + 1][j - 1] == RFIG)))
		filler->heat_map[i][j] = 1;
	if (((i - 1 >= 0 && filler->heat_map[i - 1][j] == RFIG) || \
		(i + 1 < filler->height &&\
		filler->heat_map[i + 1][j] == RFIG)))
		filler->heat_map[i][j] = 1;
}

void	near_rival_map(t_filler *filler)
{
	int		i;
	int		j;

	i = -1;
	while (++i < filler->height)
	{
		j = -1;
		while (++j < filler->width)
		{
			if (filler->heat_map[i][j] != MYFIG\
				&& filler->heat_map[i][j] != RFIG)
				touch_map(filler, i, j);
		}
	}
}

void	rest_map(t_filler *filler, int n, int i, int j)
{
	if (filler->heat_map[i][j] == 0)
	{
		if (j + 1 < filler->width && ((i - 1 >= 0 && \
			filler->heat_map[i - 1][j + 1] == n) || \
			filler->heat_map[i][j + 1] == n || (i + 1 < filler->height && \
			filler->heat_map[i + 1][j + 1] == n)))
			filler->heat_map[i][j] = n + 1;
		if (j - 1 >= 0 && ((i - 1 >= 0 && \
			filler->heat_map[i - 1][j - 1] == n) || \
			filler->heat_map[i][j - 1] == n || (i + 1 < filler->height && \
			filler->heat_map[i + 1][j - 1] == n)))
			filler->heat_map[i][j] = n + 1;
		if ((i - 1 >= 0 && filler->heat_map[i - 1][j] == n) || \
			(i + 1 < filler->height && filler->heat_map[i + 1][j] == n))
			filler->heat_map[i][j] = n + 1;
	}
}

void	blackhole(t_filler *filler)
{
	int		i;
	int		j;

	i = 0;
	while (i < filler->height)
	{
		j = 0;
		while (j < filler->width)
		{
			if (filler->heat_map[i][j] == 0)
				filler->heat_map[i][j] = max_int(filler->height, filler->width)\
				+ filler->width;
			j++;
		}
		i++;
	}
}

void	heat_map_create(t_filler *filler)
{
	int		n;
	int		i;
	int		j;

	n = 1;
	near_rival_map(filler);
	while (n < max_int(filler->height, filler->width) + filler->width)
	{
		i = 0;
		while (i < filler->height)
		{
			j = 0;
			while (j < filler->width)
			{
				rest_map(filler, n, i, j);
				j++;
			}
			i++;
		}
		n++;
	}
	blackhole(filler);
}

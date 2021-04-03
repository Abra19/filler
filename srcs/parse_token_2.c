/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:09:44 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:30:23 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	found_collision(t_filler *filler, int i, int j)
{
	int		k;
	int		l;

	k = 0;
	if (filler->heat_map[i][j] == MYFIG)
	{
		while (k < filler->t_height)
		{
			l = 0;
			while (l < filler->t_width)
			{
				if (filler->heat_map[i + k][j + l] == RFIG)
				{
					filler->collision_x = i;
					filler->collision_y = j;
				}
				l++;
			}
			k++;
		}
	}
}

void	found_contact(t_filler *filler, int i, int j)
{
	int		x;
	int		y;

	x = 0;
	while (x < filler->t_height)
	{
		y = 0;
		while (y < filler->t_width)
		{
			if (filler->heat_map[i + x][j + y] == RFIG && \
				filler->token[x][y] == '*')
			{
				filler->contact = 0;
				filler->mem_i = i;
				filler->mem_j = j;
			}
			else if (filler->heat_map[i + x][j + y] == MYFIG && \
				filler->token[x][y] == '*')
				filler->contact++;
			y++;
		}
		x++;
	}
}

int		count_sum(t_filler *filler, int i, int j)
{
	int		sum;
	int		k;
	int		l;

	sum = 0;
	k = 0;
	while (k < filler->t_height)
	{
		l = 0;
		while (l < filler->t_width)
		{
			if (filler->token[k][l] == '*' && \
				filler->heat_map[i + k][j + l] != MYFIG)
				sum += filler->heat_map[i + k][j + l];
			l++;
		}
		k++;
	}
	return (sum);
}

void	keep_coord(t_filler *filler, int i, int j)
{
	filler->sum_x = i;
	filler->sum_y = j;
}

void	choose_right_coord(int sum, t_filler *filler, int i, int j)
{
	if (filler->sum != INT32_MAX && filler->my_id == 'X' &&\
		sum <= filler->sum + 4 && j > filler->sum_y && filler->width < 20 &&\
		(i != filler->collision_x || j != filler->collision_y))
		keep_coord(filler, i, j);
	if (filler->sum != INT32_MAX && filler->my_id == 'X' && \
		sum <= filler->sum + 4 && i > filler->sum_x && filler->width < 20 &&\
		(i != filler->collision_x || j != filler->collision_y))
		keep_coord(filler, i, j);
	else if (sum <= filler->sum && sum > 0 &&
		(i != filler->collision_x || j != filler->collision_y))
	{
		if (sum == filler->sum && j < filler->sum_y)
			keep_coord(filler, i, j);
		else
		{
			keep_coord(filler, i, j);
			filler->sum = sum;
		}
	}
}

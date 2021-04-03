/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:09:44 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:28:52 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	init_param(t_filler *filler)
{
	filler->sum = INT32_MAX;
	filler->mem_i = filler->height + 1;
	filler->mem_j = filler->width + 1;
}

int		print_coord(t_filler *filler)
{
	if (filler->my_id == 'X')
	{
		filler->sum_x = filler->height - filler->sum_x - filler->t_height;
		filler->sum_y = filler->width - filler->sum_y - filler->t_width;
	}
	filler->sum_x = filler->sum_x - filler->t_start_x;
	filler->sum_y = filler->sum_y - filler->t_start_y;
	filler->t_start_x = 0;
	filler->t_end_x = 0;
	filler->t_start_y = 0;
	filler->t_end_y = 0;
	if (filler->sum != INT32_MAX)
	{
		ft_printf("%d %d\n", filler->sum_x, filler->sum_y);
		filler->put++;
	}
	else
	{
		ft_printf("%d %d\n", 0, 0);
		filler->exit_flag = 1;
		return (0);
	}
	return (1);
}

void	found_touch(t_filler *filler, int i, int j)
{
	filler->contact = 0;
	found_collision(filler, i, j);
	found_contact(filler, i, j);
}

int		count_sum_token(t_filler *filler)
{
	int		i;
	int		j;
	int		sum;

	i = 0;
	init_param(filler);
	while (i < filler->height - filler->t_height + 1)
	{
		j = 0;
		while (j < filler->width - filler->t_width + 1)
		{
			found_touch(filler, i, j);
			if (filler->contact == 1 && (i != filler->mem_i ||\
				j != filler->mem_j))
			{
				sum = count_sum(filler, i, j);
				choose_right_coord(sum, filler, i, j);
			}
			j++;
		}
		i++;
	}
	if (print_coord(filler) == 0)
		return (0);
	return (1);
}

int		parse_token(t_filler *filler, char *line)
{
	if (found_sizes(line, &filler->t_height, &filler->t_width) == 0)
	{
		ft_strdel(&line);
		return (0);
	}
	ft_strdel(&line);
	if (keep_token(filler, line) == 0)
		return (0);
	if (count_sum_token(filler) == 0)
		return (0);
	return (1);
}

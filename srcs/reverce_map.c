/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverce_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:21:56 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:34:35 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	save_coord_reverse(t_filler *filler, int i)
{
	int		j;

	j = 0;
	while (j < filler->width)
	{
		if (filler->map[i][j] == filler->my_id ||\
			filler->map[i][j] == filler->my_id + 32)
			filler->heat_map[i][j] = MYFIG;
		else if (filler->map[i][j] == filler->rival_id ||\
			filler->map[i][j] == filler->rival_id + 32)
			filler->heat_map[i][j] = RFIG;
		else
			filler->heat_map[i][j] = 0;
		j++;
	}
}

void	write_reverse_map(t_filler *filler, char **tmp_map)
{
	int		i;
	int		j;

	i = 0;
	while (i < filler->height)
	{
		j = 0;
		while (j < filler->width)
		{
			filler->map[i][j] = tmp_map[i][j];
			save_coord_reverse(filler, i);
			j++;
		}
		i++;
	}
}

void	reverse_map(t_filler *filler)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	**tmp_map;

	i = filler->height - 1;
	k = -1;
	tmp_map = (char **)ft_memalloc((filler->height + 1) * sizeof(char *));
	tmp_map[filler->height] = 0;
	while (++k < filler->height)
	{
		tmp_map[k] = (char *)ft_memalloc((filler->width + 1) * sizeof(char));
		tmp_map[k][filler->width] = '\0';
		l = -1;
		j = filler->width - 1;
		while (++l < filler->width)
		{
			tmp_map[k][l] = filler->map[i][j];
			j--;
		}
		i--;
	}
	write_reverse_map(filler, tmp_map);
	clean_up_map((void **)tmp_map, filler->height + 1);
}

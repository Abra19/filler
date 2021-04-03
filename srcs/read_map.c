/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:21:56 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:33:39 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_players_id(t_filler *filler, char *line)
{
	if (line[10] == '1' || line[10] == '2')
	{
		if (line[10] == '1')
		{
			filler->my_id = 'O';
			filler->rival_id = 'X';
		}
		else
		{
			filler->my_id = 'X';
			filler->rival_id = 'O';
		}
	}
	else
	{
		ft_strdel(&line);
		return (0);
	}
	ft_strdel(&line);
	return (1);
}

int		found_sizes(char *line, int *height, int *width)
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

void	save_coord(t_filler *filler, int i, char *line)
{
	int		j;

	j = 4;
	while (j < filler->width + 4)
	{
		filler->map[i][j - 4] = line[j];
		if (filler->map[i][j - 4] == filler->my_id ||\
			filler->map[i][j - 4] == filler->my_id + 32)
			filler->heat_map[i][j - 4] = MYFIG;
		else if (filler->map[i][j - 4] == filler->rival_id ||\
			filler->map[i][j - 4] == filler->rival_id + 32)
			filler->heat_map[i][j - 4] = RFIG;
		else
			filler->heat_map[i][j - 4] = 0;
		j++;
	}
}

void	make_map(t_filler *filler, int i, char *line)
{
	filler->map[i] = (char *)ft_memalloc((filler->width + 1) * \
	sizeof(char));
	filler->map[i][filler->width] = '\0';
	filler->heat_map[i] =\
				(int *)ft_memalloc(filler->width * sizeof(int));
	save_coord(filler, i, line);
	ft_strdel(&line);
}

int		check_map(t_filler *filler)
{
	int		i;
	int		j;
	int		sum;

	i = 0;
	sum = 0;
	while (i < filler->height)
	{
		j = 0;
		while (j < filler->width)
		{
			sum += filler->heat_map[i][j];
			j++;
		}
		i++;
	}
	return (sum);
}

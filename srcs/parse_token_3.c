/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:09:44 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:32:23 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	write_reverse_token(t_filler *filler, char **tmp_token)
{
	int		i;
	int		j;

	i = 0;
	while (i < filler->t_height)
	{
		j = 0;
		while (j < filler->t_width)
		{
			filler->token[i][j] = tmp_token[i][j];
			j++;
		}
		i++;
	}
}

void	reverse_token(t_filler *filler)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	**tmp_token;

	i = filler->t_height - 1;
	k = -1;
	tmp_token = alloc_full_token(filler);
	while (++k < filler->t_height)
	{
		tmp_token[k] = (char *)ft_memalloc((filler->t_width + 1) *\
		sizeof(char));
		tmp_token[k][filler->t_width] = '\0';
		l = -1;
		j = filler->t_width - 1;
		while (++l < filler->t_width)
		{
			tmp_token[k][l] = filler->token[i][j];
			j--;
		}
		i--;
	}
	write_reverse_token(filler, tmp_token);
	clean_up_map((void **)tmp_token, filler->t_height);
}

int		read_token(t_filler *filler, int i, char *line)
{
	int		j;

	j = 0;
	filler->btoken[i] = (char *)ft_memalloc((filler->t_width + 1) * \
	sizeof(char));
	filler->btoken[i][filler->t_width] = '\0';
	while (j < filler->t_width)
	{
		filler->btoken[i][j] = line[j];
		if (filler->btoken[i][j] != '.' && filler->btoken[i][j] != '*')
		{
			ft_strdel(&line);
			return (0);
		}
		j++;
	}
	ft_strdel(&line);
	return (1);
}

int		keep_token(t_filler *filler, char *line)
{
	int		i;
	int		res;

	i = 0;
	alloc_btoken(filler);
	while (i < filler->t_height)
	{
		if ((res = get_next_line(0, &line)) <= 0)
			return (0);
		if (res > 0)
		{
			if (read_token(filler, i, line) == 0)
				return (0);
		}
		i++;
	}
	if (cut_token(filler) == 0)
		return (0);
	if (filler->my_id == 'X')
		reverse_token(filler);
	return (1);
}

int		max_int(int a, int b)
{
	int		max;

	max = (a >= b) ? a : b;
	return (max);
}

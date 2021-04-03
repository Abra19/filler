/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 16:23:01 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:20:42 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	clean_up_maps(t_filler *filler)
{
	clean_up_map((void **)filler->map, filler->height + 1);
	clean_up_map((void **)filler->heat_map, filler->height);
}

void	clean_up_map(void **map, int height)
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

void	alloc_maps(t_filler *filler)
{
	filler->map = (char **)ft_memalloc((filler->height + 1) * sizeof(char *));
	filler->map[filler->height] = 0;
	ft_bzero(filler->map, filler->height);
	filler->heat_map = (int **)ft_memalloc((filler->height) * sizeof(int *));
	ft_bzero(filler->heat_map, filler->height);
}

void	alloc_btoken(t_filler *filler)
{
	filler->btoken = (char **)ft_memalloc((filler->t_height + 1) *\
	sizeof(char *));
	filler->btoken[filler->t_height] = 0;
	ft_bzero(filler->btoken, filler->t_height);
}

char	**alloc_full_token(t_filler *filler)
{
	char **tmp_token;

	tmp_token = (char **)ft_memalloc((filler->t_height + 1) * sizeof(char *));
	tmp_token[filler->t_height] = 0;
	return (tmp_token);
}

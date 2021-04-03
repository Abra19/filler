/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 16:23:01 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:21:36 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	copy_token(t_filler *filler)
{
	int		i;
	int		j;

	i = 0;
	while (i < filler->t_height)
	{
		j = 0;
		filler->token[i] = (char *)ft_memalloc((filler->t_width + 1)\
		* sizeof(char));
		filler->token[i][filler->t_width] = '\0';
		while (j < filler->t_width)
		{
			filler->token[i][j] =\
				filler->btoken[i + filler->t_start_x][j + filler->t_start_y];
			j++;
		}
		i++;
	}
}

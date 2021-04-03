/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:09:44 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:22:58 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	cut_token_x_left(t_filler *filler)
{
	int		i;
	int		j;

	i = 0;
	while (i < filler->t_height)
	{
		j = 0;
		while (j < filler->t_width)
		{
			if (filler->btoken[i][j] == '*')
				break ;
			j++;
		}
		if (j == filler->t_width)
			filler->t_start_x++;
		else
			break ;
		i++;
	}
}

void	cut_token_y_left(t_filler *filler)
{
	int		i;
	int		j;

	i = 0;
	while (i < filler->t_width)
	{
		j = 0;
		while (j < filler->t_height)
		{
			if (filler->btoken[j][i] == '*')
				break ;
			j++;
		}
		if (j == filler->t_height)
			filler->t_start_y++;
		else
			break ;
		i++;
	}
}

void	cut_token_x_right(t_filler *filler)
{
	int		i;
	int		j;

	i = filler->t_height - 1;
	while (i >= 0)
	{
		j = filler->t_width - 1;
		while (j >= 0)
		{
			if (filler->btoken[i][j] == '*')
				break ;
			j--;
		}
		if (j == -1)
			filler->t_end_x++;
		else
			break ;
		i--;
	}
}

void	cut_token_y_right(t_filler *filler)
{
	int		i;
	int		j;

	i = filler->t_width - 1;
	while (i >= 0)
	{
		j = filler->t_height - 1;
		while (j >= 0)
		{
			if (filler->btoken[j][i] == '*')
				break ;
			j--;
		}
		if (j == -1)
			filler->t_end_y++;
		else
			break ;
		i--;
	}
}

int		cut_token(t_filler *filler)
{
	cut_token_x_left(filler);
	cut_token_y_left(filler);
	cut_token_x_right(filler);
	cut_token_y_right(filler);
	if ((filler->t_height <= filler->t_start_x + filler->t_end_x) ||\
		(filler->t_width <= filler->t_start_y + filler->t_end_y))
	{
		clean_up_map((void **)filler->btoken,\
	filler->t_height + filler->t_start_x + filler->t_end_x + 1);
		return (0);
	}
	filler->t_height = filler->t_height - filler->t_start_x - filler->t_end_x;
	filler->t_width = filler->t_width - filler->t_start_y - filler->t_end_y;
	filler->token = (char **)ft_memalloc((filler->t_height + 1) *\
	sizeof(char *));
	filler->token[filler->t_height] = 0;
	ft_bzero(filler->token, filler->t_height);
	copy_token(filler);
	clean_up_map((void **)filler->btoken,\
	filler->t_height + filler->t_start_x + filler->t_end_x + 1);
	return (1);
}

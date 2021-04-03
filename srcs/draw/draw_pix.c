/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:20:09 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 12:55:43 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	legenga_env(t_graf *graf)
{
	t_point	top;
	t_point	bottom;

	top.x = LEGENDA;
	top.y = 0;
	top.p_color = 0xfa8072;
	bottom.x = LEGENDA;
	bottom.y = graf->height;
	bottom.p_color = 0xfa8072;
	put_line(top, bottom, graf);
}

void	draw_map(t_graf *graf)
{
	int		x;
	int		y;

	y = 0;
	legenga_env(graf);
	while (y < graf->map.ln_count)
	{
		x = 0;
		while (x < graf->map.sym_count)
		{
			if (x != graf->map.sym_count - 1)
				put_line(define_point(x, y, graf),\
				define_point(x + 1, y, graf), graf);
			if (y != graf->map.ln_count - 1)
				put_line(define_point(x, y, graf),\
				define_point(x, y + 1, graf), graf);
			x++;
		}
		y++;
	}
}

int		draw_filler(t_graf *graf)
{
	draw_map(graf);
	mlx_put_image_to_window(graf->mlx_ptr, graf->mlx_win,\
	graf->image.img_ptr, 0, 0);
	legenda(graf);
	return (1);
}

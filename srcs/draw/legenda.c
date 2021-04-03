/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legenda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:21:00 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:38:50 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	legenda(t_graf *graf)
{
	int		h;

	h = 0;
	mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h, 0xff007f,\
	"FILLER GAME");
	mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 50, 0xb8860b,\
	"Step by step:");
	mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 20, 0xffffff,\
	"->");
	mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 50, 0xb8860b,\
	"Quit:");
	mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 20, 0xffffff,\
	"Esc");
	mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 50, 0xff007f,\
	"GAMERS:");
	mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 50, 0xb8860b,\
	"name of gamer 1");
	mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 35, OCOL,\
	graf->filler.name1);
	mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 50, 0xb8860b,\
	"name of gamer 2");
	mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 35, XCOL,\
	graf->filler.name2);
}

void	print_game_score(t_graf *graf)
{
	int		h;
	char	*str;

	h = 450;
	if (graf->filler.score1 != NULL && graf->filler.score2 != NULL)
	{
		mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h, 0xff007f,\
		"SCORE:");
		mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 50, OCOL,\
		graf->filler.name1);
		mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 35, 0xb8860b,\
		graf->filler.score1);
		mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 50, XCOL,\
		graf->filler.name2);
		mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 35, 0xb8860b,\
		graf->filler.score2);
		if (ft_atoi(graf->filler.score1) > ft_atoi(graf->filler.score2))
			str = ft_strjoin(graf->filler.name1, " WON");
		else
			str = ft_strjoin(graf->filler.name2, " WON");
		mlx_string_put(graf->mlx_ptr, graf->mlx_win, 15, h += 50,\
		0xff007f, str);
		ft_strdel(&str);
	}
}

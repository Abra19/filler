/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:20:29 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/20 21:48:47 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int		key_press_interactive(int key, void *param)
{
	t_graf	*graf;

	graf = (t_graf *)param;
	if (key == RIGHT_KEY)
		loop_hook(graf);
	else if (key == QUIT_KEY)
	{
		mlx_clear_window(graf->mlx_ptr, graf->mlx_win);
		mlx_destroy_image(graf->mlx_ptr, graf->image.img_ptr);
		mlx_destroy_window(graf->mlx_ptr, graf->mlx_win);
		kill(ft_atoi("pgrep 'dlaure.filler'"), 15);
		exit(0);
	}
	return (1);
}

int		key_press_automate(int key, void *param)
{
	t_graf	*graf;

	graf = (t_graf *)param;
	if (key == QUIT_KEY)
	{
		mlx_clear_window(graf->mlx_ptr, graf->mlx_win);
		mlx_destroy_image(graf->mlx_ptr, graf->image.img_ptr);
		mlx_destroy_window(graf->mlx_ptr, graf->mlx_win);
		kill(ft_atoi("pgrep 'dlaure.filler'"), 15);
		exit(0);
	}
	return (1);
}

int		close_x(void *param)
{
	t_graf	*graf;

	graf = (t_graf *)param;
	mlx_clear_window(graf->mlx_ptr, graf->mlx_win);
	mlx_destroy_image(graf->mlx_ptr, graf->image.img_ptr);
	mlx_destroy_window(graf->mlx_ptr, graf->mlx_win);
	kill(ft_atoi("pgrep 'dlaure.filler'"), 15);
	exit(0);
}

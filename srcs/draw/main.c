/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:21:11 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:47:45 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	init_copy_map(t_graf *graf)
{
	graf->mult = min((WIDTH - LEGENDA - VBRIM) / graf->filler.height,\
	(HEIGHT - HBRIM) / graf->filler.width);
	graf->map.ln_count = graf->filler.height * graf->mult;
	graf->map.sym_count = graf->filler.width * graf->mult;
	graf->map.color = (int **)ft_memalloc(graf->map.ln_count * sizeof(int *));
}

void	alloc_map_color(t_graf *graf)
{
	int		i;

	i = 0;
	while (i < graf->map.ln_count)
	{
		graf->map.color[i] = (int *)ft_memalloc(graf->map.sym_count *\
		sizeof(int));
		i++;
	}
}

void	init_draw(t_graf *graf)
{
	graf->scale = 1;
	graf->width = WIDTH;
	graf->height = HEIGHT;
	graf->exit_flag = 0;
	graf->image.width = graf->width;
	graf->image.height = graf->height;
	graf->image.bpp = MAC_BPP * 8;
	graf->image.size_line = graf->image.width * MAC_BPP;
	graf->image.endian = 0;
}

int		init_mlx(t_graf *graf)
{
	if ((graf->mlx_ptr = mlx_init()) == NULL)
	{
		ft_putendl("start of drawing fall");
		return (0);
	}
	if ((graf->mlx_win = mlx_new_window(graf->mlx_ptr, graf->width,\
	graf->height, "filler")) == NULL)
	{
		ft_putendl("creating of new window fall");
		return (0);
	}
	if ((graf->image.img_ptr = mlx_new_image(graf->mlx_ptr,\
	graf->image.width, graf->image.height)) == NULL)
	{
		ft_putendl("creating of new image fall");
		return (0);
	}
	graf->image.addr = mlx_get_data_addr(graf->image.img_ptr,\
	&(graf->image.bpp), &(graf->image.size_line), &(graf->image.endian));
	ft_bzero(graf->image.addr, graf->image.width * graf->image.height\
	* MAC_BPP);
	return (1);
}

int		main(int argc, char **argv)
{
	t_graf		graf;

	if (argc > 2)
	{
		ft_printf("usage: ./draw    - for automatic mode or\n "
			"      ./draw -i - for interactive mode\n");
		return (0);
	}
	ft_bzero(&graf, sizeof(graf));
	init_draw(&graf);
	if (init_mlx(&graf) == 0)
		return (1);
	if (argc == 2 && ft_strcmp(argv[1], "-i") == 0)
	{
		loop_hook(&graf);
		mlx_hook(graf.mlx_win, 2, 0, key_press_interactive, &graf);
	}
	else
	{
		mlx_loop_hook(graf.mlx_ptr, loop_hook, &graf);
		mlx_hook(graf.mlx_win, 2, 0, key_press_automate, &graf);
	}
	mlx_hook(graf.mlx_win, 17, 0, close_x, &graf);
	mlx_loop(graf.mlx_ptr);
	return (0);
}

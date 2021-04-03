/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:22:14 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:06:39 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Visualisator for filler
** 2 way to run it:
** 1.
** ./filler_vm -f maps/map00 -p1 players/carli.filler -p2 ./dlaure.filler \
** 									| ./draw
** automate mode
** 2.
** ./filler_vm -f maps/map00 -p1 players/carli.filler -p2 ./dlaure.filler \
** 									| ./draw -i
** interactive mode
** Information about control in legenda
*/

#ifndef DRAW_H
# define DRAW_H
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "libft.h"
# include "mlx.h"
# include "filler.h"

/*
** parameters of pixel size
*/

# define MAC_BPP			4

# define OCOL				0xFF0000
# define SOCOL				0xFF3333
# define XCOL				0x0000FF
# define SXCOL				0x3333FF
# define ECOL				0xC0C0C0
# define BORD			    0xFFFFFF
# define HBRIM				100
# define VBRIM				100

/*
** window parameter
*/

# define WIDTH				1500
# define HEIGHT				800
# define LEGENDA			250

/*
** keyboard codes
*/

# define RIGHT_KEY			124
# define QUIT_KEY			53

/*
** struct for image
** img_ptr - pointer to image
** adr - address of start of the memory for image
** bpp - bytes for pixel
** size_line - number of bytes used to store one line of the image in memory
** endian - endian: format of order
** width of image
** height of image
*/

typedef	struct				s_image
{
	void					*img_ptr;
	char					*addr;
	int						bpp;
	int						size_line;
	int						endian;
	int						width;
	int						height;
}							t_image;

/*
** struct for map parameters
** color - array for rgb mix collor from map in decimal
** size - size of array from lines
** ln_count - numbers of lines from map
** sym_count - numbers of symbols in line from map
*/

typedef struct				s_map
{
	int						**color;
	int						ln_count;
	int						sym_count;
}							t_map;

/*
** struct for point
*/
typedef struct				s_point
{
	int						x;
	int						y;
	int						p_color;
}							t_point;

/*
** struct for Bresenhaim algoritm parameters
*/

typedef struct				s_bresen
{
	int						dx;
	int						dy;
	int						sign_x;
	int						sign_y;
	int						sum;
}							t_bresen;

/*
** struct for draw
** mlx_ptr - pointer for draw init work
** win_ptr - pointer to open window
** height - height of window
** width - width of window
** mult - scale for draw in dependance of size of map
** scale - length of unit (from 1 point to another)
** h_max - maximum height in map
** x_move - move image along OX
** y_move - move image along OY
*/

typedef struct				s_graf
{
	void					*mlx_ptr;
	void					*mlx_win;
	int						height;
	int						width;
	int						scale;
	int						exit_flag;
	int						stop;
	int						mult;
	t_map					map;
	t_image					image;
	t_filler				filler;
}							t_graf;

void						alloc_map_color(t_graf *graf);
void						clean_up_map_d(void **map, int height);
int							close_x(void *param);
int							color_gradient(t_point *start, t_point *current,\
							t_point *end);
void						copy_map(t_graf *graf);
t_point						define_point(int x, int y, t_graf *graf);
int							draw_filler(t_graf *graf);
void						draw_map(t_graf *graf);
int							found_sizes_d(char *line, int *height, int *width);
int							get_players_name(t_graf *graf, char *line);
void						handle_semifinal(t_graf *graf, char *line);
void						init_param(t_point *fst, t_point *scd,\
							t_bresen *bresen);
void						image_pixel_put(t_graf *graf, int x, int y,\
							int color);
void						init_copy_map(t_graf *graf);
int							key_press_interactive(int key, void *param);
int							key_press_automate(int key, void *param);
void						legenda(t_graf *graf);
int							loop_filler(t_graf *graf);
int							loop_hook(t_graf *graf);
int							min(int a, int b);
int							mix_light(int start, int end, double scale);
void						multiply_map(t_graf *graf, int i, int j, int k);
int							parse_board_full(t_graf *graf, char *line);
double						place(int start, int end, int current);
void						print_game_score(t_graf *graf);
void						put_line(t_point first, t_point second,\
							t_graf *graf);
int							start_map(t_graf *graf, char *line);

#endif

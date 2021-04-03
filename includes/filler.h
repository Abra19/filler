/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:22:14 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:11:58 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Player of Filler game
** In this game, two players fight each other. They play one after the other.
** The goal is to collect as many points as possible by placing
** the highest number of pieces on the the game board.
** The board is defined by X columns and N lines.
** At the beginning of each turn game piece appears.
** A game piece is defined by x columns and n lines, but inside
** each game piece included a shape marked by *: realy figure to place.
** For placing a piece on the board, it is mandatory that one, and only one
** cell of the shape covers the cell of a shape that you place previously.
** The shape must not exceed the dimensions of the board.
** When the game starts, the board already contains one shape.
** The game stops at the first error: either when a game piece cannot be placed
** anymore or it has been wrongly placed.
** Goal is to win.
** The board and the game pieces placed on the standard output.
** In order to place the game piece on the board, the player write
** coordinates of piece (not shape) on the standard ouput in format: X Y\n
** Bonus: graphic vizualizer ./draw
*/

#ifndef FILLER_H
# define FILLER_H

# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"
# include <sys/types.h>
# include <signal.h>

# define MYFIG		-1
# define RFIG		-2

/*
** my_id: sym for my player
** rival_id: sym for rival player
** name1, name2 - strings for gamers names
** score1, score2 - strings for results of game
** t_start_x, t_start_y, t_end_x, t_end_y: numbers of empty lines, columns
** width: width of board
** height: height of board
** t_width: width of token
** t_height: height of token
** map: array for map sym
** count, flag, exit_flag: technical param - terminated flags
** heat_map: int array for heat map
** token: array of sym for keep cut token - without empty lines
** btoken: initial token
** sum: min value of sum of value for * for token on heat map
** sum_x, sum_y: coords for min sum
** collision_x and y: coords of point of collision with rival
** mem_i, mem_j: memmory of coords of contact with RFIG
**	contact: intersection of MYFIG with token
** number of my turns
*/

typedef struct		s_filler
{
	char			my_id;
	char			rival_id;
	char			*name1;
	char			*name2;
	char			*score1;
	char			*score2;
	int				t_start_x;
	int				t_start_y;
	int				t_end_x;
	int				t_end_y;
	int				count;
	int				flag;
	int				width;
	int				height;
	int				t_width;
	int				t_height;
	char			**map;
	int				**heat_map;
	char			**token;
	char			**btoken;
	int				sum;
	int				sum_x;
	int				sum_y;
	int				collision_x;
	int				collision_y;
	int				contact;
	int				mem_i;
	int				mem_j;
	int				exit_flag;
	int				put;
}					t_filler;

void				alloc_btoken(t_filler *filler);
char				**alloc_full_token(t_filler *filler);
void				alloc_maps(t_filler *filler);
int					check_map(t_filler *filler);
void				choose_right_coord(int	sum, t_filler *filler, int i,\
					int j);
void				clean_up_map(void **map, int height);
void				clean_up_maps(t_filler *filler);
void				copy_token(t_filler *filler);
int					count_sum(t_filler *filler, int i, int j);
int					cut_token(t_filler *filler);
void				found_collision(t_filler *filler, int i, int j);
void				found_contact(t_filler *filler, int i, int j);
int					found_sizes(char *line, int *height, int *width);
int					get_players_id(t_filler *filler, char *line);
void				heat_map_create(t_filler *filler);
int					keep_token(t_filler *filler, char *line);
void				make_map(t_filler *filler, int i, char *line);
int					max_int(int a, int b);
int					parse_token(t_filler *filler, char *line);
int					read_token(t_filler *filler, int i, char *line);
void				reverse_map(t_filler *filler);
void				reverse_token(t_filler *filler);
void				save_coord(t_filler *filler, int i, char *line);

#endif

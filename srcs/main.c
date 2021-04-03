/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:19:13 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:27:17 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		start_pos(t_filler *filler, char *line)
{
	int		i;
	int		res;

	i = 0;
	alloc_maps(filler);
	while (i < filler->height)
	{
		if ((res = get_next_line(0, &line)) <= 0)
		{
			clean_up_map((void **)filler->map, i - 1);
			return (0);
		}
		if (res > 0)
			make_map(filler, i, line);
		i++;
	}
	if (filler->my_id == 'X')
		reverse_map(filler);
	if (check_map(filler) >= 0)
	{
		clean_up_maps(filler);
		return (0);
	}
	clean_up_map((void **)filler->map, filler->height + 1);
	return (1);
}

int		parse_map(t_filler *filler, char *line)
{
	int		res;

	if (found_sizes(line, &filler->height, &filler->width) == 0)
	{
		ft_strdel(&line);
		return (0);
	}
	ft_strdel(&line);
	if ((res = get_next_line(0, &line)) <= 0)
		return (0);
	if (res > 0)
	{
		if (line[4] != '0')
		{
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&line);
	}
	if (start_pos(filler, line) == 0)
		return (0);
	return (1);
}

int		parse_token_free(t_filler *filler, char *line)
{
	if (parse_token(filler, line) == 0)
	{
		clean_up_map((void **)filler->token, filler->t_height);
		clean_up_map((void **)filler->heat_map, filler->height);
		return (0);
	}
	clean_up_map((void **)filler->token, filler->t_height);
	clean_up_map((void **)filler->heat_map, filler->height);
	filler->count++;
	return (1);
}

int		filler_read(t_filler *filler, char *line)
{
	if (ft_strncmp(line, "$$$ exec p", 10) == 0)
	{
		if (get_players_id(filler, line) == 0)
			return (0);
		filler->flag = 1;
	}
	else if (ft_strncmp(line, "Plateau", 7) == 0)
	{
		if (parse_map(filler, line) == 0)
			return (0);
		filler->count++;
		heat_map_create(filler);
	}
	else if (ft_strncmp(line, "Piece", 5) == 0)
	{
		if (parse_token_free(filler, line) == 0)
			return (0);
	}
	else
	{
		ft_strdel(&line);
		return (0);
	}
	return (1);
}

int		main(void)
{
	t_filler	filler;
	char		*line;
	int			res;

	ft_bzero(&filler, sizeof(t_filler));
	while (filler.exit_flag == 0)
	{
		while ((res = get_next_line(0, &line)) >= 0)
		{
			if (res == 0)
				continue;
			else
			{
				if (filler_read(&filler, line) == 0)
					return (1);
				if (filler.count % 2 == 0 && filler.count != 0)
					filler.count = 0;
				if (filler.count == 0 && filler.flag == 0)
					exit(0);
			}
		}
	}
	return (0);
}

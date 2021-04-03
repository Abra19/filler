/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:21:00 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:41:00 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	handle_score(t_graf *graf, char *line)
{
	int		len;

	len = ft_strlen(line);
	graf->filler.score2 = ft_strsub((const char *)line, 10, len - 10);
	ft_strdel(&line);
	graf->exit_flag = 0;
	graf->stop = 1;
}

void	loop_filler_final(t_graf *graf, char *line)
{
	if (ft_strncmp(line, "== O", 4) == 0)
		handle_semifinal(graf, line);
	else if (ft_strncmp(line, "== X", 4) == 0)
		handle_score(graf, line);
	else if (ft_strncmp(line, "error:", 6) == 0)
	{
		ft_printf("bad map or bad player\n");
		kill(ft_atoi("pgrep 'dlaure.filler'"), 15);
		exit(0);
	}
}

int		loop_filler_body(t_graf *graf, char *line)
{
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strncmp(line, "launched", 8) == 0)
		{
			if (get_players_name(graf, line) == 0)
				return (0);
		}
		else if (ft_strncmp(line, "Plateau", 7) == 0)
		{
			parse_board_full(graf, line);
			return (1);
		}
		else if (ft_strncmp(line, "== O", 4) == 0 ||\
		ft_strncmp(line, "== X", 4) == 0 || ft_strncmp(line, "error", 5) == 0)
		{
			loop_filler_final(graf, line);
			return (1);
		}
		else
		{
			ft_strdel(&line);
			continue;
		}
	}
	return (1);
}

int		loop_filler(t_graf *graf)
{
	char	*line;

	line = NULL;
	loop_filler_body(graf, line);
	return (1);
}

int		loop_hook(t_graf *graf)
{
	loop_filler(graf);
	if (graf->exit_flag == 1)
	{
		draw_filler(graf);
		clean_up_map_d((void **)graf->map.color, graf->map.ln_count);
		graf->exit_flag = 0;
	}
	else if (graf->stop == 1)
	{
		print_game_score(graf);
		ft_strdel(&graf->filler.name1);
		ft_strdel(&graf->filler.name2);
		ft_strdel(&graf->filler.score1);
		ft_strdel(&graf->filler.score2);
	}
	return (1);
}

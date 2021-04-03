/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:21:00 by dlaure            #+#    #+#             */
/*   Updated: 2020/03/30 13:42:42 by elena_abrarova   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int		parse_board(t_graf *graf, char *line)
{
	int		res;

	if (found_sizes_d(line, &graf->filler.height, &graf->filler.width) == 0)
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
	if (start_map(graf, line) == 0)
		return (0);
	return (1);
}

char	*check_name(char *line)
{
	int		i;
	int		j;
	char	*str;

	if (line[9] == 'p')
		i = 17;
	else if (line[9] == '.')
		i = 11;
	else
	{
		ft_printf("bad player \n");
		kill(ft_atoi("pgrep 'dlaure.filler'"), 15);
		exit(0);
	}
	j = i;
	while (line[i] != '\0')
	{
		if (line[i] == '.')
			break ;
		i++;
	}
	str = ft_strsub((const char *)line, j, i - j);
	return (str);
}

int		get_players_name(t_graf *graf, char *line)
{
	int		res;

	graf->filler.name1 = check_name(line);
	ft_strdel(&line);
	if ((res = get_next_line(0, &line)) <= 0)
	{
		ft_strdel(&graf->filler.name1);
		return (0);
	}
	if (res > 0)
		ft_strdel(&line);
	if ((res = get_next_line(0, &line)) <= 0)
	{
		ft_strdel(&graf->filler.name1);
		return (0);
	}
	if (res > 0)
	{
		graf->filler.name2 = check_name(line);
		ft_strdel(&line);
	}
	return (1);
}

int		parse_board_full(t_graf *graf, char *line)
{
	if (parse_board(graf, line) == 0)
		return (0);
	copy_map(graf);
	graf->exit_flag = 1;
	clean_up_map_d((void **)graf->filler.map, graf->filler.height + 1);
	return (1);
}

void	handle_semifinal(t_graf *graf, char *line)
{
	int		len;

	len = ft_strlen(line);
	graf->filler.score1 = ft_strsub((const char *)line, 10, len - 10);
	ft_strdel(&line);
}

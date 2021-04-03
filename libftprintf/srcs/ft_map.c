/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:07:12 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 19:07:15 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** map functions count index of array of pointer function
*/

int		map1(char *str)
{
	if (ft_strcmp((const char*)str, "c") == 0 ||\
		ft_strcmp((const char*)str, "lc") == 0)
		return (0);
	else if (ft_strcmp((const char*)str, "s") == 0)
		return (1);
	else if (ft_strcmp((const char*)str, "ls") == 0)
		return (2);
	else if (ft_strcmp((const char*)str, "hhd") == 0 ||\
		ft_strcmp((const char*)str, "hhi") == 0 ||\
		ft_strcmp((const char*)str, "hd") == 0 ||\
		ft_strcmp((const char*)str, "hi") == 0 ||\
		ft_strcmp((const char*)str, "d") == 0 ||\
		ft_strcmp((const char*)str, "i") == 0 ||\
		ft_strcmp((const char*)str, "ld") == 0 ||\
		ft_strcmp((const char*)str, "li") == 0 ||\
		ft_strcmp((const char*)str, "lld") == 0 ||\
		ft_strcmp((const char*)str, "lli") == 0)
		return (3);
	else if (ft_strcmp((const char*)str, "b") == 0)
		return (4);
	else if (ft_strcmp((const char*)str, "w") == 0)
		return (5);
	else
		return (-1);
}

int		map2(char *str)
{
	if (ft_strcmp((const char*)str, "p") == 0)
		return (6);
	else if (ft_strcmp((const char*)str, "r") == 0)
		return (7);
	if (ft_strcmp((const char*)str, "hho") == 0 ||\
		ft_strcmp((const char*)str, "ho") == 0 ||\
		ft_strcmp((const char*)str, "o") == 0 ||\
		ft_strcmp((const char*)str, "lo") == 0 ||\
		ft_strcmp((const char*)str, "llo") == 0)
		return (8);
	else if (ft_strcmp((const char*)str, "hhx") == 0 ||\
		ft_strcmp((const char*)str, "hhX") == 0 ||\
		ft_strcmp((const char*)str, "hx") == 0 ||\
		ft_strcmp((const char*)str, "hX") == 0 ||\
		ft_strcmp((const char*)str, "x") == 0 ||\
		ft_strcmp((const char*)str, "X") == 0 ||\
		ft_strcmp((const char*)str, "lx") == 0 ||\
		ft_strcmp((const char*)str, "lX") == 0 ||\
		ft_strcmp((const char*)str, "llx") == 0 ||\
		ft_strcmp((const char*)str, "llX") == 0)
		return (9);
	else
		return (-1);
}

int		map3(char *str)
{
	if (ft_strcmp((const char*)str, "hhu") == 0 ||\
		ft_strcmp((const char*)str, "hu") == 0 ||\
		ft_strcmp((const char*)str, "u") == 0 ||\
		ft_strcmp((const char*)str, "lu") == 0 ||\
		ft_strcmp((const char*)str, "llu") == 0)
		return (10);
	else if (ft_strcmp((const char*)str, "f") == 0 ||\
		ft_strcmp((const char*)str, "F") == 0 ||\
		ft_strcmp((const char*)str, "lf") == 0 ||\
		ft_strcmp((const char*)str, "lF") == 0 ||\
		ft_strcmp((const char*)str, "Lf") == 0 ||\
		ft_strcmp((const char*)str, "LF") == 0)
		return (11);
	else
		return (-1);
}

int		map4(char *str)
{
	if (ft_strcmp((const char*)str, "e") == 0 ||\
		ft_strcmp((const char*)str, "E") == 0 ||\
		ft_strcmp((const char*)str, "le") == 0 ||\
		ft_strcmp((const char*)str, "lE") == 0 ||\
		ft_strcmp((const char*)str, "Le") == 0 ||\
		ft_strcmp((const char*)str, "LE") == 0)
		return (12);
	else if (ft_strcmp((const char*)str, "g") == 0 ||\
		ft_strcmp((const char*)str, "G") == 0 ||\
		ft_strcmp((const char*)str, "lg") == 0 ||\
		ft_strcmp((const char*)str, "lG") == 0 ||\
		ft_strcmp((const char*)str, "Lg") == 0 ||\
		ft_strcmp((const char*)str, "LG") == 0)
		return (13);
	else
		return (-1);
}

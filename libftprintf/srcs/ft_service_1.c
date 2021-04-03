/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_service_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:59:23 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 19:59:25 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_error(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
	return (0);
}

/*
** is specifier return 1
*/

int			is_spec(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' ||\
		c == 'o' || c == 'u' || c == 'x' || c == 'X' || c == 'b' ||\
		c == 'r' || c == 'f' || c == 'e' || c == 'E' || c == 'g' ||\
		c == 'G' || c == 'w' || c == 'F')
		return (1);
	return (0);
}

/*
** is digit (not equal 0) - return 1
*/

int			ft_isdigit_0(int c)
{
	if (c > 48 && c <= 57)
		return (1);
	return (0);
}

/*
** abs of number
*/

uint64_t	abs_int(long long a)
{
	return ((a >= 0) ? (uint64_t)a : (uint64_t)-a);
}

/*
** service function for check_and_parce
*/

int			compare(t_ptf *pr)
{
	if (pr->frt[pr->pos] != '.' && is_spec(pr->frt[pr->pos]) != 1\
		&& pr->frt[pr->pos] != '$' && pr->frt[pr->pos] != 'l' &&\
		pr->frt[pr->pos] != 'L' && pr->frt[pr->pos] != 'h')
		return (0);
	return (1);
}

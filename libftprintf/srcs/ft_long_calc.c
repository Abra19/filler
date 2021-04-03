/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:47:30 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 18:47:32 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_l(int *x, int *y)
{
	int		i;
	int		c;

	c = 0;
	i = 0;
	while (i < MAXLEN)
	{
		c = x[i] + y[i] + c;
		x[i] = c % BASE;
		c = c / BASE;
		i++;
	}
}

void	mult_l(int *res, int *x, int n)
{
	int		i;
	int		c;

	c = 0;
	i = 0;
	while (i < MAXLEN)
	{
		c = x[i] * n + c;
		res[i] = c % BASE;
		c = c / BASE;
		i++;
	}
}

/*
** addition with n < BASELEN
*/

void	add_l_n(int *x, int n)
{
	int		i;
	int		c;

	i = 1;
	c = x[0] + n;
	x[0] = c % BASE;
	c = c / BASE;
	while (i < MAXLEN)
	{
		c = x[i] + c;
		x[i] = c % BASE;
		c = c / BASE;
		i++;
	}
}

void	div_long(int *x, int n)
{
	int		c;
	int		i;

	c = 0;
	i = MAXLEN - 1;
	while (i >= 0)
	{
		c = c * BASE + x[i];
		x[i] = c / n;
		c = c % n;
		i--;
	}
}

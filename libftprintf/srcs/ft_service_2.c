/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_service_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:06:31 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:06:33 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	ft_atol(const char *str)
{
	long long int	nb;
	int				i;
	int				p;

	nb = 0;
	i = 0;
	p = 0;
	while (str[i] < 32 && str[i] != '\0')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		p = i;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
		nb = 10 * nb + (str[i++] - '0');
	if (str[p] == '-')
		return (-nb);
	return (nb);
}

/*
** write space of defined size
*/

void		write_blank(t_ptf *pr, size_t len)
{
	size_t			i;

	i = 1;
	while (i < len)
	{
		pr->buff[pr->i] = 32;
		i++;
		pr->i++;
	}
}

/*
** service functions
*/

size_t		long_sym(size_t a, size_t b, size_t c)
{
	if (a <= 0)
		return (max_len(b, c));
	else
	{
		if (a >= b)
			return (b);
		else
			return (a);
	}
}

size_t		max_len(size_t a, size_t b)
{
	return (a >= b ? a : b);
}

long double	abs_int_f(long double fnbr)
{
	long double		a;

	a = (fnbr >= 0) ? fnbr : -fnbr;
	return (a);
}

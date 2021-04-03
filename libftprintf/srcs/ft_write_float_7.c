/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_float_7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:36:25 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:36:27 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_res(t_ptf *pr, char *res, int *i, int *m)
{
	int			j;
	char		*str;
	int			n;

	j = 0;
	str = ft_uitoa_base(pr->base, pr->fround[*i]);
	n = BASELEN - ft_strlen(str);
	while (n-- > 0 && (*i != 0 || *m != 0))
	{
		res[*m] = '0';
		*m = *m + 1;
	}
	while (str[j] != '\0')
	{
		res[*m] = str[j++];
		*m = *m + 1;
	}
	ft_strdel(&str);
}

void	write_inttoa_f(t_ptf *pr, char *res, int k)
{
	int			i;
	int			j;
	int			m;
	char		*str;

	i = k - 1;
	m = 0;
	if (pr->fround[k] != 0)
	{
		j = 0;
		str = ft_uitoa_base(pr->base, pr->fround[k]);
		while (str[j] != '\0')
			res[m++] = str[j++];
		ft_strdel(&str);
	}
	while (i >= 0)
	{
		write_res(pr, res, &i, &m);
		i--;
	}
}

void	rounder_for_float(t_ptf *pr, t_ldbl *dbl)
{
	if ((pr->fround[0] % pr->base >= 5) &&\
		(((pr->fround[0] / pr->base) % 2 != 0) || (int)dbl->field.mant != 0))
	{
		add_l_n(pr->fround, 5);
		pr->dround--;
		pr->flag = 1;
	}
	if (pr->dround == 2)
	{
		if ((pr->fround[0] % pr->base < 5) &&\
			(pr->fround[0] / pr->base) % pr->base >= 5)
		{
			add_l_n(pr->fround, 5);
			pr->dround--;
			pr->flag = 1;
		}
	}
}

int		n_round(t_ptf *pr, t_ldbl *dbl)
{
	int			n;
	long long	nbr;
	int			flag;

	n = pr->dround;
	flag = 0;
	nbr = (long long)pr->fround[0];
	rounder_for_float(pr, dbl);
	if (ft_nbrlen((long long)pr->fround[0], pr->base) > \
		ft_nbrlen(nbr, pr->base))
		flag = 1;
	if (pr->dround < n || (pr->fround[0] % pr->base) == 0)
		div_long(pr->fround, 10);
	return (flag);
}

int		round_long_f(t_ptf *pr, char *res, int k, t_ldbl *dbl)
{
	int			flag;
	int			i;
	int			d;

	i = 0;
	d = pr->dround;
	pr->flag = 0;
	while (i < d)
	{
		flag = n_round(pr, dbl);
		i++;
	}
	write_inttoa_f(pr, res, k);
	return (flag);
}

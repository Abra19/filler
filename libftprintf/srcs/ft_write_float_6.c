/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_float_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:30:44 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:30:45 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_zero_f(t_prs *prs)
{
	if (is_flag_zero(prs) != 0 && prs->c_width == 0 && !is_flag_minus(prs))
		prs->sym = 48;
	else
		prs->sym = 32;
}

void	f_int_part(t_ldbl *dbl, t_ptf *pr, char *str)
{
	int			i;
	int			exp;
	int			b;

	i = 0;
	exp = dbl->field.exp - POWSIZE + 1;
	b = (exp <= LEN) ? exp : LEN;
	while (i <= b && (exp - i) >= 0)
	{
		if (str[i] == '1')
			add_l(pr->fint, pr->flnbr[exp - i]);
		i++;
	}
}

void	f_frac_part(t_ldbl *dbl, t_ptf *pr, char *str)
{
	int			exp;
	int			i;
	long double	rd;

	exp = dbl->field.exp - POWSIZE + 1;
	pr->frac = 0.0;
	rd = 0.5;
	if (exp < 64)
	{
		i = exp + 1;
		while (i <= 64)
		{
			if (i >= 0)
			{
				if (str[i] == '1')
					pr->frac = pr->frac + rd;
			}
			rd = rd * 0.5;
			i++;
		}
	}
}

void	process_binary(t_ldbl *dbl, t_ptf *pr, t_prs *prs)
{
	char		*str;

	if (dbl->field.mant == 0 && dbl->field.exp == 0)
	{
		prs->fnbr = 0;
		pr->frac = 0;
	}
	else
	{
		str = ft_itoa_mant(dbl);
		f_int_part(dbl, pr, str);
		f_frac_part(dbl, pr, str);
		ft_strdel(&str);
	}
}

void	flag_first_f(t_prs *prs, t_ldbl *dbl)
{
	if (is_flag_plus(prs) && dbl->field.sign != 1)
		prs->first = '+';
	else if (!is_flag_plus(prs) && is_flag_space(prs) && dbl->field.sign != 1)
		prs->first = 32;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_inf_nan.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:39:04 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:39:06 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_inf(t_prs *prs, t_ldbl *dbl)
{
	if (dbl->field.sign == 1)
		prs->first = '-';
	else if (is_flag_plus(prs) && dbl->field.sign == 0)
		prs->first = '+';
	else if (is_flag_space(prs))
		prs->first = 32;
	else
		prs->first = 0;
}

void	inf_first(t_ptf *pr, t_prs *prs, int n)
{
	int			i;

	if (is_flag_minus(prs))
	{
		pr->buff[pr->i++] = prs->first;
		write_inf(pr, n);
		i = 4;
		while (i++ < prs->width)
			pr->buff[pr->i++] = 32;
	}
	else
	{
		i = 0;
		while (i++ < prs->width - 4)
			pr->buff[pr->i++] = 32;
		pr->buff[pr->i++] = prs->first;
		write_inf(pr, n);
	}
}

void	inf_abs_first(t_ptf *pr, t_prs *prs, int n)
{
	int			i;

	if (is_flag_minus(prs))
	{
		write_inf(pr, n);
		i = 3;
		while (i++ < prs->width)
			pr->buff[pr->i++] = 32;
	}
	else
	{
		i = 0;
		while (i++ < prs->width - 3)
			pr->buff[pr->i++] = 32;
		write_inf(pr, n);
	}
}

void	inf_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	long long	n;

	n = ((prs->string[ft_strlen(prs->string) - 1] == 'f') ||\
		(prs->string[ft_strlen(prs->string) - 1] == 'e') ||\
		(prs->string[ft_strlen(prs->string) - 1] == 'g')) ? 32 : 0;
	flag_inf(prs, dbl);
	if (prs->first != 0)
		inf_first(pr, prs, n);
	else
		inf_abs_first(pr, prs, n);
}

void	nan_f(t_ptf *pr, t_prs *prs)
{
	long long	n;
	int			i;

	n = ((prs->string[ft_strlen(prs->string) - 1] == 'f') ||\
		(prs->string[ft_strlen(prs->string) - 1] == 'e') ||\
		(prs->string[ft_strlen(prs->string) - 1] == 'g')) ? 32 : 0;
	if (is_flag_minus(prs))
	{
		write_nan(pr, n);
		i = 3;
		while (i++ < prs->width)
			pr->buff[pr->i++] = 32;
	}
	else
	{
		i = 0;
		while (i++ < prs->width - 3)
			pr->buff[pr->i++] = 32;
		write_nan(pr, n);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 06:28:38 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 06:28:40 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	first_g_align(t_ptf *pr, t_prs *prs)
{
	int		j;

	j = 0;
	if (pr->count == 0 && prs->nul_prc != 1)
		prs->num--;
	if (prs->fnbr < 0 && prs->nul_prc != 0 && is_flag_hach(prs))
		prs->num++;
	if (is_flag_hach(prs))
	{
		while (j++ < prs->width - (prs->pr_pk - 1) - prs->sizef - prs->num)
			pr->buff[pr->i++] = prs->sym;
	}
	else
	{
		while (j++ < prs->width - pr->count - 1 - prs->sizef - prs->num)
			pr->buff[pr->i++] = prs->sym;
	}
}

void	first_g_align_null(t_ptf *pr, t_prs *prs)
{
	int		j;

	j = 0;
	if (pr->count == 0 && prs->nul_prc != 1)
		prs->num--;
	if (is_flag_hach(prs))
	{
		while (j++ < prs->width - (prs->pr_pk - 1) - prs->sizef - prs->num)
			pr->buff[pr->i++] = prs->sym;
	}
	else
	{
		while (j++ < prs->width - pr->count - prs->sizef - prs->num)
			pr->buff[pr->i++] = prs->sym;
	}
}

void	right_f_init(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	if (prs->fnbr == 0)
		prs->sizef = 1;
	if (dbl->field.exp == 15361)
		prs->sizef++;
	if ((prs->first != 0 && dbl->field.exp != 32767))
	{
		if (prs->sym != 32)
		{
			pr->buff[pr->i++] = prs->first;
			first_f_align(pr, prs);
		}
		else
		{
			first_f_align(pr, prs);
			pr->buff[pr->i++] = prs->first;
		}
	}
	else if (dbl->field.exp != 32767 && prs->width != 0)
		first_f_align(pr, prs);
}

void	rounder_g(t_ptf *pr, t_ldbl *dbl)
{
	if ((pr->fround[0] % pr->base >= 5) &&
		(((pr->fround[0] / pr->base) % 2 != 0) || \
		(int)dbl->field.mant != 0))
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

int		n_round_fg(t_ptf *pr, t_ldbl *dbl)
{
	int			n;
	long long	nbr;
	int			flag;

	n = pr->dround;
	flag = 0;
	nbr = (long long)pr->fround[0];
	rounder_g(pr, dbl);
	if (ft_nbrlen((long long)pr->fround[0], pr->base) > \
		ft_nbrlen(nbr, pr->base))
		flag = 1;
	if (pr->dround < n || (pr->fround[0] % pr->base) == 0)
		div_long(pr->fround, 10);
	return (flag);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_float_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:00:42 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:00:45 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "f" + "F"
** or "lf" + "lF" or "Lf" + "LF"
*/

void	add_space_f(t_ptf *pr, t_prs *prs, int size, int n)
{
	int		j;

	j = 0;
	while (j++ < prs->width - prs->prc - size - n)
		pr->buff[pr->i++] = prs->sym;
}

void	float_align_r(t_ptf *pr, t_prs *prs, int size, int n)
{
	if (prs->sym != 32)
	{
		pr->buff[pr->i++] = prs->first;
		add_space_f(pr, prs, size, n);
	}
	else
	{
		add_space_f(pr, prs, size, n);
		pr->buff[pr->i++] = prs->first;
	}
}

int		align_right_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	int		n;
	int		size;
	char	*res;

	res = NULL;
	if (dbl->field.exp != 32767)
	{
		n = count_n(prs);
		res = union_parts_f(pr, prs, dbl);
		size = prs->wc;
	}
	if (dbl->field.exp == 15361)
		size++;
	if (prs->first != 0 && prs->fnbr != 0 && dbl->field.exp != 32767)
		float_align_r(pr, prs, size, n);
	else if (prs->fnbr != 0 && dbl->field.exp != 32767)
		add_space_f(pr, prs, size, n);
	buff_nbr_f(pr, prs, dbl, res);
	if (dbl->field.exp != 32767)
		ft_strdel(&res);
	return (1);
}

int		count_n(t_prs *prs)
{
	int n;

	n = (prs->first != 0 || is_flag_hach(prs) != 0 || prs->prc != 0) ? 1 : 0;
	if ((prs->first != 0 && is_flag_hach(prs) != 0) || \
		(prs->first != 0 && prs->prc != 0))
		n = 2;
	return (n);
}

int		align_left_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	int		size;
	char	*res;

	res = left_res(pr, prs, dbl, &size);
	if (dbl->field.exp == 15361)
		size++;
	if (prs->first != 0 && prs->fnbr != 0 && dbl->field.exp != 32767)
	{
		pr->buff[pr->i++] = prs->first;
		buff_nbr_f(pr, prs, dbl, res);
		add_space_f(pr, prs, size, count_n(prs));
	}
	else if (prs->fnbr != 0 && dbl->field.exp != 32767)
	{
		buff_nbr_f(pr, prs, dbl, res);
		add_space_f(pr, prs, size, count_n(prs));
	}
	else
		buff_nbr_f(pr, prs, dbl, res);
	if (dbl->field.exp != 32767)
		ft_strdel(&res);
	return (1);
}

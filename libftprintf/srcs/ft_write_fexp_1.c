/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fexp_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:33:17 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:33:19 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		align_right_fe(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	int		size;
	char	*res;
	int		n;

	res = NULL;
	n = (prs->prc == 0 && !is_flag_hach(prs)) ? 3 : 4;
	if (dbl->field.exp != 32767)
	{
		count_exp(pr, prs);
		res = union_parts(pr, prs);
		if (pr->dround == 1 && (ft_nbrlen(abs_int_f(prs->fnbr) + 5, pr->base) >\
			ft_nbrlen(abs_int_f(prs->fnbr), pr->base)))
			prs->exp++;
		size = ft_nbrlen((long long)prs->exp, pr->base);
		if (prs->exp < 10)
			size++;
	}
	if (prs->first != 0 && prs->fnbr != 0 && dbl->field.exp != 32767)
		float_align_r(pr, prs, n + 1, size);
	else if (prs->fnbr != 0 && dbl->field.exp != 32767)
		add_space_f(pr, prs, n, size);
	buff_nbr_fe(pr, prs, dbl, res);
	if (dbl->field.exp != 32767)
		ft_strdel(&res);
	return (1);
}

void	first_ne_zero(t_ptf *pr, t_prs *prs, t_ldbl *dbl, char *res)
{
	pr->buff[pr->i++] = prs->first;
	buff_nbr_fe(pr, prs, dbl, res);
}

char	*prepare_write_exp(t_ptf *pr, t_prs *prs, int *size)
{
	char	*res;

	count_exp(pr, prs);
	res = union_parts(pr, prs);
	if (pr->dround == 1 && (ft_nbrlen(prs->fnbr + 5, pr->base) >\
			ft_nbrlen(prs->fnbr, pr->base)))
		prs->exp++;
	*size = ft_nbrlen((long long)prs->exp, pr->base);
	if (prs->exp < 10)
		*size = *size + 1;
	return (res);
}

int		align_left_fe(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	int		size;
	char	*res;
	int		n;

	n = (prs->prc == 0 && !is_flag_hach(prs)) ? 3 : 4;
	if (dbl->field.exp != 32767)
		res = prepare_write_exp(pr, prs, &size);
	if (prs->first != 0 && prs->fnbr != 0 && dbl->field.exp != 32767)
	{
		first_ne_zero(pr, prs, dbl, res);
		add_space_f(pr, prs, n + 1, size);
	}
	else if (prs->fnbr != 0 && dbl->field.exp != 32767)
	{
		buff_nbr_fe(pr, prs, dbl, res);
		add_space_f(pr, prs, n, size);
	}
	else
		buff_nbr_fe(pr, prs, dbl, res);
	if (dbl->field.exp != 32767)
		ft_strdel(&res);
	return (1);
}

int		process_fnegative_e(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	prs->first = '-';
	flag_zero_f(prs);
	if (prs->flags != 0)
	{
		if (is_flag_minus(prs) || prs->c_width == 1)
			align_left_fe(pr, prs, dbl);
		else
			align_right_fe(pr, prs, dbl);
	}
	else
	{
		if (prs->c_width == 1)
			align_left_fe(pr, prs, dbl);
		else
			align_right_fe(pr, prs, dbl);
	}
	return (1);
}

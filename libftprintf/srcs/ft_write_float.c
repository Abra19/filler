/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:49:14 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:49:19 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "f" + "F"
** or "lf" + "lF" or "Lf" + "LF"
*/

int		process_fnegative(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	prs->first = '-';
	flag_zero_f(prs);
	if (prs->flags != 0)
	{
		if (is_flag_minus(prs) || prs->c_width == 1)
			align_left_f(pr, prs, dbl);
		else
			align_right_f(pr, prs, dbl);
	}
	else
	{
		if (prs->c_width == 1)
			align_left_f(pr, prs, dbl);
		else
			align_right_f(pr, prs, dbl);
	}
	return (1);
}

int		flag_null_fnbr(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	if (prs->c_width == 1)
		align_left_f(pr, prs, dbl);
	else
		align_right_f(pr, prs, dbl);
	return (1);
}

int		flag_fnbr(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	flag_zero_f(prs);
	flag_first_f(prs, dbl);
	if (is_flag_minus(prs) || prs->c_width == 1)
		align_left_f(pr, prs, dbl);
	else
		align_right_f(pr, prs, dbl);
	return (1);
}

int		read_float(t_ptf *pr, t_prs *prs)
{
	pr->lflag = 0;
	if (ft_strcmp((const char*)prs->string, "f") == 0 ||\
		ft_strcmp((const char*)prs->string, "F") == 0 ||\
		ft_strcmp((const char*)prs->string, "lf") == 0 ||\
		ft_strcmp((const char*)prs->string, "lF") == 0)
		prs->fnbr = (long double)va_arg(pr->ap, double);
	else if (ft_strcmp((const char*)prs->string, "Lf") == 0 ||\
		ft_strcmp((const char*)prs->string, "LF") == 0)
	{
		prs->fnbr = va_arg(pr->ap, long double);
		pr->lflag = 1;
	}
	else
		return (0);
	return (1);
}

int		hand_float(t_ptf *pr, t_prs *prs)
{
	t_ldbl	dbl;

	pr->base = 10;
	if (read_float(pr, prs) == -1)
		return (0);
	if ((prs->no_prc == 1 || prs->n_mark == 1) || prs->prc < 0)
		prs->prc = 6;
	if (prs->flag_prc == 1 && (prs->no_prc == 1 || prs->n_mark == 1))
		prs->prc = 0;
	dbl.nbr = prs->fnbr;
	pr->fint = (int*)ft_memalloc(sizeof(int) * MAXLEN + prs->prc);
	process_binary(&dbl, pr, prs);
	if (prs->fnbr >= 0)
	{
		if (prs->flags != 0)
			flag_fnbr(pr, prs, &dbl);
		else
			flag_null_fnbr(pr, prs, &dbl);
	}
	else
		process_fnegative(pr, prs, &dbl);
	ft_memdel((void **)&(pr->fint));
	return (1);
}

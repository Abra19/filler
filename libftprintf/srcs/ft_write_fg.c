/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:39:32 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:39:35 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "g" + "G"
** or "lg" + "lG" or "Lg" + "LG"
*/

int		process_fnegative_g(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	int		prc;
	int		exp;

	prs->first = '-';
	flag_zero_fg(prs);
	fe_choice(pr, prs, &prc, &exp);
	prs->pk = prc;
	prs->el = exp;
	if (prs->flags != 0)
	{
		if (is_flag_minus(prs) || prs->c_width == 1)
			align_left_fg(pr, prs, dbl);
		else
			align_right_fg(pr, prs, dbl);
	}
	else
	{
		if (prs->c_width == 1)
			align_left_fg(pr, prs, dbl);
		else
			align_right_fg(pr, prs, dbl);
	}
	return (1);
}

int		flag_null_fnbr_g(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	int		prc;
	int		exp;

	flag_first_fg(prs, dbl);
	fe_choice(pr, prs, &prc, &exp);
	prs->pk = prc;
	prs->el = exp;
	if (prs->c_width == 1)
		align_left_fg(pr, prs, dbl);
	else
		align_right_fg(pr, prs, dbl);
	return (1);
}

int		flag_fnbr_g(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	int		exp;
	int		prc;

	flag_zero_fg(prs);
	flag_first_fg(prs, dbl);
	fe_choice(pr, prs, &prc, &exp);
	prs->pk = prc;
	prs->el = exp;
	if (is_flag_minus(prs) || prs->c_width == 1)
		align_left_fg(pr, prs, dbl);
	else
		align_right_fg(pr, prs, dbl);
	return (1);
}

int		read_float_g(t_ptf *pr, t_prs *prs)
{
	if (ft_strcmp((const char*)prs->string, "g") == 0 ||\
		ft_strcmp((const char*)prs->string, "G") == 0 ||\
		ft_strcmp((const char*)prs->string, "lg") == 0 ||\
		ft_strcmp((const char*)prs->string, "lG") == 0)
		prs->fnbr = (long double)va_arg(pr->ap, double);
	else if (ft_strcmp((const char*)prs->string, "Lg") == 0 ||\
		ft_strcmp((const char*)prs->string, "LG") == 0)
		prs->fnbr = va_arg(pr->ap, long double);
	else
		return (0);
	return (1);
}

int		hand_f_g(t_ptf *pr, t_prs *prs)
{
	t_ldbl		dbl;

	pr->base = 10;
	if (read_float_g(pr, prs) == -1)
		return (0);
	if ((prs->no_prc == 1 || prs->n_mark == 1) || prs->prc < 0)
		prs->prc = 6;
	if ((prs->flag_prc == 1) && ((prs->no_prc == 1 || prs->n_mark == 1)))
		prs->prc = 0;
	dbl.nbr = prs->fnbr;
	pr->fint = (int*)ft_memalloc(sizeof(int) * MAXLEN + prs->prc);
	process_binary(&dbl, pr, prs);
	if (prs->fnbr >= 0)
	{
		if (prs->flags != 0)
			flag_fnbr_g(pr, prs, &dbl);
		else
			flag_null_fnbr_g(pr, prs, &dbl);
	}
	else
		process_fnegative_g(pr, prs, &dbl);
	ft_memdel((void**)&pr->fint);
	return (1);
}

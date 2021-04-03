/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_float_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:56:37 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:56:38 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "f" + "F"
** or "lf" + "lF" or "Lf" + "LF"
*/

void	zero_abs_first(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	if (!is_flag_minus(prs) && prs->c_width != 1)
		add_space_f(pr, prs, 1, 2);
	pr->buff[pr->i++] = prs->first;
	pr->buff[pr->i++] = '0';
	if (is_flag_hach(prs) != 0 || prs->prc != 0)
		pr->buff[pr->i++] = '.';
	while (i++ < prs->prc)
		pr->buff[pr->i++] = '0';
	if (is_flag_minus(prs) || prs->c_width == 1)
		add_space_f(pr, prs, 1, 2);
}

void	zero_abs(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	if (!is_flag_minus(prs) && prs->c_width != 1)
		add_space_f(pr, prs, 1, 1);
	pr->buff[pr->i++] = '0';
	if (is_flag_hach(prs) != 0 || prs->prc != 0)
		pr->buff[pr->i++] = '.';
	while (i++ < prs->prc)
		pr->buff[pr->i++] = '0';
	if (is_flag_minus(prs) || prs->c_width == 1)
		add_space_f(pr, prs, 1, 1);
}

void	zero_right(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	pr->buff[pr->i++] = prs->first;
	prs->sym = 48;
	add_space_f(pr, prs, 1, 2);
	pr->buff[pr->i++] = '0';
	if (is_flag_hach(prs) != 0 || prs->prc != 0)
		pr->buff[pr->i++] = '.';
	while (i++ < prs->prc)
		pr->buff[pr->i++] = '0';
}

void	zero_left(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	prs->sym = 48;
	add_space_f(pr, prs, 1, 1);
	pr->buff[pr->i++] = '0';
	if (is_flag_hach(prs) != 0 || prs->prc != 0)
		pr->buff[pr->i++] = '.';
	while (i++ < prs->prc)
		pr->buff[pr->i++] = '0';
}

void	print_null_prc_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	flag_f_null(prs, dbl);
	if (prs->first != 0)
	{
		if (!is_flag_zero(prs))
			zero_abs_first(pr, prs);
		else
			zero_right(pr, prs);
	}
	else
	{
		if (!is_flag_zero(prs))
			zero_abs(pr, prs);
		else
			zero_left(pr, prs);
	}
}

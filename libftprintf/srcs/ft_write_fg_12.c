/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg_12.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 06:59:02 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 06:59:05 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printf_first_null(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	if (!is_flag_zero(prs))
	{
		if (!is_flag_minus(prs) && prs->c_width != 1 && !is_flag_hach(prs))
			add_space_f(pr, prs, 1, 2);
		pr->buff[pr->i++] = '0';
		if (is_flag_hach(prs) != 0 || prs->prc != 0)
			pr->buff[pr->i++] = '.';
		while (i++ < prs->prc)
			pr->buff[pr->i++] = '0';
		if (is_flag_minus(prs) || prs->c_width == 1)
			add_space_f(pr, prs, 1, 2);
	}
	else
	{
		pr->buff[pr->i++] = '0';
		if (is_flag_hach(prs) != 0 || prs->prc != 0)
			pr->buff[pr->i++] = '.';
		while (i++ < prs->prc)
			pr->buff[pr->i++] = '0';
		add_space_f(pr, prs, 1, 2);
	}
}

void	print_abs_null(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	if (!is_flag_zero(prs))
	{
		pr->buff[pr->i++] = '0';
		if (is_flag_hach(prs) != 0 || prs->prc != 0)
			pr->buff[pr->i++] = '.';
		while (i++ < prs->prc)
			pr->buff[pr->i++] = '0';
	}
	else
	{
		pr->buff[pr->i++] = '0';
		if (is_flag_hach(prs) != 0 || prs->prc != 0)
			pr->buff[pr->i++] = '.';
		while (i++ < prs->prc)
			pr->buff[pr->i++] = '0';
	}
}

void	print_null_prc_fg(t_ptf *pr, t_prs *prs)
{
	if (is_flag_hach(prs) && prs->flag_prc == 0)
		prs->prc = 5;
	else if (is_flag_hach(prs))
		prs->prc = prs->prc - 1;
	if (prs->first != 0)
		printf_first_null(pr, prs);
	else
		print_abs_null(pr, prs);
}

void	flag_zero_fg(t_prs *prs)
{
	if ((is_flag_zero(prs) && !is_flag_minus(prs)) || (is_flag_hach(prs) &&\
		is_flag_minus(prs)))
		prs->sym = 48;
	else
		prs->sym = 32;
}

void	flag_first_fg(t_prs *prs, t_ldbl *dbl)
{
	if (is_flag_plus(prs))
	{
		if (dbl->field.sign == 1)
			prs->first = '-';
		else
			prs->first = '+';
	}
	else if (is_flag_space(prs))
	{
		if (dbl->field.sign == 1)
			prs->first = '-';
		else
			prs->first = 32;
	}
	else if (dbl->field.sign == 1)
		prs->first = '-';
	else
		prs->first = 0;
}

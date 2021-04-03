/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_unbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:54:44 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:54:45 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** service functions for unsigned nbr
*/

void	unbr_first_sym(t_ptf *pr, t_prs *prs, int size)
{
	int		j;

	j = 0;
	if (prs->sym == 32)
	{
		while (j++ < size)
			pr->buff[pr->i++] = prs->sym;
		pr->buff[pr->i++] = prs->first;
	}
	else
	{
		pr->buff[pr->i++] = prs->first;
		while (j++ < size)
			pr->buff[pr->i++] = prs->sym;
	}
}

void	align_right_u(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	int		j;
	int		n;
	int		size;

	j = 0;
	n = (prs->unbr == 0 && prs->flag_prc != 1) ? 1 : 0;
	if (prs->first != 0)
	{
		n++;
		size = (int)len - (int)prc - n;
		unbr_first_sym(pr, prs, size);
		add_zero(pr, prs);
	}
	else
	{
		while (j++ < (int)len - (int)prc - n)
			pr->buff[pr->i++] = prs->sym;
		add_zero(pr, prs);
	}
	process_zero_uvalue(pr, prs);
}

void	align_left_u(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	int		size;
	int		n;

	n = (prs->unbr == 0 && prs->flag_prc != 1) ? 1 : 0;
	size = (int)len - (int)prc;
	if (prs->first != 0)
	{
		n++;
		pr->buff[pr->i++] = prs->first;
		add_zero(pr, prs);
		process_zero_uvalue(pr, prs);
		if (prs->prc >= 0)
			add_space(pr, prs, size, n);
	}
	else
	{
		add_zero(pr, prs);
		process_zero_uvalue(pr, prs);
		add_space(pr, prs, size, n);
	}
}

void	process_zero_uvalue(t_ptf *pr, t_prs *prs)
{
	if (prs->unbr != 0 || (prs->unbr == 0 && prs->flag_prc == 0 &&\
		(prs->first == 0 || prs->width != 0)) ||\
		(prs->unbr == 0 && prs->wild == 1))
		buff_unbr(pr, prs);
}

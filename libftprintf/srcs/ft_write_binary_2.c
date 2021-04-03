/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_binary_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 05:33:51 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 05:33:53 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** service function for print binary
*/

void	prefix_2(t_prs *prs)
{
	prs->first = 48;
	prs->second = 'b';
	prs->third = ':';
}

int		count_sym(t_prs *prs)
{
	int		n;

	if (is_flag_hach(prs))
		n = prs->wsize % 8 == 0 ? 3 + prs->wsize / 8 - 1 : 3 + prs->wsize / 8;
	else
		n = prs->wsize % 8 == 0 ? (prs->wsize / 8 - 1) : prs->wsize / 8;
	return (n);
}

void	align_right_u_2(t_ptf *pr, t_prs *prs)
{
	int		j;
	int		n;

	j = 0;
	n = count_sym(prs);
	if (prs->first != 0)
	{
		while (j++ < prs->width - prs->wsize - n)
			pr->buff[pr->i++] = prs->sym;
		pr->buff[pr->i++] = prs->first;
		pr->buff[pr->i++] = prs->second;
		pr->buff[pr->i++] = prs->third;
	}
	else
	{
		while (j++ < prs->width - prs->wsize - n)
			pr->buff[pr->i++] = prs->sym;
	}
	buff_unbr_2(pr, prs);
}

void	align_left_u_2(t_ptf *pr, t_prs *prs)
{
	int		n;
	int		j;

	j = 0;
	n = count_sym(prs);
	if (prs->first != 0)
	{
		pr->buff[pr->i++] = prs->first;
		pr->buff[pr->i++] = prs->second;
		pr->buff[pr->i++] = prs->third;
		buff_unbr_2(pr, prs);
		while (j++ < prs->width - prs->wsize - n)
			pr->buff[pr->i++] = prs->sym;
	}
	else
	{
		buff_unbr_2(pr, prs);
		while (j++ < prs->width - prs->wsize - n)
			pr->buff[pr->i++] = prs->sym;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nbr_base16_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:47:35 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:47:37 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** service function for nbr_16
*/

void	prs_sym(t_prs *prs)
{
	if ((is_flag_hach(prs) || is_flag_plus(prs) || is_flag_space(prs)\
		|| prs->flags == 0) && !is_flag_zero(prs))
		prs->sym = 32;
	else if (prs->prc > 0 && prs->prc != prs->wsize)
		prs->sym = 32;
	else
		prs->sym = 48;
}

void	prefix(t_prs *prs)
{
	prs->first = 48;
	if (prs->cap_let == 1)
		prs->second = 'X';
	else
		prs->second = 'x';
}

void	space_unbr16(int size, t_ptf *pr, t_prs *prs)
{
	int		j;

	j = 0;
	while (j++ < size)
		pr->buff[pr->i++] = prs->sym;
	pr->buff[pr->i++] = prs->first;
	pr->buff[pr->i++] = prs->second;
}

void	zero_unbr16(int size, t_ptf *pr, t_prs *prs)
{
	int		j;

	j = 0;
	pr->buff[pr->i++] = prs->first;
	pr->buff[pr->i++] = prs->second;
	while (j++ < size)
		pr->buff[pr->i++] = prs->sym;
}

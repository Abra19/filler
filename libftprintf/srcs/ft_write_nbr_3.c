/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nbr_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:44:10 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:44:17 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** service function for write nbr, unbr
*/

void	sym_zero(t_ptf *pr, t_prs *prs, int size)
{
	int		j;

	j = 0;
	pr->buff[pr->i++] = prs->first;
	while (j++ < size)
		pr->buff[pr->i++] = prs->sym;
}

void	sym_space(t_ptf *pr, t_prs *prs, int size)
{
	int		j;

	j = 0;
	while (j++ < size)
		pr->buff[pr->i++] = prs->sym;
	pr->buff[pr->i++] = prs->first;
}

void	process_zero_value(t_ptf *pr, t_prs *prs)
{
	if (prs->nbr != 0 || (prs->nbr == 0 && prs->flag_prc == 0))
		buff_nbr(pr, prs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_ptr_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:50:48 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:50:50 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** write ptr
*/

void	space_ptr(int size, t_ptf *pr, t_prs *prs)
{
	int		j;

	j = 0;
	while (j++ < size)
		pr->buff[pr->i++] = prs->sym;
	pr->buff[pr->i++] = prs->first;
	pr->buff[pr->i++] = prs->second;
	add_zero(pr, prs);
}

void	zero_ptr(int size, t_ptf *pr, t_prs *prs)
{
	int		j;

	j = 0;
	pr->buff[pr->i++] = prs->first;
	pr->buff[pr->i++] = prs->second;
	while (j++ < size)
		pr->buff[pr->i++] = prs->sym;
	add_zero(pr, prs);
}

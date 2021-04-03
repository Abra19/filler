/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nbr_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:42:02 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:42:03 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** service function for write nbr, unbr
*/

void	add_space(t_ptf *pr, t_prs *prs, int size, int n)
{
	int		j;

	j = 0;
	if (prs->prc < 0)
	{
		while (j++ < prs->width - prs->wsize - n)
			pr->buff[pr->i++] = 32;
	}
	else
	{
		while (j++ < size - n)
			pr->buff[pr->i++] = 32;
	}
}

void	add_zero(t_ptf *pr, t_prs *prs)
{
	int		j;

	j = 0;
	while (j++ < (prs->prc - prs->wsize))
		pr->buff[pr->i++] = 48;
}

void	align_right(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	int		j;
	int		n;
	int		size;

	j = 0;
	n = (prs->nbr == 0 && prs->flag_prc != 1) ? 1 : 0;
	if (prs->first != 0)
	{
		n++;
		size = (int)len - (int)prc - n;
		if (prs->sym == 32)
			sym_space(pr, prs, size);
		else
			sym_zero(pr, prs, size);
		add_zero(pr, prs);
	}
	else
	{
		while (j++ < (int)len - (int)prc - n)
			pr->buff[pr->i++] = prs->sym;
		add_zero(pr, prs);
	}
	process_zero_value(pr, prs);
}

void	align_left(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	int		size;
	int		n;

	n = (prs->nbr == 0 && prs->flag_prc != 1) ? 1 : 0;
	size = (int)len - (int)prc;
	if (prs->first != 0)
	{
		n++;
		pr->buff[pr->i++] = prs->first;
		add_zero(pr, prs);
		process_zero_value(pr, prs);
		if (prs->prc >= 0)
			add_space(pr, prs, size, n);
	}
	else
	{
		add_zero(pr, prs);
		process_zero_value(pr, prs);
		add_space(pr, prs, size, n);
	}
}

void	buff_nbr(t_ptf *pr, t_prs *prs)
{
	size_t	i;

	i = 0;
	prs->str = ft_uitoa_base(pr->base, prs->nbr);
	while (prs->str[i] != '\0')
		pr->buff[pr->i++] = prs->str[i++];
	ft_strdel(&prs->str);
}

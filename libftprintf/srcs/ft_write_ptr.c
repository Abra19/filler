/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:28:00 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:28:02 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	align_right_ptr(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	int		j;
	int		n;
	int		size;

	j = 0;
	n = 2;
	size = (int)len - (int)prc - n;
	prs_sym(prs);
	if (prs->sym == 32)
		space_ptr(size, pr, prs);
	else
		zero_ptr(size, pr, prs);
	if (prs->unbr == 0 && prs->flag_prc == 1 && (prs->no_prc == 1 ||\
		prs->n_mark == 1))
		prs->prc = 0;
	if ((prs->unbr != 0 || prs->prc != 0))
		buff_unbr_16(pr, prs);
	else if (prs->unbr == 0 && prs->prc == 0 && prs->width != 0)
		pr->buff[pr->i++] = 32;
}

void	align_left_ptr(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	int		n;
	int		size;

	n = 2;
	size = (int)len - (int)prc;
	pr->buff[pr->i++] = prs->first;
	pr->buff[pr->i++] = prs->second;
	add_zero(pr, prs);
	if ((prs->unbr != 0 || prs->prc != 0) ||\
		(prs->unbr == 0 && (prs->no_prc == 1 || prs->n_mark == 1)))
		buff_unbr_16(pr, prs);
	if (prs->unbr == 0 && prs->prc == 0 && prs->width != 0)
		pr->buff[pr->i++] = 32;
	add_space(pr, prs, size, n);
}

int		flag_null_ptr(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	if (len != 0)
	{
		if (prs->c_width == 1)
			align_left_ptr(pr, prs, len, prc);
		else
			align_right_ptr(pr, prs, len, prc);
	}
	return (1);
}

void	flag_ptr(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	flag_zero_u(prs);
	if (is_flag_minus(prs) || prs->c_width == 1)
		align_left_ptr(pr, prs, len, prc);
	else
		align_right_ptr(pr, prs, len, prc);
}

int		hand_ptr(t_ptf *pr, t_prs *prs)
{
	size_t	len;
	size_t	prc;

	pr->base = 16;
	prs->first = 48;
	prs->second = 'x';
	if (ft_strcmp((const char*)prs->string, "p") == 0)
		prs->unbr = (unsigned long long)va_arg(pr->ap, void*);
	if ((prs->wsize = ft_unbrlen(prs->unbr, pr->base)) == -1)
		return (0);
	if ((prs->no_prc == 1 || prs->n_mark == 1))
		prs->prc = prs->wsize;
	prc = max_len(abs_int(prs->prc), prs->wsize);
	len = max_len(prs->width, prc);
	if (len != 0 && prs->flags != 0)
		flag_ptr(pr, prs, len, prc);
	else
		flag_null_ptr(pr, prs, len, prc);
	return (1);
}

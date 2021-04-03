/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:03:57 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:03:58 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "hhd" + "hhi"
** or "hd" + "hi" or "d" + "i" or "ld" + "li" or "lld" + "lli"
*/

void	process_negative(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	flag_zero(prs);
	flag_first(prs);
	if (prs->flags != 0)
	{
		prs->first = '-';
		if (is_flag_minus(prs) || prs->c_width == 1)
			align_left(pr, prs, len, prc);
		else
			align_right(pr, prs, len, prc);
	}
	else
	{
		prs->first = '-';
		if (prs->c_width == 1)
			align_left(pr, prs, len, prc);
		else
			align_right(pr, prs, len, prc);
	}
}

int		flag_null_nbr(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	if (prs->c_width == 1)
		align_left(pr, prs, len, prc);
	else
		align_right(pr, prs, len, prc);
	return (1);
}

void	flag_nbr(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	flag_zero(prs);
	flag_first(prs);
	if (is_flag_minus(prs) || prs->c_width == 1)
		align_left(pr, prs, len, prc);
	else
		align_right(pr, prs, len, prc);
}

int		read_integer(t_ptf *pr, t_prs *prs)
{
	if (ft_strcmp((const char*)prs->string, "hhd") == 0 ||\
		ft_strcmp((const char*)prs->string, "hhi") == 0)
		prs->nbr = (char)va_arg(pr->ap, long long);
	else if (ft_strcmp((const char*)prs->string, "hd") == 0 ||\
		ft_strcmp((const char*)prs->string, "hi") == 0)
		prs->nbr = (short)va_arg(pr->ap, long long);
	else if (ft_strcmp((const char*)prs->string, "ld") == 0 ||\
		ft_strcmp((const char*)prs->string, "li") == 0)
		prs->nbr = (long)va_arg(pr->ap, long long);
	else if (ft_strcmp((const char*)prs->string, "lld") == 0 ||\
		ft_strcmp((const char*)prs->string, "lli") == 0)
		prs->nbr = va_arg(pr->ap, long long);
	else
		prs->nbr = (int)va_arg(pr->ap, long long);
	if ((prs->wsize = ft_nbrlen(prs->nbr, pr->base)) == -1)
		return (-1);
	return (1);
}

int		hand_integer(t_ptf *pr, t_prs *prs)
{
	size_t	len;
	size_t	prc;

	pr->base = 10;
	if (read_integer(pr, prs) == -1)
		return (0);
	if (prs->c_prc == 1 || prs->nul_prc == 1)
		prs->prc = 0;
	if (prs->nbr == 0)
		prs->wsize = 0;
	prc = max_len(prs->prc, prs->wsize);
	len = max_len(prs->width, prc);
	if (prs->nbr >= 0)
	{
		if (prs->flags != 0)
			flag_nbr(pr, prs, len, prc);
		else
			flag_null_nbr(pr, prs, len, prc);
	}
	else
		process_negative(pr, prs, len, prc);
	return (1);
}

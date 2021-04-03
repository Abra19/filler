/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nbr_base10.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:09:51 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:09:55 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "hhu" or "hu" or "u"
** or "lu" or "llu"
*/

int		read_integer_10(t_ptf *pr, t_prs *prs)
{
	if (ft_strcmp((const char*)prs->string, "hhu") == 0)
		prs->unbr = (unsigned char)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char*)prs->string, "hu") == 0)
		prs->unbr = (unsigned short)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char*)prs->string, "lu") == 0)
		prs->unbr = (unsigned long)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char*)prs->string, "llu") == 0)
		prs->unbr = va_arg(pr->ap, unsigned long long);
	else
		prs->unbr = (unsigned int)va_arg(pr->ap, unsigned long long);
	if ((prs->wsize = ft_unbrlen(prs->unbr, pr->base)) == -1)
		return (-1);
	return (1);
}

int		hand_base_10(t_ptf *pr, t_prs *prs)
{
	size_t	len;
	size_t	prc;

	pr->base = 10;
	if (read_integer_10(pr, prs) == -1)
		return (0);
	if (prs->c_prc == 1 || prs->nul_prc == 1)
		prs->prc = 0;
	if (prs->unbr == 0)
		prs->wsize = 0;
	prc = max_len(abs_int(prs->prc), prs->wsize);
	len = max_len(prs->width, prc);
	if (prs->flags != 0)
	{
		if (flag_unbr(pr, prs, len, prc) == 0)
			return (0);
	}
	else
		flag_null_unbr(pr, prs, len, prc);
	return (1);
}

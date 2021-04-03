/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nbr_base8.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:06:54 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:06:56 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "hho" or "ho" or "o" or
** "lo" or "llo"
*/

void	buff_unbr(t_ptf *pr, t_prs *prs)
{
	size_t	i;
	char	*mask;

	i = 0;
	mask = "0123456789ABCDEF";
	prs->str = ft_itoa_base(pr->base, prs->unbr, mask);
	while (prs->str[i] != '\0')
		pr->buff[pr->i++] = prs->str[i++];
	ft_strdel(&prs->str);
}

int		flag_null_unbr(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	if (prs->c_width == 1)
		align_left_u(pr, prs, len, prc);
	else
		align_right_u(pr, prs, len, prc);
	return (1);
}

int		flag_unbr(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	flag_zero_u(prs);
	if (is_flag_minus(prs) || prs->c_width == 1)
		align_left_u(pr, prs, len, prc);
	else
		align_right_u(pr, prs, len, prc);
	return (1);
}

int		read_integer_8(t_ptf *pr, t_prs *prs)
{
	if (ft_strcmp((const char*)prs->string, "hho") == 0)
		prs->unbr = (unsigned char)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char*)prs->string, "ho") == 0)
		prs->unbr = (unsigned short)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char*)prs->string, "lo") == 0)
		prs->unbr = (unsigned long)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char*)prs->string, "llo") == 0)
		prs->unbr = va_arg(pr->ap, unsigned long long);
	else
		prs->unbr = (unsigned int)va_arg(pr->ap, unsigned long long);
	if ((prs->wsize = ft_unbrlen(prs->unbr, pr->base)) == -1)
		return (-1);
	return (1);
}

int		hand_base_8(t_ptf *pr, t_prs *prs)
{
	size_t	len;
	size_t	prc;

	pr->base = 8;
	if (read_integer_8(pr, prs) == -1)
		return (0);
	if (prs->c_prc == 1 || prs->nul_prc == 1)
		prs->prc = 0;
	if (prs->unbr == 0)
		prs->wsize = 0;
	prc = max_len(abs_int(prs->prc), prs->wsize);
	len = max_len(prs->width, prc);
	if (prs->flags != 0)
		flag_unbr(pr, prs, len, prc);
	else
		flag_null_unbr(pr, prs, len, prc);
	return (1);
}

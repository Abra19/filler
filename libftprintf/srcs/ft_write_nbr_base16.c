/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nbr_base16.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:17:10 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:17:13 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "hhx" or
** "hhX" and "hx" or "hX" and "x" or "X" and "lx" or "lX" and "llx" or "llX"
*/

void	flag_unbr_16(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	flag_zero(prs);
	if (is_flag_zero(prs))
		prs->first = 0;
	if ((is_flag_hach(prs) && (prs->prc <= prs->wsize) && prs->unbr != 0) ||\
		(is_flag_hach(prs) && prs->unbr != 0 && prs->prc != 0) ||\
		(is_flag_hach(prs) && is_flag_zero(prs) && prs->unbr != 0))
		prefix(prs);
	if (is_flag_minus(prs) || prs->c_width == 1)
		align_left_u_16(pr, prs, len, prc);
	else
		align_right_u_16(pr, prs, len, prc);
}

int		read_integer_16_x_cap(t_ptf *pr, t_prs *prs)
{
	if (ft_strcmp((const char *)prs->string, "hhX") == 0)
		prs->unbr = (unsigned char)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char *)prs->string, "hX") == 0)
		prs->unbr = (unsigned short)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char *)prs->string, "lX") == 0)
		prs->unbr = (unsigned long)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char *)prs->string, "llX") == 0)
		prs->unbr = va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char *)prs->string, "X") == 0)
		prs->unbr = (unsigned int)va_arg(pr->ap, unsigned long long);
	if ((prs->wsize = ft_unbrlen(prs->unbr, pr->base)) == -1)
		return (-1);
	return (1);
}

int		read_integer_16_x(t_ptf *pr, t_prs *prs)
{
	if (ft_strcmp((const char*)prs->string, "hhx") == 0)
		prs->unbr = (unsigned char)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char*)prs->string, "hx") == 0)
		prs->unbr = (unsigned short)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char*)prs->string, "lx") == 0)
		prs->unbr = (unsigned long)va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char*)prs->string, "llx") == 0)
		prs->unbr = va_arg(pr->ap, unsigned long long);
	else if (ft_strcmp((const char*)prs->string, "x") == 0)
		prs->unbr = (unsigned int)va_arg(pr->ap, unsigned long long);
	if ((prs->wsize = ft_unbrlen(prs->unbr, pr->base)) == -1)
		return (-1);
	return (1);
}

void	params_unbr16(t_prs *prs)
{
	if (prs->c_prc == 1 || prs->nul_prc == 1)
		prs->prc = 0;
	if (prs->unbr == 0)
		prs->wsize = 0;
}

int		hand_base_16(t_ptf *pr, t_prs *prs)
{
	size_t	len;
	size_t	prc;

	pr->base = 16;
	if (prs->string[ft_strlen(prs->string) - 1] == 'x')
	{
		if (read_integer_16_x(pr, prs) == -1)
			return (0);
	}
	else
	{
		prs->cap_let = 1;
		if (read_integer_16_x_cap(pr, prs) == -1)
			return (0);
	}
	params_unbr16(prs);
	prc = max_len(abs_int(prs->prc), prs->wsize);
	len = max_len(prs->width, prc);
	if (prs->flags != 0)
		flag_unbr_16(pr, prs, len, prc);
	else
		flag_null_unbr_16(pr, prs, len, prc);
	return (1);
}

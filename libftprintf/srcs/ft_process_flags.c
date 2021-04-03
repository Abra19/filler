/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 05:25:59 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 05:26:01 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_first(t_prs *prs)
{
	if (is_flag_plus(prs))
		prs->first = '+';
	else if (is_flag_space(prs))
	{
		prs->first = 32;
	}
}

void	flag_zero(t_prs *prs)
{
	if (is_flag_zero(prs) && !is_flag_minus(prs) && (prs->flag_prc != 1 ||\
		prs->wild == 1) && (prs->wild != 1 || (prs->wild == 1 && prs->prc == 0\
		&& prs->flag_prc != 1)))
		prs->sym = 48;
	else
		prs->sym = 32;
	if (is_flag_zero(prs) && prs->wild == 1 && prs->c_prc == 1)
		prs->sym = 48;
}

void	flag_zero_u(t_prs *prs)
{
	if (is_flag_minus(prs))
		prs->sym = 32;
	else if (is_flag_zero(prs) && prs->flag_prc != 1)
		prs->sym = 48;
	if ((is_flag_hach(prs) && (prs->prc <= prs->wsize) && prs->unbr != 0)\
			|| (is_flag_hach(prs) && is_flag_zero(prs) &&\
			(abs_int(prs->prc) <= (uint64_t)prs->wsize) && prs->unbr != 0) ||\
			(is_flag_hach(prs) && prs->flag_prc == 1 && prs->prc == 0))
		prs->first = 48;
}

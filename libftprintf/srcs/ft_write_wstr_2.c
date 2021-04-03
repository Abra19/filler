/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_wstr_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:58:16 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:58:17 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		width_non_zero_ws(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	size_t	j;
	size_t	n;

	j = 0;
	n = count_size(prs, prc);
	while (j++ < len - n)
		pr->buff[pr->i++] = prs->sym;
	buff_wstr(pr, prs, prc);
	return (1);
}

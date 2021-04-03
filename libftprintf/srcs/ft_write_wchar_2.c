/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_wchar_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:57:07 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:57:08 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** for char - wchar manage non_zero width
*/

int		width_non_zero_wc(t_ptf *pr, t_prs *prs)
{
	int		j;

	j = 0;
	while (j++ < prs->width - prs->wsize)
		pr->buff[pr->i++] = 32;
	buff_wchar(pr, prs);
	return (1);
}

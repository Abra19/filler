/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_float_8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:00:42 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:00:45 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*left_res(t_ptf *pr, t_prs *prs, t_ldbl *dbl, int *size)
{
	char	*res;

	res = NULL;
	if (dbl->field.exp != 32767)
	{
		res = union_parts_f(pr, prs, dbl);
		*size = prs->wc;
	}
	return (res);
}

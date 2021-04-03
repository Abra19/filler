/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_inf_nan_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:40:37 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:40:39 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_inf(t_ptf *pr, int n)
{
	pr->buff[pr->i++] = 'I' + n;
	pr->buff[pr->i++] = 'N' + n;
	pr->buff[pr->i++] = 'F' + n;
}

void	write_nan(t_ptf *pr, int n)
{
	pr->buff[pr->i++] = 'N' + n;
	pr->buff[pr->i++] = 'A' + n;
	pr->buff[pr->i++] = 'N' + n;
}

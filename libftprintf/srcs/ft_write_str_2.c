/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_str_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:53:48 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:53:49 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		width_non_zero_s(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	size_t	j;

	j = 0;
	while (j++ < len - prc)
		pr->buff[pr->i++] = 32;
	buff_str(pr, prs, prc);
	return (1);
}

int		flag_null_s(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	size_t		i;

	i = 0;
	if (len != 0)
	{
		if (prs->c_width == 1)
		{
			buff_str(pr, prs, prc);
			while (i++ < len - prc)
				pr->buff[pr->i++] = 32;
		}
		else
			width_non_zero_s(pr, prs, len, prc);
	}
	if (ft_strcmp((const char*)prs->string, "r") == 0)
		ft_strdel(&prs->str);
	return (1);
}

void	flag_width_s(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	size_t	j;
	int		i;

	j = 0;
	i = 0;
	while (prs->flags[i] != '-' && prs->flags[i] != '\0')
		i++;
	if (i == ft_strlen((const char *)prs->flags))
	{
		while (j++ < len - prc)
			pr->buff[pr->i++] = 32;
		buff_str(pr, prs, prc);
	}
	else
	{
		buff_str(pr, prs, prc);
		while (j++ < len - prc)
			pr->buff[pr->i++] = 32;
	}
}

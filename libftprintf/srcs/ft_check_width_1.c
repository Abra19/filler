/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_width_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 04:58:49 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 04:58:53 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** fix width
*/

int		width_star_invalid(t_ptf *pr, t_prs *prs, int *i)
{
	char	*res;

	if (pr->frt[*i] == '\0' || pr->frt[*i] == '.' || is_spec(pr->frt[*i]) == 1\
			|| pr->frt[*i] == 'l' || pr->frt[*i] == 'L' || pr->frt[*i] == 'h'\
			|| pr->frt[*i] != '%')
	{
		*i = *i - pr->pos;
		if (*i != 0)
		{
			va_arg(pr->ap, long long);
			res = ft_strsub(pr->frt, pr->pos, *i);
			prs->width = ft_atol((const char *)res);
			pr->pos = pr->pos + *i;
			ft_strdel(&res);
		}
	}
	return (1);
}

int		width_parce_dollar(t_ptf *pr)
{
	int		i;

	i = pr->pos;
	while (pr->frt[i] != '.' && is_spec(pr->frt[i]) != 1 &&\
		pr->frt[i] != 'l' && pr->frt[i] != 'L' && pr->frt[i] != 'h'\
		&& pr->frt[i] != '%' && pr->frt[i] != '\0')
	{
		if (pr->frt[i] == '$')
			break ;
		else
			i++;
	}
	return (i);
}

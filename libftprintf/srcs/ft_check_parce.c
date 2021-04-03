/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parce.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:57:35 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 17:57:42 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** write used flags of size h, hh, l, ll, L in string
*/

int		ft_check_letters(t_ptf *pr, t_prs *prs)
{
	size_t	i;
	size_t	len;

	i = pr->pos;
	while (is_spec(pr->frt[pr->pos]) != 1 && pr->frt[pr->pos] != '\0')
	{
		if (pr->frt[pr->pos] != 'h' && pr->frt[pr->pos] != 'L' &&\
			pr->frt[pr->pos] != 'l')
		{
			print_error("size flags are invalid");
			return (0);
		}
		pr->pos++;
	}
	len = pr->pos - i;
	if (len != 0)
		prs->letters = ft_strsub(pr->frt, i, len);
	return (1);
}

/*
** write flags -+# 0 in string
*/

int		ft_check_flags(t_ptf *pr, t_prs *prs)
{
	size_t	i;
	size_t	len;

	i = pr->pos;
	while (pr->frt[pr->pos] != '*' && (ft_isdigit_0(pr->frt[pr->pos]) != 1)\
		&& (is_spec(pr->frt[pr->pos]) != 1) && pr->frt[pr->pos] != '.' &&\
		pr->frt[pr->pos] != 'h' && pr->frt[pr->pos] != 'l' && \
		pr->frt[pr->pos] != 'L' && pr->frt[pr->pos] != '\0'\
		&& pr->frt[pr->pos] != '%')
	{
		if (pr->frt[pr->pos] != '-' && pr->frt[pr->pos] != '+' &&\
			pr->frt[pr->pos] != ' ' && pr->frt[pr->pos] != '#' &&\
			pr->frt[pr->pos] != '0')
			return (0);
		pr->pos++;
	}
	len = pr->pos - i;
	if (len != 0)
		prs->flags = ft_strsub(pr->frt, i, len);
	return (1);
}

/*
** check all flags, specifiers and write in buff after that
*/

int		check_and_parse(t_ptf *pr, t_prs *prs)
{
	if (ft_check_flags(pr, prs) == 0)
		return (0);
	if (check_width(pr, prs) == 0)
	{
		ft_strdel(&prs->flags);
		return (0);
	}
	if (prs->width >= 2147483647 || prs->width <= -2147483648)
		prs->width = 0;
	if (compare(pr) != 0)
	{
		if (check_prc(pr, prs) == 0 || ft_check_letters(pr, prs) == 0)
		{
			ft_strdel(&prs->flags);
			return (0);
		}
		if (ft_specifier(pr, prs) == 0)
		{
			clean_str(prs);
			return (0);
		}
	}
	return (1);
}

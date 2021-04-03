/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:32:28 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:32:29 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier = "%"
*/

void	flag_percent(t_ptf *pr, t_prs *prs)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	flag_first(prs);
	flag_zero(prs);
	while (prs->flags[j] != '-' && prs->flags[j] != '\0')
		j++;
	if (j == ft_strlen((const char *)prs->flags))
	{
		while (i++ < prs->width - 1)
			pr->buff[pr->i++] = prs->sym;
		pr->buff[pr->i++] = '%';
	}
	else
	{
		pr->buff[pr->i++] = '%';
		while (i++ < prs->width - 1)
			pr->buff[pr->i++] = prs->sym;
	}
}

void	flag_abs_percent(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	prs->sym = 32;
	flag_first(prs);
	flag_zero(prs);
	if (prs->c_width == 1)
	{
		pr->buff[pr->i++] = '%';
		while (i++ < prs->width - 1)
			pr->buff[pr->i++] = prs->sym;
	}
	else
	{
		while (i++ < prs->width - 1)
			pr->buff[pr->i++] = prs->sym;
		pr->buff[pr->i] = '%';
		pr->i++;
	}
}

int		hand_percent(t_ptf *pr)
{
	t_prs	prs;

	ft_bzero(&prs, sizeof(prs));
	ft_check_flags(pr, &prs);
	check_width(pr, &prs);
	if (prs.width < 0)
		prs.c_width = 1;
	check_prc(pr, &prs);
	prs.no_prc = 0;
	if (prs.width != 0 && prs.flags != 0)
		flag_percent(pr, &prs);
	else
	{
		if (prs.width != 0)
			flag_abs_percent(pr, &prs);
		else
		{
			pr->buff[pr->i] = '%';
			pr->i++;
		}
	}
	ft_strdel(&prs.flags);
	return (1);
}

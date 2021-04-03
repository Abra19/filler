/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fexp_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 05:52:16 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 05:52:18 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	exp_frac(t_ptf *pr, t_prs *prs)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_uitoa_frac_prc(pr->base, pr->frac, POWSIZE);
	while (str[i++] == '0')
		prs->exp++;
	prs->exp = prs->exp + 1;
	ft_strdel(&str);
}

void	count_exp(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = MAXLEN - 1;
	while (i >= 0)
	{
		if (pr->fint[i] == 0)
			i--;
		else
			break ;
	}
	i++;
	if (i > 0)
	{
		prs->exp = (prs->fnbr == 0) ? 0 : (i - 1) * BASELEN + \
			ft_nbrlen(pr->fint[i - 1], pr->base) - 1;
	}
	else
		exp_frac(pr, prs);
}

int		round_long(t_ptf *pr, t_prs *prs, int k)
{
	int		len;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	pr->dround = 0;
	len = k * BASELEN + ft_nbrlen((long long)pr->fround[k], pr->base);
	len = len - prs->prc;
	while (i++ < len - 2)
		div_long(pr->fround, pr->base);
	if ((pr->fround[0] % pr->base >= 5))
	{
		add_l_n(pr->fround, 5);
		pr->dround = 1;
		flag = 1;
	}
	div_long(pr->fround, 10);
	return (flag);
}

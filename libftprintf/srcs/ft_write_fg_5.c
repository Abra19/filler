/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 06:20:58 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 06:21:00 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		round_long_fg_f(t_ptf *pr, char *res, int k, t_ldbl *dbl)
{
	int			flag;
	int			i;
	int			d;

	i = 0;
	d = pr->dround;
	pr->flag = 0;
	while (i < d)
	{
		flag = n_round_fg(pr, dbl);
		i++;
	}
	write_inttoa_f(pr, res, k);
	return (flag);
}

void	analyze_round_g(t_ptf *pr, t_prs *prs, int k)
{
	if ((pr->dround == 2 && abs_int_f(prs->fnbr) < 1) && k != 0)
		prs->wsize--;
	if (pr->dround == 1 && abs_int_f(prs->fnbr) < 1 && prs->wsize == prs->prc\
		&& pr->flag == 1)
		prs->wsize--;
	if (prs->wsize > prs->prc)
		prs->wsize = prs->prc;
}

int		premake_str(t_ptf *pr, t_prs *prs)
{
	int		n;

	int_part_u(pr, prs);
	n = (abs_int_f(prs->fnbr) < 1) ? prs->prc + 1 : prs->prc;
	prs->wc = (abs_int_f(prs->fnbr) >= 1) ? prs->k : 1;
	return (n);
}

char	*make_str_g(t_ptf *pr, t_prs *prs)
{
	char		*str1;
	char		*str2;
	int			i;
	char		*str;
	long long	n;

	i = 0;
	if (prs->flag_prc == 1 && prs->prc < 6 && prs->fnbr != 0 &&\
		abs_int_f(prs->fnbr) < 1)
		prs->prc = prs->pk - prs->el - 1;
	n = premake_str(pr, prs);
	str1 = ft_uitoa_frac_prc(pr->base, pr->frac, n);
	str2 = ft_strjoin(prs->s_parts, str1);
	ft_strdel(&str1);
	while (str2[i] == '0')
		i++;
	str = ft_strsub((const char *)str2, i, ft_strlen(str2) - i + 1);
	if (ft_strlen(str) == 0)
		prs->wc = 0;
	if (ft_strlen(str) < prs->prc + prs->wc)
		prs->wsize = prs->prc + prs->wc - ft_strlen(str) + 1;
	ft_strdel(&str2);
	ft_strdel(&prs->s_parts);
	return (str);
}

void	analyze_params(t_ptf *pr, t_prs *prs, char *str)
{
	int		n;

	n = ft_strlen(str);
	if (n < 2)
		pr->dround = 1;
	else
	{
		pr->dround = ((abs_int_f(prs->fnbr) < 1) && str[n - 2] >= 5 + '0') ? 2\
			: 1;
		if ((abs_int_f(prs->fnbr) < 1) && str[n - 2] == '9' &&
			str[n - 1] == '9')
		{
			pr->dround = 1;
			pr->flag_mod = 1;
		}
		if (pr->lflag == 1 && str[n - 2] < 5 + '0' && str[n - 1] < 5 + '0')
			pr->dround = 1;
		if (pr->lflag == 1 && str[n - 2] < 5 + '0' && str[n - 1] >= 5 + '0' && \
			abs_int_f(prs->fnbr * 10.) >= 1 && prs->fnbr >= 0 && \
			(abs_int_f(prs->fnbr) < 1))
			pr->dround = 2;
	}
}

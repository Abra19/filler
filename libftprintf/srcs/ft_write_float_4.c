/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_float_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:58:35 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:58:36 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "f" + "F"
** or "lf" + "lF" or "Lf" + "LF"
*/

char	*make_str(t_ptf *pr, t_prs *prs)
{
	char		*str1;
	char		*str2;
	int			i;
	char		*str;
	long long	n;

	i = 0;
	int_part_u(pr, prs);
	n = (abs_int_f(prs->fnbr) < 1) ? prs->prc + 1 : prs->prc;
	prs->wc = (abs_int_f(prs->fnbr) >= 1) ? prs->k : 1;
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

void	analyze_round(t_ptf *pr, t_prs *prs, int k)
{
	if ((pr->dround == 2 && abs_int_f(prs->fnbr) < 1) && k != 0)
		prs->wsize--;
	if (pr->dround == 0 && abs_int_f(prs->fnbr) < 1 && pr->lflag != 1)
		prs->wsize--;
	if (pr->dround == 1 && abs_int_f(prs->fnbr) < 1 &&\
		prs->wsize == prs->prc && pr->flag == 1)
		prs->wsize--;
	if (prs->wsize > prs->prc)
		prs->wsize = prs->prc;
}

void	count_params_f(t_ptf *pr, t_prs *prs, char *str)
{
	int		n;

	n = ft_strlen(str);
	pr->flag_mod = 0;
	if (abs_int_f(prs->fnbr) < 1)
		pr->flag_mod = 1;
	if (n < 2)
		pr->dround = 1;
	else
	{
		pr->dround = ((abs_int_f(prs->fnbr) < 1) && str[n - 2] >= 5 + '0') ? 2\
			: 1;
		if (pr->lflag == 1 && str[n - 2] < 5 + '0' && str[n - 1] < 5 + '0')
			pr->dround = 1;
		if (pr->lflag == 1 && str[n - 2] < 5 + '0' && str[n - 1] >= 5 + '0' && \
			abs_int_f(prs->fnbr * 10.) >= 1 && prs->fnbr >= 0 && \
			(abs_int_f(prs->fnbr) < 1))
			pr->dround = 2;
	}
}

char	*union_parts_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	char	*str;
	int		k;
	int		len;
	char	*str1;

	str = make_str(pr, prs);
	len = (ft_strlen(str) > MAXLEN * BASELEN + prs->prc) ?\
		(ft_strlen(str) / 8 + 1) : (MAXLEN + prs->prc);
	pr->fround = (int*)ft_memalloc(sizeof(int) * (len));
	k = read_long(str, pr->fround);
	len = (ft_strlen(str) > MAXLEN * BASELEN + prs->prc) ?\
		(ft_strlen(str) + 1) : (MAXLEN * BASELEN + prs->prc);
	str1 = (char *)ft_memalloc(sizeof(char) * (len + 1));
	str1[len] = '\0';
	count_params_f(pr, prs, str);
	ft_strdel(&str);
	k = round_long_f(pr, str1, k, dbl);
	analyze_round(pr, prs, k);
	if (k != 0 && abs_int_f(prs->fnbr) >= 1 &&\
		ft_nbrlen(abs_int((int)prs->fnbr) + 1, pr->base) >\
		ft_nbrlen(abs_int((int)prs->fnbr), pr->base))
		prs->wc++;
	ft_memdel((void**)&pr->fround);
	return (str1);
}

void	flag_f_null(t_prs *prs, t_ldbl *dbl)
{
	if (is_flag_plus(prs))
	{
		if (dbl->field.sign == 1)
			prs->first = '-';
		else
			prs->first = '+';
	}
	else if (is_flag_space(prs))
		if (dbl->field.sign == 1)
			prs->first = '-';
		else
			prs->first = 32;
	else if (dbl->field.sign == 1)
		prs->first = '-';
	else
		prs->first = 0;
}

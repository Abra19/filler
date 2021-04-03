/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 06:15:25 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 06:15:29 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*union_parts_fg(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	char	*str;
	int		k;
	int		len;
	char	*str1;

	str = make_str_g(pr, prs);
	len = (ft_strlen(str) > MAXLEN * BASELEN + prs->prc) ?\
		(ft_strlen(str) / 8 + 1) : (MAXLEN + prs->prc);
	pr->fround = (int*)ft_memalloc(sizeof(int) * (len));
	k = read_long(str, pr->fround);
	len = (ft_strlen(str) > MAXLEN * BASELEN + prs->prc) ?\
		(ft_strlen(str) + 1) : (MAXLEN * BASELEN + prs->prc);
	str1 = (char *)ft_memalloc(sizeof(char) * (len + 1));
	str1[len] = '\0';
	analyze_params(pr, prs, str);
	ft_strdel(&str);
	k = round_long_fg_f(pr, str1, k, dbl);
	analyze_round_g(pr, prs, k);
	if (k != 0 && abs_int_f(prs->fnbr) >= 1 &&\
		ft_nbrlen(abs_int((int)prs->fnbr) + 1, pr->base) >\
		ft_nbrlen(abs_int((int)prs->fnbr), pr->base))
		prs->wc++;
	ft_memdel((void**)&pr->fround);
	return (str1);
}

char	*format_str(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	char	*res;
	char	*str;

	res = union_parts_fg(pr, prs, dbl);
	if (prs->fnbr != 0)
		prs->prc = prs->pk - prs->el - 1;
	str = process_str(pr, prs, res);
	if (pr->flag != 0)
		prs->wc++;
	return (str);
}

void	format_str_e(t_ptf *pr, t_prs *prs)
{
	prs->num = (prs->prc == 0 && !is_flag_hach(prs)) ? 3 : 4;
	prs->sizef = ft_nbrlen((long long)prs->exp, pr->base);
	if (abs_int(prs->exp) < 10)
		prs->sizef++;
	prs->prc = prs->pk - 1;
	prs->wsize = (prs->wsize == 0) ? prs->exp : prs->wsize;
	if (pr->flag == 1)
		prs->wsize++;
	prs->new_exp = prs->wsize;
	if (abs_int_f(prs->fnbr) < 1)
		prs->new_exp = -prs->new_exp;
}

void	format_str_g(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	if ((prs->first != 0 && dbl->field.exp != 32767))
	{
		if (prs->sym != 32)
		{
			pr->buff[pr->i++] = prs->first;
			first_g_align(pr, prs);
		}
		else
		{
			first_g_align(pr, prs);
			pr->buff[pr->i++] = prs->first;
		}
	}
	else if (dbl->field.exp != 32767)
		first_g_align_null(pr, prs);
}

void	process_zero_g(t_ptf *pr, t_prs *prs, char *str)
{
	int		i;

	i = 0;
	pr->buff[pr->i++] = '0';
	if (last_null(i, str) != 0)
	{
		if (prs->prc != 0)
			pr->buff[pr->i++] = '.';
		if (pr->flag == 1)
			prs->wsize--;
		while (i++ < prs->wsize)
			pr->buff[pr->i++] = '0';
	}
}

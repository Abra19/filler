/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg_8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 06:44:03 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 06:44:05 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	buff_f_case(t_ptf *pr, t_prs *prs, t_ldbl *dbl, char *res)
{
	if (prs->fnbr != 0)
		prs->prc = prs->pk - prs->el - 1;
	if (prs->fnbr * 10 == prs->fnbr && prs->fnbr != 0)
		inf_f(pr, prs, dbl);
	else if (prs->fnbr != prs->fnbr)
		nan_f(pr, prs);
	else if (prs->fnbr == 0)
	{
		if (is_flag_hach(prs))
			print_null_prc_fg(pr, prs);
		else
			pr->buff[pr->i++] = '0';
	}
	else
		buff_f_ne_zero(pr, prs, res);
}

int		buff_nbr_fg(t_ptf *pr, t_prs *prs, t_ldbl *dbl, char *res)
{
	if (prs->pk > prs->el && prs->el >= -4)
		buff_f_case(pr, prs, dbl, res);
	else if (prs->pk <= prs->el || prs->el < -4)
		buff_e_case(pr, prs, dbl, res);
	return (1);
}

char	*process_str(t_ptf *pr, t_prs *prs, char *res)
{
	int		k;
	char	*str;

	str = ft_strsub((const char*)res, 0, prs->wc + prs->prc + 1);
	ft_strdel(&res);
	pr->fround = (int*)ft_memalloc(sizeof(int) * (MAXLEN + prs->prc));
	k = read_long(str, pr->fround);
	ft_strdel(&str);
	str = (char *)ft_memalloc(sizeof(char) * (MAXLEN + prs->prc + 1));
	str[MAXLEN + prs->prc] = '\0';
	pr->flag = round_long_ff(pr, str, k);
	ft_memdel((void**)&pr->fround);
	return (str);
}

char	*process_str_e(t_ptf *pr, t_prs *prs, char *res)
{
	char	*str;
	int		k;

	str = ft_strsub((const char *)res, prs->zero, prs->prc + 2);
	pr->fround = (int *)ft_memalloc(sizeof(int) * (MAXLEN + prs->prc));
	k = read_long(str, pr->fround);
	ft_strdel(&str);
	str = (char *)ft_memalloc(sizeof(char) * (MAXLEN + prs->prc + 1));
	str[MAXLEN + prs->prc] = '\0';
	pr->flag = round_long_fg(pr, str, k);
	ft_memdel((void **)&pr->fround);
	return (str);
}

int		process_params_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	int n;

	if ((prs->fnbr == 0 && !is_flag_hach(prs) && \
		dbl->field.exp != 32767) || ((prs->no_prc == 1 || prs->n_mark == 1)\
		&& !is_flag_hach(prs) && dbl->field.exp != 32767))
		prs->pr_pk = prs->el + 1;
	if ((prs->first != 0 && ((int)prs->fnbr - prs->fnbr != 0)) || \
		(prs->first != 0 && is_flag_hach(prs)))
		n = 2;
	else if ((prs->first == 0 && is_flag_hach(prs)) || \
		(prs->first != 0 && !is_flag_hach(prs)) || \
		(prs->first == 0 && ((int)prs->fnbr - prs->fnbr != 0)) || \
		(prs->first != 0 && ((int)prs->fnbr - prs->fnbr == 0)))
		n = 1;
	else
		n = 0;
	if (pr->flag != 0 && n > 0)
		n--;
	return (n);
}

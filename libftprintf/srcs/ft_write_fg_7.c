/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 06:39:14 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 06:39:16 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	process_params_g(t_prs *prs, t_ldbl *dbl)
{
	if ((prs->fnbr == 0 && !is_flag_hach(prs) &&\
		dbl->field.exp != 32767) || ((prs->no_prc == 1 || prs->n_mark == 1)\
		&& !is_flag_hach(prs) && dbl->field.exp != 32767))
		prs->pr_pk = prs->el + 1;
	if ((prs->first != 0 && ((int)prs->fnbr - prs->fnbr != 0)) ||\
			(prs->first != 0 && is_flag_hach(prs)))
		prs->num = 2;
	else if ((prs->first == 0 && is_flag_hach(prs)) ||\
			(prs->first != 0 && !is_flag_hach(prs)) ||\
			(prs->first == 0 && ((int)prs->fnbr - prs->fnbr != 0)) ||\
			(prs->first != 0 && ((int)prs->fnbr - prs->fnbr == 0)))
		prs->num = 1;
	else
		prs->num = 0;
	if (prs->fnbr == 0)
		prs->sizef = 1;
	if (dbl->field.exp == 15361)
		prs->sizef++;
}

int		count_frac(char *str, t_prs *prs)
{
	int		len_f;
	int		i;
	int		n;

	len_f = 0;
	n = (abs_int_f(prs->fnbr) < 1) ? 0 : prs->sizef;
	i = (abs_int_f(prs->fnbr) < 1) ? 0 : prs->sizef;
	while (len_f++ < ft_strlen(str) - n && last_null(i, str) != 0)
		i++;
	len_f--;
	return (len_f);
}

int		count_frac_g(char *str, t_ptf *pr, t_prs *prs)
{
	int		len_f;
	int		i;
	int		n;

	len_f = 0;
	i = (abs_int_f(prs->fnbr) < 1) ? 0 : prs->sizef;
	if (pr->flag != 0)
		prs->wc++;
	prs->sizef = prs->wc;
	n = (abs_int_f(prs->fnbr) < 1) ? 0 : prs->sizef;
	while (len_f++ < ft_strlen(str) - n && last_null(i, str) != 0)
		i++;
	len_f--;
	return (len_f);
}

void	pre_align_fg(t_ptf *pr, t_prs *prs)
{
	int		j;

	j = 0;
	if ((int)(prs->fnbr) - prs->fnbr == 0)
	{
		while (j++ < prs->width - prs->sizef - prs->num)
			pr->buff[pr->i++] = prs->sym;
	}
	else
	{
		while (j++ < prs->width - prs->len_f - prs->sizef\
			- prs->num - prs->wsize)
			pr->buff[pr->i++] = prs->sym;
	}
}

void	first_f_align(t_ptf *pr, t_prs *prs)
{
	int		j;
	char	*str;
	int		i;

	i = 0;
	str = ft_uitoa_frac_prc(pr->base, pr->frac, prs->prc);
	while (str[i] == '0')
		i++;
	if (abs_int_f(prs->fnbr) < 1)
		prs->wsize = i;
	ft_strdel(&str);
	j = 0;
	if (!is_flag_hach(prs))
		pre_align_fg(pr, prs);
	else
	{
		while (j++ < prs->width - (prs->pr_pk - prs->el - 1) - prs->sizef\
			- prs->num)
			pr->buff[pr->i++] = prs->sym;
	}
}

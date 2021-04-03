/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 06:53:51 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 06:53:53 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	first_align_gl_null(t_ptf *pr, t_prs *prs)
{
	int		j;

	j = 0;
	if (prs->first != 0 && (prs->fnbr >= 0 || is_flag_hach(prs)))
		prs->num++;
	if (is_flag_hach(prs))
	{
		while (j++ < prs->width - (prs->pr_pk - 1) - prs->sizef - prs->num)
			pr->buff[pr->i++] = prs->sym;
	}
	else
	{
		while (j++ < prs->width - pr->count - prs->sizef - prs->num)
			pr->buff[pr->i++] = prs->sym;
	}
}

void	print_case_gl(t_ptf *pr, t_prs *prs, t_ldbl *dbl, char *str)
{
	if (is_flag_hach(prs))
		prs->sym = 32;
	if ((prs->first != 0 && dbl->field.exp != 32767))
	{
		pr->buff[pr->i++] = prs->first;
		buff_nbr_fg(pr, prs, dbl, str);
		first_align_gl(pr, prs);
	}
	else if (dbl->field.exp != 32767)
	{
		buff_nbr_fg(pr, prs, dbl, str);
		first_align_gl_null(pr, prs);
	}
	else
		buff_nbr_fg(pr, prs, dbl, str);
	ft_strdel(&str);
}

int		last_null(int i, char *str)
{
	int		k;

	k = i;
	while (str[k] != '\0')
	{
		if (str[k] != '0')
			return (1);
		k++;
	}
	return (0);
}

void	env_in_buff_mn(t_ptf *pr, t_prs *prs, char *res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	pr->sym_frac = (abs_int_f(prs->fnbr) <= 1) ? 1 : 0;
	while (res[i] == '0')
		i++;
	if (res[i] != '\0')
		pr->buff[pr->i++] = res[i++];
	if (is_flag_hach(prs) != 0 || pr->count != 0)
		pr->buff[pr->i++] = '.';
	while (res[i] != '\0' && last_null(i, res) != 0 && j < prs->prc)
	{
		pr->buff[pr->i++] = res[i++];
		j++;
	}
	pr->buff[pr->i++] = (prs->string[ft_strlen(prs->string) - 1] == 'e' ||\
		prs->string[ft_strlen(prs->string) - 1] == 'g') ? 'e' : 'E';
	pr->buff[pr->i++] = (pr->sym_frac == 0) ? '+' : '-';
}

void	write_frac_part_int(t_ptf *pr, t_prs *prs, char *res, int j)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	if (prs->wc == 1 && abs_int_f(prs->fnbr) < 1 &&\
		abs_int_f(prs->fnbr * 10.) < 1)
	{
		pr->buff[pr->i++] = '0';
		flag = 1;
		i++;
	}
	if (ft_strlen(res) + flag >= prs->prc)
	{
		while (i++ < prs->prc - 1 && last_null(j, res) != 0)
			pr->buff[pr->i++] = res[j++];
		if (res[j] != '0' && last_null(j, res) != 0)
			pr->buff[pr->i++] = res[j];
	}
	else
	{
		while (i++ < ft_strlen(res) && last_null(j, res) != 0)
			pr->buff[pr->i++] = res[j++];
	}
}

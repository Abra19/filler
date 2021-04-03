/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:42:15 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:42:16 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		count_zero(char *res)
{
	int		i;

	i = 0;
	while (res[i] == '0')
		i++;
	i++;
	return (i);
}

int		count_zero_mn(char *res)
{
	int		i;

	i = 0;
	while (res[i] == '0')
		i++;
	return (i);
}

int		align_right_fg(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	char	*res;
	char	*str;

	prs->pr_pk = prs->pk;
	if (prs->pr_pk > prs->el && prs->el >= -4)
		print_case_f(pr, prs, dbl);
	else
	{
		res = union_parts(pr, prs);
		prs->zero = count_zero_mn(res);
		str = process_str_e(pr, prs, res);
		format_str_e(pr, prs);
		if (prs->prc > prs->new_exp && (prs->new_exp >= -4 || pr->flag != 0))
		{
			new_round_g(pr, prs, res);
			ft_strdel(&str);
			return (1);
		}
		else
			print_case_g(pr, prs, dbl, str);
		ft_strdel(&res);
	}
	return (1);
}

int		align_left_fg(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	char	*res;
	char	*str;

	prs->pr_pk = prs->pk;
	if (prs->pr_pk > prs->el && prs->el >= -4)
	{
		res = union_parts_fg(pr, prs, dbl);
		process_str_fe(pr, prs, dbl, res);
	}
	else
	{
		res = union_parts(pr, prs);
		format_str_e(pr, prs);
		str = form_str_gl(res, pr, prs);
		if (prs->prc > prs->new_exp && (prs->new_exp >= -4 || pr->flag != 0))
		{
			new_round_g(pr, prs, res);
			ft_strdel(&str);
			return (1);
		}
		else
			print_case_gl(pr, prs, dbl, str);
		ft_strdel(&res);
	}
	return (1);
}

void	fe_choice(t_ptf *pr, t_prs *prs, int *prc, int *exp)
{
	count_exp(pr, prs);
	*exp = (abs_int_f(prs->fnbr) - 1 < 0) ? -prs->exp : prs->exp;
	if (prs->fnbr == 0)
		*exp = 0;
	*prc = (prs->prc == 0) ? 1 : prs->prc;
}

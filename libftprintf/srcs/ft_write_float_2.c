/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_float_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:52:38 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:52:46 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: spec + size flags = "f" + "F"
** or "lf" + "lF" or "Lf" + "LF"
*/

int		fract_part_int_f(t_ptf *pr, t_prs *prs, char *res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (prs->wc == 0 || (prs->wc == 1 && abs_int_f(prs->fnbr) < 1))
		pr->buff[pr->i++] = '0';
	else
	{
		while (i++ < prs->wc)
			pr->buff[pr->i++] = res[j++];
	}
	if (is_flag_hach(prs) != 0 || prs->prc != 0)
		pr->buff[pr->i++] = '.';
	return (j);
}

int		first_sym_f(t_ptf *pr, t_prs *prs, int *i)
{
	int		flag;

	flag = 0;
	if (prs->wc == 1 && abs_int_f(prs->fnbr) < 1 &&\
		abs_int_f(prs->fnbr * 10.) < 1)
	{
		pr->buff[pr->i++] = '0';
		flag = 1;
		*i = *i + 1;
	}
	return (flag);
}

void	write_int_parts(t_ptf *pr, t_prs *prs, char *res)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = fract_part_int_f(pr, prs, res);
	flag = first_sym_f(pr, prs, &i);
	if (ft_strlen(res) + flag >= prs->prc)
	{
		while (i++ < prs->prc)
			pr->buff[pr->i++] = res[j++];
	}
	else
	{
		while (i++ < ft_strlen(res))
			pr->buff[pr->i++] = res[j++];
		i = 0;
		while (i++ < prs->prc - ft_strlen(res))
			pr->buff[pr->i++] = '0';
	}
}

void	write_frac_parts(t_ptf *pr, t_prs *prs, char *res)
{
	int		i;

	i = 0;
	pr->buff[pr->i++] = '0';
	if (is_flag_hach(prs) != 0 || prs->prc != 0)
		pr->buff[pr->i++] = '.';
	while (i++ < prs->wsize)
		pr->buff[pr->i++] = '0';
	i = 0;
	if (ft_strlen(res) + prs->wsize >= prs->prc)
	{
		while (i < prs->prc - prs->wsize)
			pr->buff[pr->i++] = res[i++];
	}
	else
	{
		while (i < ft_strlen(res))
			pr->buff[pr->i++] = res[i++];
		i = 0;
		while (i++ < prs->prc - ft_strlen(res) - prs->wsize)
			pr->buff[pr->i++] = '0';
	}
}

int		buff_nbr_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl, char *res)
{
	if (prs->fnbr * 10 == prs->fnbr && prs->fnbr != 0)
		inf_f(pr, prs, dbl);
	else if (prs->fnbr != prs->fnbr)
		nan_f(pr, prs);
	else if (prs->fnbr == 0)
		print_null_prc_f(pr, prs, dbl);
	else
	{
		if (prs->wsize <= 0)
			write_int_parts(pr, prs, res);
		else
			write_frac_parts(pr, prs, res);
	}
	return (1);
}

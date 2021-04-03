/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg_9.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 06:47:49 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 06:47:51 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_int_parts_me(t_ptf *pr, t_prs *prs, char *res)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (prs->wc == 0 || (prs->wc == 1 && abs_int_f(prs->fnbr) < 1))
		pr->buff[pr->i++] = '0';
	else
	{
		while (i++ < prs->wc)
			pr->buff[pr->i++] = res[j++];
	}
	if (last_null(j, res) != 0)
	{
		if (prs->prc != 0)
			pr->buff[pr->i++] = '.';
	}
	write_frac_part_int(pr, prs, res, j);
}

void	write_frac_parts_me(t_ptf *pr, t_prs *prs, char *res)
{
	int i;

	i = 0;
	pr->buff[pr->i++] = '0';
	if (last_null(i, res) != 0)
	{
		if (prs->prc != 0)
			pr->buff[pr->i++] = '.';
		while (i++ < prs->wsize)
			pr->buff[pr->i++] = '0';
	}
	i = 0;
	if (ft_strlen(res) + prs->wsize >= prs->prc)
	{
		while (i < prs->prc - prs->wsize && last_null(i, res) != 0)
			pr->buff[pr->i++] = res[i++];
	}
	else
	{
		while (i < ft_strlen(res) && last_null(i, res) != 0)
			pr->buff[pr->i++] = res[i++];
	}
}

int		round_long_fg(t_ptf *pr, char *res, int k)
{
	int			flag;
	long long	nbr;
	int			i;

	flag = 0;
	nbr = (long long)pr->fround[0];
	if (ft_nbrlen(nbr, pr->base) != 1)
	{
		if (pr->fround[0] % pr->base >= 5)
			add_l_n(pr->fround, 5);
		if (ft_nbrlen((long long)pr->fround[0], pr->base) > \
			ft_nbrlen(nbr, pr->base))
			flag = 1;
		div_long(pr->fround, 10);
	}
	write_inttoa_f(pr, res, k);
	i = count_zero(res);
	pr->count = 0;
	while (res[i] != '\0' && last_null(i, res))
	{
		i++;
		pr->count++;
	}
	return (flag);
}

void	buff_f_ne_zero(t_ptf *pr, t_prs *prs, char *res)
{
	if (is_flag_hach(prs))
	{
		if (prs->wsize <= 0)
			write_int_parts(pr, prs, res);
		else
			write_frac_parts(pr, prs, res);
	}
	else
	{
		if (prs->wsize <= 0)
			write_int_parts_me(pr, prs, res);
		else
			write_frac_parts_me(pr, prs, res);
	}
}

void	buff_e_case(t_ptf *pr, t_prs *prs, t_ldbl *dbl, char *res)
{
	prs->prc = prs->pk - 1;
	if (prs->fnbr * 10 == prs->fnbr && prs->fnbr != 0)
		inf_f(pr, prs, dbl);
	else if (prs->fnbr != prs->fnbr)
		nan_f(pr, prs);
	else if (dbl->nbr == 0)
		print_null_prc(pr, prs, dbl);
	else
	{
		if (is_flag_hach(prs))
			env_in_buff(pr, prs, res);
		else
			env_in_buff_mn(pr, prs, res);
		digit_in_buff_g(pr, prs);
	}
}

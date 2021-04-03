/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fexp_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:35:39 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:35:40 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	zero_left_f(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	prs->sym = 48;
	add_space_f(pr, prs, 5, 1);
	pr->buff[pr->i++] = '0';
	if (is_flag_hach(prs) != 0 || prs->prc != 0)
		pr->buff[pr->i++] = '.';
	while (i++ < prs->prc)
		pr->buff[pr->i++] = '0';
	if (prs->string[ft_strlen(prs->string) - 1] == 'e')
		pr->buff[pr->i++] = 'e';
	else
		pr->buff[pr->i++] = 'E';
	pr->buff[pr->i++] = '+';
	pr->buff[pr->i++] = '0';
	pr->buff[pr->i++] = '0';
}

void	print_null_prc(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	flag_f_null(prs, dbl);
	if (prs->first != 0)
	{
		if (!is_flag_zero(prs))
			zero_abs_first_e(pr, prs);
		else
			zero_right_e(pr, prs);
	}
	else
	{
		if (!is_flag_zero(prs))
			zero_abs_f(pr, prs);
		else
			zero_left_f(pr, prs);
	}
}

void	digit_in_buff(t_ptf *pr, t_prs *prs)
{
	int		i;
	char	*str;

	i = 0;
	prs->wsize = (prs->wsize == 0) ? prs->exp : prs->wsize;
	if (prs->exp == 0)
	{
		pr->buff[pr->i++] = '0';
		pr->buff[pr->i++] = '0';
	}
	else if (ft_nbrlen(prs->wsize, pr->base) == 1)
	{
		pr->buff[pr->i++] = '0';
		pr->buff[pr->i++] = prs->wsize + '0';
	}
	else
	{
		str = ft_uitoa_base(pr->base, prs->wsize);
		while (str[i] != '\0')
			pr->buff[pr->i++] = str[i++];
		ft_strdel(&str);
	}
}

void	env_in_buff(t_ptf *pr, t_prs *prs, char *res)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	pr->sym_frac = (abs_int_f(prs->fnbr) >= 1) ? 0 : 1;
	while (res[i] == '0')
		i++;
	if (res[i] != '\0')
		pr->buff[pr->i++] = res[i++];
	if (is_flag_hach(prs) != 0 || prs->prc != 0)
		pr->buff[pr->i++] = '.';
	while (k++ < prs->prc && res[i] != '\0')
		pr->buff[pr->i++] = res[i++];
	pr->buff[pr->i++] = (prs->string[ft_strlen(prs->string) - 1] == 'e' ||\
		prs->string[ft_strlen(prs->string) - 1] == 'g') ? 'e' : 'E';
	pr->buff[pr->i++] = (pr->sym_frac == 0) ? '+' : '-';
}

int		buff_nbr_fe(t_ptf *pr, t_prs *prs, t_ldbl *dbl, char *res)
{
	if (prs->fnbr * 10 == prs->fnbr && prs->fnbr != 0)
		inf_f(pr, prs, dbl);
	else if (prs->fnbr != prs->fnbr)
		nan_f(pr, prs);
	else if (prs->fnbr == 0)
		print_null_prc(pr, prs, dbl);
	else
	{
		env_in_buff(pr, prs, res);
		digit_in_buff(pr, prs);
	}
	return (1);
}

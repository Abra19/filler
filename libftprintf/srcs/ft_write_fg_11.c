/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg_11.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 06:56:37 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 06:56:38 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		round_long_ff(t_ptf *pr, char *res, int k)
{
	int			flag;
	long long	nbr;

	flag = 0;
	nbr = (long long)pr->fround[0];
	if (pr->fround[0] % pr->base >= 5 &&\
		ft_nbrlen(pr->fround[0], pr->base) != 1)
		add_l_n(pr->fround, 5);
	if (ft_nbrlen((long long)pr->fround[0], pr->base) >\
		ft_nbrlen(nbr, pr->base))
		flag = 1;
	if (ft_nbrlen(pr->fround[0], pr->base) > 2)
		div_long(pr->fround, 10);
	write_inttoa_f(pr, res, k);
	return (flag);
}

void	digit_in_buff_g(t_ptf *pr, t_prs *prs)
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

void	process_str_fe(t_ptf *pr, t_prs *prs, t_ldbl *dbl, char *res)
{
	char	*str;
	int		len_f;

	if (prs->fnbr != 0)
		prs->prc = prs->pk - prs->el - 1;
	str = process_str(pr, prs, res);
	len_f = count_frac_g(str, pr, prs);
	process_params_g(prs, dbl);
	if ((prs->first != 0 && dbl->field.exp != 32767))
	{
		pr->buff[pr->i++] = prs->first;
		buff_nbr_fg(pr, prs, dbl, str);
		first_fl_align(pr, prs, len_f);
	}
	else if (dbl->field.exp != 32767)
	{
		buff_nbr_fg(pr, prs, dbl, str);
		first_fl_align(pr, prs, len_f);
	}
	else
		buff_nbr_fg(pr, prs, dbl, str);
	ft_strdel(&str);
}

char	*form_str_gl(char *res, t_ptf *pr, t_prs *prs)
{
	int		k;
	int		i;
	char	*str;

	i = 0;
	while (res[i] == '0')
		i++;
	str = ft_strsub((const char *)res, i, prs->prc + 2);
	pr->fround = (int *)ft_memalloc(sizeof(int) * MAXLEN + prs->prc);
	k = read_long(str, pr->fround);
	ft_strdel(&str);
	str = (char *)ft_memalloc(sizeof(char) * (MAXLEN + prs->prc + 1));
	str[MAXLEN + prs->prc] = '\0';
	round_long_fg(pr, str, k);
	ft_memdel((void **)&pr->fround);
	return (str);
}

void	first_align_gl(t_ptf *pr, t_prs *prs)
{
	int		j;

	j = 0;
	if ((prs->first != 0 && (prs->fnbr >= 0 || is_flag_hach(prs))) ||\
		prs->fnbr < 0)
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

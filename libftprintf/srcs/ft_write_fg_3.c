/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fg_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:45:41 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:45:42 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "g" + "G"
** or "lg" + "lG" or "Lg" + "LG"
*/

void	new_round_g(t_ptf *pr, t_prs *prs, char *res)
{
	int		k;
	char	*str;
	int		i;

	i = 0;
	prs->pk = prs->prc;
	prs->el = prs->new_exp;
	if (prs->fnbr != 0)
		prs->prc = prs->pk - prs->new_exp - 1;
	prs->sizef = prs->wc;
	pr->fround = (int *)ft_memalloc(sizeof(int) * (MAXLEN + prs->prc));
	k = read_long(res, pr->fround);
	ft_strdel(&res);
	str = (char *)ft_memalloc(sizeof(char) * (MAXLEN + prs->prc + 1));
	str[MAXLEN + prs->prc] = '\0';
	round_long_fg(pr, str, k);
	ft_memdel((void **)&pr->fround);
	prs->wsize = prs->pk - prs->new_exp - 1;
	if (pr->flag != 0)
		prs->wsize--;
	process_zero_g(pr, prs, str);
	while (i < prs->pk - prs->new_exp - prs->wsize && last_null(i, str) != 0)
		pr->buff[pr->i++] = str[i++];
	ft_strdel(&str);
}

void	print_case_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	char	*str;

	str = format_str(pr, prs, dbl);
	prs->num = process_params_f(pr, prs, dbl);
	prs->sizef = prs->wc;
	prs->len_f = count_frac(str, prs);
	right_f_init(pr, prs, dbl);
	buff_nbr_fg(pr, prs, dbl, str);
	ft_strdel(&str);
}

void	print_case_g(t_ptf *pr, t_prs *prs, t_ldbl *dbl, char *str)
{
	if (is_flag_hach(prs))
		prs->sym = 32;
	format_str_g(pr, prs, dbl);
	buff_nbr_fg(pr, prs, dbl, str);
	ft_strdel(&str);
}

void	align_in_fg(t_ptf *pr, t_prs *prs, int len_f)
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
		while (j++ <\
			prs->width - len_f - prs->wsize - prs->sizef - prs->num)
			pr->buff[pr->i++] = prs->sym;
	}
}

void	first_fl_align(t_ptf *pr, t_prs *prs, int len_f)
{
	int		j;
	int		i;
	char	*str;

	j = 0;
	i = 0;
	str = ft_uitoa_frac_prc(pr->base, pr->frac, prs->prc);
	while (str[i] == '0')
		i++;
	if (abs_int_f(prs->fnbr) < 1)
		prs->wsize = i;
	ft_strdel(&str);
	if (prs->nul_prc != 0 && prs->fnbr != 0)
		prs->num--;
	if (!is_flag_hach(prs))
		align_in_fg(pr, prs, len_f);
	else
	{
		while (j++ < prs->width - (prs->pr_pk - prs->el - 1) - prs->sizef\
			- prs->num)
			pr->buff[pr->i++] = prs->sym;
	}
}

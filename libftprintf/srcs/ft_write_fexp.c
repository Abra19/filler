/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fexp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:30:12 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:30:17 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "e" + "E"
** or "le" + "lE" or "Le" + "LE"
*/

void	int_part_u(t_ptf *pr, t_prs *prs)
{
	int		i;
	int		j;
	int		n;
	int		flag;
	char	*str;

	i = MAXLEN - 1;
	while (pr->fint[i] == 0 && i > 0)
		i--;
	flag = i;
	prs->s_parts = (char*)ft_memalloc(sizeof(char) *\
	(MAXLEN * BASELEN + 1));
	while (i >= 0)
	{
		j = 0;
		str = ft_uitoa_base(pr->base, pr->fint[i]);
		n = BASELEN - ft_strlen(str);
		while (n-- > 0 && i != flag)
			prs->s_parts[prs->k++] = '0';
		while (str[j] != '\0')
			prs->s_parts[prs->k++] = str[j++];
		ft_strdel(&str);
		i--;
	}
}

int		flag_null_fnbr_e(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	if (prs->c_width == 1)
		align_left_fe(pr, prs, dbl);
	else
		align_right_fe(pr, prs, dbl);
	return (1);
}

int		flag_fnbr_e(t_ptf *pr, t_prs *prs, t_ldbl *dbl)
{
	flag_zero_f(prs);
	flag_first_f(prs, dbl);
	if (is_flag_minus(prs) || prs->c_width == 1)
		align_left_fe(pr, prs, dbl);
	else
		align_right_fe(pr, prs, dbl);
	return (1);
}

int		read_float_e(t_ptf *pr, t_prs *prs)
{
	if (ft_strcmp((const char*)prs->string, "e") == 0 ||\
		ft_strcmp((const char*)prs->string, "E") == 0 ||\
		ft_strcmp((const char*)prs->string, "le") == 0 ||\
		ft_strcmp((const char*)prs->string, "lE") == 0)
		prs->fnbr = (long double)va_arg(pr->ap, double);
	else if (ft_strcmp((const char*)prs->string, "Le") == 0 ||\
		ft_strcmp((const char*)prs->string, "LE") == 0)
		prs->fnbr = va_arg(pr->ap, long double);
	return (1);
}

int		hand_fexp(t_ptf *pr, t_prs *prs)
{
	t_ldbl		dbl;

	pr->base = 10;
	read_float_e(pr, prs);
	if ((prs->no_prc == 1 || prs->n_mark == 1) || prs->prc < 0)
		prs->prc = 6;
	if (prs->flag_prc == 1 && (prs->no_prc == 1 || prs->n_mark == 1))
		prs->prc = 0;
	dbl.nbr = prs->fnbr;
	pr->fint = (int*)ft_memalloc(sizeof(int) * MAXLEN + prs->prc);
	process_binary(&dbl, pr, prs);
	if (prs->fnbr >= 0)
	{
		if (prs->flags != 0)
			flag_fnbr_e(pr, prs, &dbl);
		else
			flag_null_fnbr_e(pr, prs, &dbl);
	}
	else
		process_fnegative_e(pr, prs, &dbl);
	ft_memdel((void **)&(pr->fint));
	return (1);
}

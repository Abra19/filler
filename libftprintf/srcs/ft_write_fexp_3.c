/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_fexp_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 05:48:16 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 05:48:19 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "e" + "E"
** or "le" + "lE" or "Le" + "LE"
*/

char	*make_str_f(t_ptf *pr, t_prs *prs)
{
	char	*str1;
	char	*str2;
	int		i;
	char	*str;

	i = 0;
	int_part_u(pr, prs);
	prs->wc = 1;
	str1 = ft_uitoa_frac_prc(pr->base, pr->frac, prs->prc + prs->exp);
	str2 = ft_strjoin(prs->s_parts, str1);
	ft_strdel(&str1);
	while (str2[i] == '0')
		i++;
	str = ft_strsub((const char*)str2, i, ft_strlen(str2) - i + 1);
	if (ft_strlen(str) < prs->prc + prs->wc)
		prs->wsize = prs->prc + prs->wc - ft_strlen(str);
	ft_strdel(&str2);
	ft_strdel(&prs->s_parts);
	return (str);
}

char	*union_parts(t_ptf *pr, t_prs *prs)
{
	char	*str;
	int		k;
	int		n;
	char	*str1;
	int		len;

	str = make_str_f(pr, prs);
	len = (ft_strlen(str) > MAXLEN * BASELEN + prs->prc) ?\
		(ft_strlen(str) / 8 + 1) : (MAXLEN + prs->prc);
	pr->fround = (int*)ft_memalloc(sizeof(int) * (len));
	k = read_long(str, pr->fround);
	len = (ft_strlen(str) > MAXLEN * BASELEN + prs->prc) ?\
		(ft_strlen(str) + 1) : (MAXLEN * BASELEN + prs->prc);
	str1 = (char *)ft_memalloc(sizeof(char) * (len + 1));
	str1[len] = '\0';
	ft_strdel(&str);
	n = round_long(pr, prs, k);
	write_inttoa_f(pr, str1, k);
	if (n != 0 && prs->prc == 0 && prs->fnbr < 1)
		prs->wsize = prs->exp - 1;
	else if (prs->fnbr > 1 && (ft_nbrlen((long long)(pr->fround[0] - 1),\
	pr->base) < ft_nbrlen((long long)pr->fround[0], pr->base)) && n != 0)
		prs->wsize = prs->exp + 1;
	ft_memdel((void**)&pr->fround);
	return (str1);
}

void	zero_abs_first_e(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	if (!is_flag_minus(prs) && prs->c_width != 1)
		add_space_f(pr, prs, 5, 2);
	pr->buff[pr->i++] = prs->first;
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
	if (is_flag_minus(prs) || prs->c_width == 1)
		add_space_f(pr, prs, 5, 2);
}

void	zero_right_e(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	pr->buff[pr->i++] = prs->first;
	prs->sym = 48;
	add_space_f(pr, prs, 5, 2);
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

void	zero_abs_f(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	if (!is_flag_minus(prs) && prs->c_width != 1)
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
	if (is_flag_minus(prs) || prs->c_width == 1)
		add_space_f(pr, prs, 5, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:09:56 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 19:10:06 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			(*g_hand[14])(t_ptf *pr, t_prs *prs) = {hand_wchar, hand_string,\
	hand_wstring, hand_integer, hand_binary, hand_fd, hand_ptr, hand_non_print,\
	hand_base_8, hand_base_16, hand_base_10, hand_float, hand_fexp, hand_f_g};

/*
** dispatche function in accordance of specifier and size_flags
*/

int		mapping(t_ptf *pr, t_prs *prs)
{
	if (map1(prs->string) != -1)
	{
		if ((*g_hand[map1(prs->string)])(pr, prs) == -1)
			return (0);
	}
	else if (map2(prs->string) != -1)
	{
		if ((*g_hand[map2(prs->string)])(pr, prs) == -1)
			return (0);
	}
	else if (map3(prs->string) != -1)
	{
		if ((*g_hand[map3(prs->string)])(pr, prs) == -1)
			return (0);
	}
	else if (map4(prs->string) != -1)
	{
		if ((*g_hand[map4(prs->string)])(pr, prs) == -1)
			return (0);
	}
	else
		return (0);
	return (1);
}

int		ft_specifier(t_ptf *pr, t_prs *prs)
{
	if (is_spec(pr->frt[pr->pos]) != 1)
	{
		print_error("specifier is invalid");
		return (0);
	}
	prs->spec = (char*)ft_memalloc(sizeof(char) * 2);
	prs->spec[0] = pr->frt[pr->pos];
	prs->spec[1] = '\0';
	prs->string = ft_strjoin(prs->letters, prs->spec);
	if ((prs->prc >= 2147483647 || prs->prc <= -2147483648) &&\
		pr->frt[pr->pos] != 's')
		prs->prc = 6;
	ft_strdel(&prs->spec);
	if (mapping(pr, prs) == 0)
	{
		print_error("specifier is invalid");
		ft_strdel(&prs->string);
		return (0);
	}
	ft_strdel(&prs->string);
	return (1);
}

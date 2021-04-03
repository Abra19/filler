/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_wchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:32:28 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:32:29 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "c" && "lc"
*/

int		flag_null(t_ptf *pr, t_prs *prs)
{
	int		i;

	i = 0;
	if (prs->width != 0)
	{
		if (prs->c_width == 1)
		{
			buff_wchar(pr, prs);
			while (i++ < prs->width - prs->wsize)
				pr->buff[pr->i++] = prs->sym;
		}
		else if (width_non_zero_wc(pr, prs) == 0)
			return (-1);
	}
	else
		buff_wchar(pr, prs);
	return (1);
}

int		buff_wchar(t_ptf *pr, t_prs *prs)
{
	size_t	byte;
	size_t	tmp;

	tmp = prs->wsize;
	if (prs->wsize != 1)
	{
		byte = (240 << (4 - prs->wsize)) | (prs->wc >> ((prs->wsize - 1) * 6));
		pr->buff[pr->i++] = (char)byte;
		tmp--;
		while (tmp-- > 0)
		{
			byte = ((prs->wc >> ((tmp) * 6)) & 63) | 128;
			pr->buff[pr->i++] = (char)byte;
		}
	}
	else
	{
		pr->buff[pr->i] = (char)prs->wc;
		pr->i++;
	}
	return (1);
}

int		flag_width(t_ptf *pr, t_prs *prs, int j)
{
	int		i;

	i = 0;
	if (j == ft_strlen((const char *)prs->flags))
	{
		while (i++ < prs->width - prs->wsize)
			pr->buff[pr->i++] = prs->sym;
		buff_wchar(pr, prs);
	}
	else
	{
		buff_wchar(pr, prs);
		while (i++ < prs->width - prs->wsize)
			pr->buff[pr->i++] = prs->sym;
	}
	return (1);
}

int		read_wchar(t_ptf *pr, t_prs *prs)
{
	if (ft_strcmp((const char*)prs->string, "c") == 0)
		prs->wc = (char)va_arg(pr->ap, long long);
	else if (ft_strcmp((const char*)prs->string, "lc") == 0)
		prs->wc = (int)va_arg(pr->ap, long long);
	if ((prs->wsize = size_wchar(prs)) == -1)
		return (-1);
	return (1);
}

int		hand_wchar(t_ptf *pr, t_prs *prs)
{
	size_t	j;

	if (read_wchar(pr, prs) == -1)
		return (0);
	prs->sym = (is_flag_zero(prs)) ? 48 : 32;
	if (prs->width != 0 && prs->flags != 0)
	{
		j = 0;
		while (prs->flags[j] != '-' && prs->flags[j] != '\0')
			j++;
		if (flag_width(pr, prs, j) == -1)
			return (-1);
	}
	else
	{
		if (flag_null(pr, prs) == -1)
			return (-1);
	}
	return (1);
}

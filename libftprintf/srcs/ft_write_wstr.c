/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_wstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:34:39 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:34:41 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "ls"
*/

int		flag_null_w(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	size_t		i;
	size_t		n;

	i = 0;
	if (len != 0)
	{
		if (prs->c_width == 1)
		{
			n = buff_wstr(pr, prs, prc);
			while (i++ < len - n)
				pr->buff[pr->i++] = 32;
		}
		else
			width_non_zero_ws(pr, prs, len, prc);
	}
	return (1);
}

void	flag_width_w(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	size_t	j;
	int		i;
	int		n;

	j = 0;
	i = 0;
	while (prs->flags[i] != '-' && prs->flags[i] != '\0')
		i++;
	if (i == ft_strlen((const char *)prs->flags))
	{
		while (j++ < len - prc)
			pr->buff[pr->i++] = 32;
		buff_wstr(pr, prs, prc);
	}
	else
	{
		n = buff_wstr(pr, prs, prc);
		while (j++ < len - n)
			pr->buff[pr->i++] = 32;
	}
}

int		buff_wstr(t_ptf *pr, t_prs *prs, size_t prc)
{
	size_t	i;

	i = pr->i - 1;
	if (prc > 0)
	{
		while (pr->i - i <= prc)
		{
			prs->wc = *prs->wstr;
			prs->wsize = size_wchar(prs);
			if (pr->i - i - 1 + prs->wsize <= prc)
			{
				buff_wchar(pr, prs);
				prs->wstr++;
			}
			else
				return (pr->i - i - 1);
		}
	}
	return (pr->i - i - 1);
}

int		read_wstring(t_ptf *pr, t_prs *prs)
{
	if (ft_strcmp((const char*)prs->string, "ls") == 0)
		prs->wstr = va_arg(pr->ap, wchar_t*);
	if (prs->wstr == 0)
	{
		if (pr->frt[pr->pos - 2] != '.')
			write_null(pr, prs);
	}
	if (prs->wstr != 0)
	{
		if ((prs->wsize = ft_wstrlen(prs->wstr)) == -1)
			return (-1);
	}
	return (1);
}

int		hand_wstring(t_ptf *pr, t_prs *prs)
{
	size_t	len;
	size_t	prc;

	if (read_wstring(pr, prs) == -1)
		return (0);
	if (prs->c_prc == 1 || prs->nul_prc == 1)
		write_blank(pr, prs->width + 1);
	else if (prs->wstr != 0)
	{
		prc = long_sym(prs->prc, ft_wstrlen(prs->wstr), prs->width);
		prc = count_size(prs, prc);
		len = max_len(prs->width, prc);
		if (len != 0 && prs->flags != 0 && prs->width != 0)
			flag_width_w(pr, prs, len, prc);
		else
			flag_null_w(pr, prs, len, prc);
	}
	return (1);
}

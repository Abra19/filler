/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizeof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:20:52 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:20:54 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function for char, wchar to manage size
*/

int		size_wchar(t_prs *prs)
{
	if (prs->wc <= 127)
		return (1);
	else if (prs->wc >= 128 && prs->wc <= 2047)
		return (2);
	else if (prs->wc >= 2048 && prs->wc <= 65535)
		return (3);
	else if (prs->wc >= 65536 && prs->wc <= 1114111)
		return (4);
	else
		return (-1);
}

/*
** functions for str and wstr
*/

int		count_size(t_prs *prs, size_t prc)
{
	int					n;
	size_t				j;

	n = 0;
	j = 0;
	if (prc != 0)
	{
		while (j < prc)
		{
			prs->wc = prs->wstr[j];
			prs->wsize = size_wchar(prs);
			n = n + prs->wsize;
			if ((size_t)n > prc)
				return (n - prs->wsize);
			else
				j++;
		}
	}
	return (n);
}

/*
** length of wstr
*/

size_t	ft_wstrlen(wchar_t *wstr)
{
	size_t				len;

	len = 0;
	while (*wstr != '\0')
	{
		if (*wstr <= 127)
			len = len + 1;
		else if (*wstr >= 128 && *wstr <= 2047)
			len = len + 2;
		else if (*wstr >= 2048 && *wstr <= 65535)
			len = len + 3;
		else if (*wstr >= 65536 && *wstr <= 1114111)
			len = len + 4;
		else
			return (-1);
		wstr++;
	}
	return (len);
}

/*
**  length of nbr
*/

int		ft_nbrlen(long long nbr, uint8_t base)
{
	int			size;
	uint64_t	tmp;

	tmp = abs_int(nbr);
	size = 0;
	if (tmp == 0)
		return (1);
	while (tmp > 0)
	{
		tmp = tmp / base;
		size++;
	}
	return (size);
}

/*
**  length of unbr
*/

int		ft_unbrlen(unsigned long long unbr, uint8_t base)
{
	int					size;
	unsigned long long	tmp;

	tmp = unbr;
	size = 0;
	if (tmp == 0)
		return (1);
	else
	{
		while (tmp >= 1)
		{
			tmp = tmp / base;
			size++;
		}
		return (size);
	}
}

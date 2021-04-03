/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:24:37 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:24:39 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags =  "s"
** str = null
*/

static char		g_str_0[6] = "(null)";

void	flag_min_0(t_ptf *pr, size_t len, size_t prc)
{
	size_t	i;

	i = 1;
	write_buff_null(pr, prc);
	pr->i++;
	while (i++ <= len - prc)
		pr->buff[pr->i++] = 32;
}

void	write_buff_null(t_ptf *pr, size_t prc)
{
	size_t	i;

	i = 0;
	if (prc != 0)
	{
		while (i < prc)
		{
			pr->buff[pr->i] = g_str_0[i];
			pr->i++;
			i++;
		}
	}
	else
	{
		while (g_str_0[i] != '\0')
		{
			pr->buff[pr->i] = g_str_0[i];
			i++;
			pr->i++;
		}
	}
	pr->i--;
}

void	without_flag_0(t_ptf *pr, size_t len, size_t prc)
{
	size_t	i;

	i = 0;
	if (len != 0)
	{
		while (i++ < len - prc)
			pr->buff[pr->i++] = 32;
		write_buff_null(pr, prc);
		pr->i++;
	}
	else
		write_buff_null(pr, prc);
}

void	process_null(t_ptf *pr, size_t prc, size_t len)
{
	write_blank(pr, len);
	write_buff_null(pr, prc);
}

void	write_null(t_ptf *pr, t_prs *prs)
{
	int		i;
	size_t	len;
	size_t	prc;

	prc = long_sym(prs->prc, 6, 6);
	len = max_len(prs->width, prc);
	if (len != 0 && prs->flags != 0)
	{
		i = 0;
		while (prs->flags[i] != '-' && prs->flags[i] != '\0')
			i++;
		if (i == ft_strlen((const char *)prs->flags))
			process_null(pr, prc, len);
		else
			flag_min_0(pr, len, prc);
	}
	else
	{
		if (prs->c_width == 1)
			flag_min_0(pr, len, prc);
		else
			without_flag_0(pr, len, prc);
	}
}

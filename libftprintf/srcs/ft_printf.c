/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:19:58 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 19:46:05 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** ft_printf is analog of libc function printf
** write to buffer and print after
** buffer have a dynamic size
** conversion: c, s, p
** flag l for c and s 											- bonus
** conversion: d, i, o, u, x, X with flags hh, h, l, ll
** conversion: f  and F with flags l and L
** conversion: e, E with flags l and L 							- bonus
** conversion: g, G with flags l and L 							- bonus
** conversion: b - to print in binary 							- bonus
** conversion: r - to print non-printable characters 			- bonus
** conversion: w - to print in fd								- bonus
** manage %%
** manage flags # 0 - + ' '
** manage flag * 												- bonus
** manage the minimum field-width
** manage the precision
** manage color													- bonus
*/

void	write_buff(t_ptf *pr)
{
	size_t	i;

	i = 0;
	while (i < pr->i)
	{
		write(pr->fd, &pr->buff[i], 1);
		i++;
	}
}

int		ft_printf_all(t_ptf *pr)
{
	size_t	len;

	len = (int)ft_strlen(pr->frt);
	while (pr->pos < len)
	{
		while (pr->frt[pr->pos] != '%' && pr->frt[pr->pos] != '\0')
		{
			if (pr->i == BUF_SIZE - 1)
				resize_da(pr);
			if (pr->frt[pr->pos] == '{')
				set_color(pr);
			else
			{
				pr->buff[pr->i] = pr->frt[pr->pos];
				pr->i++;
			}
			pr->pos++;
		}
		if (print_in_buff(pr, len) == 0)
			return (0);
		pr->pos++;
	}
	pr->len = pr->i;
	pr->buff[pr->i] = '\0';
	return (1);
}

/*
** print from buff
*/

int		ft_printf(char const *format, ...)
{
	t_ptf	pr;

	ft_bzero(&pr, sizeof(pr));
	pr.frt = (char*)format;
	pr.fd = 1;
	pr.buff = create_da(&pr, BUF_SIZE);
	if (format == NULL)
		return (-1);
	read_format(&pr);
	va_start(pr.ap, format);
	if (ft_printf_all(&pr) == 0)
	{
		va_end(pr.ap);
		clean_up(&pr);
		return (-1);
	}
	else
		write_buff(&pr);
	clean_up(&pr);
	va_end(pr.ap);
	return (pr.len);
}

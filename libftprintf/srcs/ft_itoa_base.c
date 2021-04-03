/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:41:58 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 18:42:00 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_uitoa_base(uint8_t base, long long nbr)
{
	char				*str;
	int					len;
	char				*mask;
	uint64_t			res;

	res = abs_int(nbr);
	mask = "0123456789ABCDEF";
	len = ft_nbrlen(nbr, base);
	str = (char*)ft_memalloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	len--;
	if (res == 0)
		str[len] = '0';
	while (res >= 1)
	{
		str[len] = mask[res % base];
		res = res / base;
		len--;
	}
	return (str);
}

char	*ft_itoa_base(uint8_t base, unsigned long long unbr, char *mask)
{
	char				*str;
	int					len;
	unsigned long long	res;

	res = unbr;
	len = ft_unbrlen(unbr, base);
	str = (char*)ft_memalloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	len--;
	if (res == 0)
		str[len] = '0';
	while (res >= 1)
	{
		str[len] = mask[res % base];
		res = res / base;
		len--;
	}
	return (str);
}

char	*ft_itoa_mant(t_ldbl *dbl)
{
	int					len;
	char				*mask;
	uint64_t			nbr;
	char				*res;

	len = LEN;
	mask = "01";
	nbr = dbl->field.mant;
	res = (char*)ft_memalloc(sizeof(char) * (len + 1));
	res[len] = '\0';
	len--;
	while (nbr >= 1)
	{
		res[len] = mask[nbr % 2];
		nbr = nbr / 2;
		len--;
	}
	return (res);
}

char	*ft_uitoa_frac_prc(uint8_t base, long double frac, int prc)
{
	char				*res;
	int					i;
	int					*c;
	long double			f;

	i = 1;
	f = frac;
	res = (char*)ft_memalloc(sizeof(char) * (prc + 2));
	c = (int*)ft_memalloc(sizeof(int) * (prc + 1));
	res[prc + 1] = '\0';
	c[0] = (int)(frac * base);
	while (i <= prc)
	{
		f = f * (long double)base - (long double)c[i - 1];
		c[i] = (int)(f * (long double)base);
		i++;
	}
	i = 0;
	while (i <= prc)
	{
		res[i] = c[i] + '0';
		i++;
	}
	ft_memdel((void**)&c);
	return (res);
}

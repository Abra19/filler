/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 05:08:26 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 05:08:28 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** string of array of int for long calc
*/

int		read_long(char *str, int *x)
{
	int					k;
	int					len;
	char				*tmp;

	k = 0;
	len = ft_strlen(str);
	tmp = (char*)ft_memalloc(sizeof(char) * (BASELEN + 1));
	tmp[BASELEN] = '\0';
	while (len > BASELEN)
	{
		ft_copycut(tmp, str, len - BASELEN, BASELEN);
		x[k] = (int)ft_atol((const char*)tmp);
		k++;
		len = len - BASELEN;
	}
	ft_strdel(&tmp);
	tmp = (char*)ft_memalloc(sizeof(char) * \
	(ft_strlen(str) - k * BASELEN + 1));
	tmp[ft_strlen(str) - k * BASELEN] = '\0';
	ft_copycut(tmp, str, 0, ft_strlen(str) - k * BASELEN);
	x[k] = (int)ft_atol((const char*)tmp);
	ft_strdel(&tmp);
	return (k);
}

/*
** array of array of int for power of 2 from 0 to 16383
*/

void	read_long_all(t_ptf *pr)
{
	unsigned long long	i;

	i = 0;
	while (i < POWSIZE)
	{
		if (i <= 24)
			read_long(pr->pow[i], pr->flnbr[i]);
		else
			mult_l(pr->flnbr[i], pr->flnbr[i - 1], 2);
		i++;
	}
}

/*
** strings of power of 2
*/

void	count_pow(t_ptf *pr)
{
	pr->pow[0] = "1";
	pr->pow[1] = "2";
	pr->pow[2] = "4";
	pr->pow[3] = "8";
	pr->pow[4] = "16";
	pr->pow[5] = "32";
	pr->pow[6] = "64";
	pr->pow[7] = "128";
	pr->pow[8] = "256";
	pr->pow[9] = "512";
	pr->pow[10] = "1024";
	pr->pow[11] = "2048";
	pr->pow[12] = "4096";
	pr->pow[13] = "8192";
	pr->pow[14] = "16384";
	pr->pow[15] = "32768";
	pr->pow[16] = "65536";
	pr->pow[17] = "131072";
	pr->pow[18] = "262144";
	pr->pow[19] = "524288";
	pr->pow[20] = "1048576";
	pr->pow[21] = "2097152";
	pr->pow[22] = "4194304";
	pr->pow[23] = "8388608";
	pr->pow[24] = "16777216";
}

void	prepare_f(t_ptf *pr)
{
	int					i;

	i = 0;
	count_pow(pr);
	while (i < POWSIZE)
	{
		pr->flnbr[i] = create_da_int(MAXLEN);
		i++;
	}
	read_long_all(pr);
}

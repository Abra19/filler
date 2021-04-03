/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:49:59 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 19:50:00 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	g_mask[20] = "%*csrdiboxXufFeEgGpw";

/*
** function for fill_spec - consider wild
*/

void	check_wild(t_ptf *pr, int *i, int *k)
{
	if (pr->frt[*i] == '*')
	{
		pr->spec[*k] = pr->frt[*i];
		pr->prespec[*k] = pr->frt[*i - 1];
		*k = *k + 1;
	}
}

/*
** fill a tab of specifiers meet in format
*/

void	fill_spec(t_ptf *pr, int *i, int *k)
{
	int		j;

	j = 0;
	if (pr->frt[*i] == '%')
	{
		*i = *i + 1;
		if (pr->frt[*i] != '%')
		{
			while (is_spec(pr->frt[*i]) != 1 && pr->frt[*i] != '\0')
			{
				check_wild(pr, i, k);
				*i = *i + 1;
			}
			while (g_mask[j] != '\0' && pr->frt[*i] != g_mask[j])
				j++;
			if (pr->frt[*i] == g_mask[j] && g_mask[j] != '%')
			{
				pr->spec[*k] = pr->frt[*i];
				pr->prespec[*k] = pr->frt[*i - 1];
				*k = *k + 1;
			}
		}
	}
}

/*
** count the number of specifiers meet in format
*/

void	count_args(t_ptf *pr, int *i)
{
	int		j;

	j = 0;
	if (pr->frt[*i] == '%')
	{
		*i = *i + 1;
		if (pr->frt[*i] != '%')
		{
			while (is_spec(pr->frt[*i]) != 1 && pr->frt[*i] != '\0')
			{
				if (pr->frt[*i] == '*')
					pr->n_args++;
				*i = *i + 1;
			}
			while (g_mask[j] != '\0' && pr->frt[*i] != g_mask[j])
				j++;
			if (pr->frt[*i] == g_mask[j] && g_mask[j] != '%')
				pr->n_args++;
		}
	}
}

void	parce_format(t_ptf *pr)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (pr->frt[i] != '\0')
	{
		count_args(pr, &i);
		i++;
	}
	pr->spec = (char*)ft_memalloc(sizeof(char) * (pr->n_args + 1));
	pr->prespec = (char*)ft_memalloc(sizeof(char) * (pr->n_args + 1));
	i = 0;
	while (pr->frt[i] != '\0')
	{
		fill_spec(pr, &i, &k);
		i++;
	}
	pr->spec[pr->n_args] = '\0';
	pr->prespec[pr->n_args] = '\0';
}

int		read_format(t_ptf *pr)
{
	parce_format(pr);
	if (ft_strchr(pr->spec, 'f') != 0 || ft_strchr(pr->spec, 'F') != 0 || \
		ft_strchr(pr->spec, 'g') != 0 || ft_strchr(pr->spec, 'G') != 0 ||\
		ft_strchr(pr->spec, 'e') != 0 || ft_strchr(pr->spec, 'E') != 0)
		prepare_f(pr);
	return (1);
}

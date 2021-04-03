/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:19:31 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 18:19:34 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** fix prc
*/

void	read_prc(char *res, t_ptf *pr, size_t *len, t_prs *prs)
{
	res = ft_strsub(pr->frt, pr->pos, *len);
	prs->prc = ft_atol((const char *)res);
	pr->pos = pr->pos + *len;
	ft_strdel(&res);
}

int		prc_digit(t_ptf *pr, size_t *len, t_prs *prs)
{
	char	*res;

	res = NULL;
	while (is_spec(pr->frt[*len]) != 1 && pr->frt[*len] != 'l' &&\
		pr->frt[*len] != 'L' && pr->frt[*len] != 'h'\
		&& pr->frt[*len] != '\0' && pr->frt[*len] != '%')
	{
		if (ft_isdigit(pr->frt[*len]) != 1 && pr->frt[*len] != '-')
		{
			print_error("precision is invalid");
			return (0);
		}
		*len = *len + 1;
	}
	*len = *len - pr->pos;
	if (*len != 0)
		read_prc(res, pr, len, prs);
	if (prs->prc < 0)
		prs->c_prc = 1;
	if (prs->prc == 0)
		prs->nul_prc = 1;
	return (1);
}

int		move_prc(t_ptf *pr, t_prs *prs)
{
	while (pr->frt[pr->pos] != '.' && is_spec(pr->frt[pr->pos]) != 1 && \
		pr->frt[pr->pos] != 'h' && pr->frt[pr->pos] != 'L' && \
		pr->frt[pr->pos] != 'l' && pr->frt[pr->pos] != '\0' &&\
		pr->frt[pr->pos] != '%')
		pr->pos++;
	if (pr->frt[pr->pos] == '.')
		prs->flag_prc = 1;
	if ((is_spec(pr->frt[pr->pos + 1]) == 1 || pr->frt[pr->pos + 1] == 'h'\
		|| pr->frt[pr->pos + 1] == 'L' || pr->frt[pr->pos + 1] == 'l' ||\
		pr->frt[pr->pos + 1] == '%'))
		prs->no_prc = 1;
	if (is_spec(pr->frt[pr->pos]) == 1 || pr->frt[pr->pos] == 'h' ||\
		pr->frt[pr->pos] == 'L' || pr->frt[pr->pos] == 'l' ||\
		pr->frt[pr->pos] == '%')
	{
		prs->n_mark = 1;
		return (0);
	}
	return (1);
}

int		prc_wild(t_ptf *pr, t_prs *prs)
{
	pr->pos++;
	if (is_spec(pr->frt[pr->pos]) != 1 && pr->frt[pr->pos] != 'l' &&\
		pr->frt[pr->pos] != 'L' && pr->frt[pr->pos] != 'h' &&\
		pr->frt[pr->pos] != '%')
	{
		print_error("precision is invalid");
		return (0);
	}
	else
	{
		prs->prc = (int)va_arg(pr->ap, long long);
		if (prs->prc < 0)
			prs->c_prc = 1;
		if (prs->prc == 0)
			prs->nul_prc = 1;
	}
	return (1);
}

int		check_prc(t_ptf *pr, t_prs *prs)
{
	size_t	len;

	if (move_prc(pr, prs) == 0)
		return (1);
	pr->pos++;
	len = pr->pos;
	if (pr->frt[pr->pos] == '*')
	{
		prs->wild = 1;
		if (prc_wild(pr, prs) == 0)
			return (0);
	}
	else
	{
		if (prc_digit(pr, &len, prs) == 0)
			return (0);
	}
	return (1);
}

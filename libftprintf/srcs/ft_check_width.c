/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:24:01 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 18:24:04 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		width_star(t_ptf *pr, t_prs *prs)
{
	int i;

	if (ft_isdigit(pr->frt[pr->pos]) != 1 && pr->frt[pr->pos] != '.'\
		&& is_spec(pr->frt[pr->pos]) != 1 && pr->frt[pr->pos] != 'l'\
		&& pr->frt[pr->pos] != 'L' && pr->frt[pr->pos] != 'h')
	{
		print_error("width is invalid");
		return (0);
	}
	else if (ft_isdigit(pr->frt[pr->pos]) == 1)
	{
		i = width_parce_dollar(pr);
		if (width_star_invalid(pr, prs, &i) == 0)
			return (0);
	}
	else
	{
		prs->width = (int)va_arg(pr->ap, long long);
		if ((int)prs->width < 0)
		{
			prs->c_width = 1;
			prs->width = -(int)prs->width;
		}
	}
	return (1);
}

int		width_parse_percent(t_ptf *pr, size_t *len, size_t i)
{
	if (ft_isdigit(pr->frt[*len]) != 1)
	{
		i = *len;
		while (pr->frt[i] != '%' && pr->frt[i] != '\0')
		{
			if (is_spec(pr->frt[i]) == 0)
				i++;
			else
				break ;
		}
		if (pr->frt[i] == '%' || pr->frt[i] == '\0')
		{
			while (*len < i)
			{
				pr->buff[pr->i++] = pr->frt[*len];
				*len = *len + 1;
			}
		}
		else
			return (0);
	}
	return (1);
}

void	found_width(t_ptf *pr, size_t *len, t_prs *prs)
{
	char	*res;

	res = ft_strsub((const char*)pr->frt, pr->pos, *len);
	prs->width = ft_atol((const char *)res);
	pr->pos = pr->pos + *len;
	ft_strdel(&res);
}

int		width_digit(t_ptf *pr, size_t *len, t_prs *prs)
{
	size_t	i;

	i = 0;
	while (pr->frt[*len] != '.' && is_spec(pr->frt[*len]) != 1 &&\
		pr->frt[*len] != 'l' && pr->frt[*len] != 'L' && pr->frt[*len] != 'h'\
		&& pr->frt[*len] != '%' && pr->frt[*len] != '\0')
	{
		if (width_parse_percent(pr, len, i) == 0)
			return (0);
		*len = *len + 1;
	}
	*len = *len - pr->pos;
	if (*len != 0)
		found_width(pr, len, prs);
	return (1);
}

int		check_width(t_ptf *pr, t_prs *prs)
{
	size_t	len;

	len = pr->pos;
	if (pr->frt[pr->pos] == '*')
	{
		pr->pos++;
		prs->wild = 1;
		if (width_star(pr, prs) == 0)
			return (0);
	}
	else
	{
		if (width_digit(pr, &len, prs) == 0)
			return (0);
	}
	return (1);
}

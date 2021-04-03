/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nbr_base16_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:46:40 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 07:46:42 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	align_right_u_16(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	int	j;
	int	n;
	int size;

	j = 0;
	n = (prs->unbr == 0 && prs->flag_prc != 1) ? 1 : 0;
	if (prs->first != 0)
	{
		n += 2;
		size = (int)len - (int)prc - n;
		if (prs->sym == 32)
			space_unbr16(size, pr, prs);
		else
			zero_unbr16(size, pr, prs);
		add_zero(pr, prs);
	}
	else
	{
		while (j++ < (int)len - (int)prc - n)
			pr->buff[pr->i++] = prs->sym;
		add_zero(pr, prs);
	}
	process_zero_u_16(pr, prs);
}

void	align_left_u_16(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	int		n;
	int		size;

	n = (prs->unbr == 0 && prs->flag_prc != 1) ? 1 : 0;
	size = (int)len - (int)prc;
	if (prs->first != 0)
	{
		n += 2;
		pr->buff[pr->i++] = prs->first;
		pr->buff[pr->i++] = prs->second;
		add_zero(pr, prs);
		process_zero_u_16(pr, prs);
		if (prs->prc >= 0)
			add_space(pr, prs, size, n);
	}
	else
	{
		add_zero(pr, prs);
		process_zero_u_16(pr, prs);
		add_space(pr, prs, size, n);
	}
}

void	process_zero_u_16(t_ptf *pr, t_prs *prs)
{
	if (prs->unbr != 0 || (prs->unbr == 0 && prs->flag_prc == 0))
		buff_unbr_16(pr, prs);
}

void	buff_unbr_16(t_ptf *pr, t_prs *prs)
{
	size_t	i;
	char	*mask;

	i = 0;
	if (prs->cap_let != 1)
		mask = "0123456789abcdef";
	else
		mask = "0123456789ABCDEF";
	prs->str = ft_itoa_base(pr->base, prs->unbr, mask);
	while (prs->str[i] != '\0')
		pr->buff[pr->i++] = prs->str[i++];
	ft_strdel(&prs->str);
}

int		flag_null_unbr_16(t_ptf *pr, t_prs *prs, size_t len, size_t prc)
{
	if (prs->c_width == 1)
		align_left_u_16(pr, prs, len, prc);
	else
		align_right_u_16(pr, prs, len, prc);
	return (1);
}

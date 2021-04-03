/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:27:27 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:27:29 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier "b"
** flag #: add 0b: in beginning
** flag 0: add 0 in first bit
** flag -: align left
** length - max from width, precision, size of nbr in binary
** with flag considering
*/

void	buff_unbr_2(t_ptf *pr, t_prs *prs)
{
	int		i;
	int		j;
	char	*mask;

	i = 0;
	j = 0;
	mask = "0123456789ABCDEF";
	prs->str = ft_itoa_base(pr->base, prs->unbr, mask);
	while (prs->str[i] != '\0')
	{
		if (is_flag_zero(prs) && (prs->wsize > ft_strlen(prs->str)))
		{
			while (j++ < (prs->wsize - ft_strlen(prs->str)))
				pr->buff[pr->i++] = 48;
		}
		pr->buff[pr->i++] = prs->str[i++];
		if ((ft_strlen(prs->str) - i) % 8 == 0 && i != ft_strlen(prs->str))
			pr->buff[pr->i++] = 32;
	}
	ft_strdel(&prs->str);
}

int		flag_null_unbr_2(t_ptf *pr, t_prs *prs)
{
	if (prs->c_width == 1)
		align_left_u_2(pr, prs);
	else
		align_right_u_2(pr, prs);
	return (1);
}

void	flag_unbr_2(t_ptf *pr, t_prs *prs)
{
	if (is_flag_zero(prs))
		prs->first = 0;
	if (is_flag_hach(prs))
		prefix_2(prs);
	if (is_flag_minus(prs) || prs->c_width == 1)
		align_left_u_2(pr, prs);
	else
		align_right_u_2(pr, prs);
}

int		read_integer_2(t_ptf *pr, t_prs *prs)
{
	int n;

	if (ft_strcmp((const char*)prs->string, "b") == 0)
		prs->unbr = va_arg(pr->ap, unsigned long long);
	if ((prs->wsize = ft_unbrlen(prs->unbr, pr->base)) == -1)
		return (-1);
	if (prs->wsize % 8 != 0 && is_flag_zero(prs))
	{
		n = 8 - prs->wsize % 8;
		prs->wsize = prs->wsize + n;
	}
	return (1);
}

int		hand_binary(t_ptf *pr, t_prs *prs)
{
	pr->base = 2;
	if (read_integer_2(pr, prs) == -1)
		return (0);
	if (prs->c_prc == 1 || prs->nul_prc == 1)
		prs->prc = 0;
	if (prs->unbr == 0)
		prs->wsize = 0;
	if (prs->flags != 0)
		flag_unbr_2(pr, prs);
	else
		flag_null_unbr_2(pr, prs);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:30:30 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 21:30:31 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to write in buff: specifier + size flags = "ls"
*/

void	align_right_str(t_ptf *pr, t_prs *prs, size_t prc)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((int)prc > prs->wsize)
	{
		while (i++ < (int)prc - prs->wsize)
			pr->buff[pr->i++] = 32;
		while (i++ <= (int)prc)
			pr->buff[pr->i++] = prs->str[j++];
	}
	else
	{
		while (i++ < (int)prc)
			pr->buff[pr->i++] = prs->str[j++];
	}
}

void	align_left_str(t_ptf *pr, t_prs *prs, size_t prc)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((int)prc > prs->wsize)
	{
		while (i++ < prs->wsize)
			pr->buff[pr->i++] = prs->str[j++];
		while (i++ <= (int)prc)
			pr->buff[pr->i++] = 32;
	}
	else
	{
		while (i++ < (int)prc)
			pr->buff[pr->i++] = prs->str[j++];
	}
}

void	buff_str(t_ptf *pr, t_prs *prs, size_t prc)
{
	int		i;

	i = 0;
	if (prc == 0)
	{
		while (prs->str[i] != '\0')
			pr->buff[pr->i++] = prs->str[i++];
	}
	else
	{
		if (is_flag_minus(prs) || prs->c_width == 1)
			align_left_str(pr, prs, prc);
		else
			align_right_str(pr, prs, prc);
	}
}

int		read_string(t_ptf *pr, t_prs *prs)
{
	if (ft_strcmp((const char*)prs->string, "s") == 0)
		prs->str = va_arg(pr->ap, char*);
	if (prs->str == 0)
	{
		if (pr->frt[pr->pos - 1] != '.' && prs->nul_prc != 1)
			write_null(pr, prs);
	}
	if (prs->str != 0)
	{
		if ((prs->wsize = ft_strlen(prs->str)) == -1)
			return (-1);
	}
	return (1);
}

int		hand_string(t_ptf *pr, t_prs *prs)
{
	size_t	len;
	size_t	prc;

	if (read_string(pr, prs) == -1)
		return (0);
	if ((prs->c_prc == 1 || prs->nul_prc == 1) && (prs->wild != 1 ||\
		prs->prc == 0))
		write_blank(pr, prs->width + 1);
	else if (prs->str != 0)
	{
		prc = long_sym(prs->prc, ft_strlen(prs->str), prs->width);
		len = max_len(prs->width, prc);
		if (len != 0 && prs->flags != 0 && prs->width != 0)
			flag_width_s(pr, prs, len, prc);
		else
			flag_null_s(pr, prs, len, prc);
	}
	return (1);
}

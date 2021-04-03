/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_in_buff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 05:10:59 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 05:11:03 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** write in buff, process %%
*/

t_prs	init_buff(void)
{
	t_prs prs;

	ft_bzero(&prs, sizeof(prs));
	prs.sym = 32;
	return (prs);
}

size_t	move_to_spec(t_ptf *pr)
{
	size_t i;

	i = pr->pos;
	while (pr->frt[i] != '%' && pr->frt[i] != '\0')
	{
		if (is_spec(pr->frt[i]) == 0)
			i++;
		else
			break ;
	}
	return (i);
}

void	write_in_buff(size_t i, t_ptf *pr)
{
	if (i != pr->pos)
		pr->buff[pr->i++] = pr->frt[pr->pos];
}

int		print_in_buff(t_ptf *pr, size_t len)
{
	size_t	i;
	t_prs	prs;

	prs = init_buff();
	if (pr->frt[pr->pos] == '%' && pr->pos < len)
	{
		pr->pos++;
		if (pr->frt[pr->pos] == '%')
			pr->buff[pr->i++] = '%';
		else
		{
			if (pr->frt[i = move_to_spec(pr)] == '%')
			{
				if (hand_percent(pr) == 0)
					return (0);
			}
			else if (pr->frt[i] == '\0')
				write_in_buff(i, pr);
			else if (check_and_parse(pr, &prs) == 0)
				return (0);
		}
	}
	clean_str(&prs);
	return (1);
}

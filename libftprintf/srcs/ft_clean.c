/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 05:00:23 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/17 05:00:25 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** free memory after use
*/

void	clean_args(t_ptf *pr)
{
	ft_memdel((void**)&(pr->buff));
}

void	clean_pow(t_ptf *pr)
{
	int		i;

	i = 0;
	while (i < POWSIZE)
	{
		ft_memdel((void **)&(pr->flnbr[i]));
		i++;
	}
}

void	clean_up(t_ptf *pr)
{
	clean_pow(pr);
	clean_args(pr);
	ft_memdel((void **)&pr->flnbr);
	ft_memdel((void**)&(pr->spec));
	ft_memdel((void**)&(pr->prespec));
}

/*
** clean str with params
*/

void	clean_str(t_prs *prs)
{
	ft_strdel(&prs->flags);
	ft_strdel(&prs->letters);
}

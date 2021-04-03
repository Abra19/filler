/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_service_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:13:17 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:13:20 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** service flag functions
*/

int		is_flag_plus(t_prs *prs)
{
	int		i;

	i = 0;
	if (prs->flags == 0)
		return (0);
	else
	{
		while (prs->flags[i] != '\0')
		{
			if (prs->flags[i] == '+')
				return (1);
			i++;
		}
	}
	return (0);
}

int		is_flag_zero(t_prs *prs)
{
	int		i;

	i = 0;
	if (prs->flags == 0)
		return (0);
	else
	{
		while (prs->flags[i] != '\0')
		{
			if (prs->flags[i] == '0')
				return (1);
			i++;
		}
	}
	return (0);
}

int		is_flag_minus(t_prs *prs)
{
	int		i;

	i = 0;
	if (prs->flags == 0)
		return (0);
	else
	{
		while (prs->flags[i] != '\0')
		{
			if (prs->flags[i] == '-')
				return (1);
			i++;
		}
	}
	return (0);
}

int		is_flag_space(t_prs *prs)
{
	int		i;

	i = 0;
	if (prs->flags == 0)
		return (0);
	else
	{
		while (prs->flags[i] != '\0')
		{
			if (prs->flags[i] == 32)
				return (1);
			i++;
		}
	}
	return (0);
}

int		is_flag_hach(t_prs *prs)
{
	int		i;

	i = 0;
	if (prs->flags == 0)
		return (0);
	else
	{
		while (prs->flags[i] != '\0')
		{
			if (prs->flags[i] == '#')
				return (1);
			i++;
		}
	}
	return (0);
}

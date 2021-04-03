/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_service_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:08:03 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:08:05 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** writes n zeroed bytes to the string str
** if n is zero bzero() does nothin
** IN: string str, bytes number n
** OUT: void
*/

void	ft_bzero(void *str, size_t n)
{
	unsigned long	i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char*)str;
	if (n != 0)
	{
		while (i < n)
		{
			ptr[i] = '\0';
			i++;
		}
	}
}

/*
** allocates and returns a “fresh” memory area
** memory allocated is initialized to 0
** if the allocation fails, the function returns NULL
** IN: size of the memory that needs to be allocated
** OUT: pointer to allocated memory area
*/

void	*ft_memalloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (res == 0)
		return (NULL);
	ft_bzero(res, size);
	return (res);
}

/*
** fried memmory with adress given by parameter
** IN: pointer's adress that needs its memory freed and set to NULL
** OUT: void
*/

void	ft_memdel(void **ap)
{
	if (ap != 0 && *ap != 0)
	{
		free(*ap);
		*ap = NULL;
	}
}

/*
** outputs the character c to the standard output
** IN: character to output
** OUT: void
*/

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/*
** outputs the string s to the standard output
** IN: string s to output
** OUT: void
*/

void	ft_putstr(char const *s)
{
	if (s != 0)
	{
		while (*s != '\0' && s != 0)
		{
			ft_putchar(*s);
			s++;
		}
	}
}

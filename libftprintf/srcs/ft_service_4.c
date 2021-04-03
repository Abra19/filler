/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_service_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:10:22 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:10:24 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** compare the null-terminated strings s1 and s2
** IN: string s1, s2
** OUT: int equal first difference *s1 - *s2 or 0
*/

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;

	i = 0;
	if (s1 == 0 && s2 == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
** fried memmory with adress given by parameter
** IN: string’s address that needs to be freed and its pointer set to NULL
** OUT: void
*/

void	ft_strdel(char **as)
{
	if (as != 0 && *as != 0)
	{
		free(*as);
		*as = NULL;
	}
}

/*
** allocates and returns a “fresh” string ending with ’\0’
** result of the concatenation of s1 and s2
** if the allocation fails the function returns NULL
** IN: strings s1 and s2
** OUT: The “fresh” string result of the concatenation of the 2 strings
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned long	size;
	char			*res;

	if ((s1 != 0) && (s2 != 0))
		size = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	else if (s1 != 0)
		size = ft_strlen((char*)s1);
	else if (s2 != 0)
		size = ft_strlen((char*)s2);
	else
		return (0);
	if ((size) == 9223372036854775807)
		return (NULL);
	if ((res = (char*)ft_memalloc(sizeof(char) * (size + 1))) == 0)
		return (NULL);
	res[size] = '\0';
	if (s1 != 0)
		res = ft_strcpy(res, (char*)s1);
	else
		res = ft_strcpy(res, (char*)s2);
	if (s1 != 0 && s2 != 0)
		res = ft_strcat(res, (char*)s2);
	return (res);
}

/*
** computes the length of the string str
** IN: string str
** OUT: lenght of string str without '\0'
*/

int		ft_strlen(const char *str)
{
	int				len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

/*
** compare n symbols of strings s1 and s2
** IN: string s1, s2, numbers of symbols n
** OUT: int equal first difference *s1 - *s2 or 0
*/

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long	i;

	i = 0;
	if (n == 0 || (s1 == 0 && s2 == 0))
		return (0);
	if (*s1 == '\0')
		return (-*s2);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	if (i == n)
		return ((unsigned char)s1[i - 1] - (unsigned char)s2[i - 1]);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

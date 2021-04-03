/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_service_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:11:51 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 20:11:52 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** allocates and returns a “fresh” substring from the string given as argument
** the substring begins at index = start and is of size len
** if start and len don’t refering to a valid substring - behavior is undef
** if the allocation fails, the function returns NULL
** IN: string s from which create the substring
** IN: start index of the first element of substring
** IN: size of the substring len
** OUT: substring
*/

char	*ft_strsub(char const *s, unsigned int start, int len)
{
	char			*res;
	int				i;

	i = 0;
	if (s == 0)
		return (NULL);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == 0)
		return (NULL);
	while (i < len)
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}

/*
** return 0 if c is not ASCII and 1 othrwise
** IN: int c
** OUT: true (1) or false (0)
*/

int		ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/*
** copy the string src to dst including '\0'
** src and dst should not overlap as the behavior is undefined
** IN: string src
** OUT: *dst
*/

char	*ft_strcpy(char *dst, const char *src)
{
	int		i;

	i = 0;
	if (src == 0 || dst == 0)
		return (NULL);
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*
** append a copy of s2 to the end of s1 then add '\0'
** s1 must have sufficient space to hold the result
** s1 and s2 should not overlap as the behavior is undefined
** IN: strings s1 and s2
** OUT: *s1
*/

char	*ft_strcat(char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == 0 && s2 == 0)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

/*
** locates the first occurrence of c in the string pointed by str
** if c is '\0' function locate the terminating '\0'e
** IN: string str, symbol c
** OUT: pointer to c or NULL if c does not appear in the string
*/

char	*ft_strchr(const char *str, int c)
{
	char	sym;

	if (str == 0)
		return (NULL);
	sym = (char)c;
	while (*str != '\0')
	{
		if (*str == sym)
			return ((char *)str);
		str++;
	}
	if (*str == sym)
		return ((char *)str);
	return (NULL);
}

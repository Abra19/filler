/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_man_col_fd_np.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:53:38 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 18:53:41 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function to manage colors of output
** don't work after %  and before specifier
*/

t_col	g_col[9] = {{"{eoc}", "\033[0m"},\
	{"{black}", "\033[30m"}, {"{red}", "\033[31m"},\
	{"{green}", "\033[32m"}, {"{yellow}", "\033[33m"},\
	{"{blue}", "\033[34m"}, {"{magenta}", "\033[35m"},\
	{"{cyan}", "\033[36m"}, {"{white}", "\033[37m"}};

void	set_color(t_ptf *pr)
{
	int		i;
	char	*cmp;
	int		flag;
	int		j;

	i = 0;
	flag = 0;
	j = 0;
	cmp = ft_strsub(pr->frt, pr->pos, ft_strlen(pr->frt) - pr->pos + 1);
	while (i < 9)
	{
		if (ft_strncmp((const char *)cmp, g_col[i].name,\
		ft_strlen(g_col[i].name)) == 0)
		{
			flag = 1;
			while (g_col[i].cntn[j] != '\0')
				pr->buff[pr->i++] = g_col[i].cntn[j++];
			pr->pos += ft_strlen(g_col[i].name) - 1;
		}
		i++;
	}
	ft_strdel(&cmp);
	if (flag == 0)
		pr->buff[pr->i++] = '{';
}

/*
** write in fd corresponding %w locate in any place of frt
*/

int		hand_fd(t_ptf *pr, t_prs *prs)
{
	if (ft_strcmp((const char*)prs->string, "w") == 0)
		prs->nbr = (int)va_arg(pr->ap, long long);
	else
		return (0);
	pr->fd = (int)prs->nbr;
	return (1);
}

/*
** write non-printable ascii character
*/

void	non_print_7_12(t_prs *prs)
{
	if (prs->wc == 7)
		prs->str = "\\a";
	else if (prs->wc == 8)
		prs->str = "\\b";
	else if (prs->wc == 9)
		prs->str = "\\t";
	else if (prs->wc == 10)
		prs->str = "\\n";
	else if (prs->wc == 11)
		prs->str = "\\v";
	else if (prs->wc == 12)
		prs->str = "\\f";
	else if (prs->wc == 13)
		prs->str = "\\r";
}

int		non_print_sym(t_prs *prs)
{
	char	*str;

	str = (char *)ft_memalloc(sizeof(char) * 2);
	str[1] = '\0';
	if (prs->wc == 0)
		prs->str = "\\0";
	else if (prs->wc >= 7 && prs->wc <= 13)
		non_print_7_12(prs);
	else if (prs->wc > 31 || prs->wc < 0)
	{
		print_error("specifier is invalid");
		ft_strdel(&str);
		return (0);
	}
	else if ((prs->wc > 0 && prs->wc <= 6) || (prs->wc > 13 && prs->wc <= 31))
	{
		prs->str = "ctrl + ";
		str[0] = prs->wc + 64;
		prs->str = ft_strjoin(prs->str, str);
	}
	ft_strdel(&str);
	return (1);
}

int		hand_non_print(t_ptf *pr, t_prs *prs)
{
	size_t	len;
	size_t	prc;

	if (ft_strcmp((const char*)prs->string, "r") == 0)
		prs->wc = (char)va_arg(pr->ap, long long);
	if (non_print_sym(prs) == 0)
	{
		ft_strdel(&prs->str);
		return (0);
	}
	prs->prc = ft_strlen(prs->str);
	prs->wsize = prs->prc;
	if (prs->str != 0)
	{
		prc = ft_strlen(prs->str);
		len = max_len(prs->width, prc);
		if (len != 0 && prs->flags != 0)
			flag_width_s(pr, prs, len, prc);
		else
			flag_null_s(pr, prs, len, prc);
	}
	return (1);
}

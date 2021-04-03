/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaure <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:50:23 by dlaure            #+#    #+#             */
/*   Updated: 2019/12/04 17:00:59 by dlaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** BUF_SIZE: initial size of buffer to print
** LEN: number of bytes in mantissa of long double
** MAXLEN: lenght of array for float defined by LDBLMAX
** BASE: base of long calc for keeping 4 decimal numbers
**
** struct s_byte and union u_ldbl for float, double, long double
**
** struct s_ptf for parsing format and write to buffer
** len: return value for ft_printf
** base:  number system base
** buff:	array for write in buff
** i:  position in buffer
** size: size of buffer, initially - BUF_SIZE
** fd: file descriptor - fd = 1 - stdout, fd > 2 - file
** ap: pointer to variadic arg
** frt: input str
** pos: position in frt
** sym_frac:  flag of case of first frac_part in case of e specifier
** n_args: number's of arg in string
** spec: array of specifier and * in order to appearance in frt
** prescpec: array of symbols anterior spec
** pow: power of 2 from 0 to 24 in string;
** flnbr: power of 2 from 0 to 16383 in int array - long calc
** fint: array for integer part of float long calc
** frac: long double for fractional part of float
** count: counter of non-zero character in fractial part in g case
** flag: flag for case of maked round
** flag_mod: don't need double round;
** lflag: long double flag
**
** struct s_prs of parameters affecting to print
** c_width: flag in case of negative value of width
** c_prc: flag in case of zero and negative value of precision
** no_prc:  flag in case of not marked precision
** cap_let: flag in case of cap_let
** flags: array of flags in format in order to appearence(+- 0#)
** letters: array for size flags (hh, h, ll, l, L)
** width: parameter of print - width
** prc: parameter of print - precision
** spec: array for reform one character = spec to str
** wc: character of type wchar_t (including char - wchar_t of size 1) for print
** wstr: string of wchar_t character to print
** str: str to print
** nbr: int of different size to print
** unbr: unsigned int of different size to print
** fnbr: long double of different size to print
** fint: array of int for integer part of double
** frac: array of int for fractional part of double
** wsize: size of arg to print
** string: str for spec and size flags
** sym: espace or 0 in dependence of flags combination
** first: first symbols for flags '+' ' ' '#'
** second:  second symbols for flag '#'
** third: for binary
** exp: value of exp for e,g
** s_parts: array for intpart of float
** k: index in array for intpart of float
** el: new value of exp in g case
** pk: new value of prc in g case
** sizef, num, lenf, new_exp - paramrters of case g
**
** struct s_col for manage colors
** name: name of colors
** cntn: script for execute
** g_mask: string of specifiers
** g_hand: array of function pointer
*/

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define BUF_SIZE		4096
# define POWSIZE		16384
# define LEN			64
# define MAXLEN			620
# define BASELEN		8
# define BASE			100000000

typedef struct			s_byte
{
	uint64_t			mant: 64;
	uint16_t			exp: 15;
	uint16_t			sign: 1;
}						t_byte;

typedef	union			u_ldbl
{
	long double			nbr;
	t_byte				field;
}						t_ldbl;

typedef struct			s_ptf
{
	size_t				len;
	uint8_t				base;
	char				*buff;
	size_t				i;
	size_t				size;
	int					fd;
	va_list				ap;
	const char			*frt;
	size_t				pos;
	int					sym_frac;
	size_t				n_args;
	char				*spec;
	char				*prespec;
	char				*pow[25];
	int					*flnbr[POWSIZE];
	int					*fint;
	int					*fround;
	long double			frac;
	int					count;
	int					flag;
	long long			dround;
	int					flag_mod;
	int					lflag;

}						t_ptf;

typedef struct			s_prs
{
	int					c_width;
	int					c_prc;
	int					no_prc;
	int					flag_prc;
	int					cap_let;
	char				*flags;
	char				*letters;
	long long			width;
	long long			prc;
	char				*spec;
	int					wc;
	wchar_t				*wstr;
	char				*str;
	long long			nbr;
	unsigned long long	unbr;
	long double			fnbr;
	int					wsize;
	char				*string;
	char				sym;
	char				first;
	char				second;
	char				third;
	int					exp;
	char				*s_parts;
	size_t				size;
	int					k;
	int					el;
	int					pk;
	int					sizef;
	int					num;
	int					len_f;
	int					new_exp;
	int					pr_pk;
	int					zero;
	int					nul_prc;
	int					n_mark;
	int					wild;
}						t_prs;

typedef struct			s_col
{
	char				*name;
	char				*cntn;
}						t_col;

extern char				g_mask[20];
extern int				(*g_hand[14])(t_ptf *pr, t_prs *prs);

uint64_t				abs_int(long long a);
long double				abs_int_f(long double fnbr);
void					add_l(int *x, int *y);
void					add_l_n(int *x, int n);
void					add_space(t_ptf *pr, t_prs *prs, int size, int n);
void					add_space_f(t_ptf *pr, t_prs *prs, int size, int n);
void					add_zero(t_ptf *pr, t_prs *prs);
void					align_left(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						align_left_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						align_left_fe(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						align_left_fg(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
void					align_left_ptr(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
void					align_left_str(t_ptf *pr, t_prs *prs, size_t prc);
void					align_left_u(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
void					align_left_u_2(t_ptf *pr, t_prs *prs);
void					align_left_u_16(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
void					align_right(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						align_right_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						align_right_fe(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						align_right_fg(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
void					align_right_ptr(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
void					align_right_str(t_ptf *pr, t_prs *prs, size_t prc);
void					align_right_u(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
void					align_right_u_2(t_ptf *pr, t_prs *prs);
void					align_right_u_16(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
void					analyze_params(t_ptf *pr, t_prs *prs, char *str);
void					analyze_round(t_ptf *pr, t_prs *prs, int k);
void					analyze_round_g(t_ptf *pr, t_prs *prs, int k);
void					buff_nbr(t_ptf *pr, t_prs *prs);
void					buff_e_case(t_ptf *pr, t_prs *prs, t_ldbl *dbl,\
							char *res);
int						buff_nbr_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl,\
							char *res);
int						buff_nbr_fe(t_ptf *pr, t_prs *prs, t_ldbl *dbl,\
							char *res);
int						buff_nbr_fg(t_ptf *pr, t_prs *prs, t_ldbl *dbl,\
							char *res);
void					buff_f_ne_zero(t_ptf *pr, t_prs *prs, char *res);
void					buff_str(t_ptf *pr, t_prs *prs, size_t prc);
void					buff_unbr(t_ptf *pr, t_prs *prs);
void					buff_unbr_2(t_ptf *pr, t_prs *prs);
void					buff_unbr_16(t_ptf *pr, t_prs *prs);
int						buff_wchar(t_ptf *pr, t_prs *prs);
int						buff_wstr(t_ptf *pr, t_prs *prs, size_t prc);
int						check_and_parse(t_ptf *pr, t_prs *prs);
int						check_prc(t_ptf *pr, t_prs *prs);
int						check_width(t_ptf *pr, t_prs *prs);
void					check_wild(t_ptf *pr, int *i, int *k);
void					clean_args(t_ptf *pr);
void					clean_pow(t_ptf *pr);
void					clean_str(t_prs *prs);
void					clean_up(t_ptf *pr);
int						compare(t_ptf *pr);
void					count_args(t_ptf *pr, int *i);
void					count_exp(t_ptf *pr, t_prs *prs);
int						count_frac(char *str, t_prs *prs);
int						count_frac_g(char *str, t_ptf *pr, t_prs *prs);
int						count_n(t_prs *prs);
void					count_pow(t_ptf *pr);
int						count_size(t_prs *prs, size_t prc);
int						count_zero(char *res);
int						count_zero_mn(char *res);
char					*create_da(t_ptf *pr, unsigned size);
int						*create_da_int(unsigned size);
void					digit_in_buff(t_ptf *pr, t_prs *prs);
void					digit_in_buff_g(t_ptf *pr, t_prs *prs);
void					div_long(int *x, int n);
void					env_in_buff(t_ptf *pr, t_prs *prs, char *res);
void					env_in_buff_mn(t_ptf *pr, t_prs *prs, char *res);
void					exp_frac(t_ptf *pr, t_prs *prs);
void					f_frac_part(t_ldbl *dbl, t_ptf *pr, char *str);
void					f_int_part(t_ldbl *dbl, t_ptf *pr, char *str);
void					fe_choice(t_ptf *pr, t_prs *prs, int *prc, int *exp);
void					fill_spec(t_ptf *pr, int *i, int *k);
void					first_align_gl(t_ptf *pr, t_prs *prs);
void					first_f_align(t_ptf *pr, t_prs *prs);
void					first_fl_align(t_ptf *pr, t_prs *prs, int len_f);
void					first_g_align(t_ptf *pr, t_prs *prs);
void					first_g_align_null(t_ptf *pr, t_prs *prs);
void					first_ne_zero(t_ptf *pr, t_prs *prs, t_ldbl *dbl,\
							char *res);
void					flag_abs_percent(t_ptf *pr, t_prs *prs);
void					flag_f_null(t_prs *prs, t_ldbl *dbl);
void					flag_first(t_prs *prs);
void					flag_first_f(t_prs *prs, t_ldbl *dbl);
void					flag_first_fg(t_prs *prs, t_ldbl *dbl);
int						flag_fnbr(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						flag_fnbr_e(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						flag_fnbr_g(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
void					flag_min_0(t_ptf *pr, size_t len, size_t prc);
void					flag_nbr(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						flag_null(t_ptf *pr, t_prs *prs);
int						flag_null_fnbr(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						flag_null_fnbr_e(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						flag_null_fnbr_g(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						flag_null_nbr(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						flag_null_ptr(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						flag_null_s(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						flag_null_unbr(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						flag_null_unbr_2(t_ptf *pr, t_prs *prs);
int						flag_null_unbr_16(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						flag_null_w(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
void					flag_percent(t_ptf *pr, t_prs *prs);
void					flag_ptr(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						flag_unbr(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
void					flag_unbr_2(t_ptf *pr, t_prs *prs);
void					flag_unbr_16(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						flag_width(t_ptf *pr, t_prs *prs, int j);
void					flag_width_s(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
void					flag_width_w(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
void					flag_zero(t_prs *prs);
void					flag_zero_f(t_prs *prs);
void					flag_zero_fg(t_prs *prs);
void					flag_zero_u(t_prs *prs);
void					float_align_r(t_ptf *pr, t_prs *prs, int size, int n);
char					*form_str_gl(char *res, t_ptf *pr, t_prs *prs);
char					*format_str(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
void					format_str_e(t_ptf *pr, t_prs *prs);
void					format_str_g(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
long long				ft_atol(const char *str);
void					ft_bzero(void *str, size_t n);
int						ft_check_flags(t_ptf *pr, t_prs *prs);
int						ft_check_letters(t_ptf *pr, t_prs *prs);
void					ft_copy(char *to, char *from, unsigned size);
void					ft_copycut(char *to, char *from, unsigned start,\
							unsigned size);
int						ft_isdigit(int c);
int						ft_isdigit_0(int c);
char					*ft_itoa_mant(t_ldbl *dbl);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
int						ft_nbrlen(long long nbr, uint8_t base);
int						ft_printf(char const *str, ...);
int						ft_printf_all(t_ptf *pr);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
int						ft_specifier(t_ptf *pr, t_prs *prs);
char					*ft_strcat(char *s1, char *s2);
char					*ft_strchr(const char *str, int c);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strcpy(char *dst, const char *src);
void					ft_strdel(char **as);
char					*ft_strjoin(char const *s1, char const *s2);
int						ft_strlen(const char *str);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strsub(char const *s, unsigned int start, int len);
char					*ft_uitoa_base(uint8_t base, long long nbr);
char					*ft_itoa_base(uint8_t base, unsigned long long unbr,\
							char *mask);
char					*ft_uitoa_frac_prc(uint8_t base, long double frac,\
							int prc);
int						ft_unbrlen (unsigned long long nbr, uint8_t base);
size_t					ft_wstrlen(wchar_t *wstr);
int						hand_base_8(t_ptf *pr, t_prs *prs);
int						hand_base_10(t_ptf *pr, t_prs *prs);
int						hand_base_16(t_ptf *pr, t_prs *prs);
int						hand_binary(t_ptf *pr, t_prs *prs);
int						hand_fd(t_ptf *pr, t_prs *prs);
int						hand_fexp(t_ptf *pr, t_prs *prs);
int						hand_float(t_ptf *pr, t_prs *prs);
int						hand_f_g(t_ptf *pr, t_prs *prs);
int						hand_integer(t_ptf *pr, t_prs *prs);
int						hand_non_print(t_ptf *pr, t_prs *prs);
int						hand_percent(t_ptf *pr);
int						hand_ptr(t_ptf *pr, t_prs *prs);
int						hand_string(t_ptf *pr, t_prs *prs);
int						hand_wstring(t_ptf *pr, t_prs *prs);
int						hand_wchar(t_ptf *pr, t_prs *prs);
void					inf_abs_first(t_ptf *pr, t_prs *prs, int n);
void					inf_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
void					inf_first(t_ptf *pr, t_prs *prs, int n);
void					int_part_u(t_ptf *pr, t_prs *prs);
int						is_flag_hach(t_prs *prs);
int						is_flag_minus(t_prs *prs);
int						is_flag_plus(t_prs *prs);
int						is_flag_space(t_prs *prs);
int						is_flag_zero(t_prs *prs);
int						is_spec(char c);
int						last_null(int i, char *str);
size_t					long_sym(size_t a, size_t b, size_t c);
char					*left_res(t_ptf *pr, t_prs *prs, t_ldbl *dbl,\
							int *size);
char					*make_str(t_ptf *pr, t_prs *prs);
char					*make_str_g(t_ptf *pr, t_prs *prs);
int						map1(char *str);
int						map2(char *str);
int						map3(char *str);
int						map4(char *str);
int						mapping(t_ptf *pr, t_prs *prs);
size_t					max_len(size_t a, size_t b);
int						move_prc(t_ptf *pr, t_prs *prs);
void					mult_l(int *res, int *x, int n);
int						n_round(t_ptf *pr, t_ldbl *dbl);
int						n_round_fg(t_ptf *pr, t_ldbl *dbl);
void					nan_f(t_ptf *pr, t_prs *prs);
void					new_round_g(t_ptf *pr, t_prs *prs, char *res);
void					non_print_7_12(t_prs *prs);
int						non_print_sym(t_prs *prs);
void					parce_format(t_ptf *pr);
void					prefix(t_prs *prs);
void					prefix_2(t_prs *prs);
void					prepare_f(t_ptf *pr);
int						prc_digit(t_ptf *pr, size_t *len, t_prs *prs);
int						prc_wild (t_ptf *pr, t_prs *prs);
void					print_case_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
void					print_case_g(t_ptf *pr, t_prs *prs, t_ldbl *dbl,\
							char *str);
void					print_case_gl(t_ptf *pr, t_prs *prs, t_ldbl *dbl,\
							char *str);
int						print_error(char *str);
int						print_in_buff(t_ptf *pr, size_t len);
void					print_null_prc(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
void					print_null_prc_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
void					print_null_prc_fg(t_ptf *pr, t_prs *prs);
void					process_binary(t_ldbl *dbl, t_ptf *pr, t_prs *prs);
int						process_fnegative(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						process_fnegative_e(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						process_fnegative_g(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
void					process_negative(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						process_params_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
void					process_params_g(t_prs *prs, t_ldbl *dbl);
char					*process_str(t_ptf *pr, t_prs *prs, char *res);
char					*process_str_e(t_ptf *pr, t_prs *prs, char *res);
void					process_str_fe(t_ptf *pr, t_prs *prs, t_ldbl *dbl,\
							char *res);
void					process_zero_g(t_ptf *pr, t_prs *prs, char *str);
void					process_zero_u_16(t_ptf *pr, t_prs *prs);
void					process_zero_uvalue(t_ptf *pr, t_prs *prs);
void					process_zero_value(t_ptf *pr, t_prs *prs);
void					prs_sym(t_prs *prs);
int						read_float(t_ptf *pr, t_prs *prs);
int						read_float_e(t_ptf *pr, t_prs *prs);
int						read_float_g(t_ptf *pr, t_prs *prs);
int						read_format(t_ptf *pr);
int						read_integer(t_ptf *pr, t_prs *prs);
int						read_integer_8(t_ptf *pr, t_prs *prs);
int						read_integer_10(t_ptf *pr, t_prs *prs);
int						read_integer_16_x_cap(t_ptf *pr, t_prs *prs);
int						read_integer_16_x(t_ptf *pr, t_prs *prs);
int						read_long(char *str, int *x);
void					read_long_all(t_ptf *pr);
void					read_prc(char *res, t_ptf *pr, size_t *len, t_prs *prs);
int						read_string(t_ptf *pr, t_prs *prs);
int						read_wchar(t_ptf *pr, t_prs *prs);
int						read_wstring(t_ptf *pr, t_prs *prs);
int						resize_da(t_ptf *pr);
void					right_f_init(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						round_long(t_ptf *pr, t_prs *prs, int k);
int						round_long_f(t_ptf *pr, char *res, int k, t_ldbl *dbl);
int						round_long_ff(t_ptf *pr, char *res, int k);
int						round_long_fg(t_ptf *pr, char *res, int k);
int						round_long_fg_f(t_ptf *pr, char *res, int k,\
							t_ldbl *dbl);
void					rounder_g(t_ptf *pr, t_ldbl *dbl);
void					set_color(t_ptf *pr);
int						size_wchar(t_prs *prs);
void					space_ptr(int size, t_ptf *pr, t_prs *prs);
void					space_unbr16(int size, t_ptf *pr, t_prs *prs);
void					sym_space(t_ptf *pr, t_prs *prs, int size);
void					sym_zero(t_ptf *pr, t_prs *prs, int size);
char					*union_parts(t_ptf *pr, t_prs *prs);
char					*union_parts_f(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
char					*union_parts_fg(t_ptf *pr, t_prs *prs, t_ldbl *dbl);
int						width_digit(t_ptf *pr, size_t *len, t_prs *prs);
int						width_star (t_ptf *pr, t_prs *prs);
void					without_flag_0(t_ptf *pr, size_t len, size_t prc);
int						width_parce_dollar(t_ptf *pr);
int						width_star_invalid(t_ptf *pr, t_prs *prs,\
							int *i);
int						width_non_zero_s(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
int						width_non_zero_wc(t_ptf *pr, t_prs *prs);
int						width_non_zero_ws(t_ptf *pr, t_prs *prs, size_t len,\
							size_t prc);
void					write_blank(t_ptf *pr, size_t len);
void					write_buff(t_ptf *pr);
void					write_buff_null(t_ptf *pr, size_t prc);
void					write_frac_part_int(t_ptf *pr, t_prs *prs,\
							char *res, int j);
void					write_frac_parts(t_ptf *pr, t_prs *prs, char *res);
void					write_frac_parts_me(t_ptf *pr, t_prs *prs, char *res);
void					write_inf(t_ptf *pr, int n);
void					write_int_parts(t_ptf *pr, t_prs *prs, char *res);
void					write_int_parts_me(t_ptf *pr, t_prs *prs, char *res);
void					write_inttoa_f(t_ptf *pr, char *res, int k);
void					write_nan(t_ptf *pr, int n);
void					write_null(t_ptf *pr, t_prs *prs);
void					write_res(t_ptf *pr, char *res, int *i, int *m);
void					zero_abs(t_ptf *pr, t_prs *prs);
void					zero_abs_f(t_ptf *pr, t_prs *prs);
void					zero_abs_first(t_ptf *pr, t_prs *prs);
void					zero_abs_first_e(t_ptf *pr, t_prs *prs);
void					zero_ptr(int size, t_ptf *pr, t_prs *prs);
void					zero_right(t_ptf *pr, t_prs *prs);
void					zero_right_e(t_ptf *pr, t_prs *prs);
void					zero_unbr16(int size, t_ptf *pr, t_prs *prs);
void					flag_inf(t_prs *prs, t_ldbl *dbl);

#endif

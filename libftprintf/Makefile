#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlaure <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/04 21:46:33 by dlaure            #+#    #+#              #
#    Updated: 2019/12/04 22:16:06 by dlaure           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a
CC = gcc
FLAGS = -Wall -Werror -Wextra
INCLUDE = -I$(HEADDIR)

HEADLST = ft_printf.h
HEADDIR = ./includes/
HEADERS = $(addprefix $(HEADDIR), $(HEADLST))

SRCDIR	= ./srcs/
SRCLST	= ft_printf.c ft_check_parce.c ft_check_precision.c ft_check_width.c\
	ft_clean.c ft_d_array.c ft_itoa_base.c ft_long_calc.c\
	ft_man_col_fd_np.c ft_map.c ft_mapping.c ft_read_format.c\
	ft_prepare_float.c ft_process_flags.c ft_service_1.c\
	ft_service_2.c ft_service_3.c ft_service_4.c ft_service_5.c\
	ft_service_flag.c ft_sizeof.c ft_write_binary.c ft_write_binary_2.c\
	ft_write_fexp_1.c ft_write_fexp_2.c ft_write_fexp.c ft_write_fexp_3.c\
	ft_write_fg_2.c ft_write_fg_3.c ft_write_fg.c ft_write_float_2.c\
	ft_write_float_3.c ft_write_float_4.c ft_write_float_5.c\
	ft_write_float.c ft_write_null.c ft_write_nbr_base8.c\
	ft_write_nbr_base10.c ft_write_nbr_base16.c ft_write_nbr.c\
	ft_write_ptr.c 	ft_write_str.c ft_write_nbr_2.c ft_write_nbr_base16_2.c\
	ft_write_wchar.c ft_write_wstr.c ft_write_percent.c ft_write_unbr.c\
	ft_write_fg_4.c ft_print_in_buff.c ft_write_nbr_3.c ft_write_nbr_base16_3.c\
	ft_write_ptr_2.c ft_write_str_2.c ft_write_wchar_2.c ft_write_wstr_2.c\
	ft_write_fexp_4.c ft_write_inf_nan.c ft_write_inf_nan_2.c\
	ft_write_float_6.c ft_write_fg_5.c ft_write_fg_6.c ft_write_fg_7.c\
	ft_write_fg_8.c ft_write_fg_9.c ft_write_fg_10.c ft_check_width_1.c\
	ft_write_fg_11.c ft_write_fg_12.c ft_write_float_7.c ft_write_float_8.c
SRC = $(addprefix $(SRCDIR), $(SRCLST))

OBJDIR = obj/
OBJLST = $(patsubst %.c, %.o, $(SRCLST))
OBJECTS	= $(addprefix $(OBJDIR), $(OBJLST))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "libftprintf created"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

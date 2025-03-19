# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mumajeed <mumajeed@student.42barcelona>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/03/19 12:00:00 by mumajeed          #+#    #+#             #
#    Updated: 2025/03/19 12:00:00 by mumajeed         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

# Nombre de los ejecutables
NAME_CLIENT = client
NAME_SERVER = server

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directorios de librerías externas
LIBFT_DIR = ./libft
PRINTF_DIR = ./ft_printf

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRCS_CLIENT = client.c utils.c
SRCS_SERVER = server.c utils.c
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

INCLUDES = -I. -I$(LIBFT_DIR) -I$(PRINTF_DIR)
LIBS = -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(LIBFT) $(PRINTF) $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	@$(MAKE) -C $(PRINTF_DIR)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBS) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBS) -o $(NAME_SERVER)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re


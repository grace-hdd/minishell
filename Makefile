# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grhaddad <grhaddad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/16 16:01:55 by grhaddad          #+#    #+#              #
#    Updated: 2026/07/16 16:01:55 by grhaddad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC		= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes -I libft

LIBFT_DIR	= includes/libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_DIR		= src
SRCS		= $(SRC_DIR)/main.c \
			$(SRC_DIR)/lexer/tokenize.c \
			$(SRC_DIR)/lexer/token_type.c \
			$(SRC_DIR)/lexer/token_create.c \
			$(SRC_DIR)/lexer/token_list.c \
			$(SRC_DIR)/lexer/handle_quotes.c \
			$(SRC_DIR)/lexer/tokenize_utils.c \
			$(SRC_DIR)/parser/parse.c \
			$(SRC_DIR)/parser/parse_cmd.c \
			$(SRC_DIR)/parser/parse_redir.c \
			$(SRC_DIR)/parser/parse_utils.c \
			$(SRC_DIR)/expand/expand.c \
			$(SRC_DIR)/expand/expand_var.c \
			$(SRC_DIR)/expand/expand_utils.c \
			$(SRC_DIR)/error/error.c

OBJS		= $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

%.o:		%.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		$(MAKE) -C $(LIBFT_DIR) clean
		rm -f $(OBJS)

fclean:		clean
		$(MAKE) -C $(LIBFT_DIR) fclean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
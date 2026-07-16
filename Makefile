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
			$(SRC_DIR)/lexer/ft_tokenize.c \
			$(SRC_DIR)/lexer/ft_token_type.c \
			$(SRC_DIR)/lexer/ft_token_create.c \
			$(SRC_DIR)/lexer/ft_token_list.c \
			$(SRC_DIR)/lexer/ft_handle_quotes.c \
			$(SRC_DIR)/lexer/ft_tokenize_utils.c \
			$(SRC_DIR)/parser/ft_parse.c \
			$(SRC_DIR)/parser/ft_parse_cmd.c \
			$(SRC_DIR)/parser/ft_parse_redir.c \
			$(SRC_DIR)/parser/ft_parse_utils.c \
			$(SRC_DIR)/expand/ft_expand.c \
			$(SRC_DIR)/expand/ft_expand_var.c \
			$(SRC_DIR)/expand/ft_expand_utils.c

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
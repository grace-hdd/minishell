# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grhaddad <grhaddad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/23 10:54:46 by grhaddad          #+#    #+#              #
#    Updated: 2026/07/23 10:54:46 by grhaddad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I includes -I libft

LIBFT_DIR   = includes/libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRC_DIR     = src
SRC_SUBDIRS := lexer parser expand error builtIn signals
OBJ_DIR     = obj

SRCS        = main.c \
			$(foreach dir,$(SRC_SUBDIRS),$(wildcard $(SRC_DIR)/$(dir)/*.c))

OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all:        $(NAME)

$(NAME):    $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean:     clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re:         fclean all

.PHONY:     all clean fclean re
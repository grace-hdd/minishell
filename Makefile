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
OBJ_DIR     = obj

SRCS        = main.c \
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

# Map each .c file path to an equivalent path inside OBJ_DIR
OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all:        $(NAME)

$(NAME):    $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Creates the target's parent directory automatically before compiling
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
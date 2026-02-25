.RECIPEPREFIX := >

NAME        := minishell

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iincludes -Iincludes/libft

SRCDIR      := src
OBJDIR      := obj
LIBFT_DIR   := includes/libft
LIBFT_A     := $(LIBFT_DIR)/libft.a

SRCS        := $(shell find $(SRCDIR) -type f -name "*.c")
OBJS        := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

RM          := rm -f
RMDIR       := rm -rf
MKDIR       := mkdir -p

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
>$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -lreadline -o $(NAME)

$(LIBFT_A):
>$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
>@$(MKDIR) $(dir $@)
>$(CC) $(CFLAGS) -c $< -o $@

clean:
>$(RMDIR) $(OBJDIR)
>$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
>$(RM) $(NAME)
>$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
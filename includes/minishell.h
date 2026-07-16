/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:05:16 by grhaddad          #+#    #+#             */
/*   Updated: 2026/02/21 00:05:16 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

/* TOKEN TYPES */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF,
}	t_token_type;

/* TOKEN */
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/* REDIRECTION */
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

/* COMMAND */
typedef struct s_cmd
{
	char			**args;
	t_redir			**redirs;
	struct s_cmd	*next;
}	t_cmd;

/* SHELL STATE */
typedef struct s_shell
{
	t_cmd	*cmds;
	char	**env;
	int		last_status;
}	t_shell;

/* LEXER */
t_token	*ft_tokenize(char *input);
t_token	*ft_new_token(t_token_type type, char *value);
void	ft_token_add_back(t_token **head, t_token *current);
void	ft_free_tokens(t_token *head);
int		ft_is_stop_char(char c);
t_token	*ft_get_operator_token(char *input, int *i);
t_token	*ft_get_quoted_token(char *input, int *i);
t_token	*ft_get_word_token(char *input, int *i);

/* PARSER */
t_cmd	*ft_parse_cmd(t_token **tokens);
int		ft_parse_redir(t_cmd *cmd, t_token **tokens);
int		ft_is_redir(t_token_type type);
void	ft_args_add_back(t_cmd *cmd, char *value);
t_cmd	*ft_parse(t_token *tokens);

/* EXPAND */
void	ft_expand(t_cmd *cmds, t_shell *shell);
char	*ft_expand_str(char *str, t_shell *shell);
char	*ft_get_var_value(char *name, t_shell *shell);
char	*ft_get_var_name(char *str, int *i);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_char_to_str(char c);

#endif
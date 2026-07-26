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
# include <stdbool.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

extern int	g_signal;

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
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/* SHELL STATE */
typedef struct s_shell
{
	t_cmd	*cmds;
	char	**env;
	int		last_status;
}	t_shell;

/* EXPAND */
typedef struct s_expand
{
	char	*str;
	int		*i;
	char	quote;
	t_shell	*shell;
}	t_expand;

/* LEXER */
t_token	*ft_tokenize(char *input);
t_token	*ft_new_token(t_token_type type, char *value);
void	ft_token_add_back(t_token **head, t_token *current);
void	ft_free_tokens(t_token *head);
int		ft_is_stop_char(char c);
t_token	*ft_get_operator_token(char *input, int *i);
t_token	*ft_get_quoted_token(char *input, int *i);
t_token	*ft_get_word_token(char *input, int *i);
int		ft_skip_quoted_sequence(char *input, int *i);

/* PARSER */
t_cmd	*ft_parse_cmd(t_token **tokens);
int		ft_parse_redir(t_cmd *cmd, t_token **tokens);
int		ft_is_redir(t_token_type type);
int		ft_args_add_back(t_cmd *cmd, char *value);
void	ft_cmd_add_back(t_cmd **head, t_cmd *cmd);
void	ft_free_args(char **args);
void	ft_free_redirs(t_redir *redir);
void	ft_free_cmds(t_cmd *head);
t_cmd	*ft_parse(t_token *tokens);

/* EXPAND */
void	ft_expand(t_cmd *cmds, t_shell *shell);
char	*ft_expand_str(char *str, t_shell *shell);
char	*ft_get_var_value(char *name, t_shell *shell);
char	*ft_get_var_name(char *str, int *i);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_char_to_str(char c);

/* ERROR */
int		ft_error_msg(const char *msg);
int		ft_syntax_error(const char *token);
int		ft_unclosed_quote_error(void);

/* BUILTIN */
int		pwd_cmd(t_shell *shell);
int		echo(t_shell *shell, t_cmd *cmd);
int		cd_cmd(t_shell *shell, t_cmd *cmd);
int		set_env_val(t_shell *shell, const char *key, const char *value);
char	*get_env_val(t_shell *shell, const char *key);
int		env_cmd(t_shell *shell, t_cmd *cmd);

#endif
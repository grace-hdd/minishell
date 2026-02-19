/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:31:44 by marvin            #+#    #+#             */
/*   Updated: 2026/02/19 16:31:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

/* TOKEN TYPES */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKE_APPEND,
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
	char			*filename;
	struct s_redir	*next;
}	t_redir;

/* COMMAND */
typedef struct s_cmd
{
	char	**args;
	t_redit **redirs;
	struct s_cmd *next;
} t_cmd;

/* SHELL STATE */
typedef struct s_shell
{
	t_cmd *cmds;
	char **env;
	int last_status;
}	t_shell;

#endif
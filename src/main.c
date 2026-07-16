/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:01:13 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/17 00:27:54 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*ft_token_name(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_REDIR_IN)
		return ("<");
	if (type == TOKEN_REDIR_OUT)
		return (">");
	if (type == TOKEN_HEREDOC)
		return ("<<");
	if (type == TOKEN_APPEND)
		return (">>");
	return ("EOF");
}

static void	ft_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("[TOKEN] %-4s : %s\n",
			ft_token_name(tokens->type), tokens->value);
		tokens = tokens->next;
	}
}

static void	ft_print_cmds(t_cmd *cmds)
{
	int		i;
	int		j;
	t_redir	*r;

	i = 0;
	while (cmds)
	{
		printf("[CMD %d]\n", i++);
		j = 0;
		while (cmds->args && cmds->args[j])
		{
			printf("  arg[%d] = %s\n", j, cmds->args[j]);
			j++;
		}
		r = cmds->redirs;
		while (r)
		{
			printf("  redir %s -> %s\n", ft_token_name(r->type), r->file);
			r = r->next;
		}
		cmds = cmds->next;
	}
}

static int	ft_process_input(char *input, t_shell *shell)
{
	t_token	*tokens;

	if (!input || !*input)
		return (0);
	tokens = ft_tokenize(input);
	if (!tokens)
		return (2);
	ft_print_tokens(tokens);
	shell->cmds = ft_parse(tokens);
	ft_free_tokens(tokens);
	if (!shell->cmds)
		return (2);
	ft_expand(shell->cmds, shell);
	ft_print_cmds(shell->cmds);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*input;

	(void)argc;
	(void)argv;
	shell.env = env;
	shell.last_status = 0;
	shell.cmds = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*input)
			add_history(input);
		shell.last_status = ft_process_input(input, &shell);
		ft_free_cmds(shell.cmds);
		shell.cmds = NULL;
		free(input);
	}
	return (shell.last_status);
}

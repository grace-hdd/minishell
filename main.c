/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 19:21:50 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/30 14:44:54 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static int	ft_process_input(char *input, t_shell *shell)
{
	t_token	*tokens;

	if (!input || !*input)
		return (shell->last_status);
	if (ft_strcmp(input, "clear") == 0)
	{
		write(STDOUT_FILENO, "\033[H\033[2J", 7);
		return (0);
	}
	if (ft_validate_quotes(input))
		return (2);
	tokens = ft_tokenize(input);
	if (!tokens)
		return (2);
	if (ft_validate_syntax(tokens))
	{
		ft_free_tokens(tokens);
		return (2);
	}
	shell->cmds = ft_parse(tokens);
	ft_free_tokens(tokens);
	if (!shell->cmds)
		return (2);
	ft_expand(shell->cmds, shell);
	return (0);
}

static int	ft_shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		setup_signals();
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (*input)
			add_history(input);
		shell->last_status = ft_process_input(input, shell);
		ft_free_cmds(shell->cmds);
		shell->cmds = NULL;
		free(input);
	}
	return (shell->last_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_environment(&shell, envp);
	if (!shell.env)
		return (ft_error_msg("allocation failure"));
	shell.last_status = 0;
	shell.cmds = NULL;
	setup_signals();
	shell.last_status = ft_shell_loop(&shell);
	free_environment(&shell);
	return (shell.last_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:01:13 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/16 16:05:03 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_shell(t_shell *shell, char **env)
{
	shell->env = env;
	shell->last_status = 0;
	shell->cmds = NULL;
}

static int	ft_process_input(char *input, t_shell *shell)
{
	t_token	*tokens;

	tokens = ft_tokenize(input);
	if (!tokens)
		return (1);
	shell->cmds = ft_parse(tokens);
	ft_free_tokens(tokens);
	if (!shell->cmds)
		return (1);
	ft_expand(shell->cmds, shell);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*input;

	(void)argc;
	(void)argv;
	ft_init_shell(&shell, env);
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
		if (!ft_process_input(input, &shell))
			shell.last_status = 0;
		ft_free_cmds(shell.cmds);
		shell.cmds = NULL;
		free(input);
	}
	return (shell.last_status);
}

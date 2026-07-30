/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:07:03 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/27 01:07:03 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_cmd(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (!shell || !shell->env)
		return (0);
	if (cmd->args[1])
	{
		write(STDERR_FILENO, "minishell: env: too many arguments\n", 35);
		shell->last_status = 1;
		return (1);
	}
	i = 0;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
		{
			write(STDOUT_FILENO, shell->env[i], ft_strlen(shell->env[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	shell->last_status = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 19:04:07 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/27 19:04:07 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_str(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	numeric_error_exit(t_shell *shell, const char *arg)
{
	(void)shell;
	write(STDERR_FILENO, "minishell: exit: ", 17);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	exit(2);
}

int	exit_cmd(t_shell *shell, t_cmd *cmd)
{
	unsigned char	exit_code;

	write(STDERR_FILENO, "exit\n", 5);
	if (!cmd->args[1])
	{
		exit_code = (unsigned char)shell->last_status;
		exit(exit_code);
	}
	if (!is_numeric_str(cmd->args[1]))
		numeric_error_exit(shell, cmd->args[1]);
	if (cmd->args[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
		shell->last_status = 1;
		return (1);
	}
	exit_code = (unsigned char)ft_atoi(cmd->args[1]);
	exit(exit_code);
	return (0);
}

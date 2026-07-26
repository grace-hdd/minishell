/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 02:03:42 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/27 02:03:42 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if the string up to '=' is a valid Bash identifier.
 */
static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Prints error message for invalid export identifiers.
 */
static int	export_error(t_shell *shell, const char *arg)
{
	write(STDERR_FILENO, "minishell: export: `", 20);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	shell->last_status = 1;
	return (1);
}

/**
 * Parses and processes a single argument for export.
 */
static int	process_export_arg(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;
	int		status;

	if (!is_valid_identifier(arg))
		return (export_error(shell, arg));
	eq = ft_strchr(arg, '=');
	if (!eq)
		return (0);
	key = ft_substr(arg, 0, eq - arg);
	if (!key)
		return (1);
	status = set_env_val(shell, key, eq + 1);
	free(key);
	return (status);
}

/**
 * Executes the export builtin command.
 */
int	export_cmd(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	err;

	if (!shell || !cmd)
		return (1);
	if (!cmd->args[1])
		return (print_sorted_export(shell));
	i = 1;
	err = 0;
	while (cmd->args[i])
	{
		if (process_export_arg(shell, cmd->args[i]) != 0)
			err = 1;
		i++;
	}
	if (!err)
		shell->last_status = 0;
	return (err);
}

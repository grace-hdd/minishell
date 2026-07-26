/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:01:27 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/27 01:59:01 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handles error printing and status code updates for cd
static int	cd_error(t_shell *shell, const char *msg, const char *arg)
{
	if (arg)
		fprintf(stderr, "minishell: cd: %s: %s\n", arg, msg);
	else
		fprintf(stderr, "minishell: cd: %s\n", msg);
	shell->last_status = 1;
	return (1);
}

// Handles system call error printing when chdir fails
static int	cd_perror(t_shell *shell, const char *path)
{
	fprintf(stderr, "minishell: cd: ");
	perror(path);
	shell->last_status = 1;
	return (1);
}

/**
 * Executes the cd buitlin command
 * Step 1: Validate argument count (accept only 1 arg)
 * Step 2: Retrieve current PWD to update OLDPWD later
 * Step 3: Call chdir()
 * Step 4: On succes, update OLDPWD and new PWD in the environment
 * Step 5: Update shell->last-status and return exit status
*/
int	cd_cmd(t_shell *shell, t_cmd *cmd)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	if (!cmd->args[1])
		return (cd_error(shell, "relative or absolute path required", NULL));
	if (cmd->args[2])
		return (cd_error(shell, "too many arguments", NULL));
	old_pwd = get_env_val(shell, "PWD");
	if (!old_pwd && getcwd(cwd, sizeof(cwd)))
		old_pwd = cwd;
	if (chdir(cmd->args[1]) != 0)
		return (cd_perror(shell, cmd->args[1]));
	if (old_pwd)
		set_env_val(shell, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_val(shell, "PWD", cwd);
	shell->last_status = 0;
	return (0);
}

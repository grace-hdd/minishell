/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:01:22 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/30 14:47:52 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_cmd(t_shell *shell)
{
	char	*cwd;
	char	*env_pwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(cwd);
		return (0);
	}
	env_pwd = ft_get_var_value("PWD", shell);
	if (env_pwd && *env_pwd)
	{
		ft_putstr_fd(env_pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(env_pwd);
		return (0);
	}
	if (env_pwd)
		free(env_pwd);
	ft_putendl_fd("minishell: pwd: error retrieving current directory",
		STDERR_FILENO);
	return (1);
}

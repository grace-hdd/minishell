/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:01:22 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/23 16:08:33 by grhaddad         ###   ########.fr       */
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
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	env_pwd = ft_get_var_value("PWD", shell);
	if (env_pwd && *env_pwd)
	{
		printf("%s\n", env_pwd);
		free(env_pwd);
		return (0);
	}
	if (env_pwd)
		free(env_pwd);
	ft_putendl_fd("minishell: pwd: error retrieving current directory",
		STDERR_FILENO);
	return (1);
}

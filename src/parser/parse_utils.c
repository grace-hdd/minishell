/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 21:09:37 by grhaddad          #+#    #+#             */
/*   Updated: 2026/02/23 21:09:37 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redir(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND);
}

void	ft_args_add_back(t_cmd *cmd, char *value)
{
	int		len;
	char	**new;
	int		i;

	len = 0;
	i = 0;
	while (cmd->args != NULL && cmd->args[len] != NULL)
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (new == NULL)
		return ;
	while (i < len)
	{
		new[i] = cmd->args[i];
		i++;
	}
	new[len] = ft_strdup(value);
	new[len + 1] = NULL;
	free(cmd->args);
	cmd->args = new;
}

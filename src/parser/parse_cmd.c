/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 20:54:58 by grhaddad          #+#    #+#             */
/*   Updated: 2026/02/23 20:54:58 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_cmd(t_token **tokens)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	while (*tokens != NULL && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			ft_args_add_back(cmd, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
		else if (ft_is_redir((*tokens)->type))
			ft_parse_redir(cmd, tokens);
	}
	return (cmd);
}

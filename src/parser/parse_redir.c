/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:04:56 by grhaddad          #+#    #+#             */
/*   Updated: 2026/02/25 17:04:56 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_valid_redir_target(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == TOKEN_PIPE || ft_is_redir(tok->type))
		return (0);
	return (1);
}

static void	ft_redir_add_back(t_cmd *cmd, t_redir *new_node)
{
    t_redir	*last;

    if (!cmd->redirs)
    {
        cmd->redirs = new_node;
        return ;
    }
    last = cmd->redirs;
    while (last->next)
        last = last->next;
    last->next = new_node;
}

static int	ft_add_redir_node(t_cmd *cmd, int type, const char *target)
{
	t_redir	*new_node;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (1);
	new_node->type = type;
	new_node->file = ft_strdup(target);
	if (!new_node->file)
	{
		free(new_node);
		return (1);
	}
	ft_redir_add_back(cmd, new_node);
	return (0);
}

int	ft_parse_redir(t_cmd *cmd, t_token **tokens)
{
	int		redir_type;
	t_token	*target;

	if (!cmd || !tokens || !*tokens)
		return (1);
	while (*tokens && ft_is_redir((*tokens)->type))
	{
		redir_type = (*tokens)->type;
		*tokens = (*tokens)->next;
		target = *tokens;
		if (!ft_is_valid_redir_target(target))
			return (1);
		if (ft_add_redir_node(cmd, redir_type, target->value))
			return (1);
		*tokens = (*tokens)->next;
	}
	return (0);
}

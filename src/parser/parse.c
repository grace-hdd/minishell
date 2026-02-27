/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 20:44:39 by grhaddad          #+#    #+#             */
/*   Updated: 2026/02/23 20:44:39 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (head == NULL || *head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd	*ft_parse(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cmd;

	head = NULL;
	while (tokens != NULL)
	{
		cmd = ft_parse_cmd(&tokens);
		if (cmd == NULL)
		{
			ft_free_cmds(head);
			return (NULL);
		}
		ft_cmd_add_back(&head, cmd);
		if (tokens != NULL && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (head);
}

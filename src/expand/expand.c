/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:59:53 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/16 16:00:19 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_expand_redirs(t_redir *redir, t_shell *shell)
{
	char	*expanded;

	while (redir)
	{
		expanded = ft_expand_str(redir->file, shell);
		free(redir->file);
		redir->file = expanded;
		redir = redir->next;
	}
}

void	ft_expand(t_cmd *cmds, t_shell *shell)
{
	char	*expanded;
	int		i;

	while (cmds)
	{
		i = 0;
		if (cmds->args)
		{
			while (cmds->args[i])
			{
				expanded = ft_expand_str(cmds->args[i], shell);
				free(cmds->args[i]);
				cmds->args[i] = expanded;
				i++;
			}
		}
		ft_expand_redirs(cmds->redirs, shell);
		cmds = cmds->next;
	}
}

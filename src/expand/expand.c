/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:59:53 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/17 00:27:50 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_expand_redirs(t_redir *redir, t_shell *shell)
{
	char	*expanded;
	char	*old;

	while (redir)
	{
		if (redir->type != TOKEN_HEREDOC)
		{
			old = redir->file;
			expanded = ft_expand_str(redir->file, shell);
			if (expanded)
			{
				redir->file = expanded;
				free(old);
			}
		}
		redir = redir->next;
	}
}

void	ft_expand(t_cmd *cmds, t_shell *shell)
{
	char	*expanded;
	char	*old;
	int		i;

	while (cmds)
	{
		i = 0;
		while (cmds->args && cmds->args[i])
		{
			old = cmds->args[i];
			expanded = ft_expand_str(cmds->args[i], shell);
			if (expanded)
			{
				cmds->args[i] = expanded;
				free(old);
			}
			i++;
		}
		ft_expand_redirs(cmds->redirs, shell);
		cmds = cmds->next;
	}
}

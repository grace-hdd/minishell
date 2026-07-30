/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:20:42 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/30 16:20:42 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	ft_redir_add_back(t_cmd *cmd, t_redir *new_node)
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

char	*ft_create_heredoc_file(void)
{
	char	*path;
	char	template[27];
	int		fd;

	ft_strlcpy(template, "/tmp/minishell-heredoc-XXXXXX", sizeof(template));
	fd = mkstemp(template);
	if (fd < 0)
		return (NULL);
	close(fd);
	path = ft_strdup(template);
	if (!path)
		return (NULL);
	return (path);
}

int	ft_write_heredoc(const char *path, const char *delimiter)
{
	char	*line;
	int		fd;
	size_t	len;

	fd = open(path, O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		len = ft_strlen(delimiter);
		if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\0')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}

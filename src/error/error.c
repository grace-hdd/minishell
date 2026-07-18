/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 23:59:01 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/16 23:59:01 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_error_msg(const char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (msg)
		ft_putendl_fd((char *)msg, 2);
	else
		ft_putendl_fd("error", 2);
	return (1);
}

int	ft_syntax_error(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token && *token)
		ft_putstr_fd((char *)token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
	return (2);
}

int	ft_unclosed_quote_error(void)
{
	ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
	return (2);
}

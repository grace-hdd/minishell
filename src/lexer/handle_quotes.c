/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:58:24 by grhaddad          #+#    #+#             */
/*   Updated: 2026/02/22 20:58:24 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_get_quoted_token(char *input, int *i)
{
	int		start;
	char	*word;
	t_token	*tok;
	char	quote;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] != '\0' && input[*i] != quote)
		(*i)++;
	if (input[*i] == '\0')
		return (NULL);
	word = ft_substr(input, start, *i - start);
	(*i)++;
	if (!word)
		return (NULL);
	tok = ft_new_token(TOKEN_WORD, word);
	free(word);
	return (tok);
}

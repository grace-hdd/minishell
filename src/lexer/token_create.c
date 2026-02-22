/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:52:07 by grhaddad          #+#    #+#             */
/*   Updated: 2026/02/21 00:52:07 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

t_token	*ft_get_word_token(char *input, int *i)
{
	int		start;
	char	*word;
	t_token	*tok;

	start = *i;
	while (input[*i] != '\0' && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '\'' && input[*i] != '"' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
		(*i)++;
	word = ft_substr(input, start, *i - start);
	if (!word)
		return (NULL);
	tok = ft_new_token(TOKEN_WORD, word);
	free(word);
	return (tok);
}

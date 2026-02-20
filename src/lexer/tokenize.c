/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:15:16 by marvin            #+#    #+#             */
/*   Updated: 2026/02/19 18:15:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *ft_get_next_token(char *input, int *i)
{
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		return (ft_get_operator_token(input, i));
	if (input[*i] == '\'' || input[*i] == '\"')
		return (ft_get_quoted_token(input, i));
	return (ft_get_word_token(input, i));
}

t_token *ft_tokenize(char *input, char **env)
{
	t_token	*head;
	t_token	*tok;
	int		i;

	i = 0;
	head = NULL;
	while (input[i])
	{
		while (input[i] == 32 || input[i] == 9)
			i++;
		if (input[i] == '\0')
			break;
		tok = ft_get_next_token(input, &i);
		if (tok == NULL)
		{
			ft_free_tokens(head);
			return (NULL);
		}
		ft_token_add_back(&head, tok);
	}
	return (head);
}

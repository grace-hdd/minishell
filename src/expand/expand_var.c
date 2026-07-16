/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:00:25 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/16 16:00:29 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var_value(char *name, t_shell *shell)
{
	char	*value;

	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(shell->last_status));
	value = getenv(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*ft_expand_var(char *str, int *i, t_shell *shell)
{
	char	*name;
	char	*value;

	(*i)++;
	name = ft_get_var_name(str, i);
	if (!name)
		return (ft_strdup(""));
	value = ft_get_var_value(name, shell);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

char	*ft_expand_str(char *str, t_shell *shell)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_expand_var(str, &i, shell);
			result = ft_strjoin_free(result, tmp);
			free(tmp);
		}
		else
		{
			tmp = ft_char_to_str(str[i]);
			result = ft_strjoin_free(result, tmp);
			free(tmp);
			i++;
		}
	}
	return (result);
}

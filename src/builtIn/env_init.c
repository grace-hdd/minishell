/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 14:00:40 by grhaddad          #+#    #+#             */
/*   Updated: 2026/07/30 14:00:40 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Creates a new env node from a KEY=VALUE string.
 */
t_env	*new_env_node(char *env_str)
{
	t_env	*node;
	char	*eq_pos;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	eq_pos = ft_strchr(env_str, '=');
	if (eq_pos)
	{
		node->key = ft_substr(env_str, 0, eq_pos - env_str);
		node->value = ft_strdup(eq_pos + 1);
	}
	else
	{
		node->key = ft_strdup(env_str);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

/**
 * Updates or sets SHLVL and PWD on startup.
 */
static void	update_default_vars(t_shell *shell)
{
	char	*shlvl_val;
	int		lvl;
	char	*new_shlvl;
	char	cwd[1024];

	shlvl_val = get_env_value(shell->env, "SHLVL");
	if (!shlvl_val)
		lvl = 1;
	else
		lvl = ft_atoi(shlvl_val) + 1;
	if (lvl < 0)
		lvl = 0;
	new_shlvl = ft_itoa(lvl);
	set_env_value(&shell->env, "SHLVL", new_shlvl);
	free(new_shlvl);

	/* PWD Logic */
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value(&shell->env, "PWD", cwd);
}

/**
 * Main initialization entry point called in main.c
 */
void	init_environment(t_shell *shell, char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	shell->env = NULL;
	if (!envp || !*envp)
	{
		set_env_value(&shell->env, "SHLVL", "1");
		return ;
	}
	head = new_env_node(envp[0]);
	current = head;
	i = 1;
	while (envp[i])
	{
		current->next = new_env_node(envp[i]);
		current = current->next;
		i++;
	}
	shell->env = head;
	update_default_vars(shell);
}

char	**env_to_array(t_env *env)
{
	int		count;
	t_env	*tmp;
	char	**array;
	char	*str;
	int		i;

	count = 0;
	tmp = env;
	while (tmp && ++count)
		tmp = tmp->next;
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		str = ft_strjoin(tmp->key, "=");
		array[i] = ft_strjoin(str, tmp->value);
		free(str);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

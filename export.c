/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:12:58 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/18 00:32:04 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env && env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
				swap (&env[i], &env[j]);
			j++;
		}
		i++;
	}
}

void	export_print(char **export_env)
{
	int	i;

	sort_env(export_env);
	while (export_env && *export_env)
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while ((*export_env)[i])
		{
			if ((*export_env)[i] == '+' && (*export_env)[i + 1] == '=')
				i++;
			ft_putchar_fd((*export_env)[i], 1);
			if (i == get_equal(*export_env) && get_equal(*export_env))
				ft_putchar_fd('"', 1);
			i++;
		}
		if (get_equal(*export_env))
			ft_putchar_fd('"', 1);
		ft_putstr_fd("\n", 1);
		export_env++;
	}
	exit_status(0);
}

void	export_join(int flag, char *var, char **env)
{
	char	*s;

	if (!flag)
		s = ft_ft_strjoin(*env, var + get_equal(var) + 1);
	else
		s = ft_ft_strjoin(*env, var + get_equal(var));
	if (!s)
		return ;
	free(*env);
	*env = s;
}

int	check_size(char *var, char *env, int size)
{
	int	c;

	c = get_equal(env);
	if (c && env[c - 1] == '+')
		c--;
	if (size && var[size - 1] == '+' && var[size] == '=' && !get_equal(env))
		return (get_equal(var) - 1 == ft_strlen(env));
	else if (size && var[size - 1] == '+' && var[size] == '=' && get_equal(env))
		return (get_equal(var) - 1 == c);
	else if (get_equal(var) && !get_equal(env))
		return (get_equal(var) == ft_strlen(env));
	else if (get_equal(var) && get_equal(env))
		return (get_equal(var) == c);
	return (0);
}

int	check_if_var_exist(char *var, char *env, int size)
{
	if (!ft_strncmp(env, var, size) && cmp_size(env, var))
		return (1);
	return (0);
}

void	env_export_all_cases(char *var, char ***env, int size)
{
	int	i;
	int	len;
	int	flag;

	i = -1;
	flag = 0;
	len = get_equal(var);
	while (env && *env && (*env)[++i])
	{
		if (check_if_var_exist(var, (*env)[i], size) && !len)
			return ;
		else if (!ft_strncmp((*env)[i], var, size) && len)
		{
			if (!check_char((*env)[i], '='))
				flag = 1;
			if (check_size(var, (*env)[i], len))
			{
				if (var[len - 1] == '+' && var[len] == '=')
					export_join(flag, var, &(*env)[i]);
				else
				{
					free((*env)[i]);
					(*env)[i] = ft_ft_strdup(var);	
				}
				return ;
			}
		}
	}
	*env = ft_ft_array(*env, var);
}

void	exec_export(char **vars, char ***env, char ***ex_env)
{
	int	i;
	int	size;

	i = 0;
	if (!vars || !vars[0])
	{
		export_print(*ex_env);
		return ;
	}
	while (vars && vars[i])
	{
		size = get_best_size(vars[i]);
		if (!check_error(vars[i], 1))
		{
			print_error(vars[i++], 0);
			continue ;
		}
		if (!get_equal(vars[i]))
		{
			env_export_all_cases(vars[i++], ex_env, size);
			continue ;
		}
		env_export_all_cases(vars[i], ex_env, size);
		env_export_all_cases(vars[i++], env, size);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:31:15 by miguiji           #+#    #+#             */
/*   Updated: 2024/04/20 14:48:37 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(char *path, t_env *env, t_node **addresses)
{
	int		response;
	char	*cwd;
	char	*new_path;

	if (path == NULL || !ft_strncmp(path, "~", 1))
	{
		response = chdir(get_environment(env->env, "HOME="));
		return (response);
	}
	if (path[0] == '/')
	{
		response = chdir(path);
		return (response);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		new_path = ft_strjoin(cwd, "/", addresses);
		cwd = ft_strjoin(new_path, path, addresses);
		response = chdir(cwd);
		return (response);
	}
	return (0);
}

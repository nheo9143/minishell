/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:41:47 by nheo              #+#    #+#             */
/*   Updated: 2022/10/09 13:41:59 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include <sys/stat.h>

static int	is_valid_command(char *cmd)
{
	struct stat	info;

	if (stat(cmd, &info) == SUCCESS)
	{
		if ((info.st_mode & S_IFMT) == S_IFDIR)
			ft_error_exit(cmd, "is a directory", ERR_IS_A_DIRECTORY);
		return (TRUE);
	}
	return (FALSE);
}

static int	is_valid_path(char *path)
{
	if (!*path || !strcmp(path, ".") || !strcmp(path, ".."))
		ft_error_exit(path, "command not found", ERR_CMD_NOT_FOUND);
	if (!ft_strchr(path, '/'))
		return (FALSE);
	is_valid_command(path);
	return (TRUE);
}

static char	*make_path(char *cmd, char **paths)
{
	char		*path;
	int			i;

	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin_3(paths[i], "/", cmd);
		if (is_valid_command(path))
			return (path);
	}
	free(path);
	return (NULL);
}

char	*get_path(char *cmd)
{
	t_env	*env_path;
	char	**paths;

	if (is_valid_path(cmd))
		return (cmd);
	env_path = get_env("PATH");
	if (!env_path)
		ft_error_exit(cmd, "No such file or directory", FAIL);
	paths = ft_split(env_path->value, ':');
	if (!paths)
		exit (FAIL);
	return (make_path(cmd, paths));
}

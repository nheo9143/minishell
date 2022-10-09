/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:41:29 by nheo              #+#    #+#             */
/*   Updated: 2022/10/09 13:41:30 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include <limits.h>

void	ft_pwd(char **cmd)
{
	char	cwd[PATH_MAX];

	if (cmd[1])
	{
		ft_error("pwd", "too many arguments", FAIL);
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_error("pwd", strerror(errno), FAIL);
		return ;
	}
	printf("%s\n", cwd);
}

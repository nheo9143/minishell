/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:43:29 by nheo              #+#    #+#             */
/*   Updated: 2022/10/09 13:43:29 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->cnt = 0;
	new->cmds = 0;
	return (new);
}

static t_type	*create_type(void)
{
	t_type	*new;

	new = malloc(sizeof(t_type));
	if (!new)
		return (0);
	new->last = NONE;
	new->redir = NONE;
	return (new);
}

static int	init_argvs(t_argv **argvs, t_cmd **cmd, t_type **type)
{
	t_argv	*argv;

	*cmd = create_cmd();
	if (!(*cmd))
		return (FAIL);
	*type = create_type();
	if (!(*type))
		return (FAIL);
	argv = create_argv();
	if (!argv)
		return (FAIL);
	ft_argvadd_back(argvs, argv);
	return (SUCCESS);
}

int	create_argvs(t_argv **argvs, t_list **tokens, t_cmd **cmd, t_type **type)
{
	t_list	*seek;

	if (init_argvs(argvs, cmd, type))
		return (E_ARGVS);
	seek = *tokens;
	while (seek)
	{
		if (put_argv(argvs, seek->content, *cmd, *type))
			return (E_ARGVS);
		seek = seek->next;
	}
	if (put_cmd(*cmd, argvs))
		return (E_ARGVS);
	free_lst_only(&(*cmd)->cmds);
	free(*cmd);
	free(*type);
	return (SUCCESS);
}

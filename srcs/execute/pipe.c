/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:41:49 by nheo              #+#    #+#             */
/*   Updated: 2022/10/09 13:41:58 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	set_stdin_pipe(int **pipes, int num)
{
	int	i;

	i = -1;
	if (!pipes)
		return ;
	if (num < 0)
	{
		while (pipes[++i])
			close(pipes[i][0]);
		return ;
	}
	dup2(pipes[num][0], STDIN_FILENO);
	while (pipes[++i])
		close(pipes[i][0]);
}

void	set_stdout_pipe(t_argv *argv, int **pipes, int num)
{
	int	i;

	i = -1;
	if (!pipes)
		return ;
	if (!argv->next)
	{
		while (pipes[++i])
			close(pipes[i][1]);
		return ;
	}
	dup2(pipes[num][1], STDOUT_FILENO);
	while (pipes[++i])
		close(pipes[i][1]);
}

void	close_pipes(int **pipes, int cnt)
{
	int	i;

	if (!pipes)
		return ;
	i = -1;
	while (++i < cnt)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

void	free_pipes(int **pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = -1;
	while (pipes[++i])
		free(pipes[i]);
	free(pipes);
}

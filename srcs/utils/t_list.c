/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:42:53 by nheo              #+#    #+#             */
/*   Updated: 2022/10/09 13:42:54 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	free_lst_only(t_list **lst)
{
	t_list	*to_free;
	t_list	*seek;

	seek = *lst;
	while (seek)
	{
		to_free = seek;
		seek = seek->next;
		if (to_free)
			free(to_free);
	}
	*lst = NULL;
}

void	free_content(void *content)
{
	free(content);
}

void	free_dummy(void *content)
{
	t_dummy	*dummy;

	dummy = (t_dummy *)content;
	if (dummy->value)
		free(dummy->value);
	free(dummy);
}

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token->value)
		free(token->value);
	free(token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:43:08 by nheo              #+#    #+#             */
/*   Updated: 2022/10/09 13:43:08 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	is_wspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' \
			|| c == '\f' || c == '\r');
}

int	only_wspace(char *str)
{
	while (*str)
	{
		if (!is_wspace(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

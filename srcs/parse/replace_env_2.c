/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:43:20 by nheo              #+#    #+#             */
/*   Updated: 2022/10/09 13:43:20 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	ft_keylen(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	if (ft_isdigit(str[i]))
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

int	is_variable(char *input, int *flag)
{
	if (*input == '\"')
		*flag ^= D_QUOTE;
	if (!(*flag & D_QUOTE) && *input == '\'')
		*flag ^= S_QUOTE;
	if (*input == '$' && !(*flag & S_QUOTE))
	{
		if (*(input + 1) == '\'' || *(input + 1) == '\"')
			return (FALSE);
		if (ft_isalpha(*(input + 1)) || *(input + 1) == '_')
			return (TRUE);
		if (!is_wspace(*(input + 1)) && *(input + 1) != '\0')
			return (TRUE);
	}
	return (FALSE);
}

static int	is_variable_hdoc(char *input)
{
	if (*input == '$')
	{
		if (*(input + 1) == '\'' || *(input + 1) == '\"')
			return (FALSE);
		if (ft_isalpha(*(input + 1)) || *(input + 1) == '_')
			return (TRUE);
		if (!is_wspace(*(input + 1)) && *(input + 1) != '\0')
			return (TRUE);
	}
	return (FALSE);
}

int	replace_env_hdoc(char **line, char *input)
{
	char	*env;
	int		size;

	size = get_size(input);
	*line = ft_calloc(size + 1, sizeof(char));
	if (!(*line))
		return (FAIL);
	while (*input)
	{
		if (is_variable_hdoc(input))
		{
			env = get_value(input);
			if (!env)
			{
				free(*line);
				return (FAIL);
			}
			ft_strlcat(*line, env, ft_strlen(env) + ft_strlen(*line) + 1);
			input += ft_keylen(input + 1) + 1;
			free(env);
		}
		else
			ft_strlcat(*line, input++, ft_strlen(*line) + 2);
	}
	return (SUCCESS);
}

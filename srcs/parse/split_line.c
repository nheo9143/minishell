#include "../../includes/parse.h"

static t_list	*create_dummy(char *addr, int size)
{
	t_list	*new;
	char	*dummy;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (NULL);
	dummy = ft_calloc(size + 1, sizeof(char));
	if (!dummy)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->content = dummy;
	ft_strlcpy(dummy, addr, size + 1);
	return (new);
}

static int	create_dummys(t_list **dummys, char *line)
{
	t_list	*dummy;
	t_dummy	dummy_info;

	while (*line == ' ')
		line++;
	while (*line)
	{
		line += search_dummy(&dummy_info, line);
		dummy = create_dummy(dummy_info.addr, dummy_info.size);
		if (!dummy)
			return (FAIL);
		if (dummy_info.type & ADD_NULL)
		{
			dummy->next = create_dummy(dummy_info.addr, 0);
			if (!dummy->next)
				return (FAIL);
		}
		ft_lstadd_back(dummys, dummy);
	}
	return (SUCCESS);
}

static t_list	*dummys_to_chunk(t_list **dummy)
{
	t_list	*chunk;
	char	*chunk_prev;
	char	*chunk_content;

	chunk_content = NULL;
	chunk = ft_calloc(1, sizeof(t_list));
	if (!chunk)
		return (NULL);
	while (*dummy)
	{
		if (!ft_strncmp((*dummy)->content, "", 1))
		{
			*dummy = (*dummy)->next;
			break ;
		}
		chunk_prev = chunk_content;
		chunk_content = ft_strjoin(chunk_content, (*dummy)->content);
		if (!chunk_content)
			return (NULL);
		if (chunk_prev)
			free(chunk_prev);
		*dummy = (*dummy)->next;
	}
	chunk->content = chunk_content;
	return (chunk);
}

void	free_dummy(void *content)
{
	free(content);
}

int	split_line(t_list **chunks, char *line)
{
	t_list	*chunk;
	t_list	*dummys;
	t_list	*h_dummys;

	dummys = NULL;
	*chunks = NULL;
	h_dummys = dummys;
	if (create_dummys(&dummys, line))
	{
		// free();
		return (FAIL);
	}
	while (dummys)
	{
		chunk = dummys_to_chunk(&dummys);
		if (!chunk)
		{
			// free();
			return (FAIL);
		}
		ft_lstadd_back(chunks, chunk);
	}
	ft_lstclear(&h_dummys, free_dummy);
	return (SUCCESS);
}

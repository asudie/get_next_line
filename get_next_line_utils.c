/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:30:45 by asmolnya          #+#    #+#             */
/*   Updated: 2024/01/02 19:44:37 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_newline(t_list *l)
{
	int	count;

	if (l == NULL)
		return (0);
	while (l)
	{
		count = 0;
		while (l->buff[count] && count < BUFFER_SIZE)
		{
			if (l->buff[count] == '\n')
				return (1);
			count++;
		}
		l = l->next_node;
	}
	return (0);
}

t_list	*find_last_node(t_list *l)
{
	if (l == NULL)
		return (NULL);
	while (l->next_node)
	{
		l = l->next_node;
	}
	return (l);
}

int	mystrcpy(char	*res, t_list *l)
{
	int	i;
	int	j;

	i = 0;
	while (l)
	{
		j = 0;
		while (l->buff[j])
		{
			if (l->buff[j] == '\n' || l->buff[j] == '\0')
			{
				res[i++] = '\n';
				res[i] = '\0';
				return (0);
			}
			res[i++] = l->buff[j++];
		}
		l = l->next_node;
	}
	res[i] = '\0';
	return (0);
}

int	count_till_newline(t_list *l)
{
	int	count;
	int	j;

	count = 0;
	while (l)
	{
		j = 0;
		while (l->buff[j])
		{
			if (l->buff[j] == '\n')
			{
				count++;
				return (count);
			}
			count++;
			j++;
		}
		l = l->next_node;
	}
	return (count);
}

void	clean_memory(t_list **l, t_list *empty_node, char *my_buff)
{
	t_list	*temp;

	if (*l == NULL)
		return ;
	while (*l)
	{
		temp = (*l)->next_node;
		free((*l)->buff);
		free(*l);
		(*l) = temp;
	}
	*l = NULL;
	if (empty_node->buff[0])
	{
		*l = empty_node;
	}
	else
	{
		free(my_buff);
		free(empty_node);
	}
}

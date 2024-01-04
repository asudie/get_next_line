/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:30:33 by asmolnya          #+#    #+#             */
/*   Updated: 2024/01/02 19:58:19 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	make_node(t_list **l, char *my_buff)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*l);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*l = new_node;
	else
		last_node->next_node = new_node;
	new_node->next_node = NULL;
	new_node->buff = my_buff;
}

char	*make_line(t_list *l)
{
	char	*res;
	int		till_newl;

	till_newl = count_till_newline(l);
	res = malloc((till_newl + 1));
	if (res == NULL)
		return (NULL);
	mystrcpy(res, l);
	return (res);
}

void	next_call(t_list **l)
{
	char	*my_buff;
	t_list	*last_node;
	t_list	*empty_node;
	int		i;
	int		j;

	i = 0;
	j = 0;
	last_node = find_last_node(*l);
	empty_node = malloc(sizeof(t_list));
	my_buff = malloc(BUFFER_SIZE + 1);
	if (my_buff == NULL || empty_node == NULL)
		return ;
	while (last_node->buff[i] && last_node->buff[i] != '\n')
		++i;
	while (last_node->buff[i] && last_node->buff[++i])
		my_buff[j++] = last_node->buff[i];
	my_buff[j] = '\0';
	empty_node->buff = my_buff;
	empty_node->next_node = NULL;
	clean_memory(l, empty_node, my_buff);
}

int	create_list(t_list **l, int fd)
{
	int		read_chars;
	char	*my_buff;

	read_chars = 0;
	my_buff = NULL;
	while (!find_newline(*l))
	{
		my_buff = malloc(BUFFER_SIZE + 1);
		if (my_buff == NULL)
			return (0);
		read_chars = read(fd, my_buff, BUFFER_SIZE);
		if (!read_chars)
		{
			free(my_buff);
			return (0);
		}
		my_buff[read_chars] = '\0';
		make_node(l, my_buff);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*l = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	create_list(&l, fd);
	if (l == NULL)
		return (NULL);
	line = make_line(l);
	next_call(&l);
	return (line);
}

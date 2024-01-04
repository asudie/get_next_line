/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:44:06 by asmolnya          #+#    #+#             */
/*   Updated: 2024/01/02 19:29:13 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*buff;
	struct s_list	*next_node;
}	t_list;

char	*get_next_line(int fd);
int		create_list(t_list **l, int fd);
int		find_newline(t_list *l);
char	*make_line(t_list *l);
void	make_node(t_list **l, char *my_buff);
t_list	*find_last_node(t_list *l);
int		count_till_newline(t_list *l);
void	next_call(t_list **l);
void	clean_memory(t_list **l, t_list *empty_node, char *my_buff);
int		mystrcpy(char *res, t_list *l);

#endif
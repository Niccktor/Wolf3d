/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 06:40:16 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/21 07:35:53 by tbeguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"
#include <fcntl.h>
#include <stdio.h>

int		count_block(char* str)
{
	int res;
	int i;
	i = 0;
	res = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != '\n')
	{
		while (str[i] && str[i] != ' ' && str[i] != '\n')
			i++;
		res++;
		while (str[i] && str[i] == ' ' && str[i] != '\n')
			i++;
	}
	return (res);
}


static void *kill_lst(t_list* lst)
{
	t_list *next;

	while (lst)
	{
		next = lst->next;
		ft_memdel(&lst->content);
		ft_memdel((void**)&lst);
		lst = next;
	}
	ft_memdel((void**)lst);
	return (NULL);
}


static t_list *get_data(int fd)
{
	t_list* lst;
	t_list*	tmp;
	char*	line;
	int		ret;
	int		len;

	len = -42;
	lst = NULL;
	while ((ret = get_next_line(fd, &line)))
	{
		if (len == -42)
			len = count_block(line);
		if (len == 0 || len != count_block(line)
			|| (tmp = ft_lstnew(line, ft_strlen(line) + sizeof(char))) == NULL)
		{
			ft_strdel(&line);
			return (kill_lst(lst));
		}
		ft_strdel(&line);
		ft_lstadd(&lst, tmp);
	}
	if (ret == -1)
		return (kill_lst(lst));
	ft_lstrev(&lst);
	return (lst);
}

static int	malloc_map(t_mlx *all, int i, int j)
{
	int x;
	all->map.height = i;
	all->map.width = j;
	if ((all->map.map = (int**)ft_memalloc(sizeof(int*) * i)) == NULL)
		return (-1);
	x = 0;
	while (x < i)
	{
		if ((all->map.map[x] = (int*)ft_memalloc(sizeof(int) * j)) == NULL)
		{
			while (x > 0)
				ft_memdel((void**)all->map.map + --x);
			return (-1);
		}
		x++;
	}
	return (0);
}

int put_data(t_mlx* all, t_list* lst)
{
	t_list* tmp;
	char** map;
	int		i;
	int		j;
	static int l = 0;

	tmp = lst;
	i = 0;
	while (i < all->map.height)
	{
		l++;
		j = 0;
		if ((map = ft_strsplit(tmp->content, ' ')) == NULL)
		{
			/*while (i > 0)
				ft_memdel((void**)all->map.map + --i);*/
			return (-1);
		}
		while (j < all->map.width)
		{
			if ((all->map.map[i][j] = ft_atoi(map[j])) < 0)
			{
				ft_strdel(&(map[j]));
				while (i > 0)
					ft_memdel((void**)all->map.map + --i);
				return (-1);
			}
			ft_strdel(&(map[j]));
			j++;
		}
		ft_memdel((void **)&map);
		tmp = tmp->next;
		i++;
	}
	kill_lst(lst);
	return (0);
}


int			read_map(t_mlx* all, char* map)
{
	int fd;
	t_list* lst;

	if ((fd = open(map, O_RDONLY)) == -1 || (lst = get_data(fd)) == NULL)
		return (-1);
	if (malloc_map(all, ft_lstcount(lst), count_block((char*)lst->content)) == -1)
		return (-1);
	if (put_data(all, lst) == -1)
		return (-1);
	int i = 0;
	int j;
	while (i < all->map.height)
	{
		j = 0;
		while (j < all->map.width)
		{
			ft_putnbr(all->map.map[i][j]);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	return (0);
}
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

#include "../inc/wolf3d.h"

static int		count_block(char *line)
{
	int i;
	int count;

	i = 0;
	count = 1;
	while (line[i] != '\n' && line[i] != '\n')
	{
		if (line[i] == ' ')
		{
			count++;
			while (line[i] != ' ')
				i++;
		}
		i++;
	}
	return (count);
}

static void kill_lst(t_list *lst)
{
	t_list *next;


	while (lst)
	{
		next = lst->next;
		ft_memdel(&lst->content);
		ft_memdel((void *)&lst);
		lst = next;
	}	
}


static t_list		*get_data(int fd)
{
	t_list	*lst;
	t_list	*tmp;
	char	*line;
	int		i;
	int		len;

	len = -42;
	i = -1;
	while ((i = get_next_line(fd, &line)))
	{
		if (len == -42)
			len = count_block(line);
		if (len == 0 || len != count_block(line) || (tmp =
					ft_lstnew(line, ft_strlen(line) + sizeof(char))) == NULL)
				return (kill_lst(lst));
		ft_strdel(&line);
		ft_lstadd(&lst, tmp);
	}
	if (ret == -1)
		return (kill_lst(lst));
	ft_lstrev(&lst);
	return (lst);
}

static int			new_map(t_mlx *all, t_list *lst)
{
	int i;

	height = ft_lstcount(lst);
	all->map.height = ft_lstcount(lst);
	all->map.width = count_block + 1;
	if (all->map.map =
			(int **)ft_memalloc(sizeof(int *) * all->map.height) == NULL)
	{
		kill_lst(lst);
		return (-1);
	}
	i = 0;
	while (i < all->map.height)
	{
		if (all->map.map[i] =
				(int *)ft_memalloc(sizeof(int) * all->map.width) == NULL)
		{
			while (i > 0)
				ft_memdel((void **)&all->map.map + --i);
			return (-1);
		}
		i++;
	}
}

static void			

static int			wf_check_map(t_mlx *all, char *map)
{
	int		fd;
	t_list	*lst;

	if ((fd = open(map, O_RDONLY)) == -1 || (lst = get_data(fd)) == NULL)
		return(-1);
	if (new_map(all,lst) == -1)
		argv_err(all);
	put_in_map(all, lst);
}

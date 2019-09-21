/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 05:51:29 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/21 06:39:07 by tbeguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"


void	inti_map(t_mlx *all, int fd)
{

}

static t_list		*get_data(int fd)
{
	t_list	*lst;
	t_list	*tmp;
	char	*line;
	int		i;

	i = -1;
	while ((i = get_next_line(fd, &line)))
	{

	}
}

static int			wf_check_map(t_mlx *all, char *map)
{
	int		fd;
	t_list	*lst;

	if ((fd = open(map, O_RDONLY)) == -1 || (lst = get_data(fd)) == NULL)
		return(NULL);

}

init_maps(all, fd);

void	init_all(t_mlx *all, char *map)
{
	int	bpp;
	int	s_l;
	int	endian;
	int	fd;

	ft_bzero(all, sizeof(t_mlx));
	fd = wf_check_map(all, map)
	all->img.width = 1080;
	all->img.height = 1920;
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, all->img.width, all->img.height,
			"Wolf3d tbeguin@42");
	all->img->img = mlx_new_image(all->mlx, all->img.width, all->img.height);
	all->img->img_str = (unsigned int *)mlx_get_data_addr(all->mlx,
			all->img.width, all->img.height, &bpp, &s_l, &endian);
}

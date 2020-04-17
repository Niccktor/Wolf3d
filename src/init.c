/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 05:51:29 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/23 22:40:16 by nicktor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"

/*
void	inti_map(t_mlx *all, int fd)
{

}*/
/*
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
*/
static void		init_maps(t_mlx *all)
{
	int i;
	int j;

	all->map.height = 10;
	all->map.width = 10;
	all->map.map = (int **)ft_memalloc(sizeof(int *) * 50);
	i = 0;
	while (i <= 10)
	{
		all->map.map[i] = (int *)ft_memalloc(sizeof(int) * 50);
		j = 0;
		while (j <= 10)
		{
			if (j == 0 || j == 9 || i == 0 || i == 9)
				all->map.map[i][j] = 1;
			else
				all->map.map[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void		init_player(t_mlx *all)
{
	all->player.x = 5.0f;
	all->player.y = 5.0f;
	all->player.z = 0.0f;
	all->player.dir_x = -1.0f;
	all->player.dir_y = 0.0f;
	all->player.p_x = 0.0f;
	all->player.p_y = 0.66f;
}

void	init_all(t_mlx *all)
{
	int	bpp;
	int	s_l;
	int	endian;

	ft_bzero(all, sizeof(t_mlx));
//	fd = wf_check_map(all, map);
	all->img.width = 500;
	all->img.height = 500;
	all->x = -1;
	all->y = -1;
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, all->img.width, all->img.height,
			"Wolf3d tbeguin@42");
	all->img.img = mlx_new_image(all->mlx, all->img.width, all->img.height);
	all->img.img_str = (unsigned int *)mlx_get_data_addr(all->img.img,
		   	&bpp, &s_l, &endian);
	ft_bzero(all->img.img_str, all->img.width * all->img.height * 4);
	init_maps(all);
	init_player(all);
	threads(*all);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 05:51:29 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/22 18:26:26 by tbeguin          ###   ########.fr       */
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

	all->map.height = 50;
	all->map.width = 50;
	all->map.map = (int **)ft_memalloc(sizeof(int *) * 50);
	i = 0;
	while (i < 50)
	{
		all->map.map[i] = (int *)ft_memalloc(sizeof(int) * 50);
		j = 0;
		while (j < 50)
		{
			if (j == 0 || j == 49 || i == 0 || i == 49)
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
	all->player.x = 20.0f;
	all->player.y = 20.0f;
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
	all->img.width = 1080;
	all->img.height = 1920;
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, all->img.width, all->img.height,
			"Wolf3d tbeguin@42");
	all->img.img = mlx_new_image(all->mlx, all->img.width, all->img.height);
	all->img.img_str = (unsigned int *)mlx_get_data_addr(all->mlx,
		   	&bpp, &s_l, &endian);
	init_maps(all);
	init_player(all);
	render(all);
}

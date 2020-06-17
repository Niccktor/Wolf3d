/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 05:29:43 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/23 23:03:17 by nicktor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# define NB_THD 5

#include <mlx.h>
#include <pthread.h>
#include "key.h"
#include "../libft/libft.h"




typedef struct			s_player
{
	double				x;
	double				y;
	double				z;
	double				dir_x;
	double				dir_y;
	double				cam_x;
	double				cam_y;
	double				p_x;
	double				p_y;
}						t_player;

typedef struct			s_map
{
	char				*file;
	int					**map;
	int					height;
	int					width;
}						t_map;

typedef struct			s_image
{
	void				*img;
	unsigned int		*img_str;
	int					height;
	int					width;
	int					bpp;
	int					endian;
}						t_image;

typedef struct			s_ray
{
	int					x;
	int					y;
	double				cam_x;
	double				dir_x;
	double				dir_y;
	double				side_dist_x;
	double				side_dist_y;
	double				dx;
	double				dy;
	int					step_x;
	int					step_y;
	int					side;
}						t_ray;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	char				*name;
	struct s_player		player;
	struct s_image		img;
	struct s_map		map;
	struct s_ray		ray;
	int					x;
	int					y;
	unsigned long		time;
	unsigned long		oldTime;
	unsigned long		fps;
	unsigned long		ticks;
}						t_mlx;

typedef struct		s_thread
{
	int					i;
	t_mlx			all;
	pthread_t		thread;
}					t_thread;

int					threads(t_mlx all);
/*
**						main.c
*/
int						argv_err(t_mlx *all);
int						ft_exit(t_mlx *all);
/*
**						init.c
*/
void					init_all(t_mlx *all, char *map_file);
/*
**						ray.c
*/

//void					render(t_mlx *all);
void					*render(void *thd);
/*
**						draw.c
*/
void					fill_pixel(t_mlx *all, int x, int y, unsigned int c);
void					ver_line(t_mlx *a, int x, int s, int e, unsigned int c);
/*
**						event.c
*/
int					key_event(int key, t_mlx *all);
int					ft_mouse_move(int x, int y, t_mlx *all);


int					threads_loop(t_mlx* all);
int					read_map(t_mlx* all, char* map);



#endif 

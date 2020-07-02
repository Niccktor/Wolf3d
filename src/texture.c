#include "../inc/wolf.h"

t_image* xpm_load(char* tex, t_mlx* all)
{
	t_image* img;
	int	bpp;
	int	s_l;
	int	endian;

	if ((img = ft_memalloc(sizeof(t_image))) == NULL)
		return (NULL);
	if ((img->img = mlx_xpm_file_to_image(all->mlx, tex, &img->width, &img->height)) == NULL)
	{
		ft_memdel((void**)&img);
		return (NULL);
	}
	img->img_str = (unsigned int *)mlx_get_data_addr(img->img, &bpp, &s_l, &endian);
	return (img);
}

int		init_texture(t_mlx* all)
{
	static char* texture[20] = { "textures/brick.xpm", NULL };
	t_image* img;
	int i;

	i = 0;
	while (i < 1 && texture[i])
	{
		if ((img = xpm_load(texture[i], all)) == NULL)
			return (-1);
		all->texture[i] = img;
		i++;
	}
	return (0);
}
/*
void	cast_celling(t_mlx* all)
{

}

void	cast_wall(t_mlx* all)
{
	double wallX;
	if (all->ray.side == 0)
		wallX = all->player.y + perpWallDist * all->ray.dir_y;
	else
		wallX = all->player.x + perpWallDist * all->ray.dir_x;
	wallX -= floor(wallX);

	int textureX;

	textureX = (int)(wallX * (double)(all->texture[0]->width));
	if (all->ray.side == 0 && all->ray.dir_x > 0)
		textureX = all->texture[0]->width - textureX - 1;
	if (all->ray.side == 1 && all->ray.dir_y < 0)
		textureX = all->texture[0]->width - textureX - 1;
	double step;
	step = 1.0 * all->texture[0]->height / lineHeight;
	double texPos = (start - all->img.height / 2 + lineHeight / 2) * step;

	int texY;
	unsigned int color;
	int j;
	j = start;
	while (j < end)
	{
		texY = (int)texPos & (all->texture[0]->height - 1);
		texPos += step;
		color = all->texture[0]->img_str[all->texture[0]->height * texY + textureX];
		//printf("%ud\n", color);
		fill_pixel(all, i, j, color);
		j++;
	}
}

void	cast_floor(t_mlx* all)
{

}*/
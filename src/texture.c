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
	static char* texture[20] = { "textures/brick.xpm", "textures/wood.xpm", "textures/stone.xpm" , NULL };
	t_image* img;
	int i;

	all->text_max = 0;
	i = 0;
	while (i < 20 && texture[i])
	{
		if ((img = xpm_load(texture[i], all)) == NULL)
			return (-1);
		all->texture[i] = img;
		all->text_max++;
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:53:19 by avast             #+#    #+#             */
/*   Updated: 2023/05/11 19:04:04 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	display_ray(t_data *data)
{
	int			j;
	int			i;
	float		u;
	float		v;
	t_ray		r;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			u = (float)i / (WIDTH - 1);
			v = (float)j / (HEIGHT - 1);
			r = get_ray(u, v, *data);
			img_pix_put(&data->img, i, j, define_color(data, r));
			i++;
		}
		j++;
	}
}

int	display(t_data *data)
{
	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	display_ray(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}

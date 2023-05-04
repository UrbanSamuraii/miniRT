/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:40:22 by avast             #+#    #+#             */
/*   Updated: 2023/05/03 17:18:01 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

// normalize les vecteurs
void	initialize_data(t_data *data, t_elem elem)
{
	data->elements = elem;
	data->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	data->focal_length = 1;
	data->height = 2 * data->focal_length
		* tan(deg_to_rad(elem.camera.fov) / 2);
	data->width = data->height * data->aspect_ratio;
	data->horizontal = data->width
		* vec3_normalize(vec3_cross(elem.camera.dir, (t_vec3){0, 1, 0}));
	data->vertical = data->height
		* vec3_normalize(vec3_cross(elem.camera.dir, data->horizontal));
	data->corner = elem.camera.origin.xyz + elem.camera.dir.xyz
		- data->horizontal.xyz / 2 - data->vertical.xyz / 2;
}


int	initialize_mlx(t_elem *elem, t_data *data)
{
	// Initialization mlx items
	ft_memset(data, 0, sizeof(*data));
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (data->win_ptr == NULL)
		return (free(data->win_ptr), MLX_ERROR);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);

	// Initialization data
	initialize_data(data, *elem);

	// Render & loop
	mlx_loop_hook(data->mlx_ptr, &display, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, 17, ButtonPressMask, &close_window, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

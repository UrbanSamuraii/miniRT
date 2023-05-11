/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:54:19 by avast             #+#    #+#             */
/*   Updated: 2023/05/11 19:07:43 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMS_H
# define PARAMS_H

# include "libft.h"
# include "colors.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>
# include <float.h>
# include <sys/wait.h>

/* A commenter pour macos */
# include <X11/X.h>
# include <X11/keysym.h>

/* A decommenter pour macos */
/* # define XK_space 49
# define XK_2 19
# define XK_1 18
# define XK_c 8
# define XK_Escape 53
# define XK_Up 126
# define XK_Down 125
# define XK_Left 123
# define XK_Right 124
# define XK_w 13
# define XK_s 1
# define XK_d 2 
# define XK_a 0
# define KeyPress 02
# define KeyPressMask (1L<<0)
# define ButtonPress 04
# define ButtonPressMask (1L<<2) */

# define ERRCOMMAS	"Too many or not enough commas.\033[0m"
# define ERRCHAR	"Invalid characters detected.\033[0m"
# define ERRRANGE	"Invalid range of a parameter.\033[0m"
# define ERRPARAM	"Invalid number of parameters.\033[0m"
# define ERRDEF		"You cannot redefine A or C.\033[0m"
# define ERRITI		1
# define ERRIPN		2
# define MLX_ERROR 1

# define WIDTH 1000
# define HEIGHT 600

# define ALL_OBJ	-1
# define SPHERE		1
# define PLANE		2
# define CYLINDER	3
# define CONUS		4

# define MIN_SHADOW	0.000001

# define BOTTOM		1
# define TOP		2

typedef float	t_vec3	__attribute__((ext_vector_type(3)));
typedef float	t_vec2	__attribute__((ext_vector_type(2)));

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_equation
{
	float	a;
	float	b;
	float	c;
	float	delta;
}			t_equa;

typedef struct s_ambient {
	float	ratio;
	t_vec3	colors;
}			t_ambient;

typedef struct s_camera {
	t_vec3	origin;
	t_vec3	dir;
	float	fov;
}			t_camera;

typedef struct s_light {
	t_vec3			origin;
	float			ratio;
	t_vec3			colors;
	struct s_light	*next;
}			t_light;

typedef struct s_objects {
	int					id;
	int					type;
	t_vec3				origin;
	t_vec3				dir;
	float				radius;
	float				height;
	t_vec3				colors;
	struct s_objects	*next;
}		t_objects;

typedef struct s_hit_record
{
	int		obj_id;
	t_vec3	obj_color;
	t_vec3	p;
	t_vec3	normal;
	float	t;
}	t_hit_rec;

typedef struct s_elements {
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights_head;
	t_objects	*objects_head;
	int			camera_initialized;
	int			ambient_initialized;
}				t_elem;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_elem		elements;
	float		aspect_ratio;
	float		focal_length;
	float		height;
	float		width;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		corner;
}	t_data;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:00:40 by avast             #+#    #+#             */
/*   Updated: 2023/05/11 18:20:21 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H


/* PARSING */

//error ------------------------------------------- //
void	error(char **to_free, t_elem *elems, int code);

//free -------------------------------------------- //
void	free_tab(char **tab);
void	free_structures(t_elem *elems);

//acl_check --------------------------------------- //
bool	ambient(t_elem *elems, char **params);
bool	camera(t_elem *elems, char **params);
bool	light(t_elem *elems, char **params);

//acl_init ---------------------------------------- //
bool	reinit_ambient(t_elem *elems, char **params);
bool	reinit_camera(t_elem *elems, char **params);
bool	reinit_light(t_elem *elems, char **params);

//parse objects ----------------------------------- //
void	init_object_head(t_elem *elems, char **params, int type);
void	new_node_object(t_elem *elems, char **params, int type);

//parse cylinders --------------------------------- //
void	init_cylinder(t_objects *object, char **params);
bool	cylinder(t_elem *elems, char **params);

//parse planes ------------------------------------ //
void	init_plane(t_objects *object, char **params);
bool	plane(t_elem *elems, char **params);

//parse spheres ----------------------------------- //
void	init_sphere(t_objects *object, char **params);
bool	sphere(t_elem *elems, char **params);

//parse utils ------------------------------------- //
t_vec3	colors_to_percent(char **tab);

//parse checks ------------------------------------ //
bool	invalid_param_number(int code, char **params);
bool	invalid_chars(char *str);
bool	not_valid_parameter(char *to_check, float min, float max);
bool	not_valid_number_of_commas(char *to_check);
bool	not_valid_range(char *to_check, float min, float max);


/* MLX INIT */
void	initialize_data(t_data *data, t_elem elem);
int		initialize_mlx(t_elem *elem, t_data *data);

/* DISPLAY */
int		display(t_data *data);
void	display_ray(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);

/* HOOKS */
int		close_window(t_data *data);
int		handle_keypress(int keysym, t_data *data);

/* RAYTRACING */
int		define_color(t_data *data, t_ray r);
bool	hit_anything(t_ray r, t_elem elem, t_hit_rec *rec, t_vec3 limit);
t_vec3	update_color_shadow(t_hit_rec rec, t_elem elem);

/* RAY_LIGTHS */
t_vec3	get_ambient_light(t_vec3 obj_color, t_ambient ambient);
t_vec3	get_direct_light(t_hit_rec rec, t_light light);
t_vec3	get_spec_light(t_camera cam, t_hit_rec rec, t_light light);

/* RAY_SPHERE */
bool	hit_sphere(t_objects sphere, t_ray r, t_vec2 limit, t_hit_rec *rec);

/* RAY_PLANE */
bool	hit_plane(t_objects plane, t_ray r, t_vec2 limit, t_hit_rec *rec);

/* RAY_CYLINDER */
bool	hit_cylinder(t_objects cylinder, t_ray r, t_vec2 limit, t_hit_rec *rec);

/* RAY_CONE */
bool	hit_cone(t_objects cone, t_ray r, t_vec2 limit, t_hit_rec *rec);

/* MATHS UTILS */
float	cal_cos(int a);
float	cal_sin(int a);
float	deg_to_rad(float a);
float	ft_abs(float a);
int		ft_sign(int a);

/* VEC3 UTILS*/
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
float	vec3_distance(t_vec3 a, t_vec3 b);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_normalize(t_vec3 a);

/* RAY UTILS*/
t_ray	get_ray(float u, float v, t_data data);
t_ray	get_shadow_ray(t_hit_rec rec, t_light light);
t_vec3	ray_at(t_ray ray, float t);
void	set_face_normal(t_ray r, t_vec3 out_normal, t_hit_rec *rec);




#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:34:06 by avast             #+#    #+#             */
/*   Updated: 2023/05/11 15:16:13 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

bool	hit_plane(t_objects plane, t_ray r, t_vec2 limit, t_hit_rec *rec)
{
	t_vec3	normal;
	t_vec3	ray_orient;
	float	root;

	normal = vec3_normalize((t_vec3){plane.dir.y,
			-plane.dir.x, 0});
	ray_orient = plane.origin.xyz - r.origin.xyz;
	if (vec3_dot(normal, r.direction) == 0)
		return (false);
	root = vec3_dot(ray_orient, normal) / vec3_dot(normal, r.direction);
	if (root == 0 || root < limit.x || limit.y < root)
		return (false);
	if (rec)
	{
		rec->obj_id = plane.id;
		rec->obj_color = plane.colors;
		rec->t = root;
		rec->p = ray_at(r, root);
		set_face_normal(r, normal, rec);
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:54:22 by avast             #+#    #+#             */
/*   Updated: 2023/05/11 14:29:56 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

static void	set_sphere_rec(t_ray r, float t, t_objects sphere, t_hit_rec *rec)
{
	t_vec3	outward_normal;

	if (rec)
	{
		rec->obj_id = sphere.id;
		rec->obj_color = sphere.colors;
		rec->t = t;
		rec->p = ray_at(r, t);
		outward_normal = (rec->p.xyz - sphere.origin.xyz) / sphere.radius;
		set_face_normal(r, outward_normal, rec);
	}
}

bool	hit_sphere(t_objects sphere, t_ray r, t_vec2 limit, t_hit_rec *rec)
{
	t_equa	equa;
	float	root;

	equa.a = vec3_dot(r.direction, r.direction);
	equa.b = vec3_dot(r.origin.xyz - sphere.origin.xyz, r.direction);
	equa.c = vec3_dot(r.origin.xyz - sphere.origin.xyz, r.origin.xyz
			- sphere.origin.xyz) - sphere.radius * sphere.radius;
	equa.delta = equa.b * equa.b - equa.a * equa.c;
	if (equa.delta < 0)
		return (false);
	root = (-equa.b - sqrt(equa.delta)) / equa.a;
	if (root < limit.x || limit.y < root)
	{
		root = (-equa.b + sqrt(equa.delta)) / equa.a;
		if (root < limit.x || limit.y < root)
			return (false);
	}
	set_sphere_rec(r, root, sphere, rec);
	return (true);
}

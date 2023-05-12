/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:54:22 by avast             #+#    #+#             */
/*   Updated: 2023/05/12 13:57:56 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"

static void	solve_cy_equa(t_objects cy, t_ray r, float *root1, float *root2)
{
	t_vec3	ra0;
	t_vec3	va;
	t_equa	equa;

	ra0 = vec3_cross(vec3_cross(cy.dir, r.origin.xyz - cy.origin.xyz), cy.dir);
	va = vec3_cross(vec3_cross(cy.dir, r.direction), cy.dir);
	equa.a = vec3_dot(va, va);
	equa.b = 2 * vec3_dot(ra0, va);
	equa.c = vec3_dot(ra0, ra0) -(cy.radius * cy.radius);
	equa.delta = equa.b * equa.b - 4 * equa.a * equa.c;
	if (equa.delta < 0)
	{
		*root1 = -1;
		*root2 = -1;
		return ;
	}
	*root1 = (-equa.b - sqrtf(equa.delta)) / (2 * equa.a);
	*root2 = (-equa.b + sqrtf(equa.delta)) / (2 * equa.a);
}

static float	hit_cylinder_cap(t_objects cy, t_ray r, t_vec2 limit, int side)
{
	t_vec3	p;
	t_vec3	normal;
	float	root;

	if (side == BOTTOM)
	{
		p = cy.origin.xyz - (cy.height / 2.0) * cy.dir.xyz;
		normal = cy.dir;
	}
	else
	{
		p = cy.origin.xyz + (cy.height / 2.0) * cy.dir.xyz;
		normal = -cy.dir;
	}
	if (vec3_dot(normal, r.direction) == 0)
		return (-1);
	root = vec3_dot(p.xyz - r.origin.xyz, normal)
		/ vec3_dot(normal, r.direction);
	if (root == 0 || root < limit.x || limit.y < root)
		return (-1);
	if (vec3_dot(ray_at(r, root).xyz - p.xyz, ray_at(r, root).xyz - p.xyz)
		<= cy.radius * cy.radius)
		return (root);
	else
		return (-1);
}

static float	min_positive(float a, float b, float c, float d)
{
	float	min_pos;

	min_pos = -1;
	if (a > 0 && (a < min_pos || min_pos == -1))
		min_pos = a;
	if (b > 0 && (b < min_pos || min_pos == -1))
		min_pos = b;
	if (c > 0 && (c < min_pos || min_pos == -1))
		min_pos = c;
	if (d > 0 && (d < min_pos || min_pos == -1))
		min_pos = d;
	return (min_pos);
}

static void	set_cyl_rec(t_ray r, float roots[4], t_objects cyl, t_hit_rec *rec)
{
	t_vec3	projection;
	t_vec3	closest;
	t_vec3	dot;

	if (rec)
	{
		rec->obj_id = cyl.id;
		rec->obj_color = cyl.colors;
		rec->t = min_positive(roots[0], roots[1], roots[2], roots[3]);
		rec->p = ray_at(r, rec->t);
		if (rec->t == roots[0] || rec->t == roots[1])
		{
			projection = vec3_dot(rec->p.xyz - cyl.origin.xyz, cyl.dir)
				* cyl.dir.xyz;
			closest = projection.xyz + cyl.origin.xyz;
			dot = vec3_dot(rec->p.xyz - closest.xyx, cyl.dir) * cyl.dir.xyz;
			rec->normal = vec3_normalize(rec->p.xyz - closest.xyz - dot.xyz);
		}
		else
			set_face_normal(r, cyl.dir, rec);
	}
}

bool	hit_cylinder(t_objects cyl, t_ray r, t_vec2 limit, t_hit_rec *rec)
{
	float	roots[4];
	float	dot[2];

	solve_cy_equa(cyl, r, &roots[0], &roots[1]);
	if (roots[0] < limit.x || roots[0] > limit.y)
		roots[0] = -1;
	if (roots[1] < limit.x || roots[1] > limit.y)
		roots[1] = -1;
	dot[0] = vec3_dot(ray_at(r, roots[0]).xyz - cyl.origin.xyz, cyl.dir);
	dot[1] = vec3_dot(ray_at(r, roots[1]).xyz - cyl.origin.xyz, cyl.dir);
	if (dot[0] < -cyl.height / 2 || dot[0] > cyl.height / 2)
		roots[0] = -1;
	if (dot[1] < -cyl.height / 2 || dot[1] > cyl.height / 2)
		roots[1] = -1;
	roots[2] = hit_cylinder_cap(cyl, r, limit, BOTTOM);
	roots[3] = hit_cylinder_cap(cyl, r, limit, TOP);
	if (roots[0] < 0 && roots[1] < 0 && roots[2] < 0 && roots[3] < 0)
		return (false);
	set_cyl_rec(r, roots, cyl, rec);
	return (true);
}

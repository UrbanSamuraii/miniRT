/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:54:22 by avast             #+#    #+#             */
/*   Updated: 2023/05/10 17:44:59 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

/* bool	hit_cylinder(t_objects cylinder, t_ray r, t_vec2 limit, t_hit_rec *rec)
{
    (void)limit;
    // Calculate the vector from the ray origin to the center of the cylinder
    t_vec3 ray_to_cylinder = cylinder.origin.xyz - r.origin.xyz;

    // Project the vector onto the cylinder orientation
	float projection = vec3_dot(ray_to_cylinder, cylinder.dir);
	t_vec3 oc_parallel = projection * cylinder.dir.xyz;

    // Calculate the vector from the cylinder center to the closest point on the ray to the cylinder axis
    const t_vec3 q = ray_to_cylinder.xyz - oc_parallel.xyz;

     // Calculate the squared distance from the ray to the cylinder axis
    float dist2 = vec3_dot(q, q);

    // Calculate the squared radius of the cylinder
    float radius2 = cylinder.radius * cylinder.radius;

    if (dist2 <= radius2)
    {
        float t1 = projection - sqrtf(radius2 - dist2);
        float t2 = projection + sqrtf(radius2 - dist2);
        if (t1 > - cylinder.height / 2 && t1 < cylinder.height / 2 && rec)
        {
            rec->t = t1;
            rec->p = ray_at(r, t1);
            rec->normal = (t_vec3){q.x, 0, q.z};
            set_face_normal(r, rec->normal, rec);
            return (true);
        }
        else if (t2 > - cylinder.height / 2 && t2 < cylinder.height /2 && rec)
        {
            rec->t = t2;
            rec->p = ray_at(r, t2);
            rec->normal = (t_vec3){q.x, 0, q.z};
            set_face_normal(r, rec->normal, rec);
            return (true);
        }
    }
    return (false);
}
 */

float	hit_cylinder_cap(t_objects cylinder, t_ray r, t_vec2 limit, t_vec3 point)
{
	t_vec3	normal;
	t_vec3	ray_orient;
	float	root;

	normal = cylinder.dir;
	//normal = vec3_normalize((t_vec3){cylinder.dir.y, -cylinder.dir.x, 0});
	ray_orient = vec3_normalize(point.xyz - r.origin.xyz);
	if (vec3_dot(normal, r.direction) == 0)
		return (-1);
	root = vec3_dot(ray_orient, normal) / vec3_dot(normal, r.direction);
	if (root == 0 || root < limit.x || limit.y < root)
		return (-1);
	if (vec3_dot(ray_at(r, root).xyz - point.xyz, ray_at(r, root).xyz - point.xyz) < cylinder.radius * cylinder.radius)
		return (root);
	else
		return (-1);
	
/* 	if (rec)
	{
		rec->obj_id = cylinder.id;
		rec->obj_color = cylinder.colors;
		rec->t = root;
		rec->p = ray_at(r, root);
		set_face_normal(r, normal, rec);
	} */
}
/* float	hit_cylinder_cap2(t_objects cylinder, t_ray r, t_vec2 limit, t_vec3 point)
{
	t_vec3	normal;
	t_vec3	ray_orient;
	float	root;

	//normal = cylinder.dir;
	normal = vec3_normalize((t_vec3){cylinder.dir.y,
			-cylinder.dir.x, 0});
	ray_orient = vec3_normalize(point.xyz - r.origin.xyz);
	if (vec3_dot(normal, r.direction) == 0)
		return (-1);
	root = vec3_dot(ray_orient, normal) / vec3_dot(normal, r.direction);
	if (root == 0 || root < limit.x || limit.y < root)
		return (-1);
	if (vec3_dot(ray_at(r, root).xyz - point.xyz, ray_at(r, root).xyz - point.xyz) < cylinder.radius * cylinder.radius)
		return (root);
	else
		return (-1);
} */

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

bool	hit_cylinder(t_objects cylinder, t_ray r, t_vec2 limit, t_hit_rec *rec)
{
    t_vec3  va;
    t_vec3  ra0;
    t_vec3  ra1;
    t_vec3  ra2;
	t_vec3	deltap;
	t_vec3 vvaa;
	t_vec3	dva;
    float   a;
    float   b;
    float   c;
    float   root1;
    float   root2;
    float   root3;
    float   root4;

	deltap = r.origin.xyz - cylinder.origin.xyz;
	vvaa = r.direction.xyz - vec3_dot(r.direction, cylinder.dir) * cylinder.dir.xyz;
	dva = deltap.xyz - vec3_dot(deltap, cylinder.dir) * cylinder.dir.xyz;
    ra1 = cylinder.origin.xyz - (cylinder.height / 2) * cylinder.dir.xyz;
    ra2 = cylinder.origin.xyz + (cylinder.height / 2) * cylinder.dir.xyz;
    ra0 = vec3_cross(vec3_cross(cylinder.dir, r.origin.xyz - ra1.xyz), cylinder.dir);
    va = vec3_cross(vec3_cross(cylinder.dir, r.direction), cylinder.dir);
    a = vec3_dot(va, va);
    b = vec3_dot(2 * ra0.xyz, va);
    c = vec3_dot(ra0, ra0) -(cylinder.radius * cylinder.radius);
    a = vec3_dot(vvaa, vvaa);
    b = 2 * vec3_dot(vvaa, dva);
    c = vec3_dot(dva, dva) -(cylinder.radius * cylinder.radius);
    if (b * b - 4 * a * c < 0)
        return (false);
    root1 = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);
    root2 = (-b - sqrtf(b * b - 4 * a * c)) / (2 * a);
    //top.xyz = cylinder.origin.xyz + cylinder.height * cylinder.dir.xyz;
    //bottom.xyz = cylinder.origin.xyz - cylinder.height * cylinder.dir.xyz;
/*     if (root1 < limit.x || root1 > limit.y)
    {
        if (root2 < limit.x || root2 > limit.y)
            return (false);
    } */
	if (root1 > limit.y)
		root1 = -1;
	if (root2 > limit.y)
		root2 = -1;
    if (root1 >= 0)
    {
 		if (vec3_dot(ray_at(r, root1).xyz - ra1.xyz, cylinder.dir) <= 0
			|| vec3_dot(ray_at(r, root1).xyz - ra2.xyz, cylinder.dir) >= 0) 
				root1 = -1;
    }
   if (root2 >= 0)
     {
		if (vec3_dot(ray_at(r, root2).xyz - ra1.xyz, cylinder.dir) <= 0
			|| vec3_dot(ray_at(r, root2).xyz - ra2.xyz, cylinder.dir) >= 0)
			root2 = -1;
    }
	root3 = hit_cylinder_cap(cylinder, r, limit, ra1);
	root4 = hit_cylinder_cap(cylinder, r, limit, ra2);
    if (root1 < 0 && root2 < 0 && root3 < 0 && root4 < 0)
		return (false);
	if (rec)
	{
		rec->obj_id = cylinder.id;
		rec->obj_color = cylinder.colors;
		rec->t = min_positive(root1, root2, root3, root4);
		rec->p = ray_at(r, rec->t);
		if (rec->t == root1 || rec->t == root2)
			rec->normal = vec3_normalize((t_vec3){rec->p.x - cylinder.origin.x, rec->p.y - cylinder.origin.y, rec->p.z - cylinder.origin.z});
		else
			rec->normal = cylinder.dir;
		//t_vec3 plane_normal = vec3_normalize((t_vec3){cylinder.dir.y, -cylinder.dir.x, 0});
		//rec->normal = vec3_normalize(rec->normal.xyz - vec3_dot(rec->normal, plane_normal) * plane_normal.xyz);
		//set_face_normal(r, rec->normal, rec);
	}
	return (true);
}

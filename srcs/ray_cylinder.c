/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:54:22 by avast             #+#    #+#             */
/*   Updated: 2023/05/04 16:47:19 by avast            ###   ########.fr       */
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
bool	hit_cylinder(t_objects cylinder, t_ray r, t_vec2 limit, t_hit_rec *rec)
{
    t_vec3  va;
    t_vec3  rao;
    float   a;
    float   b;
    float   c;
    float   root;

    va = vec3_normalize(vec3_cross(vec3_cross(cylinder.dir, r.direction), cylinder.dir));
    rao = vec3_normalize(vec3_cross(vec3_cross(cylinder.dir, r.origin.xyz - cylinder.origin.xyz), cylinder.dir));
    a = vec3_dot(va, va);
    b = 2 * vec3_dot(rao, va);
    c = vec3_dot(rao, rao) -(cylinder.radius * cylinder.radius);
    if (b * b -4 * a * c < 0)
        return (false);
    root = (-b + sqrtf(b * b - 4 * a * c)) / 2 * a;
    //top.xyz = cylinder.origin.xyz + cylinder.height * cylinder.dir.xyz;
    //bottom.xyz = cylinder.origin.xyz - cylinder.height * cylinder.dir.xyz;
    if (root < limit.x || root > limit.y)
    {
        root = (-b + sqrtf(b * b - 4 * a * c)) / 2 * a;
        if (root < limit.x || root > limit.y)
            return (false);
    }
    if (rec)
    {
        rec->t = root;
        rec->p = ray_at(r, root);
        t_vec3 V = vec3_normalize((t_vec3){rec->p.x - cylinder.origin.x, 0, rec->p.z - cylinder.origin.z});
        rec->normal = V;
        //t_vec3 plane_normal = vec3_normalize((t_vec3){cylinder.dir.y, -cylinder.dir.x, 0});
        //rec->normal = vec3_normalize(rec->normal.xyz - vec3_dot(rec->normal, plane_normal) * plane_normal.xyz);
        set_face_normal(r, rec->normal, rec);
    }
    return (true);
}

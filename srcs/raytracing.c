/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:13:35 by avast             #+#    #+#             */
/*   Updated: 2023/05/11 19:04:01 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"


static int	get_color(t_vec3 color)
{
	int		new_color;

	color.xyz *= 255.999;
	if (color.x > 255)
		color.x = 255;
	if (color.y > 255)
		color.y = 255;
	if (color.z > 255)
		color.z = 255;
	new_color = (((int)color.x & 0x0ff) << 16)
		| (((int)color.y & 0x0ff) << 8) | ((int)color.z & 0x0ff);
	return (new_color);
}

static void	save_rec(float *closest, t_hit_rec tmp, t_hit_rec *rec, bool *hit)
{
	*hit = true;
	if (rec)
	{
		*closest = tmp.t;
		*rec = tmp;
	}
}

bool	hit_anything(t_ray r, t_elem elem, t_hit_rec *rec, t_vec3 limit)
{
	float		closest;
	bool		hit_anything;
	t_hit_rec	tmp_rec;
	t_objects	*obj;

	closest = limit.y;
	hit_anything = false;
	obj = elem.objects_head;
	while (obj)
	{
		if (obj->id != (int)limit.z && obj->type == SPHERE
			&& hit_sphere(*obj, r, (t_vec2){limit.x, closest}, &tmp_rec))
			save_rec(&closest, tmp_rec, rec, &hit_anything);
		if (obj->id != (int)limit.z && obj->type == PLANE
			&& hit_plane(*obj, r, (t_vec2){limit.x, closest}, &tmp_rec))
			save_rec(&closest, tmp_rec, rec, &hit_anything);
		if (obj->id != (int)limit.z && obj->type == CYLINDER
			&& hit_cylinder(*obj, r, (t_vec2){limit.x, closest}, &tmp_rec))
			save_rec(&closest, tmp_rec, rec, &hit_anything);
		// ajouter la ligne cylindre
		if (limit.z >= 0 && hit_anything)
			break ;
		obj = obj->next;
	}
	return (hit_anything);
}

t_vec3	update_color_shadow(t_hit_rec rec, t_elem elem)
{
	t_light	*light;
	t_vec3	color;
	t_ray	shadow_ray;

	light = elem.lights_head;
	color = (t_vec3){0, 0, 0};
	while (light)
	{
		shadow_ray = get_shadow_ray(rec, *light);
		if (!hit_anything(shadow_ray, elem, NULL, (t_vec3){MIN_SHADOW,
				vec3_distance(rec.p, light->origin), (float)rec.obj_id}))
		{
			color.xyz += get_direct_light(rec, *light);
			color.xyz += get_spec_light(elem.camera, rec, *light);
		}
		light = light->next;
	}
	color.xyz += get_ambient_light(rec.obj_color, elem.ambient);
	return (color.xyz / 3);
}

int	define_color(t_data *data, t_ray r)
{
	t_vec3		color;
	t_hit_rec	rec;

	color = (t_vec3){0, 0, 0};
	if (hit_anything(r, data->elements, &rec, (t_vec3){0, INFINITY, ALL_OBJ}))
		color = update_color_shadow(rec, data->elements);
	else
		color.xyz = get_ambient_light(color, data->elements.ambient).xyz / 3;
	return (get_color(color));
}

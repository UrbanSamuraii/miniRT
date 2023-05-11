/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:20:31 by avast             #+#    #+#             */
/*   Updated: 2023/05/11 19:11:45 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"

t_vec3	get_ambient_light(t_vec3 obj_color, t_ambient ambient)
{
	return (ambient.ratio * (ambient.colors.xyz + obj_color.xyz));
}

t_vec3	get_direct_light(t_hit_rec rec, t_light light)
{
	t_vec3	directional_light;
	float	dot;
	t_vec3	color;

	directional_light.xyz = vec3_normalize(light.origin.xyz - rec.p.xyz);
	dot = vec3_dot(rec.normal, directional_light);
	if (dot < 0)
		color.xyz = 0;
	else
		color.xyz = light.ratio * dot * (light.colors.xyz + rec.obj_color.xyz);
	return (color);
}

// Couleur lumiere + Portion reflexion plastique + Rugosite surface
t_vec3	get_spec_light(t_camera cam, t_hit_rec rec, t_light light)
{
	t_vec3	dir_l;
	t_vec3	ref_l;
	float	dot;
	t_vec3	color;

	dir_l = vec3_normalize(light.origin.xyz - rec.p.xyz);
	ref_l.xyz = vec3_normalize(-dir_l.xyz + 2 * vec3_dot(dir_l, rec.normal)
			* rec.normal.xyz);
	dot = vec3_dot(ref_l, vec3_normalize(cam.origin.xyz - rec.p.xyz));
	if (dot < 0)
		color.xyz = 0;
	else
		color.xyz = light.ratio * powf(dot, 23)
			* (rec.obj_color.xyz + ((1 - 0.5) * rec.obj_color.xyz + 0.5));
	return (color);
}

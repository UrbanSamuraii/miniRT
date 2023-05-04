/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:09:26 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/03 16:53:52 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/includes/libft.h"

// in this function i initialize ambient structure if it was not initialized
// if it was already initialized, i print an error (change to stderr) and exit
bool	reinit_ambient(t_elem *elems, char **params)
{
	char	**colors;

	if (elems->flag_ambient == 0)
	{
		elems->ambient.ratio = ft_atof(params[1]);
		colors = ft_split(params[2], ',');
		elems->ambient.colors = colors_to_percent(colors);
		free_tab(colors);
		return (EXIT_SUCCESS);
	}
	ft_dprintf(2, FRED"Error\n"ERRDEF"\n");
	return (EXIT_FAILURE);
}

// in this function i initialize camera structure if it was not initialized
// if it was already initialized, i print an error (change to stderr) and exit
bool	reinit_camera(t_elem *elems, char **params)
{
	char	**tab;

	if (elems->flag_camera == 0)
	{
		//elems->camera = malloc(sizeof(t_camera));
		tab = ft_split(params[1], ',');
		elems->camera.origin = (t_vec3){ft_atof(tab[0]),
			ft_atof(tab[1]), ft_atof(tab[2])};
		free_tab(tab);
		tab = ft_split(params[2], ',');
		elems->camera.dir = vec3_normalize((t_vec3){ft_atof(tab[0]),
				ft_atof(tab[1]), ft_atof(tab[2])});
		free_tab(tab);
		elems->camera.fov = ft_atof(params[3]);
		return (EXIT_SUCCESS);
	}
	ft_dprintf(2, FRED"Error\n"ERRDEF"\n");
	return (EXIT_FAILURE);
}

// in this function i check every parameter of the line A
// if some parameter outranges or has wrong number of parameters
// this function will exit with failure status
bool	ambient(t_elem *elems, char **params)
{
	int		i;

	printf(YELLOW"CHECKING AMBIENT..."RESET"\n");
	if (invalid_param_number(3, params))
		return (EXIT_FAILURE);
	if (not_valid_parameter(params[1], 0, 1))
		return (EXIT_FAILURE);
	if (not_valid_range(params[2], 0, 255))
		return (EXIT_FAILURE);
	if (reinit_ambient(elems, params))
		return (EXIT_FAILURE);
	i = 0;
	while (params[i])
		printf("[%s] ", params[i++]);
	printf ("\n");
	printf(GREEN"AMBIENT OK!"RESET"\n");
	return (EXIT_SUCCESS);
}

// in this function i check every parameter of the line C
// if some parameter outranges or has wrong number of parameters
// this function will exit with failure status
bool	camera(t_elem *elems, char **params)
{
	int		i;

	printf(YELLOW"CHECKING CAMERA..."RESET"\n");
	if (invalid_param_number(4, params))
		return (EXIT_FAILURE);
	if (not_valid_range(params[1], -DBL_MAX, DBL_MAX))
		return (EXIT_FAILURE);
	if (not_valid_range(params[2], -1, 1))
		return (EXIT_FAILURE);
	if (not_valid_parameter(params[3], 0, 180))
		return (EXIT_FAILURE);
	if (params[3][0] == '0')
		return (printf(FRED"fov cannot be null."RESET"\n"), EXIT_FAILURE);
	if (reinit_camera(elems, params))
		return (EXIT_FAILURE);
	i = 0;
	while (params[i])
		printf("[%s] ", params[i++]);
	printf ("\n");
	printf(GREEN"CAMERA OK!"RESET"\n");
	return (EXIT_SUCCESS);
}

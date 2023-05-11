/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:09 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/11 19:09:13 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"

int	which_type_identifier(char *str)
{
	if (ft_strncmp(str, "A", 2) == 0)
		return (0);
	else if (ft_strncmp(str, "C", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "L", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "sp", 3) == 0)
		return (3);
	else if (ft_strncmp(str, "pl", 3) == 0)
		return (4);
	else if (ft_strncmp(str, "cy", 3) == 0)
		return (5);
	else if (ft_strncmp(str, "co", 3) == 0)
		return (6);
	else if (str == NULL)
		return (7);
	return (-1);
}

void	parse_line(t_elem *elements, char *line)
{
	int			id;
	char		*tmp;
	char		**words;
	static bool	(*funcs[6])(t_elem *, char **) = {ambient, camera, light,
		sphere, plane, cylinder};

	tmp = ft_strtrim(line, '\n');
	words = ft_split(tmp, ' ');
	free(tmp);
	id = which_type_identifier(words[0]);
	if (id == -1)
	{
		ft_dprintf(2, FRED"Error\nInvalid type identifier."RESET"\n");
		error(words, elements);
	}
	if (id != 6 && funcs[id](elements, words) == EXIT_FAILURE)
		error(words, elements);
	free_tab(words);
}

void	elements_init(t_elem *elements)
{
	elements->ambient_initialized = false;
	elements->ambient.colors = (t_vec3){0, 0, 0};
	elements->ambient.ratio = 0;
	elements->camera_initialized = false;
	elements->camera.origin = (t_vec3){0, 0, 0};
	elements->camera.dir = (t_vec3){0, 0, 0};
	elements->camera.fov = 0;
	elements->lights_head = NULL;
	elements->objects_head = NULL;
}

void	parsing(t_elem *elem, int fd)
{
	char		*buff;

	elements_init(elem);
	buff = get_next_line(fd);
	while (buff != NULL)
	{
		parse_line(elem, buff);
		buff = get_next_line(fd);
	}
	if (elem->camera_initialized == false)
	{
		free_structures(elem);
		ft_dprintf(2, FRED"Error\nCamera not initialized."RESET);
		exit(1);
	}
}

int	main(int ac, char *av[])
{
	int		fd;
	t_data	data;
	t_elem	elem;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (perror("Error at opening"), 1);
		parsing(&elem, fd);
		close(fd);
		if (initialize_mlx(&elem, &data) == MLX_ERROR)
			return (free_structures(&elem), 1);
	}
	else
		printf(BWHITE"Second argument required."RESET"\n");
	return (0);
}

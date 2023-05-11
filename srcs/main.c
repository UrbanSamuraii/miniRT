/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:09 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/11 20:20:17 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "proto.h"

static bool	extension_error(char *filename)
{
	int	i;

	i = 0;
	while (filename[i] != '\0')
		i++;
	if (i <= 3 || filename[i - 3] != '.'
		|| filename[i - 2] != 'r' || filename[i - 1] != 't')
	{
		ft_dprintf(2, FRED"Error\nWrong file extension.\n"RESET);
		exit(1);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	int		fd;
	t_data	data;
	t_elem	elem;

	if (ac == 2 && extension_error(av[1]) == EXIT_SUCCESS)
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
		ft_dprintf(2, BWHITE"Second argument required."RESET"\n");
	return (0);
}

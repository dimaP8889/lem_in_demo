/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpogrebn <dpogrebn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:02:22 by dpogrebn          #+#    #+#             */
/*   Updated: 2018/06/14 17:48:32 by dpogrebn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_free_mass(t_room	**mass_room)
{
	int count;

	count = 0;
	while (mass_room[count])
	{
		free(mass_room[count]->name);
		while (mass_room[count]->r_name)
		{
		 	free(mass_room[count]->r_name);
		 	mass_room[count]->r_name = mass_room[count]->r_name->next;
		}
		count++;
	}
	free(mass_room);
}

int		main()
{
	t_room	**mass_room;
	int		fd;
	int		ants;

	fd = open("src/read", O_RDONLY);
	ants = ft_check_num(fd);
	mass_room = ft_valid(fd);
	ft_move_ants(ants, mass_room);
	//ft_free_room(room);
	ft_free_mass(mass_room);
	system("leaks lem-in");
	//ft_print_room(in->rooms);
}
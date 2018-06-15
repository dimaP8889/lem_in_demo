/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitriy1 <dmitriy1@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:02:22 by dpogrebn          #+#    #+#             */
/*   Updated: 2018/06/15 02:23:50 by dmitriy1         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_free_mass(t_room	**mass_room)
{
	int count;
	t_name	*name;

	count = 0;
	while (mass_room[count])
	{
		while (mass_room[count]->r_name)
		{
			//ft_printf("%s\n", mass_room[count]->name);
			name = mass_room[count]->r_name;
		 	mass_room[count]->r_name = mass_room[count]->r_name->next;
		 	free(name);
		}
		free(mass_room[count]->name);
		free(mass_room[count]->next_room);
		free(mass_room[count]);
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
	ants = ft_check_num(0);
	mass_room = ft_valid(0);
	ft_move_ants(ants, mass_room);
	ft_free_mass(mass_room);
	system("leaks lem-in");
	//ft_print_room(in->rooms);
}
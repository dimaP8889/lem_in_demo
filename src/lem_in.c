/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitriy1 <dmitriy1@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:02:22 by dpogrebn          #+#    #+#             */
/*   Updated: 2018/06/14 03:59:46 by dmitriy1         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main()
{
	t_room	*room;
	t_room	**mass_room;
	int		fd;
	int		ants;

	room = (t_room *)malloc(sizeof(t_room));
	fd = open("src/read", O_RDONLY);
	ants = ft_check_num(fd);
	mass_room = ft_valid(room, fd);
	//ft_print_room(in->rooms);
	ft_move_ants(ants, mass_room);
	//ft_print_room(in->rooms);
}
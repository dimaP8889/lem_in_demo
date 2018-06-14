/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_way.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitriy1 <dmitriy1@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:40:23 by dpogrebn          #+#    #+#             */
/*   Updated: 2018/06/14 01:51:45 by dmitriy1         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_find_next_link(t_name *room, t_room **mass_rooms, int len)
{
	int		count;

	count = 0;
	while (room)
	{
		if (mass_rooms[room->num]->length_bk < len)
		{
			len = mass_rooms[room->num]->length_bk;
			count = room->num;
		}
		room = room->next;
	}
	return (count);
}

void	ft_make_way(t_room **mass_rooms)
{
	int		count;
	int		len;

	count = ft_find_start(mass_rooms);
	len = mass_rooms[count]->length_bk;
	mass_rooms[count]->left_way = 1;
	while (!mass_rooms[count]->fin)
	{
		//ft_printf("%s\n", mass_rooms[count]->name);
		count = ft_find_next_link(mass_rooms[count]->r_name, mass_rooms, len);
		mass_rooms[count]->left_way = 1;
		len--;
		if (len < 0)
			ft_exit();
	}
}
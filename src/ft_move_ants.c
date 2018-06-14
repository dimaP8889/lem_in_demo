/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitriy1 <dmitriy1@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 12:31:09 by dmitriy1          #+#    #+#             */
/*   Updated: 2018/06/14 10:38:02 by dmitriy1         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ants 	*ft_make_ant(t_ants *ant, char *name)
{
	t_ants *ant_cp;
	static int	ct;

	if (!ct)
		ct = 2;
	ant_cp = ant;
	while (ant->next)
	{
		ant = ant->next;
	}
	ant->next = (t_ants *)malloc(sizeof(t_ants));
	ant->next->name = name;
	ant->next->num = ct;
	ct++;
	ant->next->next = NULL;
	return (ant_cp);
}

t_ants 	*ft_make_new(t_ants *ant, char *name)
{
	ant = (t_ants *)malloc(sizeof(t_ants));
	ant->name = name;
	ant->num = 1;
	ant->next = NULL;
	return (ant);
}

t_ants 	*ft_print_ants(t_ants *ants_cp, char *finish)
{
	t_ants	*ants;

	ants = ants_cp;
	if (ants && !ft_strcmp(ants->name, finish))
	{
		ft_printf("L%i-", ants->num);
		ft_printf("%s ", ants->name);
		ants_cp = ants_cp->next;
		ants = ants->next;
	}
	while (ants)
	{
		ft_printf("L%i-", ants->num);
		ft_printf("%s ", ants->name);
		ants = ants->next;
	}
	ft_printf("\n");
	return (ants_cp);
}

void	ft_change_room(t_ants *ants, char *src, char *dst)
{
	while (ants)
	{
		if (!ft_strcmp(ants->name, src))
		{
			ants->name = dst;
			return;
		}
		ants = ants->next;
	}
}

int		ft_find_next(t_name *room, t_room **mass_rooms, int count)
{
	int		num;
	num = 0;

	while (room)
	{
		if (mass_rooms[room->num]->left_way 
		&& mass_rooms[room->num]->length_bk < mass_rooms[count]->length_bk)
		{
			num = room->num;
		}
		room = room->next;
	}
	return (num);
}

int		ft_find_next_bk(t_name *room, t_room **mass_rooms, int count)
{
	int		num;
	num = 0;

	while (room)
	{
		if (mass_rooms[room->num]->left_way 
		&& mass_rooms[room->num]->length_bk > mass_rooms[count]->length_bk)
		{
			num = room->num;
		}
		room = room->next;
	}
	return (num);
}

int		ft_find_last(t_room **mass_rooms, int count)
{
	while (mass_rooms[count]->free && !mass_rooms[count]->start)
	{
		count = ft_find_next_bk(mass_rooms[count]->r_name, mass_rooms, count);
	}
	return (count);
}

int			ft_untill_start(t_room **mass_rooms, int count, int in, t_ants *ant)
{
	int		next;
	int		finish;

	finish = ft_find_finish(mass_rooms);
	if (!mass_rooms[count]->free && !mass_rooms[count]->fin)
	{
		mass_rooms[count]->free = 1;
		next = ft_find_next(mass_rooms[count]->r_name, mass_rooms, count);
		ft_change_room(ant, mass_rooms[count]->name, mass_rooms[next]->name);
		count = ft_find_next_bk(mass_rooms[count]->r_name, mass_rooms, count);
		if (mass_rooms[next]->fin)
			mass_rooms[next]->ants++;
		else
			mass_rooms[next]->free = 0;
	}
	else
	{
		if (in == 1)
			mass_rooms[finish]->ants++;
		count = ft_find_next_bk(mass_rooms[count]->r_name, mass_rooms, count);
	}
	return (count);
}

t_ants 		*ft_start(t_room **mass_rooms, int count, int in, t_ants *ant)
{
	int start;
	int	finish;

	start = ft_find_start(mass_rooms);
	finish = ft_find_finish(mass_rooms);
	count = ft_find_next(mass_rooms[count]->r_name, mass_rooms, count);
	mass_rooms[count]->free = 0;
	mass_rooms[start]->ants--;
	if (!in)
		mass_rooms[finish]->ants++;
	if (mass_rooms[start]->ants >= 0)
	{
		if (!ant)
			ant = ft_make_new(ant, mass_rooms[count]->name);
		else
			ant = ft_make_ant(ant, mass_rooms[count]->name);
	}
	return (ant);
}

t_ants *ft_move(t_room **mass_rooms, int finish, t_ants *ant, int moves)
{
	int		count;
	int		start;
	int		in;

	in = moves;
	start = ft_find_start(mass_rooms);
	count = finish;
	while (moves)
	{
		count = ft_untill_start(mass_rooms, count, in, ant);
		moves--;
	}
	if (!moves)
	{
		ant = ft_start(mass_rooms, count, in, ant);
	}
	return (ant);
}

void	ft_move_ants(int ants, t_room **mass_rooms)
{
	int		start;
	int		fin;
	t_ants *ant;
	int		moves;

	ant = NULL;
	start = ft_find_start(mass_rooms);
	fin = ft_find_finish(mass_rooms);
	moves = mass_rooms[start]->length_bk;
	mass_rooms[start]->ants = ants;
	while (mass_rooms[fin]->ants < ants)
	{
		ant = ft_move(mass_rooms, fin, ant, moves);
		ant = ft_print_ants(ant, mass_rooms[fin]->name);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitriy1 <dmitriy1@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 12:31:09 by dmitriy1          #+#    #+#             */
/*   Updated: 2018/06/13 14:21:44 by dmitriy1         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ants 	*ft_make_next_ant(char *name, int num, t_ants *ant)
{
	t_ants *ant_cp;

	ant_cp = ant;
	while (ant->next)
		ant = ant->next;
	ant->next = (t_ants *)malloc(sizeof(t_ants));
	ant->next->name = name;
	ant->next->num = num;
	ant->next->next = NULL;
	return (ant_cp);
}

void		ft_null_move(t_room **mass_rooms)
{
	int		count;

	count = 0;
	while (mass_rooms[count])
	{
		mass_rooms[count]->move = 0;
		count++;
	}
}

t_ants 	*ft_make_ant(char *name, int num)
{
	t_ants *ant;

	ant = (t_ants *)malloc(sizeof(t_ants));
	ant->name = name;
	ant->num = num;
	ant->change = 0;
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
		if (ants->next && !ft_strcmp(ants->next->name, finish))
		{
			ft_printf("L%i-", ants->next->num);
			ft_printf("%s ", ants->next->name);
			if (ants->next->next)
				ants->next = ants->next->next;
			else
				ants->next = NULL;
		}
		ants = ants->next;
	}
	ft_printf("\n");
	return (ants_cp);
}

int		ft_find_free(t_name *room, t_room **mass_rooms, int len)
{
	//(void)len;
	while (room)
	{
		// ft_printf("name :%s\n", mass_rooms[room->num]->name);
		// ft_printf("left :%i\n", mass_rooms[room->num]->left_way);
		// ft_printf("num :%i\n", num);
		// ft_printf("free :%i\n", mass_rooms[room->num]->free);
		// ft_printf("start :%i\n", mass_rooms[room->num]->start);
		// ft_printf("\n");
		if (mass_rooms[room->num]->fin)
			return (room->num);
		if (mass_rooms[room->num]->free && !mass_rooms[room->num]->start 
		&& mass_rooms[room->num]->length_bk > len)
			return (room->num);
		room = room->next;
	}
	//ft_printf("ret -1 :\n");
	return (-1);
}

void	ft_change_room(t_ants *ants, char *dst, char *src)
{
	// ft_printf("src :%s\n", src);
	// ft_printf("dst :%s\n", dst);
	while (ants)
	{
		//ft_printf("name %s\n", ants->name);
		if (!ft_strcmp(ants->name, src))
		{
			ants->name = dst;
			//ft_printf("name_dst %s\n", ants->name);
			//ft_printf("name_src %s\n", src);
			return;
		}
		ants = ants->next;
	}
	//ft_printf("\n");
}

void	ft_check_near(t_room **mass_rooms, int num, t_ants *ants_cp)
{
	int		count;
	int		cnt;
	int		next_num;
	t_ants	*ants;
	cnt = 1;

	ants = ants_cp;
	count = 0;
	while (mass_rooms[count])
	{
			if (mass_rooms[count]->length_bk == num)
			{
				if (!mass_rooms[count]->free)
				{
					cnt =  mass_rooms[count]->left_way;
					next_num = ft_find_free(mass_rooms[count]->r_name, mass_rooms, num);
					if (next_num != -1 && !mass_rooms[count]->move)
					{
						mass_rooms[next_num]->free = 0;
						ft_change_room(ants, mass_rooms[next_num]->name, mass_rooms[count]->name);
						mass_rooms[next_num]->move = 1;
						if (mass_rooms[next_num]->fin)
						{
							mass_rooms[next_num]->ants++;
							mass_rooms[next_num]->free = 1;
						}
						mass_rooms[count]->free = 1;
					}
				}
			}
		count++;
	}
}


t_ants 	*ft_start(t_name *room, t_room **mass_rooms, int start, t_ants *ants)
{
	static	int	ant;

	if (!ant)
		ant = 1;
	while (room && mass_rooms[start]->ants)
	{
		if (mass_rooms[room->num]->free)
		{
			if (!ants)
				ants = ft_make_ant(mass_rooms[room->num]->name, ant);
			else
				ants = ft_make_next_ant(mass_rooms[room->num]->name, ant, ants);
			mass_rooms[start]->ants--;
			mass_rooms[room->num]->free = 0;
			ant++;
		}
		room = room->next;
	}
	return (ants);
}

t_ants 	*ft_one_move(t_room **mass_rooms, int start, int moves, t_ants *ants)
{
	while (moves)
	{
		ft_check_near(mass_rooms, moves, ants);
		moves--;
	}
	if (!moves)
	{
		ants = ft_start(mass_rooms[start]->r_name, mass_rooms, start, ants);
	}
	return (ants);
}

void	ft_move_ants(int ants, t_room **mass_rooms)
{
	int		start;
	int		finish;
	int		moves;
	t_ants	*ant;

	moves = 0;
	finish = ft_find_finish(mass_rooms);
	start = ft_find_start(mass_rooms);
	mass_rooms[start]->ants = ants;
	while (mass_rooms[finish]->ants < ants)
	{
		if (moves > mass_rooms[finish]->length_bk)
			moves = mass_rooms[finish]->length_bk;
		ant = ft_one_move(mass_rooms, start, moves, ant);
		ft_null_move(mass_rooms);
		ant = ft_print_ants(ant, mass_rooms[finish]->name);
		moves++;
	}
	// while (ants)
	// ft_move(mass_rooms);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitriy1 <dmitriy1@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:15:40 by dpogrebn          #+#    #+#             */
/*   Updated: 2018/06/14 13:53:46 by dmitriy1         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_exit()
{
	ft_printf("ERROR\n");
	exit(1);
}

void	ft_comment(char **str, int fd, t_room *room)
{
	static int	start;
	static int	fin;

	while (*str[0] == '#' && (ft_strcmp(*str, "##start")) 
	&& (ft_strcmp(*str, "##end")))
	{
		free(*str);
		get_next_line(fd, str);
	}
	if (!ft_strcmp(*str, "##start"))
	{
		start++;
		(room)->start = 1;
		free(*str);
		get_next_line(fd, str);
	}
	else
		(room)->start = 0;
	if (!ft_strcmp(*str, "##end"))
	{
		fin++;
		free(*str);
		(room)->fin = 1;
		get_next_line(fd, str);
	}
	else
		(room)->fin = 0;
	if (start > 1|| fin > 1)
	{
		ft_exit();
	}
	*str[0] == '#' ? ft_comment(str, fd, (room)) : *str[0] == '#';
}

int		ft_mass_len(char **mass)
{
	int		len;

	len = 0;
	while (mass[len])
		len++;
	return (len);
}


void	ft_check_digit(char *str)
{
	int	num;

	num = 0;
	while (str[num])
	{
		if (!ft_isdigit(str[num]))
			ft_exit();
		num++;
	}
}

void	ft_check_name(char *str)
{
	if (str[0] == 'L' || ft_strstr(str, "-"))
	{
		ft_exit();
	}
}

void		ft_valid_room(char **str, int fd, t_room *room)
{
	char	**params;
	int		count;

	count = 0;
	room->fin = 0;
	room->start = 0;
	if (*str[0] == '#')
		ft_comment(str, fd, room);
	params = ft_strsplit(*str, ' ');
	if (ft_mass_len(params) != 3 || !ft_strlen(*str))
		ft_exit();
	ft_check_name(params[0]);
	room->name = ft_strdup(params[0]);
	ft_check_digit(params[1]);
	ft_check_digit(params[2]);
	room->x = ft_atoi(params[1]);
	room->y = ft_atoi(params[2]);
	//system("leaks lem-in");
	while (params[count])
	{
		free(params[count]);
		count++;
	}
	free(params);
	//system("leaks lem-in");
}


t_room	*ft_find_end(char **str, int fd, t_room *room)
{

	//system("leaks lem-in");
	ft_valid_room(str, fd, room);
	free(*str);
	//system("leaks lem-in");
	room->next_room = (t_room *)malloc(sizeof(t_room));
	room = room->next_room;
	get_next_line(fd, str);
	return (room);

}

t_room	*ft_check_rooms(t_room *room, int fd, char **str)
{
	t_room 	*rooms;

	room = (t_room *)malloc(sizeof(t_room));
	rooms = room;
	get_next_line(fd, str);
	while (!ft_strstr(*str, "-"))
	{
		//free(*str);
		room = ft_find_end(str, fd, room);
	}
	room->next_room = NULL;
	return (rooms);
}

int		ft_count_links(t_room *rooms)
{
	int		count;

	count = 0;
	while (rooms)
	{
		rooms = rooms->next_room;
		count++;
	}
	return (count);
}

int	ft_check_num(int fd)
{
	char	*str;
	int		ants;

	ants = 0;
	get_next_line(fd, &str);
	while (str[0] == '#' && (ft_strcmp(str, "##start")) 
	&& (ft_strcmp(str, "##end")))
	{
		free(str);
		get_next_line(fd, &str);
	}
	ants = ft_atoi(str);
	ft_check_digit(str);
	if (!ants)
		ft_exit();
	free(str);
	return (ants);
}

void			ft_check_same_coord(t_room *room, t_room **mass_rooms, int coord)
{
	int		count;

	count = 0;
	while (mass_rooms[count])
	{
		if ((room->x == mass_rooms[count]->x && room->y == mass_rooms[count]->y) 
		|| !ft_strcmp(room->name, mass_rooms[count]->name))
			if (count != coord)
				ft_exit();
		count++;
	}
}

void			ft_check_rights(t_room **mass_rooms)
{
	int		count;

	count = 0;
	while (mass_rooms[count])
	{
		ft_check_same_coord(mass_rooms[count], mass_rooms, count);
		count++;
	}
}

t_room			**ft_set_params(t_room **mass_rooms)
{
	int		coun;

	coun = 0;
	while (mass_rooms[coun])
	{
		mass_rooms[coun]->r_name = NULL;
		mass_rooms[coun]->next_room = NULL;
		mass_rooms[coun]->free = 1;
		mass_rooms[coun]->ants = 0;
		mass_rooms[coun]->left_way = 0;
		mass_rooms[coun]->use_bk = 0;
		mass_rooms[coun]->length_bk = 0;
		coun++;
	}
	return (mass_rooms);
}

void	ft_free_room(t_room	*room)
{
	while (room)
	{
		free(room->name);
		free(room);
		room = room->next_room;
	}
}

t_room			**ft_valid(int fd)
{
	t_room	**mass_rooms;
	t_room	*in;
	int		coun;
	char	*str;

	in = (t_room *)malloc(sizeof(t_room));
	str = NULL;
	coun = 0;
	in = ft_check_rooms(in, fd, &str);
	mass_rooms = (t_room **)malloc(sizeof(t_room *) * ft_count_links(in));
	while (in->next_room)
	{
		mass_rooms[coun] = (t_room *)malloc(sizeof(t_room));
		mass_rooms[coun]->name = ft_strdup(in->name);
		mass_rooms[coun]->x = in->x;
		mass_rooms[coun]->y = in->y;
		mass_rooms[coun]->start = in->start;
		mass_rooms[coun]->fin = in->fin;
		free(in->name);
		free(in);
		in = in->next_room;
		coun++;
	}
	mass_rooms[coun] = NULL;
	mass_rooms = ft_set_params(mass_rooms);
	ft_check_rights(mass_rooms);
	ft_make_links(mass_rooms, fd, str);
	return (mass_rooms);
}
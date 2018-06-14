/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitriy1 <dmitriy1@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 13:31:24 by dmitriy1          #+#    #+#             */
/*   Updated: 2018/06/14 03:45:44 by dmitriy1         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_check_valid_link(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '-')
	{
		i++;
		if (!str[i])
			ft_exit();
	}
	i++;
	while (str[i])
	{
		if (str[i] == '-')
			ft_exit();
		i++;
	}
}

char	*ft_find_first(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != '-')
		i++;
	ret = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] != '-')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_find_second(char *str)
{
	char	*ret;

	ret = ft_strchr(str, '-');
	ret++;
	return (ret);
}

int		ft_find_cont(char *name, t_room **mass_rooms)
{
	int	count;

	count = 0;
	while (ft_strcmp(name, mass_rooms[count]->name))
	{
		if (!mass_rooms[count])
			ft_exit();
		count++;
	}
	return (count);
}

void	ft_check_right_name(char *f, t_room **mass_rooms)
{
	int		count;

	count = 0;
	while (mass_rooms[count])
	{
		if (!ft_strcmp(mass_rooms[count]->name, f))
			return;
		count++;
	}
	ft_exit();
}

void	ft_linked(t_links *links, char *str, t_room **mass_rooms)
{
	char	*f_name;
	char	*s_name;

	f_name = ft_find_first(str);
	s_name = ft_find_second(str);
	links->f_name = ft_strdup(f_name);
	links->s_name = ft_strdup(s_name);
	ft_check_right_name(links->f_name, mass_rooms);
	ft_check_right_name(links->s_name, mass_rooms);
}

void	ft_make_links(t_room **mass_rooms, int fd, char *str)
{
	int 	end;
	t_links	*links;
	t_links	*links_cp;
	t_room **mass_rooms_cp;
	int		num_rooms;

	num_rooms = 0;
	end = 1;
	mass_rooms_cp = mass_rooms;
	links = (t_links *)malloc(sizeof(t_links));
	links_cp = links;
	while (end)
	{
		ft_check_valid_link(str);
		if (str[0] == '#')
			ft_comment(&str, fd, mass_rooms[0]);
		ft_linked(links, str, mass_rooms);
		end = get_next_line(fd, &str);
		num_rooms++;
		if (end)
		{
			links->next = (t_links *)malloc(sizeof(t_links));
			links = links->next;
		}
	}
	links->next = NULL;
	ft_make_graph(mass_rooms_cp, links_cp);
	ft_put_len(mass_rooms_cp);
	ft_make_way(mass_rooms_cp);
}

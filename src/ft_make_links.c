/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpogrebn <dpogrebn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 13:31:24 by dmitriy1          #+#    #+#             */
/*   Updated: 2018/06/14 22:47:56 by dpogrebn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	free(f_name);
}

void	ft_free_links(t_links	*links)
{
	while (links)
	{
		free(links->f_name);
		free(links->s_name);
		free(links);
		links = links->next;
	}
}

void	ft_malloc_link(int end, t_links	**links, char *str)
{
	if (end && str[0] != '#' )
	{
		(*links)->next = (t_links *)malloc(sizeof(t_links));
		*links = (*links)->next;
	}
}

int	ft_lose(char **str, int fd)
{
	int		end;

	end = 0;
	while (*str[0] == '#')
	{
		free(*str);
		end = get_next_line(fd, str);
	}
	return (end);
}

void	ft_make_links(t_room **mass_rooms, int fd, char *str)
{
	int 	end;
	t_links	*links;
	t_links	*links_cp;
	t_room **mass_rooms_cp;

	end = 1;
	mass_rooms_cp = mass_rooms;
	links = (t_links *)malloc(sizeof(t_links));
	links_cp = links;
	while (end)
	{
		if (str[0] == '#')
			end = ft_lose(&str, fd);
		if (!end)
			break ;
		ft_check_valid_link(str);
		ft_linked(links, str, mass_rooms);
		free(str);
		end = get_next_line(fd, &str);
		ft_malloc_link(end, &links, str);
	}
	links->next = NULL;
	ft_make_graph(mass_rooms_cp, links_cp);
	ft_free_links(links_cp);
	ft_put_len(mass_rooms_cp);
	ft_make_way(mass_rooms_cp);
}

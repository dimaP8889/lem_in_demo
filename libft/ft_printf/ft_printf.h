/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpogrebn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 21:10:55 by dpogrebn          #+#    #+#             */
/*   Updated: 2018/02/20 21:10:57 by dpogrebn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../includes/libft.h"
# include <stdarg.h>
# include <stdlib.h>

# define CONVERS "sSpdDioOuUxXcC%"
# define FLAGS "#0-+ "
# define SIZES "hhlljz"

typedef struct			s_printf
{
	int					width;
	char				*width_char;
	int					precision;
	char				*precision_char;
	char				*flag;
	char				*size;
	char				*convers;
	char				*print;
	int					found_perc;
	char				*out;
	char				*out_num;
	int					base;
	char				*string;
	int					check_num;
	int					return_val;
	int					check_zero;
	int					move;
	int					tihs;
	int					this_is_funny_o_sharp;
	int					str_lenght;
	struct s_printf		*next;
}						t_printf;

typedef struct			s_flags_num
{
	int					sharp_xh;
	int					sharp_x;
	int					sharp_o;
	int					sharp_p;
	int					count_x;
	int					plus;
	int					space;
	int					zero;
	int					minus;
}						t_flags_num;

typedef struct			s_size
{
	signed char			hh;
	unsigned char		u_hh;
	short				h;
	unsigned short		u_h;
	int					i;
	unsigned int		u_i;
	long				l;
	unsigned long		u_l;
	long long			ll;
	unsigned long long	u_ll;
	intmax_t			j;
	uintmax_t			u_j;
	size_t				u_z;
	ssize_t				z;
}						t_size;

int						ft_printf(const char *string, ...);
void					ft_find_params(const char *string, t_printf *params);
void					ft_converse(t_printf *params, void *string);
char					*ft_strjoin_free(char **s1, char const *s2);
char					*ft_itoa_base(size_t index, int base, int hex);
void					ft_make_flag(t_printf *params);
void					ft_check_size_l(t_printf *param,
t_size *size, void *number);
void					ft_check_size_h(t_printf *params,
t_size *size, void *number);
void					ft_check_size_hh(t_printf *param,
t_size *size, void *number);
void					ft_check_size_ll(t_printf *params,
t_size *size, void *number);
void					ft_check_size_j(t_printf *param,
t_size *size, void *number);
void					ft_check_size_z(t_printf *param,
t_size *size, void *number);
void					ft_make_out(t_printf *params);
void					ft_check_no_size(t_printf *params,
t_size *size, void *number);
void					ft_check_size(t_printf *p, t_size *size, void *number);
void					ft_print_num(t_printf *params);
void					ft_make_unicode_char(t_printf *params,
unsigned int symb);
void					ft_pars(const char **string, t_printf *params);
void					ft_find_convers(const char **string, t_printf *params);
void					ft_choose_size(int max, t_printf *params);
int						check_size_base(const char *string);
void					ft_no_converse(t_printf *params);
void					ft_s_converse_string(t_printf *params,
void *string, int count_prec);
void					ft_l_converse_string(t_printf *params,
void *string, int count_prec);
void					ft_cut_str(t_printf *params, int count_prec);
int						ft_find_base(t_printf *params);
void					ft_add_letter(t_printf *params, t_flags_num *flag);
void					ft_flag_minus(t_printf *params, t_flags_num *flag);
void					ft_finish_flags(t_printf *params, t_flags_num *flag);
void					ft_set_flags(t_flags_num *flag);

#endif

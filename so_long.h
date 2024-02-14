/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:48:00 by mhromylo          #+#    #+#             */
/*   Updated: 2024/02/14 09:51:26 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define MLX_ERROR 1

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include "./libft/ft_printf.h"

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	char	**map;
	int		map_width;
	int		map_height;
	int		collectibles;
	int		movements;
	int		fd;
	void	*hero;
	void	*item;
	void	*floor;
	void	*wall;
	void	*exit;
	int		counthero;
	int		countexit;

}				t_game;

void	draw_all(t_game *game);
int		read_map(t_game *game, char **argv);
void	check_walls(t_game *game);
void	map_valid(t_game *game);
void	set_world(t_game *game);
int		key_hook(int keycode, t_game *game);
int		finish(t_game *game);
void	walls_check(t_game *game);
int		width_map(char *str);
void	is_valid_path(int a, int b, int y, int z, t_game *game);
void	cleen_img(t_game *game);
void	free_map(t_game *game);

#endif

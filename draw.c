/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:08:10 by mhromylo          #+#    #+#             */
/*   Updated: 2024/02/14 10:44:30 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_player(t_game *game, int y, int x)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->hero,
		x * 48, y * 48);
	game->player_x = x;
	game->player_y = y;
}

static void	set_item(t_game *game, int y, int x)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->item,
		x * 48, y * 48);
	game->collectibles++;
}

static void	set_exit(t_game *game, int y, int x)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->exit,
		x * 48, y * 48);
	game->exit_x = x;
	game->exit_y = y;
}

void	set_world(t_game *game)
{
	int	i;
	int	j;

	game->floor = mlx_xpm_file_to_image(game->mlx_ptr, "images/floor.xpm",
			&i, &j);
	game->wall = mlx_xpm_file_to_image(game->mlx_ptr, "images/walls.xpm",
			&i, &j);
	game->hero = mlx_xpm_file_to_image(game->mlx_ptr, "images/player.xpm",
			&i, &j);
	game->exit = mlx_xpm_file_to_image(game->mlx_ptr, "images/exit.xpm",
			&i, &j);
	game->item = mlx_xpm_file_to_image(game->mlx_ptr, "images/collect.xpm",
			&i, &j);
}

void	draw_all(t_game *game)
{
	int	row;
	int	column;

	game->collectibles = 0;
	row = 0;
	while (row < game->map_height)
	{
		column = 0;
		while (game->map[row][column])
		{
			if (game->map[row][column] == '1')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
					game->wall, column * 48, row * 48);
			if (game->map[row][column] == 'C')
				set_item(game, row, column);
			if (game->map[row][column] == 'P')
				set_player(game, row, column);
			if (game->map[row][column] == 'E')
				set_exit(game, row, column);
			if (game->map[row][column] == '0')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
					game->floor, column * 48, row * 48);
			column++;
		}
		row++;
	}
}

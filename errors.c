/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:04:48 by mhromylo          #+#    #+#             */
/*   Updated: 2024/02/14 10:31:32 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleen_img(t_game *game)
{
	if (game->floor)
		mlx_destroy_image(game->mlx_ptr, game->floor);
	if (game->wall)
		mlx_destroy_image(game->mlx_ptr, game->wall);
	if (game->hero)
		mlx_destroy_image(game->mlx_ptr, game->hero);
	if (game->exit)
		mlx_destroy_image(game->mlx_ptr, game->exit);
	if (game->item)
		mlx_destroy_image(game->mlx_ptr, game->item);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map != NULL)
	{
		int i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			game->map[i] = NULL;
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}

int	finish(t_game *game)
{
	cleen_img(game);
	free_map(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
}

void	walls_check(t_game *game)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i++ <= game->map_width - 3)
	{
		if (game->map[0][i] != '1' || game->map[game->map_height - 1][i] != '1')
		{
			ft_printf("Error\n map must be closed/surrounded by walls");
			finish(game);
		}
	}
	while (j++ < game->map_height - 1)
	{
		if (game->map[j][0] != '1' || game->map[j][i] != '1')
		{
			ft_printf("Error\n map must be closed/surrounded by walls");
			finish(game);
		}
	}
}

static void	map_checker(t_game *game, int x, int y)
{
	if (game->map[x][y] != '1' && game->map[x][y] != '0' && game->map[x][y] != 'P' &&
	game->map[x][y] != 'E' && game->map[x][y] != 'C' && game->map[x][y] != '\n')
	{
		ft_printf("Error\n map is not valid");
		finish(game);
	}
	if (game->map[x][y] == 'C')
		game->collectibles++;
	if (game->map[x][y] == 'P')
	{
		game->counthero++;
		game->player_x = x;
		game->player_y = y;
	}
	if (game->map[x][y] == 'E')
	{
		game->countexit++;
		game->exit_x = x;
		game->exit_y = y;
	}
}

void	map_valid(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y <= game->map_height - 1)
	{
		x = 0;
		while (x <= game->map_width)
		{
			map_checker(game, y, x);
			x++;
		}
		if (width_map(game->map[0]) != game->map_width)
		{
			ft_printf("Error\n Map is not rectangular");
			finish(game);
		}
		y++;
	}
	if (!(game->counthero == 1 && game->countexit == 1 && game->collectibles > 0))
	{
		ft_printf("Error\n The map must contain 1 exit, at least 1 collectible, and 1 player to be valid.");
		finish(game);
	}
}

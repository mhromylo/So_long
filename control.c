/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:40:29 by mhromylo          #+#    #+#             */
/*   Updated: 2024/02/14 10:37:00 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	move_valid(t_game *game, int i, int j)
{
	if (game->map[j][i] == 'E')
	{
		if (game->collectibles != 0)
			return (0);
		ft_printf("You win!\n");
		finish(game);
	}
	if (game->map[j][i] == '0')
	{
		game->map[j][i] = 'P';
		game->player_x = i;
		game->player_y = j;
		game->movements++;
	}
	if (game->map[j][i] == 'C')
	{
		game->map[j][i] = 'P';
		game->player_x = i;
		game->player_y = j;
		game->movements++;
		game->collectibles--;
	}
	return (1);
}

static int	buttons_w_s(t_game *game, int keycode)
{
	int	i;
	int	j;

	i = game->player_x;
	j = game->player_y;
	if (keycode == 13)
	{
		j--;
		if (game->map[j][i] == '1')
			return (0);
		if (!move_valid(game, i, j))
			return (0);
		game->map[j + 1][i] = '0';
	}
	else if (keycode == 1)
	{
		j++;
		if (game->map[j][i] == '1')
			return (0);
		if (!move_valid(game, i, j))
			return (0);
		game->map[j - 1][i] = '0';
	}
	ft_printf("Moves: %d\n", game->movements);
	ft_printf("Moves: %d\n", game->collectibles);
	return (1);
}

static int	buttons_a_d(t_game *game, int keycode)
{
	int	i;
	int	j;

	i = game->player_x;
	j = game->player_y;
	if (keycode == 0)
	{
		i--;
		if (game->map[j][i] == '1')
			return (0);
		if (!move_valid(game, i, j))
			return (0);
		game->map[j][i + 1] = '0';
	}
	if (keycode == 2)
	{
		i++;
		if (game->map[j][i] == '1')
			return (0);
		if (!move_valid(game, i, j))
			return (0);
		game->map[j][i - 1] = '0';
	}
	ft_printf("Moves: %d\n", game->movements);
	ft_printf("Moves: %d\n", game->collectibles);
	return (1);
}

int	key_hook(int keycode, t_game *game)
{
	int	valid;

	if (keycode == 53)
		finish(game);
	if (keycode == 13)
		valid = buttons_w_s(game, keycode);
	if (keycode == 1)
		valid = buttons_w_s(game, keycode);
	if (keycode == 0)
		valid = buttons_a_d(game, keycode);
	if (keycode == 2)
		valid = buttons_a_d(game, keycode);
	if (valid)
		draw_all(game);
	return (1);
}

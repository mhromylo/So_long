/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:44:45 by mhromylo          #+#    #+#             */
/*   Updated: 2024/02/14 09:57:53 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
		return (0);
	ft_memset(&game, 0, sizeof(t_game));
	read_map(&game, argv);
	walls_check(&game);
	map_valid(&game);
	is_valid_path(game.player_x, game.player_y, game.exit_x, game.exit_y, &game);
	free_map(&game);
	read_map(&game, argv);
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, (game.map_width * 48), (game.map_height * 48), "So_long");
	set_world(&game);
	draw_all(&game);
	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_hook(game.win_ptr, 17, 0, (void *)exit, 0);
	mlx_loop(game.mlx_ptr);
}


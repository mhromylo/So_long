/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:50:21 by mhromylo          #+#    #+#             */
/*   Updated: 2024/02/14 09:53:37 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	width_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] == '\n')
		i--;
	return (i);
}

static int	add_line(t_game *game, char *line)
{
	char	**temp;
	int		i;

	if (!line)
		return (0);
	i = 0;
	game->map_height++;
	temp = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!temp)
		return (0);
	temp[game->map_height] = NULL;
	while (i < game->map_height - 1)
	{
		temp[i] = game->map[i];
		i++;
	}
	temp[i] = line;
	if (game->map)
		free(game->map);
	game->map = temp;
	return(1);
}

int	read_map(t_game *game, char **argv)
{
	char	*mapread;

	game->fd = open(argv[1], O_RDONLY);
	if (game->fd < 0)
	{
		ft_printf("Error\n Can't read the file");
		finish(game);
		return (0);
	}
	while (1)
	{
		mapread = get_next_line(game->fd);
		if (!add_line(game, mapread))
			break ;
	}
	close (game->fd);
	game->map_width = width_map(game->map[0]);
	return (1);
}

static void	dfs(int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || game->map[x][y] == '1' || game->map[x][y] == 'W')
		return ;
	game->map[x][y] = 'W';
	dfs((x + 1), y, game);
	dfs((x - 1), y, game);
	dfs(x, (y + 1), game);
	dfs(x, (y - 1), game);
}

void	is_valid_path(int a, int b, int y, int z, t_game *game)
{
	dfs(a, b, game);
	if (game->map[y][z] != 'W')
	{
		ft_printf("Error\n The map must contain a valid path.");
		finish(game);
	}
	game->map_height = 0;
}

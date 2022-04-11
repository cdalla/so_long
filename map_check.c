/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/19 10:18:25 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/04/08 13:38:25 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// check map input
// The map can be composed of only these 5 characters:
// 0 for an empty space,
// 1 for a wall,
// C for a collectible,
// E for a map exit,
// P for the player’s starting position.

// The map must contain at least 1 exit, 1 collectible, and 1 starting position.
// • The map must be rectangular.
// • The map must be closed/surrounded by walls.

// - get map size
// - copy map in array
// - check map content
//     -walls (first line, last line, first column, last column)

// check borders
//     check line length
//     check char values inside
//     read array line by line , check values (add a counter for collectible)
//     read first and last line and check everything is 1
//     read first and last column and check that everything is 1
//     2 funtion
//      - double loop checking borders
//      - parse line by line, check length first, 
//		reading every line check valid values

#include "game.h"

int	check_cell(t_game *game, int i);

int	read_map(char *mapname, t_game *game)
{
	if (get_map_size (mapname, game) == 1 || save_map(mapname, game) == 1)
	{
		free_map(game);
		return (1);
	}
	if (check_line(game, 0) == 1 || check_borders(game) == 1)
	{
		free_map(game);
		return (1);
	}
	return (0);
}

int	save_map(char *mapname, t_game *game)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(mapname, O_RDONLY);
	if (fd < 1)
		return (1);
	game->map.map_text = (char **)malloc((game->map.height + 1)
			* sizeof(char*));
	if (!game->map.map_text)
		return (1);
	while (i < game->map.height)
	{
		game->map.map_text[i] = get_next_line(fd);
		i++;
	}
	game->map.map_text[i] = 0;
	close(fd);
	return (0);
}

int	check_line(t_game *game, int i)
{
	game->map.col_check = 0;
	game->map.play_check = 0;
	game->map.exit_check = 0;
	game->collect = 0;
	game->map.width = ft_strlen(game->map.map_text[0]);
	while (i < game->map.height)
	{
		if ((int)ft_strlen(game->map.map_text[i]) != game->map.width)
			return (1);
		if (check_cell(game, i) == 1)
			return (1);
		i++;
	}
	if (game->map.col_check == 0 || game->map.play_check == 0
		|| game->map.exit_check == 0 || game->map.play_check > 1)
		return (1);
	return (0);
}

int	check_cell(t_game *game, int i)
{
	int	j;

	j = 0;
	while (j < (game->map.width))
	{
		if (ft_strchr_index("01CEP", game->map.map_text[i][j]) == -1)
			return (1);
		if (game->map.map_text[i][j] == 'P')
		{
			game->player.pos_x = j;
			game->player.pos_y = i;
			game->map.play_check += 1;
		}
		if (game->map.map_text[i][j] == 'C')
		{
			game->collect += 1;
			game->map.col_check += 1;
		}
		if (game->map.map_text[i][j] == 'E')
			game->map.exit_check += 1;
		j++;
	}
	return (0);
}

int	check_borders(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		if (game->map.map_text[i][0] != '1')
			return (1);
		else if (game->map.map_text[i][game->map.width - 1] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < game->map.width)
	{
		if (game->map.map_text[game->map.height - 1][i] != '1')
			return (1);
		else if (game->map.map_text[0][i] != '1')
			return (1);
		i++;
	}
	return (0);
}

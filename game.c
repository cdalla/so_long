/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/19 09:34:58 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/03/25 15:40:40 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//main funtion where the  game starts
//get a map name in input
//check map values
//start game
//print initial configuration of the map
//hook every key and move the player accordingly
//!!!! FREE MAP AND MAPNAME !!!!!!!!

#include "game.h"

int	main(int argc, char **argv)
{
	t_game	game;
	char	*mapname;

	game.map.map_text = 0;
	game.moves = 0;
	if (argc != 2 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4],
		".ber", 4) != 0)
	{
		write(1, "Error\nINVALID INPUT", 19);
		return (0);
	}
	mapname = ft_strdup(argv[1]);
	if (read_map(mapname, &game) == 1)
	{
		write(1, "Error\nMAP ERROR", 15);
		free(mapname);
		return (0);
	}
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 30 * game.map.width,
			30 *(game.map.height + 1), "so_long");
	mlx_hook(game.win, 2, 0, key_event, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx, get_image, &game);
	mlx_loop(game.mlx);
}

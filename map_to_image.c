/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_to_image.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/19 10:38:26 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/04/05 12:39:51 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	game_end(t_game *game);
void	map_to_image2(t_game *game, char *text, int pos_x, int pos_y);

int	get_image(t_game *game)
{
	game->img.player = mlx_xpm_file_to_image(game->mlx,
			"./images/player.xpm", &game->img.width, &game->img.height);
	game->img.wall = mlx_xpm_file_to_image(game->mlx,
			"./images/wall.xpm", &game->img.width, &game->img.height);
	game->img.floor = mlx_xpm_file_to_image(game->mlx,
			"./images/floor.xpm", &game->img.width, &game->img.height);
	game->img.exit = mlx_xpm_file_to_image(game->mlx,
			"./images/door.xpm", &game->img.width, &game->img.height);
	game->img.monster = mlx_xpm_file_to_image(game->mlx,
			"./images/monster.xpm", &game->img.width, &game->img.height);
	if (game->collect == 0)
		game->img.exit = mlx_xpm_file_to_image(game->mlx,
				"./images/opendoor.xpm", &game->img.width, &game->img.height);
	mlx_clear_window(game->mlx, game->win);
	map_to_image(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->img.player, game->player.pos_x
		* game->img.width, game->player.pos_y * game->img.height);
	put_score(game);
	if (game->collect == 0 && game->map.map_text
		[game->player.pos_y][game->player.pos_x] == 'E')
		game_end(game);
	return (0);
}

void	map_to_image(t_game *game)
{
	int		i;
	int		pos_x;
	int		pos_y;
	char	**text;

	text = game->map.map_text;
	i = 0;
	pos_y = 0;
	while (text[i])
	{
		pos_x = 0;
		map_to_image2(game, text[i], pos_x, pos_y);
		i++;
		pos_y += game->img.height;
	}
}

void	map_to_image2(t_game *game, char *text, int pos_x, int pos_y)
{
	int	j;

	j = 0;
	while (text[j])
	{
		if (text[j] == '1')
			mlx_put_image_to_window(game->mlx,
				game->win, game->img.wall, pos_x, pos_y);
		if (text[j] == '0' || text[j] == 'P' || text[j] == 'C')
			mlx_put_image_to_window(game->mlx,
				game->win, game->img.floor, pos_x, pos_y);
		if (text[j] == 'E')
			mlx_put_image_to_window(game->mlx,
				game->win, game->img.exit, pos_x, pos_y);
		if (text[j] == 'C')
			mlx_put_image_to_window(game->mlx,
				game->win, game->img.monster, pos_x, pos_y);
		j++;
		pos_x += game->img.width;
	}
}

void	put_score(t_game *game)
{	
	char	*moves;
	char	*collect;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(game->moves);
	tmp2 = ft_itoa(game->collect);
	moves = ft_strjoin("Movement count: ", tmp1);
	collect = ft_strjoin("Collectible remaining: ", tmp2);
	mlx_string_put(game->mlx, game->win, game->img.width, game->img.height
		* game->map.height + (game->img.height / 2), 0xcd8500, moves);
	if (game->collect == 0)
		mlx_string_put(game->mlx, game->win, game->img.width
			* (game->map.width / 2), game->img.height * game->map.height
			+ (game->img.height / 2), 0xff7f, collect);
	else
		mlx_string_put(game->mlx, game->win, game->img.width
			* (game->map.width / 2), game->img.height * game->map.height
			+ (game->img.height / 2), 0x8b3626, collect);
	free(tmp1);
	free(tmp2);
	free(moves);
	free(collect);
}

void	game_end(t_game *game)
{
	char	*win;
	char	*loss;
	int		x;
	int		y;

	y = 1;
	win = "WINNER";
	loss = "LOSER";
	while (y < game->map.width)
	{
		x = 1;
		while (x < game->map.height)
		{
			mlx_string_put(game->mlx, game->win, game->img.width
				* x, game->img.height * x, 0xff7f, win);
			x += 1;
		}
		y += 1;
	}
}

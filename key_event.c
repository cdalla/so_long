/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_event.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/19 10:03:54 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/03/22 11:14:09 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//movement change player pos according to key pressed, if move is valid
//check if a wall is on player path and deny move
//if P stand on C position, delete P and decrease C count
//if door open and player pos == door pos WIN END GAME
// 13W 0A 1S 2D
#include "game.h"

int	key_event(int key, t_game *game)
{
	if (key == 53 || (game->collect == 0 && game->map.map_text
			[game->player.pos_y][game->player.pos_x] == 'E' && key))
		close_game(game);
	else if (key == 13 && valid(key, game) == 0 && collect(key, game) == 0)
	{
		game->player.pos_y -= 1;
		game->moves += 1;
	}
	else if (key == 0 && valid(key, game) == 0 && collect(key, game) == 0)
	{
		game->player.pos_x -= 1;
		game->moves += 1;
	}
	else if (key == 1 && valid(key, game) == 0 && collect(key, game) == 0)
	{
		game->player.pos_y += 1;
		game->moves += 1;
	}
	else if (key == 2 && valid(key, game) == 0 && collect(key, game) == 0)
	{
		game->player.pos_x += 1;
		game->moves += 1;
	}
	return (0);
}

//if next position is '1' in array return 1 else return 0
int	valid(int keycode, t_game *game)
{
	if (keycode == 13 && game->map.map_text[game->player.pos_y - 1]
		[game->player.pos_x] == '1')
		return (1);
	else if (keycode == 0 && game->map.map_text[game->player.pos_y]
		[game->player.pos_x - 1] == '1')
		return (1);
	else if (keycode == 1 && game->map.map_text[game->player.pos_y + 1]
		[game->player.pos_x] == '1')
		return (1);
	else if (keycode == 2 && game->map.map_text[game->player.pos_y]
		[game->player.pos_x + 1] == '1')
		return (1);
	return (0);
}

int	collect(int keycode, t_game *game)
{
	if (keycode == 13 && game->map.map_text[game->player.pos_y - 1]
		[game->player.pos_x] == 'C')
	{
		game->map.map_text[game->player.pos_y - 1][game->player.pos_x] = '0';
		game->collect -= 1;
	}
	else if (keycode == 0 && game->map.map_text[game->player.pos_y]
		[game->player.pos_x - 1] == 'C')
	{
		game->map.map_text[game->player.pos_y][game->player.pos_x - 1] = '0';
		game->collect -= 1;
	}
	else if (keycode == 1 && game->map.map_text[game->player.pos_y + 1]
		[game->player.pos_x] == 'C')
	{
		game->map.map_text[game->player.pos_y + 1][game->player.pos_x] = '0';
		game->collect -= 1;
	}
	else if (keycode == 2 && game->map.map_text[game->player.pos_y]
		[game->player.pos_x + 1] == 'C')
	{
		game->map.map_text[game->player.pos_y][game->player.pos_x + 1] = '0';
		game->collect -= 1;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/19 09:53:38 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/03/19 11:55:54 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "GNL/get_next_line.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_map
{
	int		width;
	int		height;
	int		col_check;
	int		play_check;
	int		exit_check;
	char	**map_text;
}				t_map;

typedef struct s_image
{
	void	*player;
	void	*wall;
	void	*floor;
	void	*exit;
	void	*monster;
	int		width;
	int		height;
}				t_image;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			collect;
	int			moves;
	t_map		map;
	t_image		img;
	t_player	player;
}				t_game;

//MAP
int		read_map(char *mapname, t_game *game);
int		get_map_size(char *mapname, t_game *game);
int		save_map(char *mapname, t_game *game);
int		check_borders(t_game *game);
int		check_line(t_game *game, int i);
void	print_map(t_game *game);

//UTILS
int		close_game(t_game *game);
int		get_image(t_game *game);
void	free_map(t_game *game);
void	map_to_image(t_game *game);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	put_score(t_game *game);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//MOVEMENT
int		key_event(int key, t_game *game);
int		valid(int keycode, t_game *game);
int		collect(int keycode, t_game *game);

#endif
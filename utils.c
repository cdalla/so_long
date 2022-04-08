/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/19 11:03:45 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/04/08 12:02:01 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.map_text)
	{
		while (game->map.map_text[i] && game->map.map_text[i])
		{
			if (game->map.map_text[i] != 0)
				free(game->map.map_text[i]);
			i++;
		}
		free(game->map.map_text);
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = (ft_strlen((char *)s1)) + (ft_strlen((char *)s2)) + 1;
	join = (char *)malloc(len * sizeof(char));
	if (join == 0)
		return (0);
	ft_strlcpy(&(join[ft_strlcpy(join, s1, len)]), s2, len);
	return (join);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0)
		return (0);
	while (index < n && s1[index])
	{
		if (s1[index] != s2[index])
			return ((unsigned char) s1[index] - s2[index]);
		else if (index + 1 == n)
			break ;
		else
			index++;
	}
	return ((unsigned char) s1[index] - s2[index]);
}

int	get_map_size(char *mapname, t_game *game)
{
	int		fd;
	char	*s;

	s = "";
	fd = open(mapname, O_RDONLY);
	if (fd < 1)
		return (1);
	game->map.height = 0;
	while (s)
	{
		s = get_next_line(fd);
		if (s)
			game->map.height += 1;
		free(s);
	}
	close(fd);
	return (0);
}

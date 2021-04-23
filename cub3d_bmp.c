#include "cub3d.h"

static int	pixel_color(t_img *img, int width, int height)
{
	int		argb;
	char	*dest;

	dest = img->adr + (height * img->len + width * (img->bpp / 8));
	argb = *(unsigned int *)dest;
	return (argb);
}

static void	a_write(int fd, int c, int s)
{
	write(fd, &c, s);
}

static void	bmp_header(int fd, int x, int y, int bpp)
{
	write(fd, "BM", 2);
	a_write(fd, ((x * y) * 4 + 58), 4);
	write(fd, "\0\0\0\0", 4);
	a_write(fd, 58, 4);
	a_write(fd, 40, 4);
	a_write(fd, x, 4);
	a_write(fd, y, 4);
	a_write(fd, 1, 2);
	a_write(fd, bpp, 2);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 28);
}

bool	screenshot(t_img *img, int x, int y, t_all *all)
{
	int	fd;
	int	sx;

	sx = 0;
	fd = open("img.bmp", O_CREAT | O_RDWR);
	if (fd < 0)
		return (exit_game(all));
	bmp_header(fd, x, y, img->bpp);
	while (y != 0)
	{
		while (sx != x)
		{
			a_write(fd, pixel_color(img, sx, y), 4);
			++sx;
		}
		sx = 0;
		--y;
	}
	close(fd);
	exit_game(all);
	return (true);
}

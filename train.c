
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	ft_atoi(char* str) {
	int	res = 0;

	while (*str) {
		if (*str >= '0' && *str <= '9')
			res = res * 10 + (*str - '0');
		str++;
	}

	return res;
}

void	ft_free_field(int** field, int h) {
	if (!field)
		return ;
	
	for (int i = 0; i < h; i++)
		free(field[i]);
	free(field);
}

int** ft_create_field(int w, int h) {
	int **field;

	field = calloc(h, sizeof(int*));
	if (!field)
		return NULL;

	for (int i = 0; i < h; i++) {
		field[i] = calloc(w, sizeof(int));
		if (!field[i]) {
			ft_free_field(field, h);
			return NULL;
		}
	}

	return field;
}

void	ft_fill_field(int** field, int w, int h) {
	char	c;
	int		pen = 0;
	int		x = 0;
	int		y = 0;

	while(read(0, &c, 1) > 0) {
		if (c == 'x')
			pen = (!pen);
		else if (c == 'a' && x > 0)
			x--;
		else if (c == 'd' && x < w - 1)
			x++;
		else if (c == 'w' && y > 0)
			y--;
		else if(c == 's' && y < h - 1)
			y++;

		if (pen)
			field[y][x] = 1;
	}
}

int	ft_count_neighbours(int **field, int w, int h, int x, int y) {
	int	res = 0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)
				continue;
			if (x + j >= 0 
				&& x + j < w 
				&& y + i >= 0 
				&& y + i < h)
				res += field[y + i][x + j];
		}
	}
	return res;
}

void ft_copy_field(int **field, int **copy, int w, int h) {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++)
			copy[y][x] = field[y][x];
	}
}

void ft_simulation(int **field, int **temp, int w, int h, int it) {
	int	n;
	
	for (int i = 0; i < it; i++) {
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				n = ft_count_neighbours(field, w, h, x, y);
				if (field[y][x])
					temp[y][x] = ((n == 2) || (n == 3));
				else
					temp[y][x] = (n == 3);
			}
		}

		ft_copy_field(temp, field, w, h);
	}
}

void ft_print_field(int **field, int w, int h) {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (field[y][x])
				putchar('O');
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

int	main(int argc, char **argv) {
	int		w;
	int		h;
	int		it;
	int**	field = NULL;
	int**	temp = NULL;

	if (argc != 4)
		return (0);

	w = ft_atoi(argv[1]);
	h = ft_atoi(argv[2]);
	it = ft_atoi(argv[3]);

	field = ft_create_field(w, h);
	temp = ft_create_field(w, h);
	if(!field || !temp) {
		ft_free_field(field, h);
		ft_free_field(temp, h);
		return (0);
	}

	ft_fill_field(field, w, h);

	ft_simulation(field, temp, w, h, it);

	ft_print_field(field, w, h);

	ft_free_field(field, h);
	ft_free_field(temp, h);

	return (1);
}
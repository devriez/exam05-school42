
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	ft_atoi(char* str) {
	int	res = 0;

	while(*str >= '0' && *str <= '9') {
		res = res * 10 + (*str - '0');
		str++;
	}
	return res;
}

void	ft_free_field(int **field, int	h) {
	if (!field)
		return ;
	
	for (int i = 0; i < h; i++) {
		if (!field[i])
			continue;
		else
			free(field[i]);
	}
	free(field);
}

int**	ft_create_field(int w, int h) {
	int** field = calloc(h, sizeof(int*));

	if (!field)
		return (0);

	for (int i = 0; i < h; i++) {
		field[i] = calloc(w, sizeof(int));
		if (!field[i]) {
			ft_free_field(field, h);
			return NULL;
		}
	}
	return field;
}

void	ft_fill_field(int **field, int w, int h) {
	char	c;
	int		x = 0;
	int		y = 0;
	int		pen = 0;

	while(read(0, &c, 1) > 0) {
		if (c == 'x')
			pen = (pen ? 0 : 1);
		else if (c == 'w' && y > 0)
			y--;
		else if (c == 's' && y < h -1)
			y++;
		else if (c == 'a' && x > 0)
			x--;
		else if (c == 'd' && x < w - 1)
			x++;
		
		if (pen)
			field[y][x] = 1;
	}
}

void ft_copy_field(int **field, int **copy, int w, int h) {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			copy[y][x] = field[y][x];
		}
	}
}

int	ft_count_neighbrs(int **field, int w, int h, int x, int y) {
	int	res = 0;

	for (int i = -1; i <=1; i++) {
		for (int j = -1; j <= 1; j++) {
			if(i == 0 && j == 0)
				continue;
			if (x + j >= 0 && x + j <= w - 1
				&& y + i >= 0 && y + i <= h - 1)
				if(field[y + i][x + j] == 1)
					res++;
		}
	}
	return res;
}

void ft_simulation(int **field, int **temp, int w, int h, int it) {
	int	neighbrs;

	for (int i = 0; i < it; i++) {
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				neighbrs = ft_count_neighbrs(field, w, h, x, y);
				if (field[y][x])
					temp[y][x] = (neighbrs == 2 || neighbrs == 3);
				else
					temp[y][x] = (neighbrs == 3);
			}
		}
		ft_copy_field(temp, field, w, h);
	}
}

void ft_print_res(int** field, int w, int h) {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (field[y][x] == 1)
				putchar('O');
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

int	main(int argc, char** argv) {
	if (argc != 4)
		return 0;
	int	w;
	int	h;
	int	it;
	int	**field = NULL;
	int	**temp = NULL;

	w = ft_atoi(argv[1]);
	h = ft_atoi(argv[2]);
	it = ft_atoi(argv[3]);

	field = ft_create_field(w, h);
	temp = ft_create_field(w,h);

	if(!field || !temp) {
		ft_free_field(field, h);
		ft_free_field(temp, h);
		return (0);
	}

	ft_fill_field(field, w, h);

	ft_simulation(field, temp, w, h, it);

	ft_print_res(field, w, h);

	ft_free_field(field, h);
	ft_free_field(temp, h);
	return (1);
}
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
** Структура карты:
** rows  — количество строк
** cols  — количество колонок
** empty — символ пустой клетки
** obstacle — символ препятствия
** full — символ, которым будем рисовать квадрат
** field — сама карта (массив строк)
*/
typedef struct s_map
{
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
	char	**field;
}	t_map;

/*
** Храним лучший найденный квадрат:
** size — длина стороны
** row, col — координаты правого нижнего угла
*/
typedef struct s_best
{
	int	size;
	int	row;
	int	col;
}	t_best;

/*
** Печать ошибки в stderr
*/
void	print_error(void)
{
	fprintf(stderr, "map error\n");
}

/*
** Освобождение памяти карты
** filled_rows — сколько строк реально было выделено
** (важно при ошибках, чтобы не словить segfault)
*/
void	free_map(t_map *m, int filled_rows)
{
	if (!m->field)
		return;

	for (int i = 0; i < filled_rows; i++)
		free(m->field[i]);

	free(m->field);
}

int	ft_min3(int a, int b, int c) {
	if (a <= b && a <= c)
		return a;
	if (b <= a && b <= c)
		return b;
	return c;
}

/*
** Парсинг первой строки
** Пример: "9.ox"
**
** 9   → количество строк
** .   → empty
** o   → obstacle
** x   → full
*/
int	parse_header(char *line, t_map *m)
{
	int	i = 0;

	// читаем число (количество строк)
	while (line[i] >= '0' && line[i] <= '9')
	{
		m->rows = m->rows * 10 + (line[i] - '0');
		i++;
	}

	// если нет числа или оно <= 0 → ошибка
	if (i == 0 || m->rows <= 0)
		return (0);

	for (int k = 0; k < 3; k++)
	{
		if (line[i + k] == '\0' || line[i + k] == '\n')
			return (0);
	}
	// читаем три символа
	m->empty = line[i++];
	m->obstacle = line[i++];
	m->full = line[i++];

	// символы должны быть разными
	if (m->empty == m->obstacle
		|| m->empty == m->full
		|| m->obstacle == m->full)
		return (0);

	// строка должна заканчиваться \n
	if (line[i] != '\n')
		return (0);

	return (1);
}

/*
** Чтение карты из файла
*/
int	read_map(FILE *fp, t_map *m)
{
	char	*line = NULL;
	size_t	len = 0;
	ssize_t	read;
	int		i;

	// выделяем массив указателей на строки (и зануляем!)
	m->field = calloc(m->rows, sizeof(char *));
	if (!m->field)
		return (0);

	i = 0;
	while (i < m->rows)
	{
		// читаем строку
		read = getline(&line, &len, fp);
		if (read <= 0)
		{
			free(line);
			free_map(m, i);
			return (0);
		}

		// убираем \n
		if (line[read - 1] == '\n')
			line[--read] = '\0';

		// первая строка задаёт ширину карты
		if (i == 0)
			m->cols = read;

		// проверка длины строк
		if (read != m->cols || read == 0)
		{
			free(line);
			free_map(m, i);
			return (0);
		}

		// выделяем память под строку карты
		m->field[i] = malloc(read + 1);
		if (!m->field[i])
		{
			free(line);
			free_map(m, i);
			return (0);
		}

		// копируем строку и проверяем символы
		for (int j = 0; j < m->cols; j++)
		{
			// допускаются только empty и obstacle
			if (line[j] != m->empty && line[j] != m->obstacle)
			{
				free(line);
				free_map(m, i + 1);
				return (0);
			}
			m->field[i][j] = line[j];
		}
		m->field[i][m->cols] = '\0';
		i++;
	}

	// проверяем, нет ли лишних строк в файле
	if (getline(&line, &len, fp) > 0)
	{
		free(line);
		free_map(m, m->rows);
		return (0);
	}

	free(line);
	return (1);
}

/*
** Основной алгоритм (Dynamic Programming)
**
** dp[j] — размер максимального квадрата,
**         который заканчивается в текущей позиции
**
** используем только 1 строку → O(m) память
*/
void	solve_bsq(t_map *m)
{
	int		*dp;
	int		prev_diag; // значение dp[j-1] из предыдущей строки
	int		temp;
	t_best	best = {0, 0, 0};

	// массив DP (одна строка)
	dp = calloc(m->cols, sizeof(int));
	if (!dp)
		return;

	for (int i = 0; i < m->rows; i++)
	{
		prev_diag = 0;

		for (int j = 0; j < m->cols; j++)
		{
			temp = dp[j]; // сохраняем старое значение (для диагонали)

			if (m->field[i][j] == m->obstacle)
				dp[j] = 0;
			else if (i == 0 || j == 0)
				dp[j] = 1;
			else
			{
				// берём минимум из:
				// верх, лево, диагональ
				int min = dp[j];
				if (dp[j - 1] < min)
					min = dp[j - 1];
				if (prev_diag < min)
					min = prev_diag;

				dp[j] = min + 1;
			}

			// обновляем лучший квадрат
			if (dp[j] > best.size)
			{
				best.size = dp[j];
				best.row = i;
				best.col = j;
			}

			// обновляем диагональ
			prev_diag = temp;
		}
	}

	// заполняем найденный квадрат символом full
	for (int i = best.row - best.size + 1; i <= best.row; i++)
	{
		for (int j = best.col - best.size + 1; j <= best.col; j++)
			m->field[i][j] = m->full;
	}

	// вывод карты
	for (int i = 0; i < m->rows; i++)
	{
		fputs(m->field[i], stdout);
		fputs("\n", stdout);
	}

	free(dp);
}

/*
** Обработка одного источника (файл или stdin)
*/
void	process(FILE *fp)
{
	char	*line = NULL;
	size_t	len = 0;
	t_map	m = {0};

	// читаем первую строку
	if (getline(&line, &len, fp) <= 0)
	{
		print_error();
		free(line);
		return;
	}

	// парсим заголовок
	if (!parse_header(line, &m))
	{
		print_error();
		free(line);
		return;
	}
	free(line);

	// читаем карту
	if (!read_map(fp, &m))
	{
		print_error();
		return;
	}

	// решаем задачу
	solve_bsq(&m);

	// освобождаем память
	free_map(&m, m.rows);
}

/*
** main:
** - если нет аргументов → читаем stdin
** - иначе обрабатываем каждый файл
*/
int	main(int argc, char **argv)
{
	FILE	*fp;

	if (argc == 1)
	{
		process(stdin);
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			fp = fopen(argv[i], "r");
			if (!fp)
				print_error();
			else
			{
				process(fp);
				fclose(fp);
			}

			// разделяем выводы разных карт
			if (i < argc - 1)
				fputs("\n", stdout);
		}
	}
	return (0);
}

//Celescu Rares

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

struct image {
	char magicword[3];
	int m, n, maxval, tip;
	unsigned char **data;
	int x1, x2, y1, y2;
};

typedef struct image imagine;

imagine citire_binara(FILE *f, imagine *img, int cnt)
{
	if (cnt > 0) {
		for (int i = 0; i < img->m; i++)
			free(img->data[i]);
		free(img->data);
	}
	fscanf(f, "%d%d%d\n", &img->n, &img->m, &img->maxval);
	if (img->tip == 3)
		img->n = img->n * 3;
	img->data = (unsigned char **)malloc(img->m * sizeof(unsigned char *));
	if (!img->data) {
		printf("Alocarea a esuat\n");
		exit(-1);
	}
	for (int i = 0; i < img->m; i++) {
		img->data[i] = (unsigned char *)malloc(img->n * sizeof(unsigned char));
		if (!img->data[i]) {
			for (int j = i - 1; j >= 0; j--)
				free(img->data[j]);
			free(img->data);
			printf("Alocarea a esuat\n");
			exit(-1);
		}
	}
	for (int i = 0; i < img->m; i++)
		for (int j = 0; j < img->n; j++)
			fread(&img->data[i][j], sizeof(unsigned char), 1, f);
	img->x1 = 0, img->y1 = 0, img->x2 = img->n / img->tip, img->y2 = img->m;
	return *img;
}

imagine citire(FILE *f, imagine *img, int cnt)
{
	if (cnt > 0) {
		for (int i = 0; i < img->m; i++)
			free(img->data[i]);
		free(img->data);
	}
	fscanf(f, "%d%d%d\n", &img->n, &img->m, &img->maxval);
	if (img->tip == 3)
		img->n = img->n * 3;
	img->data = (unsigned char **)malloc(img->m * sizeof(unsigned char *));
	if (!img->data) {
		printf("Alocarea a esuat\n");
		exit(-1);
	}
	for (int i = 0; i < img->m; i++) {
		img->data[i] = (unsigned char *)malloc(img->n * sizeof(unsigned char));
		if (!img->data[i]) {
			for (int j = i; j >= 0; j--)
				free(img->data[j]);
			free(img->data);
			printf("Alocarea a esuatt\n");
			exit(-1);
		}
	}
		for (int i = 0; i < img->m; i++)
			for (int j = 0; j < img->n; j++)
				fscanf(f, "%hhu", &img->data[i][j]);
		img->x1 = 0, img->y1 = 0, img->x2 = img->n / img->tip;
		img->y2 = img->m;
		return *img;
}

void histograma(imagine *img, char comanda[])
{
	char comanda1[100];
	strcpy(comanda1, comanda);
	char *p = strtok(comanda1, " ");
	p = strtok(NULL, " ");
	if (!p) {
		printf("Invalid command\n");
		return;
	}
	p = strtok(NULL, " ");
	if (!p) {
		printf("Invalid command\n");
		return;
	}
	p = strtok(NULL, " ");
	if (p) {
		printf("Invalid command\n");
		return;
	}
	if (img->tip == 3) {
		printf("Black and white image needed\n");
	} else {
		char *ptr = strtok(comanda, " ");
		ptr = strtok(NULL, " ");
		int x, y, cpy, frecvmax = 0;
		x = atoi(ptr);
		ptr = strtok(NULL, " ");
		y = atoi(ptr);
		int interval = 256 / y;
		cpy = y;
		while (cpy > 1)
			cpy = cpy / 2;
		if (cpy != 1) {
			printf("Invalid set of parameters\n");
		} else {
			const int max = 256;
			int frecv[max];
			for (int i = 0; i < max; i++)
				frecv[i] = 0;
			for (int i = 0; i < img->m; i++)
				for (int j = 0; j < img->n; j++)
					frecv[img->data[i][j]]++;
			int frcv[max];
			for (int i = 0; i < max; i++)
				frcv[i] = 0;
			for (int i = 0; i < 256 ; i = i + interval) {
				for (int j = i; j < i + interval; j++)
					frcv[i / interval] = frcv[i / interval] + frecv[j];
				if (frcv[i / interval] > frecvmax)
					frecvmax = frcv[i / interval];
			}
			for (int i = 0; i < y; i++) {
				double nrstelute = (double)frcv[i] / frecvmax  * x;
				printf("%d\t|\t", (int)nrstelute);
				for (int j = 0; j < (int)nrstelute; j++)
					printf("*");
				printf("\n");
			}
			}
	}
}

void equalize(imagine *img)
{
	if (img->tip == 3) {
		printf("Black and white image needed\n");
	} else {
		int frecv[256];
		for (int i = 0; i < 256; i++)
			frecv[i] = 0;
		for (int i = 0; i < img->m; i++)
			for (int j = 0; j < img->n; j++)
				frecv[img->data[i][j]]++;
		for (int i = 1; i < 256; i++)
			frecv[i] = frecv[i] + frecv[i - 1];
		for (int i = 0; i < img->m; i++)
			for (int j = 0; j < img->n; j++) {
				double nou;
				nou = 255.0 / (img->m * img->n) * frecv[img->data[i][j]];
				if (nou < 0)
					nou = 0;
				if (nou > 255)
					nou = 255;
				nou = round(nou);
				img->data[i][j] = nou;
			}
		printf("Equalize done\n");
	}
}

void rotatieintreaga(imagine *img)
{
	unsigned char **mat = malloc(img->n * sizeof(unsigned char *));
	for (int i = 0; i < img->n; i++)
		mat[i] = malloc(img->m * sizeof(unsigned char));
	for (int i = 0; i < img->m; i++)
		for (int j = 0; j < img->n; j++)
			mat[j][img->m - i - 1] = img->data[i][j];
	for (int i = 0 ; i < img->m; i++)
		free(img->data[i]);
	free(img->data);
	int aux = img->m;
	img->m = img->n;
	img->n = aux;
	img->y1 = 0, img->x1 = 0, img->y2 = img->n, img->x2 = img->m;
	img->data = (unsigned char **)malloc(img->m * sizeof(unsigned char *));
	for (int i = 0; i < img->m; i++)
		img->data[i] = (unsigned char *)malloc(img->n * sizeof(unsigned char));
	for (int i = 0; i < img->m ; i++)
		for (int j = 0; j < img->n ; j++)
			img->data[i][j] = mat[i][j];
	for (int i = 0; i < img->m; i++)
		free(mat[i]);
	free(mat);
}

void rotatieselect(imagine *img)
{
	int m = img->y2 - img->y1, n = img->x2 - img->x1;
	unsigned char **mat = (unsigned char **)malloc(m * sizeof(unsigned char *));
	for (int i = 0; i < m; i++)
		mat[i] = (unsigned char *)malloc(n * sizeof(unsigned char));
	for (int i = 0; i < m ; i++)
		for (int j = 0; j < n; j++)
			mat[j][m - i - 1] = img->data[img->y1 + i][img->x1 + j];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			img->data[img->y1 + i][img->x1 + j] = mat[i][j];
	for (int i = 0; i < m; i++)
		free(mat[i]);
	free(mat);
}

void rotatieselectcolor(imagine *img)
{
	img->x1 = img->x1 / 3, img->x2 = img->x2 / 3;
	int m = img->y2 - img->y1, n = img->x2 - img->x1;
	unsigned char ***mat = malloc(m * sizeof(unsigned char **));
	for (int i = 0; i < m; i++) {
		mat[i] = (unsigned char **)malloc(n * sizeof(unsigned char *));
		for (int j = 0; j < n ; j++)
			mat[i][j] = (unsigned char *)malloc(3 * sizeof(unsigned char));
	}
	int y1 = img->y1, x1 = img->x1;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			for (int c = 0; c < 3; c++)
				mat[j][m - 1 - i][c] = img->data[y1 + i][3 * (x1 + j) + c];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			for (int c = 0; c < 3; c++)
				img->data[y1 + i][3 * (x1 + j) + c] = mat[i][j][c];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			free(mat[i][j]);
		free(mat[i]);
	}
	img->x1 = img->x1 * 3, img->x2 = img->x2 * 3;
	free(mat);
}

void rotatiecolorintreg(imagine *img)
{
	img->n = img->n / 3;
	unsigned char ***mat = malloc(img->n * sizeof(unsigned char **));
	for (int i = 0; i < img->n; i++) {
		mat[i] = (unsigned char **)malloc(img->m * sizeof(unsigned char *));
		for (int j = 0; j < img->m; j++)
			mat[i][j] = (unsigned char *)malloc(3 * sizeof(unsigned char));
	}
	for (int i = 0; i < img->m; i++)
		for (int j = 0; j < img->n; j++)
			for (int c = 0; c < 3; c++)
				mat[j][img->m - i - 1][c] = img->data[i][j * 3 + c];
	for (int i = 0; i < img->m; i++)
		free(img->data[i]);
	free(img->data);
	img->data = (unsigned char **)malloc(img->n * sizeof(unsigned char *));
	for (int i = 0; i < img->n; i++) {
		img->data[i] = malloc(3 * img->m * sizeof(unsigned char));
		for (int j = 0; j < img->m; j++)
			for (int c = 0; c < 3; c++)
				img->data[i][j * 3 + c] = mat[i][j][c];
	}
	int aux = img->m;
	img->m = img->n;
	img->n = aux;
	img->x1 = 0, img->y1 = 0, img->x2 = img->n, img->y2 = img->m;
	img->n = img->n * 3;
	for (int i = 0; i < img->m; i++) {
		for (int j = 0; j < img->n / 3; j++)
			free(mat[i][j]);
		free(mat[i]);
	}
	free(mat);
}

void rotatie1(imagine *img, char comanda[])
{
	char *p = strtok(comanda, " ");
	p = strtok(NULL, " ");
	if (!p) {
		printf("Invalid command\n");
		return;
	}
	int m = img->x2 - img->x1, n = img->y2 - img->y1, x1 = img->x1;
	int y1 = img->y1, y2 = img->y2, x2 = img->x2;
	int h = img->m, w = img->n;
	int unghi = atoi(p);
	if (unghi == 0 || unghi == 360) {
		printf("Rotated %d\n", unghi);
	} else if (unghi % 90 != 0) {
		printf("Unsupported rotation angle\n");
	} else if ((m != n) && (x1 != 0 && y1 != 0 && x2 != w && y2 != h)) {
		printf("The selection must be square\n");
	} else {
		int rotatii = 0;
		if (unghi == 90 || unghi == -270)
			rotatii = 1;
		if (unghi == 180 || unghi == -180)
			rotatii = 2;
		if (unghi == -90 || unghi == 270)
			rotatii = 3;
		int tiprotatie;
		img->x1 = img->x1 * img->tip, x1 = x1 * img->tip;
		img->x2 = img->x2 * img->tip, x2 = x2 * img->tip;
		if ((x1 != 0 || y1 != 0 || x2 != w || y2 != h) && (x2 != h || y2 != w))
			tiprotatie = 2;
		else
			tiprotatie = 1;
		for (int i = 0; i < rotatii; i++) {
			if (tiprotatie == 1) {
				if (img->tip == 1)
					rotatieintreaga(img);
				else
					rotatiecolorintreg(img);
			} else {
				if (img->tip == 1)
					rotatieselect(img);
				else
					rotatieselectcolor(img);
				}
		}
	printf("Rotated %d\n", unghi);
	}
}

void select1(imagine *img, char comanda[])
{
	int continua = 1;
	for (int i = 7; i < (int)strlen(comanda) - 1; i++)
		if (continua == 1)
			if ((isalpha(comanda[i]) && comanda[8] != 'L')) {
				printf("Invalid command\n");
				continua = 0;
			}
	if (continua == 1) {
		if (comanda[8] == 'L' && comanda[7] == 'A' && comanda[9] == 'L') {
			img->x1 = 0, img->y1 = 0, img->x2 = img->n / img->tip;
			img->y2 = img->m;
			printf("Selected ALL\n");
		} else {
			int x1, x2, y1, y2;
			char *p = strtok(comanda, " ");
			if (!p) {
				printf("Invalid command\n");
				return;
			}
			p = strtok(NULL, " ");
			if (!p) {
				printf("Invalid command\n");
				return;
			}
			x1 = atoi(p);
			p = strtok(NULL, " ");
			if (!p) {
				printf("Invalid command\n");
				return;
			}
			y1 = atoi(p);
			p = strtok(NULL, " ");
			if (!p) {
				printf("Invalid command\n");
				return;
			}
			x2 = atoi(p);
			p = strtok(NULL, " ");
			if (!p) {
				printf("Invalid command\n");
				return;
			}
			y2 = atoi(p);
			if (x1 > x2) {
				int aux = x1;
				x1 = x2;
				x2 = aux;
			}
			if (y1 > y2) {
				int aux = y1;
				y1 = y2;
				y2 = aux;
			}
			int m = img->m, n = img->n, t = img->tip;
			if (x1 < 0  || y1 < 0 || y2 > m || x2 > n / t || x2 <= 0) {
				printf("Invalid set of coordinates\n");
				continua = 0;
			} else if (y2 <= 0) {
				printf("Invalid set of coordinates\n");
				continua = 0;
			} else if ((x1 == x2 && x1 == n) || (y1 == y2 && y1 == m)) {
				printf("Invalid set of coordinates\n");
				continua = 0;
			} else if (x1 == x2 && x2 == y1 && y1 == y2 && y1 < m) {
				printf("Invalid set of coordinates\n");
				continua = 0;
			}
			if (continua == 1) {
				img->x1 = x1, img->x2 = x2, img->y1 = y1;
				img->y2 = y2;
				printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
			}
		}
	}
}

void crop(imagine *img)
{
	img->x2 = img->x2 * img->tip;
	img->x1 = img->x1 * img->tip;
	int n = img->x2 - img->x1, m = img->y2 - img->y1;
	unsigned char **mat = (unsigned char **)malloc(m * sizeof(unsigned char *));
	if (!mat) {
		printf("Eroare la alocare\n");
		exit(-1);
	}
	for (int i = 0; i < m; i++) {
		mat[i] = (unsigned char *)malloc(n * sizeof(unsigned char));
		if (!mat[i]) {
			for (int j = i; j >= 0 ; j--)
				free(mat[i]);
			free(mat);
			printf("Eroare la alocare\n");
			exit(-1);
		}
	}
	int i1 = 0;
	for (int i = img->y1; i < img->y2; i++) {
		int j1 = 0;
		for (int j = img->x1; j < img->x2; j++) {
			mat[i1][j1] = img->data[i][j];
			j1++;
		}
		i1++;
	}
	for (int i = 0; i < img->m; i++)
		free(img->data[i]);
	free(img->data);
	img->data = (unsigned char **)malloc(m * sizeof(unsigned char *));
	if (!mat) {
		printf("Eroare la alocare\n");
		exit(-1);
	}
	for (int i = 0; i < m; i++) {
		img->data[i] = (unsigned char *)malloc(n * sizeof(unsigned char));
		if (!img->data[i]) {
			for (int j = i; j >= 0 ; j--)
				free(img->data[j]);
			free(img->data);
			printf("Eroare la alocare\n");
			exit(-1);
		}
	}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			img->data[i][j] = mat[i][j];
	img->m = m, img->n = n, img->x1 = 0, img->y1 = 0, img->x2 = n, img->y2 = m;
	for (int i = 0; i < m; i++)
		free(mat[i]);
	free(mat);
	printf("Image cropped\n");
	img->x2 = img->x2 / img->tip;
	img->x1 = img->x1 / img->tip;
}

void apply(imagine *img, char comanda[])
{
	if (comanda[5] == '\0') {
		printf("Invalid command\n");
	} else if (!strchr("ESBG", comanda[6])) {
		printf("APPLY parameter invalid\n");
	} else if (img->tip == 1) {
		printf("Easy, Charlie Chaplin\n");
	} else {
		double k[3][3];
		if (comanda[6] == 'E') {
			k[0][0] = -1, k[0][1] = -1, k[0][2] = -1, k[1][0] = -1;
			k[1][1] = 8, k[1][2] = -1, k[2][0] = -1, k[2][1] = -1, k[2][2] = -1;
		}
		if (comanda[6] == 'S') {
			k[0][0] = 0, k[0][1] = -1, k[0][2] = 0, k[1][0] = -1;
			k[1][1] = 5, k[1][2] = -1, k[2][0] = 0, k[2][1] = -1, k[2][2] = 0;
		}
		if (comanda[6] == 'B') {
			k[0][0] = 1.0 / 9, k[0][1] = 1.0 / 9;
			k[0][2] = 1.0 / 9, k[1][0] = 1.0 / 9;
			k[1][1] = 1.0 / 9, k[1][2] = 1.0 / 9;
			k[2][0] = 1.0 / 9, k[2][1] = 1.0 / 9, k[2][2] = 1.0 / 9;
		}
		if (comanda[6] == 'G') {
			k[0][0] = 1.0 / 16, k[0][1] = 2.0 / 16;
			k[0][2] = 1.0 / 16, k[1][0] = 2.0 / 16;
			k[1][1] = 4.0 / 16, k[1][2] = 2.0 / 16;
			k[2][0] = 1.0 / 16, k[2][1] = 2.0 / 16, k[2][2] = 1.0 / 16;
		}
		int x1 = img->x1, x2 = img->x2, y1 = img->y1, y2 = img->y2;
		if (x1 < 1)
			x1 = 1;
		if (y1 < 1)
			y1 = 1;
		if (x2 > img->n / 3 - 1)
			x2 = img->n / 3 - 1;
		if (y2 > img->m - 1)
			y2 = img->m - 1;
		unsigned char **mat = malloc(img->m * sizeof(unsigned char *));
		for (int i = 0; i < img->m; i++)
			mat[i] = (unsigned char *)malloc(img->n * sizeof(unsigned char));
		for (int i = y1 ; i < y2; i++)
			for (int j = x1; j < x2; j++) {
				double r = 0, g = 0, b = 0;
				for (int a = 0; a < 3; a++)
					for (int c = 0; c < 3; c++) {
						int x = a - 1;
						r += img->data[i + x][3 * (j + c - 1)] * k[a][c];
						g += img->data[i + x][3 * (j + c - 1) + 1] * k[a][c];
						b += img->data[i + x][3 * (j + c - 1) + 2] * k[a][c];
					}
			r = round(r);
			b = round(b);
			g = round(g);
			if (r < 0)
				r = 0;
			if (r > 255)
				r = 255;
			if (g < 0)
				g = 0;
			if (g > 255)
				g = 255;
			if (b < 0)
				b = 0;
			if (b > 255)
				b = 255;
			mat[i][3 * j] = r;
			mat[i][3 * j + 1] = g;
			mat[i][3 * j + 2] = b;
		}
		for (int i = y1; i < y2; i++)
			for (int j = x1 * 3; j < x2 * 3; j++)
				img->data[i][j] = mat[i][j];
		for (int i = 0; i < img->m; i++)
			free(mat[i]);
		free(mat);
		printf("%s done\n", comanda);
	}
}

void freeimg(imagine *img)
{
	for (int i = 0; i < img->m; i++)
		free(img->data[i]);
	free(img->data);
}

void save(imagine *img, char comanda[])
{
	FILE *g;
	char fisier_load[100];
	char *p = strtok(comanda, " ");
	p = strtok(NULL, " ");
	strcpy(fisier_load, p);
	p = strtok(NULL, " ");
	if (p) {
		g = fopen(fisier_load, "w");
		if (!g) {
			printf("Failed to save %s\n", fisier_load);
		} else {
			if (img->magicword[1] > '3')
				img->magicword[1] = img->magicword[1] - 3;
			fprintf(g, "%s\n", img->magicword);
			if (img->tip == 1)
				fprintf(g, "%d %d\n", img->n, img->m);
			else
				fprintf(g, "%d %d\n", img->n / 3, img->m);
			fprintf(g, "%d\n", img->maxval);
			for (int i = 0; i < img->m; i++) {
				for (int j = 0; j < img->n; j++)
					fprintf(g, "%hhu ", img->data[i][j]);
				fprintf(g, "\n");
			}
		}
		} else {
			g = fopen(fisier_load, "wb");
			if (!g) {
				printf("Failed to save %s\n", fisier_load);
			} else {
				if (img->magicword[1] <= '3')
					img->magicword[1] = img->magicword[1] + 3;
				fprintf(g, "%s\n", img->magicword);
				if (img->tip == 1)
					fprintf(g, "%d %d\n", img->n, img->m);
				else
					fprintf(g, "%d %d\n", img->n / 3, img->m);
				fprintf(g, "%d\n", img->maxval);
				for (int i = 0; i < img->m; i++) {
					for (int j = 0; j < img->n; j++)
						fwrite(&img->data[i][j], sizeof(unsigned char), 1, g);
				}
			}
		}
		fclose(g);
		printf("Saved %s\n", fisier_load);
}

int main(void)
{
	int continua = 1, cnt = 0;
	char comanda[100], comanda1[100], nume_fisier[100] = "0";
	FILE *f;
	imagine img;
	while (continua == 1) {
		fgets(comanda, sizeof(comanda) - 1, stdin);
		char *p2 = strchr(comanda, '\n');
		if (p2)
			*p2 = '\0';
		strcpy(comanda1, comanda);
		char *p1 = strtok(comanda, " ");
		if (!p1) {
			printf("Invalid command\n");
		} else if (strcmp(p1, "LOAD") == 0) {
			p1 = strtok(NULL, " ");
			strcpy(nume_fisier, p1);
			f = fopen(nume_fisier, "rb");
			if (!f) {
				printf("Failed to load %s\n", nume_fisier);
				strcpy(nume_fisier, "0");
				if (cnt > 0)
					freeimg(&img);
				cnt = 0;
			} else {
				fscanf(f, "%s\n", img.magicword);
				img.tip = (strchr("36", img.magicword[1])) ? 3 : 1;
				if (strchr("456", img.magicword[1]))
					img = citire_binara(f, &img, cnt);
				else
					img = citire(f, &img, cnt);
				cnt++, fclose(f);
				printf("Loaded %s\n", nume_fisier);
			}
		} else if (strcmp("SELECT", comanda) == 0) {
			if (strlen(nume_fisier) == 1)
				printf("No image loaded\n");
			else
				select1(&img, comanda1);
		} else if (strcmp("HISTOGRAM", comanda) == 0) {
			if (strlen(nume_fisier) == 1)
				printf("No image loaded\n");
			else
				histograma(&img, comanda1);
		} else if (strcmp("EQUALIZE", comanda) == 0) {
			if (strlen(nume_fisier) == 1)
				printf("No image loaded\n");
			else
				equalize(&img);
		} else if (strcmp("ROTATE", comanda) == 0) {
			if (strlen(nume_fisier) == 1)
				printf("No image loaded\n");
			else
				rotatie1(&img, comanda1);
		} else if (strcmp("CROP", comanda) == 0) {
			if (strlen(nume_fisier) == 1)
				printf("No image loaded\n");
			else
				crop(&img);
		} else if (strcmp("APPLY", comanda) == 0) {
			if (strlen(nume_fisier) == 1)
				printf("No image loaded\n");
			else
				apply(&img, comanda1);
		} else if (strcmp("SAVE", comanda) == 0) {
			if (strlen(nume_fisier) == 1)
				printf("No image loaded\n");
			else
				save(&img, comanda1);
		} else if (strcmp("EXIT", comanda) == 0) {
			continua = 0;
			if (strlen(nume_fisier) != 1 && f)
				freeimg(&img);
			else
				printf("No image loaded\n");
		} else {
			printf("Invalid command\n");
		}
	}
	return 0;
}

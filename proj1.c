/**
 * @file      proj1.c
 * @author    R. R. Carvalho, 105607
 * @version   0.1
 * @date      2013-04-30T01:40-0300
 */



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define	MAXVLEN	1000000
#define TESTFILE "dados5000.txt"
#define VECTORLEN 5000



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * New Types' Definitions
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct
{
	int n_comp;
	clock_t t_exec;
} Performance;



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Functions' Prototypes
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void bubbleSort(int v[], int n);
void insertionSort(int v[], int n);
void selectionSort(int v[], int n);
void mergeSort(int v[], int n);
void quickSort(int v[], int n, int opcao);
int kSmallest(int v[], int n, int k);

Performance insertion_sort(int *V, int n);
Performance selection_sort(int *V, int n);
Performance bubble_sort(int *V, int n);

Performance partition(int *q, int *V, int p, int r);
Performance randomized_partition(int *q, int *V, int p, int r);
Performance quick_sort(int *V, int p, int r, Performance (*partition)(int *q, int *V, int p, int r));

Performance merge_sort(int *V, int p, int r);

Performance k_smallest(int *q, int *V, int n, int k);

int *read_vector(FILE *file, int n);
int random_index(int p, int r);
void swap(int *V, int a, int b);



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Main
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int frequency_of_primes (int n) {
  int i, j, q;
  int freq=n-1;
  for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
  return freq;
}

int main()
{
	int i, j, m, n, *V, q;
	FILE *file;
	Performance partial[100], mean;
/*
	file = fopen(TESTFILE, "r");
	n = VECTORLEN;
	if (!fscanf(file, " %d", &m)) {
		puts("Erro ao ler o numero de vetores.");
		exit(1);
	} else {
		for (i = 0; i < m; i++) {
			V = read_vector(file, n);
			partial[i] = bubble_sort(V,n);
			free(V);
		}
		mean.n_comp = 0;
		mean.t_exec = 0;
		for (i = 0; i < m; i++) {
			mean.n_comp += partial[i].n_comp;
			mean.t_exec += partial[i].t_exec;
		}
		mean.n_comp = mean.n_comp / 100;
		mean.t_exec = mean.t_exec / 100;
		printf("bubbleSort %f número_medio_de_comparações %f tempo_médio_de_execução\n", (double) mean.n_comp, (double)mean.t_exec / CLOCKS_PER_SEC);
	}
	fclose(file);

	file = fopen(TESTFILE, "r");
	n = VECTORLEN;
	if (!fscanf(file, " %d", &m)) {
		puts("Erro ao ler o numero de vetores.");
		exit(1);
	} else {
		for (i = 0; i < m; i++) {
			V = read_vector(file, n);
			partial[i] = insertion_sort(V,n);
			free(V);
		}
		mean.n_comp = 0;
		mean.t_exec = 0;
		for (i = 0; i < m; i++) {
			mean.n_comp += partial[i].n_comp;
			mean.t_exec += partial[i].t_exec;
		}
		mean.n_comp = mean.n_comp / 100;
		mean.t_exec = mean.t_exec / 100;
		printf("insertionSort %f número_medio_de_comparações %f tempo_médio_de_execução\n", (double) mean.n_comp, (double)mean.t_exec / CLOCKS_PER_SEC);
	}
	fclose(file);

	file = fopen(TESTFILE, "r");
	n = VECTORLEN;
	if (!fscanf(file, " %d", &m)) {
		puts("Erro ao ler o numero de vetores.");
		exit(1);
	} else {
		for (i = 0; i < m; i++) {
			V = read_vector(file, n);
			partial[i] = selection_sort(V,n);
			free(V);
		}
		mean.n_comp = 0;
		mean.t_exec = 0;
		for (i = 0; i < m; i++) {
			mean.n_comp += partial[i].n_comp;
			mean.t_exec += partial[i].t_exec;
		}
		mean.n_comp = mean.n_comp / 100;
		mean.t_exec = mean.t_exec / 100;
		printf("selectionSort %f número_medio_de_comparações %f tempo_médio_de_execução\n", (double) mean.n_comp, (double)mean.t_exec / CLOCKS_PER_SEC);
	}
	fclose(file);

	file = fopen(TESTFILE, "r");
	n = VECTORLEN;
	if (!fscanf(file, " %d", &m)) {
		puts("Erro ao ler o numero de vetores.");
		exit(1);
	} else {
		for (i = 0; i < m; i++) {
			V = read_vector(file, n);
			partial[i] = merge_sort(V,0,n-1);
			free(V);
		}
		mean.n_comp = 0;
		mean.t_exec = 0;
		for (i = 0; i < m; i++) {
			mean.n_comp += partial[i].n_comp;
			mean.t_exec += partial[i].t_exec;
		}
		mean.n_comp = mean.n_comp / 100;
		mean.t_exec = mean.t_exec / 100;
		printf("mergeSort %f número_medio_de_comparações %f tempo_médio_de_execução\n", (double) mean.n_comp, (double)mean.t_exec / CLOCKS_PER_SEC);
	}
	fclose(file);

	file = fopen(TESTFILE, "r");
	n = VECTORLEN;
	if (!fscanf(file, " %d", &m)) {
		puts("Erro ao ler o numero de vetores.");
		exit(1);
	} else {
		for (i = 0; i < m; i++) {
			V = read_vector(file, n);
			partial[i] = quick_sort(V, 0, n-1, partition);
			free(V);
		}
		mean.n_comp = 0;
		mean.t_exec = 0;
		for (i = 0; i < m; i++) {
			mean.n_comp += partial[i].n_comp;
			mean.t_exec += partial[i].t_exec;
		}
		mean.n_comp = mean.n_comp / 100;
		mean.t_exec = mean.t_exec / 100;
		printf("quickSort1 %f número_medio_de_comparações %f tempo_médio_de_execução\n", (double) mean.n_comp, (double)mean.t_exec / CLOCKS_PER_SEC);
	}
	fclose(file);

	file = fopen(TESTFILE, "r");
	n = VECTORLEN;
	if (!fscanf(file, " %d", &m)) {
		puts("Erro ao ler o numero de vetores.");
		exit(1);
	} else {
		for (i = 0; i < m; i++) {
			V = read_vector(file, n);
			partial[i] = quick_sort(V, 0, n-1, randomized_partition);
			free(V);
		}
		mean.n_comp = 0;
		mean.t_exec = 0;
		for (i = 0; i < m; i++) {
			mean.n_comp += partial[i].n_comp;
			mean.t_exec += partial[i].t_exec;
		}
		mean.n_comp = mean.n_comp / 100;
		mean.t_exec = mean.t_exec / 100;
		printf("quickSort2 %f número_medio_de_comparações %f tempo_médio_de_execução\n", (double) mean.n_comp, (double)mean.t_exec / CLOCKS_PER_SEC);
	}
	fclose(file);
*/

	file = fopen(TESTFILE, "r");
	n = VECTORLEN;
	if (!fscanf(file, " %d", &m)) {
		puts("Erro ao ler o numero de vetores.");
		exit(1);
	} else {
		for (i = 0; i < m; i++) {
			V = read_vector(file, n);
			partial[i] = k_smallest(&q, V, n, n/2);
			free(V);
		}
		mean.n_comp = 0;
		mean.t_exec = 0;
		for (i = 0; i < m; i++) {
			mean.n_comp += partial[i].n_comp;
			mean.t_exec += partial[i].t_exec;
		}
		mean.n_comp = mean.n_comp / 100;
		mean.t_exec = mean.t_exec / 100;
		printf("kSmallest %f número_medio_de_comparações %f tempo_médio_de_execução\n", (double) mean.n_comp, (double)mean.t_exec / CLOCKS_PER_SEC);
	}
	fclose(file);

	//out = insertion_sort(V,n);
	//out = selection_sort(V,n);
	//out = bubble_sort(V,n);

	//out = quick_sort(V, 0, n-1, randomized_partition);

	//out = merge_sort(V,0,n-1);


	return 0;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Insertion Sort
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
Performance insertion_sort(int *V, int n)
{
	int i, j, aux;
	Performance out = {0,0};

	out.t_exec = clock();
	for (j = 1; j < n; j++) {
		i = j;
		while ((i > 0) && (V[i-1] > V[i])) {
			out.n_comp++;
			swap(V, i-1, i);
			i--;
		}
	}
	out.t_exec = clock() - out.t_exec;

	return out;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Selection Sort
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
Performance selection_sort(int *V, int n)
{
	int i, j, m, aux;
	Performance out = {0,0};

	out.t_exec = clock();
	for (j = 0; j <= n; j++) {
		m = j;
		for (i = j+1; i < n; i++)
			if (V[i] < V[m]) {
				out.n_comp++;
				m = i;
			}
		if (j != m) {
			out.n_comp++;
			swap(V, j, m);
		}
	}
	out.t_exec = clock() - out.t_exec;

	return out;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Bubble Sort
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
Performance bubble_sort(int *V, int n)
{
	int i, j;
	Performance out = {0,0};

	out.t_exec = clock();
	do {
		j = 0;
		for (i = 1; i < n; i++) {
			if (V[i-1] > V[i]) {
				out.n_comp++;
				swap(V, i-1, i);
				j = i;
			}
		}
		n = j;
	} while (n);
	out.t_exec = clock() - out.t_exec;

	return out;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Quick Sort
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
Performance partition(int *q, int *V, int p, int r)
{
	int i, j, tmp;
	Performance out = {0,0};

	tmp = V[r];
	i = p - 1;
	for (j = p; j < r; j++)
		if (V[j] <= tmp) {
			out.n_comp++;
			swap(V, ++i, j);
		}
	swap(V, i+1, r);

	*q = i+1;

	return out;
}

Performance randomized_partition(int *q, int *V, int p, int r)
{
	Performance out = {0,0};

	swap(V, p, random_index(p, r));
	out = partition(q, V, p, r);

	return out;
}

Performance quick_sort(int *V, int p, int r, Performance (*part_func)(int *q, int *V, int p, int r))
{
	int q;
	Performance tmp, out = {0,0};

	out.t_exec = clock();
	if (p < r) {
		tmp = (*part_func)(&q, V, p, r);
		out.n_comp += tmp.n_comp;

		tmp = quick_sort(V, p, q-1, part_func);
		out.n_comp += tmp.n_comp;

		tmp = quick_sort(V, q+1, r, part_func);
		out.n_comp += tmp.n_comp;
	}
	out.t_exec = clock() - out.t_exec;

	return out;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Merge Sort
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
Performance merge(int *V, int p, int q, int r)
{
	int i, j, k, n1, n2, *L, *R;
	Performance out = {0,0};

	n1 = q-p+1;
	n2 = r-q;
	L = (int *) calloc(n1+1, sizeof(int));
	R = (int *) calloc(n2+1, sizeof(int));

	for (i = 0; i < n1; i++)
		L[i] = V[p+i];
	L[n1] = INT_MAX;

	for (j = 0; j < n2; j++)
		R[j] = V[q+1+j];
	R[n2] = INT_MAX;

	i = j = 0;
	for (k = p; k <= r; k++) {
		if (L[i] <= R[j]) {
			out.n_comp++;
			V[k] = L[i];
			i++;
		} else {
			out.n_comp++;
			V[k] = R[j];
			j++;
		}
	}

	free(L);
	free(R);

	return out;
}

Performance merge_sort(int *V, int p, int r)
{
	int q;
	Performance tmp, out = {0,0};

	out.t_exec = clock();
	if (p < r) {
		q = (p+r)/2;
		tmp = merge_sort(V, p, q);
		out.n_comp += tmp.n_comp;

		tmp = merge_sort(V, q+1, r);
		out.n_comp += tmp.n_comp;

		tmp = merge(V, p, q, r);
		out.n_comp += tmp.n_comp;
	}
	out.t_exec = clock() - out.t_exec;

	return out;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * k-th Order Statistic
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


Performance k_smallest(int *q, int *V, int n, int k)
{
	Performance tmp, out = {0,0};
	int i, j, l;

	int nsc = n / 5;
	int  U[nsc][5], M[nsc];

	if ( n <= 5 ) {
		tmp = insertion_sort(V, n);
		*q = V[n/2];
	} else {
		l = i = 0;
		while (i < n) {
			for (j = 0; j < 5; j++)
				U[l][j] = V[i++];
			tmp = insertion_sort(U[l++], 5);
			out.n_comp += tmp.n_comp;
		}
		for (i = 0; i < nsc; i++) {
			M[i] = U[i][2];
		}

		tmp = k_smallest(q, M, nsc, nsc/2);
		out.n_comp += tmp.n_comp;

		/*for ( l = 0; l < nsc; l++ ) {
			for ( i = 0; i < 5; i++ ) {
				printf(" %d",U[l][i]);
			}
			puts("");
		}*/
	}

	return out;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Helper Functions
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int *read_vector(FILE *file, int n)
{
	int i, *V;

	V = (int *) calloc(n, sizeof(int));
	for(i = 0; i < n; i++)
		if (!fscanf(file, " %d", &V[i])) {
			puts("Erro ao ler um elemento do vetor.");
			free(V);
			exit(1);
		}

	return V;
}

int random_index(int p, int r)
{
	time_t ts;

	time(&ts);
	srand((unsigned int) ts);

	return (rand()%(r - p +1) + p);
}

void swap(int *V, int a, int b)
{
	int aux;
	aux = V[a];
	V[a] = V[b];
	V[b] = aux;
}

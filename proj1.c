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

#define	MAXVLEN	1000000



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * New Types' Definitions
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct
{
	int n_comp;
	float t_exec;
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

Performance k_smallest(int *V, int n);

int *read_vector(int n);
int random_index(int p, int r);
void swap(int *V, int a, int b);



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Main
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int main()
{
	int i, n, *V, q;
	Performance out;
/*
	if (!scanf(" %d", &n)) {
		puts("Erro ao ler o tamanho do vetor.");
		exit(1);
	}
	else
		V = read_vector(n);
*/
	V = (int *) calloc(10, sizeof(int));

	V[0]=34;
	V[1]=75;
	V[2]=37;
	V[3]=97;
	V[4]=25;
	V[5]=72;
	V[6]=44;
	V[7]=83;
	V[8]=43;
	V[9]=12;

	out = quick_sort(V, 0, 9, randomized_partition);

	printf("Foram feitas %d comparações para ordenar o vetor.\n", out.n_comp);
	for (i = 0; i < 10; i++)
		printf("%d ", V[i]);
	puts("");

	free(V);


	return 0;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Insertion Sort
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
Performance insertion_sort(int *V, int n)
{
	int i, j, aux;
	Performance out = {0,0};

	for (j = 1; j < n; j++) {
		i = j;
		while ((i > 0) && (V[i-1] > V[i])) {
			out.n_comp++;
			swap(V, i-1, i);
			i--;
		}
	}

	return out;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Selection Sort
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
Performance selection_sort(int *V, int n)
{
	int i, j, m, aux;
	Performance out = {0,0};

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

	return out;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Bubble Sort
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
Performance bubble_sort(int *V, int n)
{
	int i, j;
	Performance out = {0,0};

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

	return out;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Quick Sort
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
Performance partition(int *q, int *V, int p, int r)
{
	int i, j, tmp;
	Performance out = {0,0};

	tmp = V[p];
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

	if (p < r) {
		tmp = (*part_func)(&q, V, p, r);
		out.n_comp += tmp.n_comp;
		out.t_exec += tmp.t_exec;

		tmp = quick_sort(V, p, q-1, part_func);
		out.n_comp += tmp.n_comp;
		out.t_exec += tmp.t_exec;

		tmp = quick_sort(V, q+1, r, part_func);
		out.n_comp += tmp.n_comp;
		out.t_exec += tmp.t_exec;
	}

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

	if (p < r) {
		q = (p+r)/2;
		tmp = merge_sort(V, p, q);
		out.n_comp += tmp.n_comp;
		out.t_exec += tmp.t_exec;

		tmp = merge_sort(V, q+1, r);
		out.n_comp += tmp.n_comp;
		out.t_exec += tmp.t_exec;

		tmp = merge(V, p, q, r);
		out.n_comp += tmp.n_comp;
		out.t_exec += tmp.t_exec;
	}

	return out;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * k-th Order Statistic
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Helper Functions
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int *read_vector(int n)
{
	int i, *V;

	V = (int *) calloc(n, sizeof(int));
	for(i = 0; i < n; i++)
		if (!scanf(" %d", &V[i])) {
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

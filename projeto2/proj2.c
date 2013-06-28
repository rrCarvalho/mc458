/**
 * @file      proj2.c
 * @author    R. R. Carvalho, 105607
 * @version   0.1
 * @date      2013-05-27T19:30-0300
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <string.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

const unsigned int DELETE = 1;
const unsigned int INSERT = 4;
const unsigned int COPY = 3;
const unsigned int REPLACE = 1;
const unsigned int TWIDDLE = 1;
const unsigned int KILL = 1;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

const unsigned int BUFFERLEN = 32;
const unsigned int MAX_EDIT = 1024;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef struct {
	char o;				/* operação */
	union {
		char c;			/* caracter inserido/trocado */
		int n;			/* ou posição do kill */
	};
} operation_t;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void editDistance( char *x, char *y, int m, int n, int ***c, operation_t ***op )
{
	int i, j;

	for ( i = 0; i <= m; i++ ) {
		(*c)[i][0] = i*DELETE;
		(*op)[i][0].o = 'd';
	}
	for ( j = 0; j <= n; j++ ) {
		(*c)[0][j] = j*INSERT;
		(*op)[0][j].o = 'i';
	}
	for ( i = 1; i <= m; i++ ) {
		for ( j = 1; j <= n; j++ ) {
			(*c)[i][j] = INT_MAX;
			if ( x[i] == y[j] ) {
				(*c)[i][j] = (*c)[i-1][j-1] + COPY;
				(*op)[i][j].o = 'c';
			}
			if ( x[i] != y[j] ) {
				(*c)[i][j] = (*c)[i-1][j-1] + REPLACE;
				(*op)[i][j].o = 'r';
				(*op)[i][j].c = y[j];
			}
			if ( i >= 2 && j >= 2
			&& x[i] == y[j-1] && x[i-1] == y[j]
			&& ((*c)[i-2][j-2] + TWIDDLE) < (*c)[i][j] ) {
				(*c)[i][j] = (*c)[i-2][j-2] * TWIDDLE;
				(*op)[i][j].o = 't';
			}
			if ( ((*c)[i-1][j] + DELETE) < (*c)[i][j] ) {
				(*c)[i][j] = (*c)[i-1][j] + DELETE;
				(*op)[i][j].o = 'd';
			}
			if ( ((*c)[i][j-1] + INSERT) < (*c)[i][j] ) {
				(*c)[i][j] = (*c)[i][j-1] + INSERT;
				(*op)[i][j].o = 'i';
				(*op)[i][j].c = y[j];
			}
		}
	}
	for ( i = 0; i <= m-1; i++ ) {
		if ( ((*c)[i][n] + KILL) < (*c)[m][n] ) {
			(*c)[m][n] = (*c)[i][n] + KILL;
			(*op)[m][n].o = 'k';
			(*op)[m][n].n = i;
		}
	}
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void opSequence( operation_t **op, int p, int q )
{
	int i, j;

	if ( p == 0 && q == 0 )
		return;
	if ( op[p][q].o == 'c' || op[p][q].o == 'r' ) {
		i = p-1;
		j = q-1;
	} else
	if ( op[p][q].o == 't' ) {
		i = p-2;
		j = q-2;
	} else
	if ( op[p][q].o == 'd' ) {
		i = p-1;
		j = q;
	} else
	if ( op[p][q].o == 'i' ) {
		i = p;
		j = q-1;
	} else {
		i = op[p][q].n;
		j = q;
	}
	opSequence( op, i, j );
	printf( " %c", op[p][q].o );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int freadl( char **line, FILE *fh )
{
	char c;
	char *buffer, *lnew, *lout;
	unsigned int llen;
	unsigned int blen;

	lout = (char *)calloc( BUFFERLEN, sizeof( char ) );

	llen = 0;
	do {
		blen = 0;
		buffer = (char *)calloc( BUFFERLEN, sizeof( char ) );
		do {
			c = (char)fgetc( fh );
			strncat( buffer, &c , 1 );
			blen++;
		} while ( blen < BUFFERLEN && buffer[blen - 1] != '\n' && !feof( fh ) );
		lnew = (char *)calloc( llen + blen, sizeof( char ) );
		strncpy( lnew, lout, llen );
		strncat( lnew, buffer, blen );
		llen += blen;
		free( lout );
		lout = lnew;
		free( buffer );
	} while ( lout[llen - 1] != '\n' );
	llen -= 1;

	*line = (char *)calloc( llen, sizeof( char ) );
	strncpy( *line, lout, llen );
	free( lout );

	return llen;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int main ( int argc, char *argv[] )
{
	FILE *fh;
	int linelen;
	char *line;
	int i,j;


	fh = fopen( argv[1], "r" );
	if ( fh == NULL ) {
		fprintf( stderr, "Couldn't open file.\n" );
		exit( EXIT_FAILURE );
	}


	char *x = (char *)calloc( 24, sizeof( char ) );
	strncpy( x, " Como pode um peixe vivo", 24 );
	char *y = (char *)calloc( 16, sizeof( char ) );
	strncpy( y, " Love of my life", 16 );

	int **c = (int **)calloc( 24, sizeof( int * ) );
	for ( i = 0; i <= 23; i++ )
		c[i] = (int *)calloc( 16, sizeof( int ) );

	operation_t **op = (operation_t **)calloc( 24, sizeof( operation_t * ) );
	for ( i = 0; i <= 23; i++ )
		op[i] = (operation_t *)calloc( 16, sizeof( operation_t ) );

	editDistance( x, y, 23, 15, &c, &op );

	for ( i = 0; i <= 23; i++ ) {
		for ( j = 0; j <= 15; j++ ) {
			printf( "\t%d", c[i][j] );
		}
		printf( "\n" );
	}

	printf( "\n\n" );

	for ( i = 0; i <= 23; i++ ) {
		for ( j = 0; j <= 15; j++ ) {
			printf( "\t%c", op[i][j].o );
		}
		printf( "\n" );
	}

	opSequence( op, 23, 15 );

	fclose( fh );

	return 0;
}

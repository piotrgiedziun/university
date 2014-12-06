/**
* parms
* top left bottom right
*
* example:
* 0 0 10 10
*/
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>

#define MATRIX_WIDTH				2016
#define MATRIX_HEIGHT				2016
#define MATRIX_SIZE					MATRIX_WIDTH*MATRIX_HEIGHT
#define TILE_WIDTH					48//48
#define TILE_HEIGHT					48//48
#define ELEMENTS_PER_THREAD_Y		16
#define ROWS_PER_THREAD				2
#define ELEMENTS_PER_MATRIX_ROW		MATRIX_WIDTH*TILE_HEIGHT
#define TILE_SIZE					TILE_WIDTH*TILE_HEIGHT
#define INIT_THREADS_PER_BLOCK		256
#define INIT_ELEMENTS_PER_THREAD	90 
#define INIT_ELEMENTS_PER_BLOCK		INIT_ELEMENTS_PER_THREAD*INIT_THREADS_PER_BLOCK

#define TILE_DIM 32
#define BLOCK_ROWS 8

// window struct
struct WINDOW {
	int top;
	int left;
	int bottom;
	int right;
} show_window = { 0, 0, 10, 10 };

/*
* Matrix transpose - device function 
* ----------------------------------------
* Description:
* 	this function transpose matrix element block by block
*	and line by line
* Parms:
* 	- idata (int*)	- input matrix
*	- odata (int*)	- output matix (allocated alrea)
*/
__global__ void transpose_matrix(int* idata, int* odata) {
	// allocate shared memory
	__shared__ int tile[TILE_HEIGHT][TILE_WIDTH];
	
	// estimate current position
	int inputPos = blockIdx.y*ELEMENTS_PER_MATRIX_ROW + blockIdx.x*TILE_WIDTH;
	int outputPos = blockIdx.x*ELEMENTS_PER_MATRIX_ROW + blockIdx.y*TILE_WIDTH;
	int coPos;
	int startPos = threadIdx.y*ROWS_PER_THREAD;
	
	// copy to shared memory
	for(int j=0; j <= ROWS_PER_THREAD-1; j++) {
		coPos = startPos*MATRIX_WIDTH + (MATRIX_WIDTH*j);
		for(int i=threadIdx.x; i < TILE_WIDTH; i+=ELEMENTS_PER_THREAD_Y) {
			tile[startPos+j][i] = idata[inputPos+i+coPos];	
		}
	}

	__syncthreads();

	// copy back to global memory
	for(int j=0; j <= ROWS_PER_THREAD-1; j++) {
		coPos = startPos*MATRIX_WIDTH + (MATRIX_WIDTH*j);
		for(int i=threadIdx.x; i < TILE_WIDTH; i+=ELEMENTS_PER_THREAD_Y) {
			odata[outputPos+i+coPos] = tile[i][startPos+j];
		}
	}

}

/*
* Initialize matrix - device function 
* ----------------------------------------
* Description:
* 	this function initialze matrix INIT_ELEMENTS_PER_THREAD elements by elements
* Parms:
* 	- idata (int*)	- matrix
*	- size (int)	- matrix size (number of elements)
*/
__global__ void init_matrix( int *idata, int size ) {
	int	elements_count;
	int start_id = (threadIdx.x * INIT_ELEMENTS_PER_THREAD );
	
	// set elements count
	if ( start_id+INIT_ELEMENTS_PER_THREAD > size ) {
		elements_count = size-start_id;
	}else{
		elements_count = INIT_ELEMENTS_PER_THREAD;
	}
	
	// set elementsPerThread elements
	int value = start_id + ( blockIdx.x * INIT_ELEMENTS_PER_BLOCK );
	for( int i=0; i < elements_count; i++ )
		idata[value+i] = value+i;
}

__global__ void init_matrix_zero( int *idata, int size ) {
	int	elements_count;
	int start_id = (threadIdx.x * INIT_ELEMENTS_PER_THREAD );
	
	// set elements count
	if ( start_id+INIT_ELEMENTS_PER_THREAD > size ) {
		elements_count = size-start_id;
	}else{
		elements_count = INIT_ELEMENTS_PER_THREAD;
	}
	
	// set elementsPerThread elements
	int value = start_id + ( blockIdx.x * INIT_ELEMENTS_PER_BLOCK );
	for( int i=0; i < elements_count; i++ )
		idata[value+i] = 0;
}

/*
* Print matrix window - host function
* ----------------------------------------
* Description:
* 	this function copy data form device
* 	and print output to screen
* 	host matrix size has to be the same as device matrix size
* Pamrs:
*	- h_matrix (int*) - host matrix
*	- d_matrix (int*) - device matrix
*	- start_height, start_width, end_height, end_width (int) - displaying area
*/
void print_matrix_window(int* h_matrix, int* d_matrix, int start_height, int start_width, int end_height, int end_width ) {
	cudaMemcpy( h_matrix, d_matrix, sizeof(int)*MATRIX_SIZE, cudaMemcpyDeviceToHost);
	printf("--------------------\n");
	for(int y=start_height; y < end_height; y++) {
		for(int x=start_width; x < end_width; x++) {
			printf("%d\t", h_matrix[x + ( y * MATRIX_WIDTH ) ]);
		}
		printf("\n");
	}
}

/*
* return GB per second for given data
*/
double GBperSec(float runtime, double bytes) {
	return 100*(bytes/1073741824)/runtime;
}

int main( int argc, char *argv[]) {
	if( argc > 4) {
		show_window.top=atoi(argv[1]);
		show_window.left=atoi(argv[2]);
		show_window.bottom=atoi(argv[3]);
		show_window.right=atoi(argv[4]);
	}
	
	int *d_idata, *d_odata, *h_matrix, blocks_count;
	cudaEvent_t init_start, init_end;
	float init_time;
	// create init events
	cudaEventCreate(&init_start);
	cudaEventCreate(&init_end);
	cudaEvent_t transpose_start, transpose_end;
	float transpose_time;
	// create transpose events
	cudaEventCreate(&transpose_start);
	cudaEventCreate(&transpose_end);

	// size validation
	if ( MATRIX_WIDTH % TILE_WIDTH != 0
	 	|| MATRIX_HEIGHT % TILE_HEIGHT != 0) {
		printf("Invalid matrix size\n");
		return 1;
	}

	cudaMalloc( (void**)&d_idata, sizeof(int) * MATRIX_SIZE );
	cudaMalloc( (void**)&d_odata, sizeof(int) * MATRIX_SIZE );
	h_matrix = new int[ MATRIX_SIZE ];
	
	// matrix initialization
	// set data to global memory
	blocks_count = ceil(((MATRIX_SIZE+INIT_THREADS_PER_BLOCK-1)/INIT_THREADS_PER_BLOCK)/INIT_ELEMENTS_PER_THREAD);
	
	cudaEventRecord(init_start, 0);
 
	init_matrix<<< blocks_count, INIT_THREADS_PER_BLOCK >>>(d_idata, MATRIX_SIZE);
	init_matrix_zero<<< blocks_count, INIT_THREADS_PER_BLOCK >>>(d_odata, MATRIX_SIZE);
	
	cudaEventRecord(init_end, 0);
	cudaEventSynchronize(init_end);
	cudaEventElapsedTime(&init_time, init_start, init_end);
	
	printf("init matrix:\n\tblocks count: %d\n\tthreads per block: %d\n\telements per thread: %d\n\ttime: %f ms\n\tspeed: %lf GB/s\n",
		blocks_count, INIT_THREADS_PER_BLOCK, INIT_ELEMENTS_PER_THREAD, init_time, GBperSec(init_time, MATRIX_SIZE*sizeof(int)));
	print_matrix_window(h_matrix, d_idata, show_window.top, show_window.left, show_window.bottom, show_window.right);
	
	dim3 blocks(MATRIX_HEIGHT/TILE_HEIGHT, MATRIX_WIDTH/TILE_HEIGHT);
	dim3 threads(ELEMENTS_PER_THREAD_Y, TILE_WIDTH/ROWS_PER_THREAD);

	cudaEventRecord(transpose_start, 0);

	transpose_matrix<<< blocks, threads >>>(d_idata, d_odata);
	
	cudaEventRecord(transpose_end, 0);
	cudaEventSynchronize(transpose_end);
	cudaEventElapsedTime(&transpose_time, transpose_start, transpose_end);

	printf("\ntranspose matrix:\n\tblocks count x: %d\n\tblocks count y: %d\n\tthreads count x: %d\n\tthreads count y: %d\n\ttime: %f ms\n\tspeed: %lf GB/s\n",
		MATRIX_HEIGHT/TILE_HEIGHT, MATRIX_WIDTH/TILE_HEIGHT, ELEMENTS_PER_THREAD_Y, TILE_WIDTH/ROWS_PER_THREAD,
	 transpose_time, GBperSec(transpose_time, MATRIX_SIZE*sizeof(int)));
	print_matrix_window(h_matrix, d_odata, show_window.top, show_window.left, show_window.bottom, show_window.right);
		
	// clear memory allocation
	cudaFree( d_idata );
	cudaFree( d_odata );
	delete [] h_matrix;
	return 0;
}

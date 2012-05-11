#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>

#define MATRIX_WIDTH				2025
#define MATRIX_HEIGHT				2025
#define MATRIX_SIZE					4100625
#define TAIL_WIDTH					45
#define TAIL_HEIHGT					45
#define INIT_THREADS_PER_BLOCK		256
#define INIT_ELEMENTS_PER_THREAD	90 

// simple set to testing
// #define MATRIX_WIDTH				10
// #define MATRIX_HEIGHT			10
// #define MATRIX_SIZE				100
// #define TAIL_WIDTH				45
// #define TAIL_HEIHGT				45
// #define INIT_THREADS_PER_BLOCK	2
// #define INIT_ELEMENTS_PER_THREAD	2

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
	__shared__ int shared_input[TAIL_HEIHGT][TAIL_WIDTH];
	__shared__ int shared_output[TAIL_HEIHGT][TAIL_WIDTH];
	
	// estimate current position
	int line = threadIdx.x;
	int blok = blockIdx.x;
	
	// local data from global memory (idata) to shared memory (shared_input)
	
	// transose line to shared memory (shared_output)
	
	// export converted data to output
	//__syncthreads();
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
	int	elements_count,
		start_id = threadIdx.x + (blockIdx.x * INIT_THREADS_PER_BLOCK );
	
	// set elements count
	if ( start_id+INIT_ELEMENTS_PER_THREAD > size ) {
		elements_count = size-start_id;
	}else{
		elements_count = INIT_ELEMENTS_PER_THREAD;
	}
	
	// set elementsPerThread elements
	for( int i=start_id; i < elements_count; i++ )
		idata[i] = i;
}

// slower version
__global__ void init_matrix_cpy( int *idata, int size ) {
	int init_values[INIT_ELEMENTS_PER_THREAD], // temp array of inital values
	 	elements_count,
		start_id = ( threadIdx.x + (blockIdx.x * blockDim.x) );
	
	// set elements count
	if ( start_id+INIT_ELEMENTS_PER_THREAD > size ) {
		elements_count = size-start_id;
	}else{
		elements_count = INIT_ELEMENTS_PER_THREAD;
	}
	
	// set elementsPerThread elements
	for( int i=0; i < elements_count; i++ )
		init_values[i] = i;
	
	// copy initial data to global memoory (idata)	
	 memcpy(idata+start_id, init_values, elements_count * sizeof(int));
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


double GBperSec(float runtime, double bytes) {
	return 100*(bytes/1073741824)/runtime;
}

int main(void) {
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
	if ( MATRIX_WIDTH % TAIL_WIDTH != 0
	 	|| MATRIX_HEIGHT % TAIL_HEIHGT != 0) {
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
	cudaEventRecord(init_end, 0);
	cudaEventSynchronize(init_end);
	cudaEventElapsedTime(&init_time, init_start, init_end);
	
	printf("init matrix:\n\tblocks count: %d\n\tthreads per block: %d\n\telements per thread: %d\n\ttime: %f ms\n\tspeed: %lf GB/s\n",
		blocks_count, INIT_THREADS_PER_BLOCK, INIT_ELEMENTS_PER_THREAD, init_time, GBperSec(init_time, MATRIX_SIZE*sizeof(int)));
	print_matrix_window(h_matrix, d_idata, 0, 0, 10, 10);
	
	blocks_count = MATRIX_SIZE / (TAIL_WIDTH*TAIL_HEIHGT);
	
	cudaEventRecord(transpose_start, 0);
	transpose_matrix<<< blocks_count, TAIL_HEIHGT >>>(d_idata, d_odata);
	cudaEventRecord(transpose_end, 0);
	cudaEventSynchronize(transpose_end);
	cudaEventElapsedTime(&transpose_time, transpose_start, transpose_end);

	printf("\ntranspose matrix:\n\tblocks count: %d\n\tthreads per block: %d\n\ttime: %f ms\n\tspeed: %lf GB/s\n",
		blocks_count, TAIL_HEIHGT, transpose_time, GBperSec(transpose_time, MATRIX_SIZE*sizeof(int)));
	//print_matrix_window(h_matrix, d_odata, 0, 0, 10, 10);
		
	// clear memory allocation
	cudaFree( d_idata );
	cudaFree( d_odata );
	delete [] h_matrix;
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>

#define MATRIX_WIDTH				2025
#define MATRIX_HEIGHT				2025
#define MATRIX_SIZE					MATRIX_WIDTH*MATRIX_HEIGHT
#define TILE_WIDTH					45
#define TILE_HEIGHT					45
#define INIT_THREADS_PER_BLOCK		256
#define INIT_ELEMENTS_PER_THREAD	90 
#define INIT_ELEMENTS_PER_BLOCK		INIT_ELEMENTS_PER_THREAD*INIT_THREADS_PER_BLOCK

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
__global__ void transpose_matrix(int* idata, int* odata, int block_per_row) {
	// allocate shared memory
	__shared__ int shared_input[TILE_HEIGHT][TILE_WIDTH];
	__shared__ int shared_output[TILE_WIDTH][TILE_HEIGHT];
	
	// estimate current position
	int line = threadIdx.x;
	int block = blockIdx.x;
	
	// local data from global memory (idata) to shared memory (shared_input)
	int block_row = (block/block_per_row);
	int block_column = block % block_per_row;
	
	// cpy
	int block_start_pos =(block_row * (TILE_HEIGHT*MATRIX_WIDTH) + (block_column*TILE_WIDTH + (line*MATRIX_WIDTH))); //(block_row*TILE_HEIGHT+(line*MATRIX_WIDTH));
	//int block_shift = TILE_WIDTH*block;
	
	for(int i=0; i < TILE_WIDTH; i++) {
		shared_input[line][i] = idata[block_start_pos+i];
	}
	
	// single transposition blok
	for(int i=0;i<TILE_WIDTH;i++)
	{
		shared_output[i][line] = shared_input[line][i];
	}

__syncthreads();
	if(block == 0) {
		block_start_pos = (block_column * (TILE_WIDTH*MATRIX_HEIGHT) + (block_row*TILE_HEIGHT + (line*MATRIX_HEIGHT)));
		for(int i=0; i<TILE_HEIGHT; i++) {
			odata[block_start_pos+i] = shared_output[line][i];
 		}
	//v 2 memcpy
	//memcpy( odata, shared_output, TILE_HEIGHT * sizeof(int) );  // TODO: napisac poprawnie zapisywanie wynikow w macierzy wynikowej
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

int main(void) {
	int number_of_device,device_number;
	cudaGetDeviceCount(&number_of_device);
	if(number_of_device >0){
		for(device_number=0;device_number<number_of_device; device_number++){
			cudaDeviceProp device_prop;
			cudaGetDeviceProperties(&device_prop, device_number);
			printf("number of device: %d prop: %s\n",device_number, device_prop.name);
		}
	}

	int *d_idata, *d_odata, *h_matrix, blocks_count, block_per_row;
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
	
	cudaEventRecord(init_end, 0);
	cudaEventSynchronize(init_end);
	cudaEventElapsedTime(&init_time, init_start, init_end);
	
	printf("init matrix:\n\tblocks count: %d\n\tthreads per block: %d\n\telements per thread: %d\n\ttime: %f ms\n\tspeed: %lf GB/s\n",
		blocks_count, INIT_THREADS_PER_BLOCK, INIT_ELEMENTS_PER_THREAD, init_time, GBperSec(init_time, MATRIX_SIZE*sizeof(int)));
	print_matrix_window(h_matrix, d_idata, 0, 0, 10, 10);
	
	blocks_count = MATRIX_SIZE / (TILE_WIDTH*TILE_HEIGHT);
	block_per_row = MATRIX_WIDTH/TILE_WIDTH;
	
	cudaEventRecord(transpose_start, 0);

	transpose_matrix<<< blocks_count, TILE_HEIGHT >>>(d_idata, d_odata, block_per_row);
	
	cudaEventRecord(transpose_end, 0);
	cudaEventSynchronize(transpose_end);
	cudaEventElapsedTime(&transpose_time, transpose_start, transpose_end);

	printf("\ntranspose matrix:\n\tblocks count: %d\n\tthreads per block: %d\n\tblock per row: %d\n\ttime: %f ms\n\tspeed: %lf GB/s\n",
		blocks_count, TILE_HEIGHT, block_per_row, transpose_time, GBperSec(transpose_time, MATRIX_SIZE*sizeof(int)));
	print_matrix_window(h_matrix, d_odata, 0, 0, 10, 10);
		
	// clear memory allocation
	cudaFree( d_idata );
	cudaFree( d_odata );
	delete [] h_matrix;
	return 0;
}

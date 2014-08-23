#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void init_matrix(int* matrix, int width, int height) {
 srand(time(NULL));
 for(int y=0; y<height; y++) {
  for(int x=0; x<width; x++) {
   matrix[x+(y*width)] = rand()%10;
  }
 }
}

void print_matrix(int* matrix, int width, int height) {
 printf("--------------------\n");
 for(int y=0; y<height; y++) {
  for(int x=0; x<width; x++) {
   printf("%d ", matrix[x+(y*width)]);
  }
  printf("\n");
 }
}

void transpose_matrix(int* input, int* output, int width, int height) {
 for(int y=0; y<height; y++) {
  for(int x=0; x<width; x++) {
   output[y + (x * height)] = input[x + (y*width)];
  }
 }
}

void doIt(double &t1,double &t2 ) {
 int width = 2016;
 int height = 2016;
 int *input = new int[width*height];
 int *output = new int[width*height];
 clock_t clock_start,clock_end;

 //init matix with random values
 clock_start = clock();
 init_matrix(input, width, height);
 clock_end = clock();
 t1 = (clock_end-clock_start)/(double)CLOCKS_PER_SEC;
//printf("czas wykonania algorytmu : %f\n",(clock_end-clock_start)/(double)CLOCKS_PER_SEC); 
//print_matrix(input, width, height);

 clock_start = clock();
 transpose_matrix(input, output, width, height);
 clock_end = clock();
 t2 = (clock_end-clock_start)/(double)CLOCKS_PER_SEC;
//printf("czas wykonania algorytmu : %f\n",(clock_end-clock_start)/(double)CLOCKS_PER_SEC); 
//print_matrix(output, height, width);

 delete [] input;
 delete [] output;
}

int main(void)
{
int n;
double t1,t2,avg,avg1,avg2,sumt1=0,sumt2=0;
printf("podaj liczbe prob: \n");
scanf("%d",&n);
	for(int i=0;i<n;i++)
	{	
		doIt(t1,t2);
		sumt1+=t1;
		sumt2+=t2;
	}
printf("sredni czas wykonania calego algorytmu: %f\n", (sumt1+sumt2)/n);
printf("sredni czas wykonania alokacji: %f\n", sumt1/n);
printf("sredni czas wykonania transpozycji: %f\n",sumt2/n);
}

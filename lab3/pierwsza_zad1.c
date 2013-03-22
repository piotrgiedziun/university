/**
* Obliczanie ilosci liczb pierwszych z zadanego zakresu
*
* usage:
* ./pierwsza_zad1 [zakres_start] [zakres_end]
*/
#include <stdlib.h>

int pierwsza(int n)  {
	int i = 0;
	for(i=2;i*i<=n;i++) { 
		if(n%i == 0) return 0; 
	}
	return 1; 
} 

// argv[1] -> start
// argv[2] -> stop
int main(int argc, char* argv[]) {
	int i,
	pierwsze = 0,
	start = atoi(argv[1]),
        end = atoi(argv[2]);

	for(i = start; i < end; i++) {
		if( pierwsza(i) == 1 )
			pierwsze++;
	}
	exit(pierwsze);
	return i;
}

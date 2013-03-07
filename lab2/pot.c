#include <stdlib.h>

// argv[1] -> id
// argv[2] -> steps
int main(int argc, char* argv[]) {
	int i;
	for(i = 0; i<atoi(argv[2]); i++) {
		printf("[child %d] step %d\n", atoi(argv[1]), i);
		sleep(1);
	}
	exit(i);
	return i;
}



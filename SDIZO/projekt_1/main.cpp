#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>
#include <queue>
#include <iomanip>


#include "node.h"
#include "lista_nastepnikow.h"
#include "edge_list.h"

using namespace std;

/*
 * define constants
 */
const int INFINITY = INT_MAX; //max_value = 100
char *file_name = "input/4.jjd";
bool type_matrix = true;
bool type_dijkstra = false;

/*
 * define structures
 */
priority_queue< node, vector<node>, greater<node> > pq;
//list<nastepnik> *list_repr;
nastepnik *list_repr;
edgesList *edges_list;
node *n;
int **matrix;

/*
 * define variables
 */
int nodes_count;
int edges_count;


void read_from_file_matrix() {
	ifstream file;
	string line;

	file.open(file_name);

	file >> nodes_count;
	file >> edges_count;

	/*
	 * initialize lists
	 */
	matrix = new int*[nodes_count+1] ;
	edges_list = new edgesList((edges_count+1));
	for( int i = 1 ; i <= nodes_count ; i++ )
		matrix[i] = new int[edges_count+1];

	/*
	 * read data to list
	 */
	int i = 0; //line counter
	int j = 1; //eged counter
	int index, value;
	while ( getline(file, line) ) {
		istringstream iss(line);

		while (iss >> index) {
			iss >> value;
			//cout << i << "," << j << "," << index << "," << value << endl;
			if(edges_list->isset(i, index) || edges_list->isset(index, i)){
				continue;
			}
			edges_list->add(i, index, value);
			matrix[i][j] = value;
			//matrix[index][j] = value;
			matrix[index][j] = -value;
			j++;
		}
		i++;
	}
}

void read_from_file_list() {
	ifstream file;
	string line;

	file.open(file_name);

	file >> nodes_count;
	file >> edges_count;

	/*
	 * initialize lists
	 */
	//list_repr = new list<nastepnik>[nodes_count+1];
	list_repr = new nastepnik[nodes_count+1];
	edges_list = new edgesList((edges_count+1));

	/*
	 * read data to list
	 */
	int i = 0; //line counter
	int index, value;
	nastepnik *item;
	nastepnik n;

	while ( getline(file, line) ) {
		istringstream iss(line);

		//list_repr[i] = NULL;

		item = &list_repr[i];

		while (iss >> index) {
			iss >> value;

			//sprawdza czy juz dodano
			if(edges_list->isset(i, index) || edges_list->isset(index, i)){
				continue;
			}
			n.id = index;
			n.d = value;

			//list_repr[i].push_back(n);
			item->n = new nastepnik(index, value);
			item = item->n;


			edges_list->add(i, index, value);
		}
		i++;

	}
}

bool dijkstra_list() {
	// Tworzy listę odległości
	n = new node[nodes_count+1];

	/*
	 * initialize distance list
	 * 1 					-> 0
	 * 2 - nodes_count+1 	-> INFINITY
	 */
	for(int i=1; i <= nodes_count; i++) {
		n[i].d = INFINITY;
		n[i].id = i;
		n[i].p = NULL;
	}
	n[1].d = 0;

	node u, *v;
	nastepnik *item;
	int w;

	pq.push(n[1]);

	while(!pq.empty()) {
		// Zdejmuje minimum
		u = pq.top();

		// Dla sasiadów
		//for(list<nastepnik>::iterator v_id = list_repr[u].begin(); v_id != list_repr[u].end(); ++v_id) {
		item = (list_repr[u].n);

		while(item != NULL) {
			//v = &n[v_id->id];
			v = &n[item->id];

			w = item->d;
			if (v->d > (u.d + w)) {
				v->d = u.d + w;
				v->p = &u;
				pq.push(*v);
			}

			item = item->n;

		}
		//}
		pq.pop();
	}
	return true;
}

bool dijkstra_matrix() {
	// Tworzy listę odległości
	n = new node[nodes_count+1];

	/*
	 * initialize distance list
	 * 1 					-> 0
	 * 2 - nodes_count+1 	-> INFINITY
	 */
	for(int i=1; i<=nodes_count; i++) {
		n[i].d = INFINITY;
		n[i].id = i;
	}
	n[1].d = 0;

	node u, *v;
	int w;

	pq.push(n[1]);

	while(!pq.empty()) {

			u = pq.top();
			u.v = true;
			//find edge
				for(int e = 1; e <= edges_count; e++) {
					if(matrix[u][e] > 0) {

						for(int cn = 1; cn <= nodes_count; cn++) {
							if(matrix[cn][e] < 0 && !n[cn].v) {

								//cout << "found: " << u << " -> " << cn << " (" << matrix[u][e] << ")" << endl;

									v = &(n[cn]);

									w = u.d + matrix[u][e];
									if (v->d > w ) {
										v->d = w;

										pq.push(*v);
									}


								break;
							}

						}
						//continue;
					}
				}

				pq.pop();
			}
	return true;
}

bool ford_bellman_matrix() {
	// Tworzy listę odległości
		n = new node[nodes_count+1];

		/*
		 * initialize distance list
		 * 1 					-> 0
		 * 2 - nodes_count+1 	-> INFINITY
		 */
		for(int i=1; i<=nodes_count; i++) {
			n[i].d = INFINITY;
			n[i].id = i;
		}
		n[1].d = 0;

		node u, *v;
		nastepnik *item;
		int w;

		//for(int i = 1; i <= nodes_count; i++) {
			for(int j = 1; j <= nodes_count; j++) {
				u = n[j];
				for(int e = 1; e <= edges_count; e++) {
									if(matrix[u][e] > 0) {

										for(int cn = 1; cn <= nodes_count; cn++) {
											if(matrix[cn][e] < 0 && !n[cn].v) {

												//cout << "found: " << u << " -> " << cn << " (" << matrix[u][e] << ")" << endl;

													v = &(n[cn]);

													w = u.d + matrix[u][e];
													if (v->d > w ) {
														v->d = w;

														pq.push(*v);
													}


												break;
											}

										}
										//continue;
									}
								}
			}
		//}
		return true;
}

bool ford_bellman_list() {
	// Tworzy listę odległości
	n = new node[nodes_count+1];

	/*
	 * initialize distance list
	 * 1 					-> 0
	 * 2 - nodes_count+1 	-> INFINITY
	 */
	for(int i=1; i<=nodes_count; i++) {
		n[i].d = INFINITY;
		n[i].id = i;
	}
	n[1].d = 0;

	node u, *v;
	nastepnik *item;
	int w;

	for(int i = 1; i <= nodes_count; i++) {
		for(int j = 1; j <= nodes_count; j++) {
			u = n[j];
			item = (list_repr[u].n);

			while(item != NULL) {
				//v = &n[v_id->id];
				v = &n[item->id];

				w = item->d;
				if (v->d > (u.d + w)) {
					v->d = u.d + w;
					v->p = &u;
					pq.push(*v);
				}

				item = item->n;

			}
		}
	}
	return true;
}

void show_result(bool matrix) {
	cout << endl << "RESULTS:" << endl;

	cout << endl << "distance dump" << endl;
	for(int i=1; i<=nodes_count; i++) {
		cout << "> " << i << " => " << n[i].d << endl;
	}
}

void read_from_file(bool matrix) {
	if(matrix)
		read_from_file_matrix();
	else
		read_from_file_list();
}

bool dijkstra(bool matrix) {
	if(matrix)
		return dijkstra_matrix();

	return dijkstra_list();
}

bool ford_bellman(bool matrix) {
	if(matrix)
		return ford_bellman_matrix();

	return ford_bellman_list();
}

int main(int argc, char* argv[]) {
	if(argc > 1) {
		file_name = argv[1];
		if(strcmp(argv[2], "matrix") == 0) {
			type_matrix = true;
		}else{
			type_matrix = false;
		}

		if(strcmp(argv[3], "dijkstra") == 0) {
			type_dijkstra = true;
		}else{
			type_dijkstra = false;
		}
	}

	int read_start, read_end, code_start, code_end;

	read_start=clock();
	read_from_file(type_matrix);
	read_end=clock();

	if(type_dijkstra == true) {
		code_start=clock();
		dijkstra(type_matrix);
		code_end=clock();
	}else{
		code_start=clock();
		if(ford_bellman(type_matrix)) {
			//cout << "ok" << endl;
		}
		code_end=clock();
	}

//	show_result(type_matrix);

//	cout << endl << "TIME:" << endl;

	cout.setf(ios::fixed);
//	cout << "read: " << setprecision(4) << ((read_end - read_start)/(double)CLOCKS_PER_SEC) << " s" << endl;
//	cout << "code: " << setprecision(4) << ((code_end - code_start)/(double)CLOCKS_PER_SEC) << " s" <<  endl;
//	cout << "all: " << setprecision(4) << ((code_end - read_start)/(double)CLOCKS_PER_SEC) << " s" <<  endl;
	cout << setprecision(4) << ((code_end - read_start)/(double)CLOCKS_PER_SEC) << endl;

	/*
	 * clear memory
	 */
	delete [] list_repr;
	edges_list->free();

	if(type_matrix) {
		for( int i = 1 ; i <= nodes_count ; i++ )
			delete [] matrix[i];
		delete [] matrix;
	}

    return 1;
}

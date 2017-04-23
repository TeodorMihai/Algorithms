#include <bits/stdc++.h>

using namespace std;


struct Vertex {

	Vertex *next;
	int x;
};


int main() {


	Vertex* p = NULL;
	Vertex* a = NULL;
	Vertex* t = NULL;

	a = new Vertex;
	p = new Vertex;
	t = new Vertex;

	a->next = p;
	printf("a->next=%p\np=%p\nt=%p\n\n",a->next, p, t);

	p = t;

	printf("a->next=%p\np=%p\nt=%p\n",a->next, p, t);

	return 0;
}
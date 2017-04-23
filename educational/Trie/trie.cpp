#include <fstream>
#include <cstring>

using namespace std;

ifstream fin("trie.in");
ofstream fout("trie.out");

#define CH (*s - 'a')

const int MAXDIC = 26;
const int MAXWORD = 32;

class Vertex{

public:

	Vertex *sons[MAXDIC];
	int frequency;
	int numberSons;

	Vertex() {

		for(int i = 0 ; i < MAXDIC; ++i) {

			sons[i] = NULL;
			numberSons = 0;
			frequency = 0;
		}
	}
};


char s[MAXWORD];

Vertex* root = NULL;

void add(Vertex* curent, char* s) {

	if(*s == '\0' || *s == '\n') {

		curent->frequency++;

		return ;
	}

	if(curent->sons[CH])
		add(curent->sons[CH], s + 1);
	else {

		curent->sons[CH] = new Vertex();
		curent->numberSons++;
		add(curent->sons[CH], s + 1);
	}

}

int query1(Vertex* curent, char* s) {

	if(*s == '\0' || *s == '\n')
		return curent->frequency;
	if(curent->sons[CH] != NULL)
		return query1(curent->sons[CH], s + 1);
	return 0;
}

int query2(Vertex* curent, char* s) {

	if(*s == '\0' || *s == '\n' || curent->sons[CH] == NULL)
		return 0;

	return 1 + query2(curent->sons[CH], s + 1);
}

int del(Vertex* curent, char* s) {

	if(*s == '\0' || *s == '\n')
		curent->frequency--;

	else if( del(curent->sons[CH], s + 1) ) {
	
		curent->sons[CH] = 0;
		curent->numberSons--;
	}

	if(curent->frequency == 0 && curent->numberSons == 0 && curent != root) {
		delete curent; 
		return 1;
	}

	return 0;
}

int main() {

	root = new Vertex();

	int type;

	while(fin >> type) {

		fin >> s ;

		switch(type) {

			case 0: add(root, s) ; break;
			case 1: del(root, s); break;
			case 2: fout << query1(root, s) << '\n'; break;
			case 3: fout << query2(root, s) << '\n'; break;
		}
	}
	return 0;
}

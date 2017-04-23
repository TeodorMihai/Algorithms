#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

#define testfile "test2.txt"

ifstream fin("lista.de.cuvinte.txt");
ifstream testin(testfile);
ofstream fout ("output.txt");

int lin; int col;//dimensiuni grid

char s[100]; //pentru fiecare cuvant

char word[100]; int index_word;
char last_word[100]; //pentru nu a afisa 2 cuvinte care sunt la fel si poernesc de pe aceeasi poztie (se ajunge in moduri diferite)


char grid[1000][1000];

//folosesc un trie ca sa retin cuvintele si sa nu caud de 2 ori acelasi prefix
struct Trie {

	int final; //ca sa stim daca nodul in care am ajuns are o cale care defineste un cuavnt
	Trie *fiu[26];//un vectori de pointeri, contine 26 de pointeri

	Trie() {

		final = 0;

		for(unsigned i = 0 ; i < 26 ; ++i)
			fiu[i] = NULL;
	}
};

Trie *T = new Trie;

void ins(Trie* nod, char *s) {

	if(*s == '\n' || *s == '\0') {
		nod->final = 1;
		return ;
	}
	if(nod->fiu[(*s) - 'a'] == NULL) {//daca nu a mai fost un cuvant cu acelasi prefix trebuie sa creezi noduri

		nod->fiu[(*s) - 'a'] = new Trie;
	}

	ins(nod->fiu[(*s) - 'a'], s + 1);
}



void read() {

	int index = 0;

	while(testin >> grid[index++]);//citesc gridul

	lin = index - 1;
	col = strlen(grid[0]);

	while(fin >> s) //citesc cuvintele
		ins(T, s);
	

}

void search(Trie *nod, const int startx, const int starty, int x, int y, int count_right) {
	//ma aflu pe pozitia x, yin grid. Am plecat de la startx, starty si am mers pana acum count_right la dreapta fara interferente de mers in sus



	if(nod->final == 1 && strcmp(last_word, word)) { //adica am parcurs deja un cuvant si cuvantul gasit nu e exact la fel cu cel anterior (erau mai multe metode de a ajunge la acelasi cuvant)

		word[index_word] = '\0'; 
		strcpy(last_word, word);
		
		fout << startx << "," << starty << "," << word << '\n';

	}

	//try right, incerc in dreapta daca exista vreun match cu vreun cuvant
	if(y + 1 < col && count_right + 1 <= 3 && nod->fiu[ grid[x][y + 1]  - 'a'] != NULL){ //are sens sa mergem pe aici

		word[index_word++] = grid[x][y + 1];

		search(nod->fiu[ grid[x][y + 1] - 'a' ], startx, starty, x, y + 1, count_right + 1);

		index_word--;//ma intorc practic scod ultima litera

	}

	//try up, in sus, match
	if(x - 1 >= 0 && nod->fiu[ grid[x - 1][y]  - 'a'] != NULL){ //are sens sa mergem pe aici
		
		word[index_word++] = grid[x - 1][y];

		search(nod->fiu[ grid[x - 1][y] - 'a' ], startx, starty, x - 1, y, 1);

		index_word--;

	}


}


void solve() {

	last_word[0] = '0';
	last_word[1] = '\0';
	//am pus un cuvant care nu e in lista ('0') 


	for(unsigned i = 0 ; i < lin ; ++i) 
		for(unsigned j = 0 ; j < col ;++j) {

			index_word = 0;

			if(T->fiu[ grid[i][j] - 'a' ] != NULL) { //prima litera

				word[index_word++] = grid[i][j];
				search(T->fiu[ grid[i][j] - 'a'], i , j, i, j, 1);
			}
		}
	
}

int main() {

	read();

	solve();

	return 0;
}
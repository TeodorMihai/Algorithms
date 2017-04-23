#include <bits/stdc++.h>

using namespace std;

const int SMAX = 1e6 + 6;
const int LMAX = 1e4 + 4;
const int WMAX = 102;
const int ALPHA = 26;


typedef struct State {

	vector<int> finish;
	int passes;
	State* sons[ALPHA];
	State* fail;

	State() {

		fail = NULL;
		passes = 0;
		for(int i = 0 ; i < ALPHA; ++i)
			sons[i] = NULL;
	}

} State;

State* root;
State* p;

int nrWords;
char s[SMAX]; int ns;
char word[LMAX]; int nword;

int cnt[WMAX];

State* q[LMAX * WMAX]; //vectori cu starile automatului
int st; int dr;

int res[WMAX];

void ins(char* p, State* current, int ind) {

	if(isalpha(*p) == 0) {
		current->finish.push_back(ind);
		return;
	} 

	int nxt = *p - 'a';
	if(current->sons[nxt] == NULL)
		current->sons[nxt] = new State();
	ins(p + 1, current->sons[nxt], ind);
}

void bfs(State* root) {

	root->fail = root;
	State* go = NULL;

	for(q[st = dr = 1] = root; st <= dr ; ) {

		State* state = q[st++];
		for(int i = 0 ; i < ALPHA; ++i) 
			if(state->sons[i] != NULL) { //nodul pt care gasesc failul
				
				go = state->fail;//go <=> state
				while(go != root && go->sons[i] == NULL)
					go = go->fail;

				if(go->sons[i] != NULL && go->sons[i] != state->sons[i]) 
					go = go->sons[i];
				//s-a gasit un match && nu pointeaza catre el insusi
		 		state->sons[i]->fail = go;
		 		q[++dr] = state->sons[i];
		 		//e arbore structura, nu am nevoie de viz
			}	
	} 

	root->fail = NULL;
}

void addUp() {


	for(int i = dr ; i > 0 ; --i) {

		State* state = q[i];

		if(state->fail != NULL)
			state->fail->passes += state->passes;

		for(int x : state->finish) 
			res[x] = state->passes;
	}
}

int main() {

	freopen("ahocorasick.in", "r", stdin);
	freopen("ahocorasick.out", "w", stdout);

	scanf("%s", s);
	scanf("%d", &nrWords);

	root = new State();

	for(int i = 1; i <= nrWords; ++i) {
		scanf("%s", word);
		ins(word, root, i);
	}

	bfs(root);

	int ns = strlen(s);
	State* current = root;

	//parsez textul, ma duc inainte, sau pe un fail si inainte
	for(int i = 0 ; i < ns; ++i) {

		int nx = s[i] - 'a';

		while( current->sons[nx] == NULL && current != root)
			current = current->fail;

		if(current->sons[nx] != NULL)
			current = current->sons[nx];

		//s-a gasit macar un match, exista litera at least
		current->passes++;
	}

	//am marcat +1 in anumiste stari dar trebuie marcate si 
	//prefixele respective , chiar daca nu sunt cele mai lungi
	//orce tranzitie de fail practic insemna ca se putea ajunge la fel de bine in nodul
	//respectiv 
	addUp();

	for(int i = 1; i <= nrWords; ++i)
		printf("%d\n", res[i]);

	return 0;
}
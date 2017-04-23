#include <bits/stdc++.h>

using namespace std;

ifstream fin("evaluare.in");
ofstream fout("evaluare.out");

const int NMAX = 200001;

class Nod {

public:

	Nod* st;
	Nod* dr;

	int value;
	bool isLeaf;

	Nod() {
		this->st = NULL;
		this->dr = NULL;
	}

	Nod(Nod* st, Nod* dr, int value, bool isLeaf) {
		
		this->st = st;
		this->dr = dr;
		this->value = value;
		this->isLeaf = isLeaf;
	}

};

stack<char> st;

int op;
char* s;
char* str;

char* nr;

int isoperator(char c) {

	if(c == '+' || c == '-' || c == '/' || c == '*')
		return 1;
	return 0;
}

int prioritate(char c) {

	if(c == '+' || c =='-')
		return 1;

	if(c == '*' || c == '/')
		return 2;
	
	return 0;
}

//stiva: operator arbore drept, arborele stang fiind deja baga in expresie
char* postexpression(char *s) {

	char* output = new char[NMAX];
	int index = 0;
	int indout = 0;

	while(s[index] != '\0') {

		bool ok = false;

		while( isdigit(s[index]) ) {

			output[indout] = s[index];
			index++;
			indout++;
			ok = true;
		}

		if(ok) {

		    output[indout++] = ' ';
		    continue;
		}

		if(s[index] == '(') {
			st.push('('); 
			index++;
			continue;
		}

		//tot ce era de evaluat in interior a fost evaluat, a ramas doar un numar probabil si un semn
		//care dau rezulatul final din parateza
		if(s[index] == ')') {

			while(st.top() != '(') {
				output[indout++] = st.top();
				st.pop();
			}

			st.pop();
			index++;
			continue;
		}

		if(isoperator(s[index])) {

			while(!st.empty() && st.top() != '(' && prioritate(s[index]) <= prioritate(st.top()) ) {
				/*

			    while there is an operator token, o2, at the top of the operator stack, and either

			        o1 is left-associative and its precedence is less than or equal to that of o2, or
			        o1 is right associative, and has precedence less than that of o2,

			    then pop o2 off the operator stack, onto the output queue; 

			    right associative: ^ (exponentierea)
			    left associative: -,/
			    associative: +, *

			    */
				
				output[indout++] = st.top();
				st.pop();
			}

			st.push(s[index]);
			index++;
			continue;
		}
	}

	while(!st.empty()) {

		output[indout++] = st.top();
		st.pop();
	}

	output[indout] = '\0';

	return output;

}

int getNext() {

	while(*str != '\0' && *str == ' ')
		++str;

	

	if(*str != '\0' && isdigit(*str)) {

		int ind = 0;
		op = 0;
		while(*str != '\0' && isdigit(*str)) {

			nr[ind++] = *str;
			++str;
		}

		reverse(nr, nr + ind);

		nr[ind] = '\0';

		ind = 0;

		int x = 0;

		while(nr[ind] != '\0') {
			x = x * 10 + nr[ind] - '0';
			++ind;
		}

		return x;
	}

	if(*str != '\0') {

		op = 1;
		char x = *str;
		++str;
		return x;
	}

}

void createTree(Nod*);


void createNode(Nod* curent) {

	if(*str == '\0') return;

	int x = getNext();


	if(op == 0) {
 
			Nod* newNod = new Nod(NULL, NULL, x, true);
			
			if(curent->dr == NULL) 
				
				curent->dr = newNod;

			 else 	curent->st= newNod;


		} else {

			Nod* newNod = new Nod(NULL, NULL, x, false);

			if(curent->dr == NULL) {

				curent->dr = newNod;
				createTree(curent->dr);

			} else {

				curent->st = newNod;

				createTree(curent->st);

			}
		}
}


void createTree(Nod* curent) {

	createNode(curent);

	createNode(curent);				
}

void printInOrdine(Nod* curent) {


	if(curent->st != NULL)
		printInOrdine(curent->st);

	if(!curent->isLeaf)
		cout << (char) (curent->value) ;
	else 
		cout << curent->value;

	if(curent->dr != NULL)
		printInOrdine(curent->dr);
}


int eval(Nod* root) {

	if(root->isLeaf)
		return root->value;

	int left = eval(root->st);
	int right = eval(root->dr);

	switch(root->value) {

		case '+': return left + right; break;
		case '-': return left - right; break;
		case '*': return left * right; break;
		case '/': return left / right; break;
	}
}


int main() {


	s = new char[NMAX];
	nr = new char[100];

	fin >> s;
	str = postexpression(s);
	
	int n = strlen(str);
	
	reverse(str, str + n);

	fout << str << '\n'; 

	Nod* root = new Nod(NULL, NULL, getNext(), false);

	createTree(root);
	//printInOrdine(root);

	//fout << eval(root) << '\n'; 


	return 0;

}
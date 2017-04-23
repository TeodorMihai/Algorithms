#include <bits/stdc++.h>

using namespace std;


void f(int* p) {

	//se face o copie a dresei de memorie a variabilei p, asta insemna ca nu pot retine schimbarile asupra ei!!
	//in schimb pot sa o sterg, delete, delete insemna ca voi marca adresa ca fiind reutiliziabila, which is okay
	//nu am nevoie sa o modific ca sa fac asta

	p = new int; //cand aloc se schimba adresa, insa enoi nu vom avea avea acces la noua adresa, decat la cea veche
	//daca modific *p, atunci se retin schimbarile pentru ca am modificat intr.adevar valoarea de la adresa unde e tinuta valoarea.
	//2 pointeri, asa am acces la adresa unde e retinuta adresa variabilei	


	printf("%p %d\n", p, *p);
}


void f2(int** p) {//sau int* &p

	*p = new int; 
	**p = 9;
}



int main() {


	int *p; 

	int t = 0x000021; // 1 * 16 + 1

	printf("%d\n", t);
	

	printf("%p\n", p); //de ce ar trebui sa initilizezi pointerii cu null

	p = new int;//se aloca o zona de memorie la o adresa x
	*p = 7;

	printf("%p %d \n", p, *p); 

	f(p); // se transmit functiei si adresa si valoarea 

	printf("%p %d \n", p, *p);

	f2(&p);//ii dau adresa unde e stocata adresa variabilei p
	//s-a schimbat !!
	printf("%p %d\n", p, *p);
	


	int h = 33;

	printf("%x\n", h);//reprezentarea hexa a numarului
	return 0;
}
#include <bits/stdc++.h>

using namespace std;

ifstream fin("heapuri.in");
ofstream fout("heapuri.out");

template<class T = int>
class Less {
public:
	bool operator()(const T& a, const T& b) {
		return a < b;
	}
};


template<class T = int>
class Greater {
public:
	bool operator()(const T& a, const T& b) {
		return a > b;
	}
};


template<class T = int, class Comp = Greater<int> >
class Heap {

private:
	int ord; 	//cate elemente au fost inserate
	int nheap;  //cate elemente am in heap

	vector<T> history;  	//history[i] = elementul care a fost al i-lea
	vector<int> heap; 		//heap[i] = nr de ordine al elementul de pe pozitia i din heap
	vector<int> inv; 		//inv[i] = indexul in heap al celui de-al i-lea element

	Comp comp;

	T getValue(int node) {
		return history[heap[node]];
	}

	int father(int node) {
		return node / 2;
	}

	int leftSon(int node) {
		return node * 2;
	}

	int rightSon(int node) {
		return node * 2 + 1;
	}

	void up(int current) { 

		if(current <= 1) return ;

		if(comp(getValue(current), getValue(father(current))) == false)  {
			swap(inv[heap[current]], inv[heap[father(current)]]);
			swap(heap[current], heap[father(current)]);
			up(father(current));
		}
	}

	void down(int current) {

		int substitute = current;

		if(rightSon(current) <= nheap && comp(getValue(rightSon(current)),getValue(substitute)) == false)
			substitute = rightSon(current);

		if(leftSon(current) <= nheap && comp(getValue(leftSon(current)), getValue(substitute)) == false)
			substitute = leftSon(current);

		if(substitute != current) {

			swap(inv[heap[substitute]], inv[heap[current]]);
			swap(heap[substitute], heap[current]);
			down(substitute);
		}
	}

public:
	Heap(int maxElements) {

		ord = 0;
		nheap = 0;

		history.reserve(maxElements + 1);
		heap.reserve(maxElements + 1); //start from 1
		inv.reserve(maxElements + 1);
	}

	void push(const T& x) {

		
		history[++ord] = x;
		heap[++nheap] = ord;
		inv[ord] = nheap;

		up(nheap);

	}	

	T top() {

		return getValue(1);
	}

	void pop(const int& pos) {

		heap[inv[pos]] = heap[nheap];
		inv[heap[nheap]] = inv[pos];
		nheap--;
		down(inv[pos]);
	}
};


int main() {


	int n; fin >> n;
	
	Heap<> h(n);

	while(n--) {

		int t; int x;
		fin >> t;

		if(t == 1) {
			fin >> x;
			h.push(x); //se insereaza x
		}

		if(t == 2) {
			fin >> x;
			h.pop(x); //se sterge al x-lea element inserat
		}

		if(t == 3)
			fout << h.top() << '\n';
	}

	return 0;
}
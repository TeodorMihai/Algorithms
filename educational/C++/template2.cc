#include "template2.h"

#include <stdlib.h>
#include <stdio.h>

template<typename T>
KeyStorage<T>::KeyStorage(int k){
		this -> key = k;
}

template<typename T>
KeyStorage<T>::~KeyStorage() {

}	

template<typename T>
T KeyStorage<T>::getMember() {
	
	return this -> member;
}

template <typename T>
void KeyStorage<T>::setMember(T inf) {
	this -> member = inf;
}

template class KeyStorage<int>;
template class KeyStorage<float>;

int main() {
	
	KeyStorage<int> x(6);
	x.setMember(31);
	printf("%d\n", x.getMember());
}

	

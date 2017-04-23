#include <bits/stdc++.h>
#include <cstddef>

using namespace std;


template<typename T>
class Allocator {
public : 
    //    typedefs
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

public : 
    //    convert an allocator<T> to allocator<U>
    template<typename U>
    struct rebind {
        typedef Allocator<U> other;
    };

public : 
    inline explicit Allocator() {}
    inline ~Allocator() {}
    inline explicit Allocator(Allocator const&) {}
    template<typename U>
    inline explicit Allocator(Allocator<U> const&) {}

    //    address
    inline pointer address(reference r) { return &r; }
    inline const_pointer address(const_reference r) { return &r; }

    //    memory allocation
    inline pointer allocate(size_type cnt, 
       typename std::allocator<void>::const_pointer = 0) { 
      return reinterpret_cast<pointer>(::operator new(cnt * sizeof (T))); 
    }
    inline void deallocate(pointer p, size_type) { 
        ::operator delete(p); 
    }

    //    size
    inline size_type max_size() const { 
        return std::numeric_limits<size_type>::max() / sizeof(T);
 }

    //    construction/destruction
    inline void construct(pointer p, const T& t) { new(p) T(t); }
    inline void destroy(pointer p) { p->~T(); }

    inline bool operator==(Allocator const&) { return true; }
    inline bool operator!=(Allocator const& a) { return !operator==(a); }
};    // 



template<typename T>
class Iter {

public:
	T* current;


	T operator* () {
		return *current;
	}

	void operator++ () {
		current = current + 1;
	}

	void operator-- () {
		current = current - 1;
	}

	Iter& operator= (const Iter& other) {

		this->current = other.current;
		return *this;
	}

	bool operator!= (const Iter& other) {
		return this->current != other.current;
	}



};




template<class T>
class vect {

public:	
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::size_t size_type;
	typedef Iter<T> iterator;

	friend class Iter<T>;

	vect() {

		cap = 8;
		array = new T[cap];
	}

	iterator begin() {

		iterator it;
		it.current = &array[0];

		return it;
	}

	iterator end() {

		iterator it;

		if(sz == 0)
			it.current = &array[sz];
		else 
			it.current = &array[sz];
		
		return it;
	}

	void push_back(const value_type el) {


		if(sz == cap - 1) {
			cap *= 2;
			array = (T*) realloc(array, sizeof(T) * cap);
		}

		*(array + sz) = el;
		sz++;
	}

	T& operator[] (const int& index) {
		return array[index];
	}

private:
	pointer array;
	size_type sz;
	size_type cap;
	

};


class Na {

private:
	int x;
public:
	void f(Na obj) {
		cout << obj.x << '\n';
	}
} ;

int main() {
/*
	vector<int> v;

	v.push_back(5);

	vector<int>::value_type x;
	vector<int>::reference y = x;
	vector<int>::iterator it = v.begin();

	cout << *it << '\n';
	x = 5;

	vect<int> a;

	a.push_back(6);
	a.push_back(7);
	a.push_back(8);
	a.push_back(9);

	vect<int>::value_type xx;
	vect<int>::iterator itt = a.begin();

	cout << *itt << '\n';

	for(itt = a.begin(); itt != a.end(); ++itt)
		cout << *itt << '\n';

	a[1] = 3;
	cout << a[1] << '\n';

	vector<int, Allocator<int> > b;
	*/
	Na nn;
	Na nnn;
	nn.f(nnn);

	int x = 2 & 2;
	cout << x << '\n';

	return 0;
}
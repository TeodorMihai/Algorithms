
template<typename T>
T getmax(T a, T b) {
	return a > b ? a : b;
}

template<typename T>
class KeyStorage {
public:
	int key;
	T member;
};

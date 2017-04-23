template<typename T>
class KeyStorage {

public: 
	KeyStorage(int);
	~KeyStorage();
 	
	T getMember();
	void setMember(T element);
private:
	T member;
	int key;
};

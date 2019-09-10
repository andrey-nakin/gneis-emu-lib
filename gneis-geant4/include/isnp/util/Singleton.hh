#ifndef	isnp_util_Singleton_hh
#define	isnp_util_Singleton_hh

namespace isnp {

namespace util {

template<typename T>
class Singleton {
public:

	static T* GetInstance() {

		if (!instance) {
			instance = new T();
		}

		return instance;

	}

protected:

	virtual ~Singleton() {

		instance = nullptr;

	}

private:

	static T* instance;

};

template<typename T>
T* Singleton<T>::instance = nullptr;

}

}

#endif	//	isnp_util_Singleton_hh

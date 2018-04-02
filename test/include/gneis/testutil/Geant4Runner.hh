#ifndef gneis_testutil_Geant4Runner_hh
#define gneis_testutil_Geant4Runner_hh

#include <functional>

namespace gneis {

namespace testutil {

class Geant4Runner {
public:

	Geant4Runner() = delete;

	static void Run(std::function<void()> closure);

};

}

}

#endif	//	gneis_testutil_Geant4Runner_hh

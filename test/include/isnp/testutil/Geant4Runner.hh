#ifndef isnp_testutil_Geant4Runner_hh
#define isnp_testutil_Geant4Runner_hh

#include <functional>

namespace isnp {

namespace testutil {

class Geant4Runner {
public:

	Geant4Runner() = delete;

	static void Run(std::function<void()> closure);

};

}

}

#endif	//	isnp_testutil_Geant4Runner_hh

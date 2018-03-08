#ifndef basic_runner_hh
#define basic_runner_hh

#include <functional>
#include <G4RunManager.hh>

namespace gneis {

namespace runner {

/**
 * Class initializes and runs Geant4
 */
class BasicRunner {
public:

	BasicRunner();
	virtual ~BasicRunner();

	BasicRunner(BasicRunner const&) = delete;
	BasicRunner& operator=(BasicRunner const&) = delete;

	int run(int argc, const char* const argv[],
			std::function<void(G4RunManager&)> closure);

private:

};

}

}

#endif	//	basic_runner_hh

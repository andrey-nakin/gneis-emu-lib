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

	BasicRunner(int argc, char* argv[]);
	virtual ~BasicRunner();

	BasicRunner(BasicRunner const&) = delete;
	BasicRunner& operator=(BasicRunner const&) = delete;

	int Run(std::function<void(G4RunManager&)> closure);

private:

	int const argc;
	char const* const* const argv;

	static long SystemTime();

};

}

}

#endif	//	basic_runner_hh

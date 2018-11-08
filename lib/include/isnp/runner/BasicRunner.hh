#ifndef isnp_runner_BasicRunner_hh
#define isnp_runner_BasicRunner_hh

#include <memory>
#include <functional>

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

namespace isnp {

namespace runner {

class CommandLineParser;

/**
 * Class initializes and runs Geant4
 */
class BasicRunner {
public:

	BasicRunner(int argc, char* argv[]);
	virtual ~BasicRunner();

	int Run(std::function<void(G4RunManager&)> closure);

private:

	std::unique_ptr<CommandLineParser> const parser;

};

}

}

#endif	//	isnp_runner_BasicRunner_hh

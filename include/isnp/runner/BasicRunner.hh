#ifndef isnp_runner_BasicRunner_hh
#define isnp_runner_BasicRunner_hh

#include <functional>
#include <G4RunManager.hh>

#include "isnp/runner/CommandLineParser.hh"

namespace isnp {

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

	CommandLineParser const parser;

	static long SystemTime();

};

}

}

#endif	//	isnp_runner_BasicRunner_hh

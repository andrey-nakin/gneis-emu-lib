#ifndef isnp_generator_SpallationMessenger_hh
#define isnp_generator_SpallationMessenger_hh

#include "G4UImessenger.hh"

#include "isnp/generator/Spallation.hh"

namespace isnp {

namespace generator {

class SpallationMessenger: public G4UImessenger {
public:

	SpallationMessenger(Spallation* spallation);
	~SpallationMessenger();

private:

	Spallation* const spallation;

};

}

}

#endif	//	isnp_generator_SpallationMessenger_hh

#ifndef gneis_generator_Spallation_hh
#define gneis_generator_Spallation_hh

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>

namespace gneis {

namespace generator {

/**
 * Class emulates 1GeV proton beam used in the spallation process.
 */
class Spallation: public G4VUserPrimaryGeneratorAction {
public:

	Spallation();
	~Spallation();

	void GeneratePrimaries(G4Event*);

private:

	G4ParticleGun* particleGun;

};

}

}

#endif	//	gneis_generator_Spallation_hh

#ifndef isnp_generator_Spallation_hh
#define isnp_generator_Spallation_hh

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>

#include <gtest/gtest_prod.h>

namespace isnp {

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

	FRIEND_TEST(Spallation, GeneratePosition);

	G4double diameter;
	G4ParticleGun* particleGun;

	G4ThreeVector GeneratePosition() const;

};

}

}

#endif	//	isnp_generator_Spallation_hh

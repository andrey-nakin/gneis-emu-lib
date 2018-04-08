#ifndef isnp_generator_Spallation_hh
#define isnp_generator_Spallation_hh

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4Transform3D.hh>

#include <memory>

#include <gtest/gtest_prod.h>

namespace isnp {

namespace generator {

class SpallationMessenger;

/**
 * Class emulates 1GeV proton beam used in the spallation process.
 */
class Spallation: public G4VUserPrimaryGeneratorAction {
public:

	Spallation();
	~Spallation();

	void GeneratePrimaries(G4Event*);

	G4double GetDiameter() const {
		return diameter;
	}

	void SetDiameter(G4double const v) {
		diameter = v;
	}

	G4int GetVerbose() const {
		return verbose;
	}

	void SetVerbose(G4int const v) {
		verbose = v;
	}

private:

	FRIEND_TEST(Spallation, GeneratePositionStatistics);FRIEND_TEST(Spallation, ZeroDiameter);FRIEND_TEST(Spallation, GeneratePosition);FRIEND_TEST(Spallation, GenerateDirection);

	std::unique_ptr<G4ParticleGun> const particleGun;
	std::unique_ptr<SpallationMessenger> const messenger;
	G4double diameter;
	unsigned counter;
	G4int verbose;

	G4ThreeVector GenerateDirection(G4Transform3D const&) const;
	G4ThreeVector GeneratePosition(G4Transform3D const&) const;

	static std::unique_ptr<G4ParticleGun> MakeGun();

};

}

}

#endif	//	isnp_generator_Spallation_hh

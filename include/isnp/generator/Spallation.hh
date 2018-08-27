#ifndef isnp_generator_Spallation_hh
#define isnp_generator_Spallation_hh

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4Transform3D.hh>

#include <memory>

#include <gtest/gtest_prod.h>

#include "isnp/dist/UniformRectangle.hh"
#include "isnp/dist/UniformCircle.hh"
#include "isnp/dist/GaussEllipse.hh"

namespace isnp {

namespace generator {

class SpallationMessenger;

/**
 * Class emulates 1GeV proton beam used in the spallation process.
 */
class Spallation: public G4VUserPrimaryGeneratorAction {
public:

	enum class Mode {
		UniformCircle, GaussianEllipse, UniformRectangle
	};

	Spallation();
	~Spallation();

	void GeneratePrimaries(G4Event*);

	G4double GetPositionX() const {
		return positionX;
	}

	void SetPositionX(G4double const v) {
		positionX = v;
	}

	G4double GetPositionY() const {
		return positionY;
	}

	void SetPositionY(G4double const v) {
		positionY = v;
	}

	G4int GetVerboseLevel() const {
		return verboseLevel;
	}

	void SetVerboseLevel(G4int const aVerboseLevel) {
		verboseLevel = aVerboseLevel;
	}

	Mode GetMode() const {

		return mode;

	}

	void SetMode(Mode const aMode) {

		mode = aMode;

	}

	dist::UniformRectangle const& GetUniformRectangle() const {

		return uniformRectangle;

	}

	dist::UniformRectangle& GetUniformRectangle() {

		return uniformRectangle;

	}

	dist::UniformCircle const& GetUniformCircle() const {

		return uniformCircle;

	}

	dist::UniformCircle& GetUniformCircle() {

		return uniformCircle;

	}

	dist::GaussEllipse const& GetGaussEllipse() const {

		return gaussEllipse;

	}

	dist::GaussEllipse& GetGaussEllipse() {

		return gaussEllipse;

	}

private:

	FRIEND_TEST(Spallation, PositionY);

	FRIEND_TEST(Spallation, PositionX);

	FRIEND_TEST(Spallation, GeneratePositionStatistics);

	FRIEND_TEST(Spallation, GeneratePosition);

	FRIEND_TEST(Spallation, GenerateDirection);

	std::unique_ptr<G4ParticleGun> const particleGun;
	std::unique_ptr<SpallationMessenger> const messenger;
	G4double positionX, positionY;
	unsigned counter;
	G4int verboseLevel;
	Mode mode;
	dist::UniformRectangle uniformRectangle;
	dist::UniformCircle uniformCircle;
	dist::GaussEllipse gaussEllipse;

	G4ThreeVector GenerateDirection(G4Transform3D const&) const;
	G4ThreeVector GeneratePosition(G4Transform3D const&) const;

	static std::unique_ptr<G4ParticleGun> MakeGun();

};

}

}

#endif	//	isnp_generator_Spallation_hh

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

	enum class Mode {
		UniformCircle, GaussianEllipse
	};

	class UniformCircleProps {
	public:

		UniformCircleProps();

		G4double GetDiameter() const {
			return diameter;
		}

		void SetDiameter(G4double const v) {
			diameter = v;
		}

	private:

		G4double diameter;

	};

	class GaussianEllipseProps {
	public:

		GaussianEllipseProps();

		G4double GetXWidth() const {

			return xWidth;

		}

		void SetXWidth(G4double const aXWidth) {

			xWidth = aXWidth;

		}

		G4double GetYWidth() const {

			return yWidth;

		}

		void SetYWidth(G4double const aYWidth) {

			yWidth = aYWidth;

		}

	private:

		G4double xWidth, yWidth;

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

	UniformCircleProps& GetUcProps() {

		return ucProps;

	}

	UniformCircleProps const& GetUcProps() const {

		return ucProps;

	}

	GaussianEllipseProps& GetGeProps() {

		return geProps;

	}

	GaussianEllipseProps const& GetGeProps() const {

		return geProps;

	}

private:

	FRIEND_TEST(Spallation, PositionY);

	FRIEND_TEST(Spallation, PositionX);

	FRIEND_TEST(Spallation, GeneratePositionStatistics);

	FRIEND_TEST(Spallation, GeneratePositionStatisticsGE);

	FRIEND_TEST(Spallation, ZeroDiameter);

	FRIEND_TEST(Spallation, GeneratePosition);

	FRIEND_TEST(Spallation, GenerateDirection);

	std::unique_ptr<G4ParticleGun> const particleGun;
	std::unique_ptr<SpallationMessenger> const messenger;
	G4double positionX, positionY;
	unsigned counter;
	G4int verboseLevel;
	Mode mode;
	UniformCircleProps ucProps;
	GaussianEllipseProps geProps;

	G4ThreeVector GenerateDirection(G4Transform3D const&) const;
	G4ThreeVector GeneratePosition(G4Transform3D const&) const;
	G4ThreeVector GeneratePositionUC() const;
	G4ThreeVector GeneratePositionGE() const;

	static std::unique_ptr<G4ParticleGun> MakeGun();

};

}

}

#endif	//	isnp_generator_Spallation_hh

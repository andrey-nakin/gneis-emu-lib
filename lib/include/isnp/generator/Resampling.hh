#ifndef isnp_generator_Resampling_hh
#define isnp_generator_Resampling_hh

#include <memory>
#include <exception>

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4String.hh>

#include <gtest/gtest_prod.h>

#include "isnp/util/DataFrame.hh"

namespace isnp {

namespace generator {

class ResamplingMessenger;

/**
 * Class generates random particles using the given data files as a sample.
 */
class Resampling: public G4VUserPrimaryGeneratorAction {
public:

	class NoFileException: public std::exception {

	};

	class EmptySampleException: public std::exception {

	};

	Resampling();
	~Resampling();

	void GeneratePrimaries(G4Event*) override;

	const G4String& GetSampleFileName() const {
		return sampleFileName;
	}
	void SetSampleFileName(const G4String&);

	G4int GetVerboseLevel() const {
		return verboseLevel;
	}

	void SetVerboseLevel(G4int const aVerboseLevel) {
		verboseLevel = aVerboseLevel;
	}

private:

	std::unique_ptr<ResamplingMessenger> const messenger;
	std::unique_ptr<G4ParticleGun> const particleGun;
	G4String sampleFileName, energyColumn, directionXColumn, directionYColumn,
			directionZColumn, positionXColumn, positionYColumn, positionZColumn,
			typeColumn;
	bool sampleFileLoaded;
	unsigned counter;
	G4int verboseLevel;
	std::unique_ptr<util::DataFrame> dataFrame;

	static std::unique_ptr<G4ParticleGun> MakeGun();
	static G4ThreeVector CalculatePosition(const G4ThreeVector& direction,
			const G4ThreeVector& targetPos);
	void LoadSampleFile();
	G4double ShootNumber(G4String const& column,
			util::DataFrame::size_type rowNo) const;
	G4ThreeVector ShootVector(G4String const& columnX, const G4String& columnY,
			const G4String& columnZ, util::DataFrame::size_type rowNo) const;

};

}

}

#endif	//	isnp_generator_Resampling_hh

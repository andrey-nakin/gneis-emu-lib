#ifndef isnp_generator_Resampling_hh
#define isnp_generator_Resampling_hh

#include <memory>

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

	Resampling();
	~Resampling();

	void GeneratePrimaries(G4Event*) override;

	const G4String& GetSampleFileName() const {
		return sampleFileName;
	}
	void SetSampleFileName(const G4String&);

private:

	std::unique_ptr<G4ParticleGun> const particleGun;
	G4String sampleFileName, energyColumn;
	bool sampleFileLoaded;
	std::unique_ptr<util::DataFrame> dataFrame;

	static std::unique_ptr<G4ParticleGun> MakeGun();
	void LoadSampleFile();

};

}

}

#endif	//	isnp_generator_Resampling_hh

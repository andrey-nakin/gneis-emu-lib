#ifndef isnp_detector_Basic_hh
#define isnp_detector_Basic_hh

#include <vector>
#include <G4VSensitiveDetector.hh>
#include <G4ParticleDefinition.hh>

namespace isnp {

namespace detector {

class Basic: public G4VSensitiveDetector {
public:

	Basic();
	Basic(const G4String& name);
	virtual ~Basic();

protected:

	virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);

private:

	struct Data {
		G4ParticleDefinition const* particle;
		G4double totalEnergy, kineticEnergy, time;
		G4ThreeVector direction, position;
	};

	std::vector<Data> accum;

	void flush();

};

}

}

#endif	//	isnp_detector_Basic_hh

#ifndef basic_neutrons_hh
#define basic_neutrons_hh

#include <vector>
#include <G4VSensitiveDetector.hh>

namespace gneis {

namespace detector {

class BasicNeutrons: public G4VSensitiveDetector {
public:

	BasicNeutrons();
	BasicNeutrons(const G4String& name);
	virtual ~BasicNeutrons();

protected:

	virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);

private:

	std::vector<double> energies;
	std::vector<G4ThreeVector> momenta;

	void flush();

};

}

}

#endif	//	basic_neutrons_hh

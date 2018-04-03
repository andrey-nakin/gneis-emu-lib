#ifndef isnp_detector_Basic_hh
#define isnp_detector_Basic_hh

#include <vector>
#include <map>
#include <G4VSensitiveDetector.hh>

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

	typedef std::vector<double>::size_type key_type;

	std::map<key_type, G4String> nameMap;
	std::map<G4String, key_type> keyMap;
	std::vector<key_type> names;
	std::vector<double> energies;
	std::vector<G4ThreeVector> momenta;

	void flush();

};

}

}

#endif	//	isnp_detector_Basic_hh

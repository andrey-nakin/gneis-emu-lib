#ifndef beam5_hpp
#define beam5_hpp

#include <G4VUserDetectorConstruction.hh>

namespace gneis {

namespace facility {

class Beam5: public G4VUserDetectorConstruction {
public:

	Beam5(G4VSensitiveDetector* aDetector);
	virtual ~Beam5();

	virtual G4VPhysicalVolume* Construct();

private:

	G4VSensitiveDetector* const detector;

};

}

}

#endif

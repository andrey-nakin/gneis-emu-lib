#ifndef beam5_hpp
#define beam5_hpp

#include <G4VUserDetectorConstruction.hh>
#include <globals.hh>

class Beam5: public G4VUserDetectorConstruction {
public:

	Beam5();
	virtual ~Beam5();

	virtual G4VPhysicalVolume* Construct();

};

#endif

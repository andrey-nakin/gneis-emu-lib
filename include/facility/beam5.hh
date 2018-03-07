#ifndef beam5_hpp
#define beam5_hpp

#include <G4VUserDetectorConstruction.hh>

namespace gneis {

namespace facility {

class Beam5: public G4VUserDetectorConstruction {
public:

	typedef enum {
		D50, D75, D100
	} CollimatorDiameter;

	Beam5(CollimatorDiameter aDiameter, G4VSensitiveDetector* aDetector);
	virtual ~Beam5();

	virtual G4VPhysicalVolume* Construct();

	G4double getAngle() const;
	void setAngle(G4double angle);

private:

	G4double angle;
	CollimatorDiameter const diameter;
	G4VSensitiveDetector* const detector;

	static G4double toDouble(CollimatorDiameter d);

};

}

}

#endif

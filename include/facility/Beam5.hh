#ifndef beam5_hpp
#define beam5_hpp

#include <G4VUserDetectorConstruction.hh>
#include <G4LogicalVolume.hh>

namespace gneis {

namespace facility {

class Beam5: public G4VUserDetectorConstruction {
public:

	enum class CollimatorDiameter {
		D50, D75, D100
	};

	Beam5(CollimatorDiameter aDiameter, G4VSensitiveDetector* aDetector);
	virtual ~Beam5();

	virtual G4VPhysicalVolume* Construct();

	G4bool getCollimatorsHaveDetectors() const;
	void setCollimatorsHaveDetectors(G4bool v);

	G4double getAngle() const;
	void setAngle(G4double angle);

private:

	CollimatorDiameter const diameter;
	G4VSensitiveDetector* const detector;
	G4double zeroPosition, length, worldRadius, angle;
	G4bool collimatorsHaveDetectors;

	static G4double ToDouble(CollimatorDiameter d);

	void PlaceComponent(G4LogicalVolume *world, G4LogicalVolume *component,
			G4double position);
	void PlaceCollimator(G4LogicalVolume *world, G4LogicalVolume *collimator,
			G4double position);

	G4VSolid* MakeCylinder(G4String const &name, G4double halfLength);

};

}

}

#endif

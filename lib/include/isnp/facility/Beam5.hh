#ifndef isnp_facility_Beam5_hpp
#define isnp_facility_Beam5_hpp

#include <memory>
#include <G4VUserDetectorConstruction.hh>
#include <G4LogicalVolume.hh>

namespace isnp {

namespace facility {

class Beam5Messenger;

class Beam5: public G4VUserDetectorConstruction {
public:

	Beam5();
	virtual ~Beam5();

	virtual G4VPhysicalVolume* Construct();

	G4bool GetCollimatorsHaveDetectors() const;
	void SetCollimatorsHaveDetectors(G4bool v);

	G4double GetAngle() const;
	void SetAngle(G4double angle);

	G4double GetDiameter() const;
	void SetDiameter(G4double angle);

	G4int GetVerboseLevel() const;
	void SetVerboseLevel(G4int aVerboseLevel);

	void SetDetector(G4VSensitiveDetector* aDetector);
	G4VSensitiveDetector* GetDetector() const;

private:

	std::unique_ptr<Beam5Messenger> const messenger;
	G4VSensitiveDetector* detector;
	G4double zeroPosition, length, angle;
	G4bool collimatorsHaveDetectors;
	G4double diameter;
	G4int verboseLevel;
	G4double ntubeInnerRadius, ntubeOuterRadius;
	G4double worldRadius;

	void PlaceComponent(G4LogicalVolume *world, G4LogicalVolume *component,
			G4double position);
	void PlaceCollimator(G4LogicalVolume *world, G4LogicalVolume *collimator,
			G4double position);

	G4VSolid* MakeCylinder(G4String const &name, G4double halfLength);
	G4VSensitiveDetector* MakeDefaultDetector();

};

}

}

#endif	//	isnp_facility_Beam5_hpp

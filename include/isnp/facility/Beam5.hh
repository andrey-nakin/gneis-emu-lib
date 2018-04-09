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

	Beam5(G4VSensitiveDetector* aDetector);
	virtual ~Beam5();

	virtual G4VPhysicalVolume* Construct();

	G4bool GetCollimatorsHaveDetectors() const;
	void SetCollimatorsHaveDetectors(G4bool v);

	G4double GetAngle() const;
	void SetAngle(G4double angle);

	G4double GetDiameter() const;
	void SetDiameter(G4double angle);

	G4bool GetHaveCollimator1() const;
	void SetHaveCollimator1(G4bool haveC1);

	G4bool GetHaveCollimator2() const;
	void SetHaveCollimator2(G4bool haveC2);

	G4bool GetHaveCollimator3() const;
	void SetHaveCollimator3(G4bool haveC3);

	G4bool GetHaveCollimator4() const;
	void SetHaveCollimator4(G4bool haveC4);

	G4bool GetHaveCollimator5() const;
	void SetHaveCollimator5(G4bool haveC5);

	G4int GetVerboseLevel() const;
	void SetVerboseLevel(G4int aVerboseLevel);

private:

	std::unique_ptr<Beam5Messenger> const messenger;
	G4VSensitiveDetector* const detector;
	G4double zeroPosition, length, worldRadius, angle;
	G4bool collimatorsHaveDetectors;
	G4double diameter;
	G4bool haveCollimator1, haveCollimator2, haveCollimator3, haveCollimator4,
			haveCollimator5;
	G4int verboseLevel;

	void PlaceComponent(G4LogicalVolume *world, G4LogicalVolume *component,
			G4double position);
	void PlaceCollimator(G4LogicalVolume *world, G4LogicalVolume *collimator,
			G4double position);

	G4VSolid* MakeCylinder(G4String const &name, G4double halfLength);

};

}

}

#endif	//	isnp_facility_Beam5_hpp

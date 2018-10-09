#ifndef isnp_facility_Beam5_hpp
#define isnp_facility_Beam5_hpp

#include <memory>
#include <G4VUserDetectorConstruction.hh>
#include <G4LogicalVolume.hh>
#include "isnp/util/Singleton.hh"

namespace isnp {

namespace facility {

class Beam5Messenger;

class Beam5: public G4VUserDetectorConstruction, public util::Singleton<Beam5> {
public:

	~Beam5() override;

	virtual G4VPhysicalVolume* Construct();

	G4bool GetHasSpallationTarget() const;
	void SetHasSpallationTarget(G4bool v);

	G4double GetXAngle() const;
	void SetXAngle(G4double angle);

	G4double GetYAngle() const;
	void SetYAngle(G4double angle);

	G4double GetDetectorZPosition() const;
	void SetDetectorZPosition(G4double pos);

	G4int GetVerboseLevel() const;
	void SetVerboseLevel(G4int aVerboseLevel);

	void SetDetector(G4VSensitiveDetector* aDetector);
	G4VSensitiveDetector* GetDetector() const;

	G4double GetC5Diameter() const;
	void SetC5Diameter(G4double angle);

	G4String const& GetC5Material() const;
	void SetC5Material(G4String const& aMaterial);

private:

	friend class util::Singleton<Beam5>;
	Beam5();

	std::unique_ptr<Beam5Messenger> const messenger;
	G4VSensitiveDetector* detector;
	G4double zeroPosition, worldLength, xAngle, yAngle;
	G4bool hasSpallationTarget;
	G4double c5Diameter;
	G4int verboseLevel;
	G4double ntubeInnerRadius, ntubeOuterRadius, ntubeFlangeThickness,
			ntube1Length, ntube2Length, ntube4Length, ntube5Length, wallLength,
			windowThickness, detectorZPosition;
	G4String ntubeMaterial, ntubeFlangeMaterial, ntubeInnerMaterial,
			wallMaterial, worldMaterial, windowMaterial, c5Material;
	G4double worldRadius;

	void PlaceComponent(G4LogicalVolume *world, G4LogicalVolume *component,
			G4double position, G4double componentLength, G4bool checkOverlaps =
					true);
	void PlaceCollimator(G4LogicalVolume *world, G4LogicalVolume *collimator,
			G4double position, G4double collimatorLength);

	G4VSolid* MakeCylinder(G4String const &name, G4double halfLength);
	G4VSensitiveDetector* MakeDefaultDetector();
	G4LogicalVolume* MakeFlange(G4int ntubeNo, G4int flangeNo);
	void AddNTube(G4LogicalVolume* logicWorld, G4double length, G4double zPos,
			G4int ntubeNo);

};

}

}

#endif	//	isnp_facility_Beam5_hpp

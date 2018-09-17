#ifndef isnp_facility_BasicSpallation_hpp
#define isnp_facility_BasicSpallation_hpp

#include <memory>

#include <G4VUserDetectorConstruction.hh>
#include <G4LogicalVolume.hh>

namespace isnp {

namespace facility {

class BasicSpallationMessenger;

class BasicSpallation: public G4VUserDetectorConstruction {
public:

	BasicSpallation();
	~BasicSpallation() override;

	G4VPhysicalVolume* Construct() override;

	G4double GetHorizontalAngle() const;
	void SetHorizontalAngle(G4double anAngle);

	G4double GetVerticalAngle() const;
	void SetVerticalAngle(G4double anAngle);

	G4double GetDistance() const;
	void SetDistance(G4double aDistance);

	G4double GetDetectorWidth() const;
	void SetDetectorWidth(G4double aWidth);

	G4double GetDetectorHeight() const;
	void SetDetectorHeight(G4double aHeight);

	G4double GetDetectorLength() const;
	void SetDetectorLength(G4double aLength);

	G4int GetVerboseLevel() const;
	void SetVerboseLevel(G4int aVerbose);

	G4String GetWorldMaterial() const {
		return worldMaterial;
	}
	void SetWorldMaterial(const G4String&);

	G4VSensitiveDetector* GetDetector() const;
	void SetDetector(G4VSensitiveDetector* aDetector);

private:

	G4VSensitiveDetector* detector;
	std::unique_ptr<BasicSpallationMessenger> const messenger;
	G4double worldRadius, horizontalAngle, verticalAngle, distance,
			detectorWidth, detectorHeight, detectorLength;
	G4int verboseLevel;
	G4String worldMaterial;
	G4LogicalVolume* logicWorld;

	static G4double HalfOf(G4double v);
	G4VSensitiveDetector* MakeDefaultDetector();

};

}

}

#endif	//	isnp_facility_BasicSpallation_hpp

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

	BasicSpallation(G4VSensitiveDetector* aDetector);
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

	G4int GetVerbose() const;
	void SetVerbose(G4int aVerbose);

private:

	G4VSensitiveDetector* const detector;
	std::unique_ptr<BasicSpallationMessenger> const messenger;
	G4double worldRadius, horizontalAngle, verticalAngle, distance, detectorWidth,
			detectorHeight, detectorLength;
	G4int verbose;

	static G4double HalfOf(G4double v);

};

}

}

#endif	//	isnp_facility_BasicSpallation_hpp

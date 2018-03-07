#include <G4RunManager.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4Cons.hh>
#include <G4Orb.hh>
#include <G4Tubs.hh>
#include <G4Sphere.hh>
#include <G4Trd.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>
#include <G4SDManager.hh>

#include "facility/beam5.hh"

gneis::facility::Beam5::Beam5(CollimatorDiameter const aDiameter,
		G4VSensitiveDetector* const aDetector) :
		G4VUserDetectorConstruction(), diameter(aDiameter), detector(aDetector) {
}

gneis::facility::Beam5::~Beam5() {
}

G4VPhysicalVolume* gneis::facility::Beam5::Construct() {
	// Get nist material manager
	const auto nist = G4NistManager::Instance();

	// Option to switch on/off checking of volumes overlaps
	const G4bool checkOverlaps = true;
	const G4double worldRadius = 100.0 * mm;

	const auto solidWorld = new G4Box("World", 100 * mm, 100 * mm, 16 * m);

	const auto logicWorld = new G4LogicalVolume(solidWorld,	//	reference to Solid
			nist->FindOrBuildMaterial("G4_Galactic"),	//	world material
			"World");	//	name
	logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

	const auto physWorld = new G4PVPlacement(0,      //no rotation
			G4ThreeVector(),       //at (0,0,0)
			logicWorld,            //its logical volume
			"World",               //its name
			0,                     //its mother  volume
			false,                 //no boolean operation
			0,                     //copy number
			checkOverlaps);        //overlaps checking

	const G4String strFinalCollimator = "collimator-C5";
	const auto solidFinalCollimator = new G4Tubs(strFinalCollimator,
			0.5 * toDouble(diameter),	// min radius
			worldRadius,	// max radius
			1000.0 * mm,	// length
			0.0 * deg,	// start angle
			360.0 * deg);	// end angle
	const auto logicFinalCollimator = new G4LogicalVolume(solidFinalCollimator,
			nist->FindOrBuildMaterial("G4_BRASS"), strFinalCollimator);

	return physWorld;
}

G4double gneis::facility::Beam5::toDouble(CollimatorDiameter const d) {
	switch (d) {
	case D50:
		return 50.0 * mm;

	case D75:
		return 75.0 * mm;

	case D100:
		return 100.0 * mm;
	}

	return 0.0;
}

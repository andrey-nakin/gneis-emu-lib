#include "detector/beam5.hh"

#include <G4RunManager.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4Cons.hh>
#include <G4Orb.hh>
#include <G4Sphere.hh>
#include <G4Trd.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>
#include <G4SDManager.hh>

gneis::detector::Beam5::Beam5() :
		G4VUserDetectorConstruction() {
}

gneis::detector::Beam5::~Beam5() {
}

G4VPhysicalVolume* gneis::detector::Beam5::Construct() {
	// Get nist material manager
	const auto nist = G4NistManager::Instance();

	// Option to switch on/off checking of volumes overlaps
	const G4bool checkOverlaps = true;

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

	return physWorld;
}

#include <G4RunManager.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4Cons.hh>
#include <G4Orb.hh>
#include <G4Tubs.hh>
#include <G4Sphere.hh>
#include <G4Trd.hh>
#include <G4SubtractionSolid.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>
#include <G4SDManager.hh>

#include "facility/beam5.hh"
#include "detector/basic-neutrons.hh"

gneis::facility::Beam5::Beam5(CollimatorDiameter const aDiameter,
		G4VSensitiveDetector* const aDetector) :
		G4VUserDetectorConstruction(), angle(30.0 * deg), diameter(aDiameter), detector(
				aDetector) {
}

gneis::facility::Beam5::~Beam5() {
}

G4VPhysicalVolume* gneis::facility::Beam5::Construct() {
	// Get nist material manager
	const auto nist = G4NistManager::Instance();
	const auto sdMan = G4SDManager::GetSDMpointer();

	// Option to switch on/off checking of volumes overlaps
	const G4bool checkOverlaps = true;
	const G4double worldRadius = 100.0 * mm;

	const G4String nameWorld = "world";
	const auto solidWorld = new G4Tubs(nameWorld, 0.0, worldRadius, 18.0 * m,
			0.0 * deg, 360.0 * deg);

	const auto logicWorld = new G4LogicalVolume(solidWorld,	//	reference to Solid
			nist->FindOrBuildMaterial("G4_Galactic"),	//	world material
			nameWorld);	//	name
	logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

	const auto physWorld = new G4PVPlacement(0,      //no rotation
			G4ThreeVector(),       //at (0,0,0)
			logicWorld,            //its logical volume
			nameWorld,               //its name
			0,                     //its mother  volume
			false,                 //no boolean operation
			0,                     //copy number
			checkOverlaps);        //overlaps checking

	{
		// Collimator C1
		const G4String strC1 = "collimator-C1";
		const auto solidC1Whole = new G4Tubs(strC1, 0.0, worldRadius,
				200.0 * mm, 0.0 * deg, 360.0 * deg);
		const auto solidC1Cut = new G4Box(strC1, 70.0 * mm, 90.0 * mm,
				200.0 * m);
		const auto solidC1 = new G4SubtractionSolid(strC1, solidC1Whole,
				solidC1Cut);
		const auto logicC1 = new G4LogicalVolume(solidC1,
				nist->FindOrBuildMaterial("G4_BRASS"), strC1);
		const auto detC1 = new gneis::detector::BasicNeutrons("detector-C1");
		sdMan->AddNewDetector(detC1);
		logicC1->SetSensitiveDetector(detC1);
	}

	{
		// Collimator C2
		const G4String strC2 = "collimator-C2";
		const auto solidC2Whole = new G4Tubs(strC2, 0.0, worldRadius,
				355.0 * mm, 0.0 * deg, 360.0 * deg);
		const auto solidC2Cut = new G4Box(strC2, 105.0 * mm, 50.0 * mm,
				355.0 * m);
		const auto solidC2 = new G4SubtractionSolid(strC2, solidC2Whole,
				solidC2Cut);
		const auto logicC2 = new G4LogicalVolume(solidC2,
				nist->FindOrBuildMaterial("G4_STEEL"), strC2);
		const auto detC2 = new gneis::detector::BasicNeutrons("detector-C2");
		sdMan->AddNewDetector(detC2);
		logicC2->SetSensitiveDetector(detC2);
	}

	{
		// Collimator C3
		const G4String strC3 = "collimator-C3";
		const auto solidC3 = new G4Tubs(strC3, 60.0 * mm, worldRadius,
				300.0 * mm, 0.0 * deg, 360.0 * deg);
		const auto logicC3 = new G4LogicalVolume(solidC3,
				nist->FindOrBuildMaterial("G4_STEEL"), strC3);
		const auto detC3 = new gneis::detector::BasicNeutrons("detector-C3");
		sdMan->AddNewDetector(detC3);
		logicC3->SetSensitiveDetector(detC3);
	}

	{
		// Collimator C4
		const G4String strC4 = "collimator-C4";
		const auto solidC4 = new G4Tubs(strC4, 60.0 * mm, worldRadius,
				0.5 * 875.0 * mm, 0.0 * deg, 360.0 * deg);
		const auto logicC4 = new G4LogicalVolume(solidC4,
				nist->FindOrBuildMaterial("G4_STEEL"), strC4);
		const auto detC4 = new gneis::detector::BasicNeutrons("detector-C4");
		sdMan->AddNewDetector(detC4);
		logicC4->SetSensitiveDetector(detC4);
	}

	{
		// Collimator C5
		const G4String strC5 = "collimator-C5";
		const auto solidC5 = new G4Tubs(strC5, 0.5 * toDouble(diameter), // min radius
		worldRadius,	// max radius
				500.0 * mm,	// length
				0.0 * deg,	// start angle
				360.0 * deg);	// end angle
		const auto logicC5 = new G4LogicalVolume(solidC5,
				nist->FindOrBuildMaterial("G4_BRASS"), strC5);
		const auto detC5 = new gneis::detector::BasicNeutrons("detector-C5");
		sdMan->AddNewDetector(detC5);
		logicC5->SetSensitiveDetector(detC5);
	}

	return physWorld;
}

G4double gneis::facility::Beam5::getAngle() const {
	return angle;
}

void gneis::facility::Beam5::setAngle(G4double const aAngle) {
	this->angle = aAngle;
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

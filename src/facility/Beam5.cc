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
#include <G4RotationMatrix.hh>

#include "facility/Beam5.hh"
#include "facility/component/SpallationTarget.hh"
#include "facility/component/CollimatorC1.hh"
#include "facility/component/CollimatorC2.hh"
#include "detector/BasicNeutrons.hh"
#include "util/NameBuilder.hh"

gneis::facility::Beam5::Beam5(CollimatorDiameter const aDiameter,
		G4VSensitiveDetector* const aDetector) :
		G4VUserDetectorConstruction(), diameter(aDiameter), detector(aDetector), zeroPosition(
				1.0 * m), length(36.0 * m), worldRadius(200.0 * mm), angle(
				30.0 * deg), collimatorsHaveDetectors(true) {
}

gneis::facility::Beam5::~Beam5() {
}

G4VPhysicalVolume* gneis::facility::Beam5::Construct() {
	// Get nist material manager
	auto const nist = G4NistManager::Instance();

	// Option to switch on/off checking of volumes overlaps
	G4RotationMatrix* const noRotation = nullptr;
	G4bool const single = false;
	G4int const numOfCopies = 0;
	G4bool const checkOverlaps = true;

	G4String const nameWorld = "world";
	auto const solidWorld = MakeCylinder(nameWorld, zeroPosition + length);
	auto const logicWorld = new G4LogicalVolume(solidWorld,
			nist->FindOrBuildMaterial("G4_Galactic"), nameWorld);
	logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

	auto const physWorld = new G4PVPlacement(noRotation, G4ThreeVector(),
			logicWorld, nameWorld, nullptr, false, 0, checkOverlaps);

	{
		// Neutron source
		auto const logicSpTarget = component::SpallationTarget::Instance();
		new G4PVPlacement(noRotation,
				G4ThreeVector(0, 0, 0.5 * (zeroPosition - length)),
				logicSpTarget, logicSpTarget->GetName(), logicWorld, single,
				numOfCopies, checkOverlaps);
	}

	{
		// Collimator C1
		auto const solidC1Outer = MakeCylinder(
				component::CollimatorC1::GetDefaultName(),
				component::CollimatorC1::GetLength());
		auto const logicC1 = component::CollimatorC1::Instance(solidC1Outer);
		PlaceCollimator(logicWorld, logicC1, 6 * m);
	}

	{
		// Collimator C2
		auto const solidC2Outer = MakeCylinder(
				component::CollimatorC2::GetDefaultName(),
				component::CollimatorC2::GetLength());
		auto const logicC2 = component::CollimatorC2::Instance(solidC2Outer);
		PlaceCollimator(logicWorld, logicC2, 12 * m);
	}

	/*

	 {
	 // Collimator C3
	 const G4String strC3 = "collimator-C3";
	 const auto solidC3 = new G4Tubs(strC3, 60.0 * mm, worldRadius,
	 300.0 * mm, 0.0 * deg, 360.0 * deg);
	 const auto logicC3 = new G4LogicalVolume(solidC3,
	 nist->FindOrBuildMaterial("G4_STEEL"), strC3);
	 if (collimatorsHaveDetectors) {
	 const auto detC3 = new gneis::detector::BasicNeutrons(
	 "detector-C3");
	 sdMan->AddNewDetector(detC3);
	 logicC3->SetSensitiveDetector(detC3);
	 }
	 }

	 {
	 // Collimator C4
	 const G4String strC4 = "collimator-C4";
	 const auto solidC4 = new G4Tubs(strC4, 60.0 * mm, worldRadius,
	 0.5 * 875.0 * mm, 0.0 * deg, 360.0 * deg);
	 const auto logicC4 = new G4LogicalVolume(solidC4,
	 nist->FindOrBuildMaterial("G4_STEEL"), strC4);
	 if (collimatorsHaveDetectors) {
	 const auto detC4 = new gneis::detector::BasicNeutrons(
	 "detector-C4");
	 sdMan->AddNewDetector(detC4);
	 logicC4->SetSensitiveDetector(detC4);
	 }
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
	 if (collimatorsHaveDetectors) {
	 const auto detC5 = new gneis::detector::BasicNeutrons(
	 "detector-C5");
	 sdMan->AddNewDetector(detC5);
	 logicC5->SetSensitiveDetector(detC5);
	 }
	 }
	 */

	return physWorld;
}

G4bool gneis::facility::Beam5::getCollimatorsHaveDetectors() const {
	return collimatorsHaveDetectors;
}

void gneis::facility::Beam5::setCollimatorsHaveDetectors(G4bool const v) {
	this->collimatorsHaveDetectors = v;
}

G4double gneis::facility::Beam5::getAngle() const {
	return angle;
}

void gneis::facility::Beam5::setAngle(G4double const aAngle) {
	this->angle = aAngle;
}

G4double gneis::facility::Beam5::ToDouble(CollimatorDiameter const d) {
	switch (d) {
	case CollimatorDiameter::D50:
		return 50.0 * mm;

	case CollimatorDiameter::D75:
		return 75.0 * mm;

	case CollimatorDiameter::D100:
		return 100.0 * mm;
	}

	return 0.0;
}

void gneis::facility::Beam5::PlaceComponent(G4LogicalVolume* const world,
		G4LogicalVolume* const component, G4double const position) {

	G4RotationMatrix* const noRotation = nullptr;
	G4bool const single = false;
	G4int const numOfCopies = 0;
	G4bool const checkOverlaps = true;

	new G4PVPlacement(noRotation,
			G4ThreeVector(0, 0, 0.5 * (zeroPosition - length) + position),
			component, component->GetName(), world, single, numOfCopies,
			checkOverlaps);
}

void gneis::facility::Beam5::PlaceCollimator(G4LogicalVolume* const world,
		G4LogicalVolume* const collimator, G4double const position) {

	if (collimatorsHaveDetectors) {
		const auto sdMan = G4SDManager::GetSDMpointer();
		const auto det = new gneis::detector::BasicNeutrons(
				util::NameBuilder::Make(collimator->GetName(), "Detector"));
		sdMan->AddNewDetector(det);
		collimator->SetSensitiveDetector(det);
	}

	PlaceComponent(world, collimator, position);
}

G4VSolid* gneis::facility::Beam5::MakeCylinder(G4String const &name,
		G4double const len) {
	return new G4Tubs(name, 0.0, worldRadius, 0.5 * len, 0.0 * deg, 360.0 * deg);
}

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

#include "isnp/facility/Beam5.hh"
#include "isnp/facility/component/SpallationTarget.hh"
#include "isnp/facility/component/CollimatorC1.hh"
#include "isnp/facility/component/CollimatorC2.hh"
#include "isnp/facility/component/CollimatorC3.hh"
#include "isnp/facility/component/CollimatorC4.hh"
#include "isnp/facility/component/CollimatorC5.hh"
#include "isnp/detector/BasicNeutrons.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

Beam5::Beam5(G4VSensitiveDetector* const aDetector) :
		G4VUserDetectorConstruction(), detector(aDetector), zeroPosition(
				0.5 * m), length(36.0 * m), worldRadius(200.0 * mm), angle(
				30.0 * deg), collimatorsHaveDetectors(true), diameter(100 * mm) {
}

Beam5::~Beam5() {
}

G4VPhysicalVolume* Beam5::Construct() {

	// Get nist material manager
	auto const nist = G4NistManager::Instance();

	// Option to switch on/off checking of volumes overlaps
	G4RotationMatrix* const noRotation = nullptr;
	G4bool const single = false;
	G4int const numOfCopies = 0;
	G4bool const checkOverlaps = true;

	G4String const nameWorld = "World";
	auto const solidWorld = MakeCylinder(nameWorld, zeroPosition + length);
	auto const logicWorld = new G4LogicalVolume(solidWorld,
			nist->FindOrBuildMaterial("G4_Galactic"), nameWorld);
	logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

	auto const physWorld = new G4PVPlacement(noRotation, G4ThreeVector(),
			logicWorld, nameWorld, nullptr, single, numOfCopies, checkOverlaps);

	{
		// Neutron source
		auto const logicSpTarget = component::SpallationTarget::Instance();
		G4RotationMatrix rotm = G4RotationMatrix();
		rotm.rotateY(angle);
		G4ThreeVector const position = G4ThreeVector(0, 0,
				0.5 * (zeroPosition - length));
		G4Transform3D const transform = G4Transform3D(rotm, position);
		component::SpallationTarget::SetTransform(transform);
		new G4PVPlacement(transform, logicSpTarget, logicSpTarget->GetName(),
				logicWorld, single, numOfCopies, checkOverlaps);
	}

	if (false) {
		{
			// Collimator C1
			auto const logicC1 = component::CollimatorC1::AsCylinder(
					worldRadius);
			PlaceCollimator(logicWorld, logicC1, 6 * m);
		}

		{
			// Collimator C2
			auto const logicC2 = component::CollimatorC2::AsCylinder(
					worldRadius);
			PlaceCollimator(logicWorld, logicC2, 12 * m);
		}

		{
			// Collimator C3
			auto const logicC3 = component::CollimatorC3::AsCylinder(
					worldRadius);
			PlaceCollimator(logicWorld, logicC3, 23 * m);
		}

		{
			// Collimator C4
			auto const logicC4 = component::CollimatorC4::AsCylinder(
					worldRadius);
			PlaceCollimator(logicWorld, logicC4, 29 * m);
		}

		{
			// Collimator C5
			auto const logicC5 = component::CollimatorC5::AsCylinder(
					worldRadius, diameter);
			PlaceCollimator(logicWorld, logicC5, 35 * m);
		}
	}

	if (detector) {
		// Target
		G4String const name = "Target";
		const auto solidTarget = new G4Box(name, 50 * mm, 50 * mm, 5 * mm);
		const auto logicTarget = new G4LogicalVolume(solidTarget,
				nist->FindOrBuildMaterial("G4_Galactic"), name);
		logicTarget->SetVisAttributes(G4VisAttributes(G4Colour::Red()));

		const auto sdMan = G4SDManager::GetSDMpointer();
		sdMan->AddNewDetector(detector);
		logicTarget->SetSensitiveDetector(detector);

		PlaceComponent(logicWorld, logicTarget, 4.5 * m - 10 * mm);
	}

	return physWorld;

}

G4bool Beam5::getCollimatorsHaveDetectors() const {

	return collimatorsHaveDetectors;

}

void Beam5::setCollimatorsHaveDetectors(G4bool const v) {

	this->collimatorsHaveDetectors = v;

}

G4double Beam5::getAngle() const {

	return angle;

}

void Beam5::setAngle(G4double const aAngle) {

	this->angle = aAngle;

}

void Beam5::PlaceComponent(G4LogicalVolume* const world,
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

void Beam5::PlaceCollimator(G4LogicalVolume* const world,
		G4LogicalVolume* const collimator, G4double const position) {

	if (collimatorsHaveDetectors) {
		const auto sdMan = G4SDManager::GetSDMpointer();
		const auto det = new isnp::detector::BasicNeutrons(
				util::NameBuilder::Make(collimator->GetName(), "Detector"));
		sdMan->AddNewDetector(det);
		collimator->SetSensitiveDetector(det);
	}

	PlaceComponent(world, collimator, position);

}

G4VSolid* Beam5::MakeCylinder(G4String const &name, G4double const len) {

	return new G4Tubs(name, 0.0, worldRadius, 0.5 * len, 0.0 * deg, 360.0 * deg);

}

}

}

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
#include "G4Threading.hh"

#include "isnp/facility/Beam5.hh"
#include "isnp/facility/Beam5Messenger.hh"
#include "isnp/facility/component/SpallationTarget.hh"
#include "isnp/facility/component/CollimatorC1.hh"
#include "isnp/facility/component/CollimatorC2.hh"
#include "isnp/facility/component/CollimatorC3.hh"
#include "isnp/facility/component/CollimatorC4.hh"
#include "isnp/facility/component/CollimatorC5.hh"
#include "isnp/detector/Basic.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

Beam5::Beam5() :
		G4VUserDetectorConstruction(), messenger(
				std::make_unique < Beam5Messenger > (*this)), detector(nullptr), zeroPosition(
				0.5 * m), length(36.0 * m), angle(30.0 * deg), collimatorsHaveDetectors(
				false), diameter(100 * mm), verboseLevel(0), ntubeInnerRadius(
				120 * mm), ntubeOuterRadius(130 * mm), ntubeFlangeThickness(
				1. * mm), ntubeMaterial("DUR_AMG3"), ntubeFlangeMaterial(
				"G4_Al"), ntubeInnerMaterial("FOREVACUUM_100"), worldRadius(
				ntubeOuterRadius) {
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

	{
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating collimator #1\n";
		}

		component::CollimatorC1 const c;
		auto const logicC1 = c.AsCylinder(worldRadius);
		PlaceCollimator(logicWorld, logicC1, 6 * m);
	}

	{
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating collimator #2\n";
		}

		component::CollimatorC2 const c;
		auto const logicC2 = c.AsCylinder(worldRadius);
		PlaceCollimator(logicWorld, logicC2, 12 * m);
	}

	{
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating collimator #3\n";
		}

		auto const logicC3 = component::CollimatorC3::AsCylinder(worldRadius);
		PlaceCollimator(logicWorld, logicC3, 23 * m);
	}

	{
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating collimator #4\n";
		}

		auto const logicC4 = component::CollimatorC4::AsCylinder(worldRadius);
		PlaceCollimator(logicWorld, logicC4, 29 * m);
	}

	{
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating collimator #5 with diameter "
					<< diameter / mm << " mm \n";
		}

		auto const logicC5 = component::CollimatorC5::AsCylinder(worldRadius,
				diameter);
		PlaceCollimator(logicWorld, logicC5, 35 * m);
	}

	if (!detector) {
		detector = MakeDefaultDetector();
	}

	if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
		G4cout << "Beam5: creating detector\n";
	}

	// Target
	G4String const name = "Target";
	const auto solidTarget = new G4Box(name, 50 * mm, 50 * mm, 5 * mm);
	const auto logicTarget = new G4LogicalVolume(solidTarget,
			nist->FindOrBuildMaterial("G4_Galactic"), name);
	logicTarget->SetVisAttributes(G4VisAttributes(G4Colour::Red()));

	const auto sdMan = G4SDManager::GetSDMpointer();
	sdMan->AddNewDetector(detector);
	logicTarget->SetSensitiveDetector(detector);

	PlaceComponent(logicWorld, logicTarget, 36 * m - 10 * mm);

	return physWorld;

}

G4bool Beam5::GetCollimatorsHaveDetectors() const {

	return collimatorsHaveDetectors;

}

void Beam5::SetCollimatorsHaveDetectors(G4bool const v) {

	this->collimatorsHaveDetectors = v;

}

G4double Beam5::GetAngle() const {

	return angle;

}

void Beam5::SetAngle(G4double const aAngle) {

	this->angle = aAngle;

}

G4double Beam5::GetDiameter() const {

	return diameter;

}

void Beam5::SetDiameter(G4double const aDiameter) {

	this->diameter = aDiameter;

}

G4int Beam5::GetVerboseLevel() const {
	return verboseLevel;
}

void Beam5::SetVerboseLevel(G4int const aVerboseLevel) {
	verboseLevel = aVerboseLevel;
}

void Beam5::SetDetector(G4VSensitiveDetector* aDetector) {

	detector = aDetector;

}

G4VSensitiveDetector* Beam5::GetDetector() const {

	return detector;

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
		const auto det = new isnp::detector::Basic(
				util::NameBuilder::Make(collimator->GetName(), "Detector"));
		sdMan->AddNewDetector(det);
		collimator->SetSensitiveDetector(det);
	}

	PlaceComponent(world, collimator, position);

}

G4VSolid* Beam5::MakeCylinder(G4String const &name, G4double const len) {

	return new G4Tubs(name, 0.0, worldRadius, 0.5 * len, 0.0 * deg, 360.0 * deg);

}

G4VSensitiveDetector* Beam5::MakeDefaultDetector() {

	return new isnp::detector::Basic;

}

}

}

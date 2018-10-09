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
#include "isnp/facility/component/BeamPointer.hh"
#include "isnp/detector/Basic.hh"
#include "isnp/util/NameBuilder.hh"
#include "isnp/repository/Colours.hh"

namespace isnp {

namespace facility {

Beam5::Beam5() :
		G4VUserDetectorConstruction(), messenger(
				std::make_unique < Beam5Messenger > (*this)), detector(nullptr), zeroPosition(
				0.5 * m), worldLength(50.5 * m), xAngle(-2. * deg), yAngle(
				-32.0 * deg), hasSpallationTarget(true), c5Diameter(100 * mm), verboseLevel(
				0), ntubeInnerRadius(120 * mm), ntubeOuterRadius(130 * mm), ntubeFlangeThickness(
				1. * mm), ntube1Length(4.5 * m), ntube2Length(7.7 * m), ntube4Length(
				5.8 * m), ntube5Length(8.6 * m), wallLength(6. * m), windowThickness(
				2. * mm), detectorZPosition(36. * m), ntubeMaterial("DUR_AMG3"), ntubeFlangeMaterial(
				"G4_Al"), ntubeInnerMaterial("FOREVACUUM_100"), wallMaterial(
				"G4_CONCRETE"), worldMaterial("G4_AIR"), windowMaterial(
				"G4_Al"), c5Material("BR05C5S5"), worldRadius(190. * mm) {
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
	auto const solidWorld = MakeCylinder(nameWorld, zeroPosition + worldLength);
	auto const logicWorld = new G4LogicalVolume(solidWorld,
			nist->FindOrBuildMaterial(worldMaterial), nameWorld);
	logicWorld->SetVisAttributes(
			G4VisAttributes(true, repository::Colours::Air()));

	auto const physWorld = new G4PVPlacement(noRotation, G4ThreeVector(),
			logicWorld, nameWorld, nullptr, single, numOfCopies, checkOverlaps);

	{
		// Neutron source
		auto const pos = G4ThreeVector(0, 0,
				0.5 * (zeroPosition - worldLength));

		if (hasSpallationTarget) {
			auto const spallationTarget =
					component::SpallationTarget::GetInstance();
			spallationTarget->SetRotation(G4ThreeVector(-xAngle, -yAngle, 0.));
			spallationTarget->SetPosition(pos);
			spallationTarget->Place(logicWorld);
		}

		// Beam position
		auto const bp = component::BeamPointer::GetInstance();
		bp->SetRotation(G4ThreeVector());
		bp->SetPosition(pos);
	}

	G4double zPos = 5.4 * m;

	{
		// vacuum chamber

		G4String const sChamber = "chamber";
		auto const solidChamber = new G4Tubs(sChamber, 0, worldRadius, zPos / 2,
				0.0 * deg, 360.0 * deg);
		auto const logicChamber = new G4LogicalVolume(solidChamber,
				nist->FindOrBuildMaterial("G4_Galactic"), sChamber);
		logicChamber->SetVisAttributes(G4VisAttributes(false));
		PlaceComponent(logicWorld, logicChamber, 0., zPos, false);

	}

	{
		// neutron window

		G4String const sWindow = "window";
		auto const solidWindow = new G4Tubs(sWindow, 0, worldRadius,
				windowThickness / 2, 0.0 * deg, 360.0 * deg);
		auto const logicWindow = new G4LogicalVolume(solidWindow,
				nist->FindOrBuildMaterial(windowMaterial), sWindow);
		logicWindow->SetVisAttributes(
				G4VisAttributes(repository::Colours::Aluminium()));
		PlaceComponent(logicWorld, logicWindow, zPos, windowThickness);
	}

	zPos = 5.9 * m;

	{
		// Collimator #1
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating collimator #1" << G4endl;
		}

		component::CollimatorC1 const c;
		auto const logicC1 = c.AsCylinder(worldRadius);
		PlaceCollimator(logicWorld, logicC1, zPos, c.GetLength());
		zPos += c.GetLength();
	}

	{
		// Neutron tube #1
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating neutron tube #1" << G4endl;
		}

		AddNTube(logicWorld, ntube1Length, zPos, 1);
		zPos += ntube1Length;
	}

	{
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating collimator #2" << G4endl;
		}

		component::CollimatorC2 const c;
		auto const logicC2 = c.AsCylinder(worldRadius);
		PlaceCollimator(logicWorld, logicC2, zPos, c.GetLength());
		zPos += c.GetLength();
	}

	{
		// Neutron tube #2
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating neutron tube #2" << G4endl;
		}

		AddNTube(logicWorld, ntube2Length, zPos, 2);
		zPos += ntube2Length;
	}

	zPos = 23.2 * m;

	{
		// concrete wall with collimatots #3 and #4

		// first flange
		PlaceComponent(logicWorld, MakeFlange(3, 1), zPos,
				ntubeFlangeThickness);
		zPos += ntubeFlangeThickness;

		// Collimator #3
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating collimator #3" << G4endl;
		}

		component::CollimatorC3 const c;
		auto const logicC3 = c.AsCylinder();
		PlaceCollimator(logicWorld, logicC3, zPos, c.GetLength());

		{
			G4String const sInner = util::NameBuilder::Make(c.GetDefaultName(),
					"inner");
			auto const solidInner = new G4Tubs(sInner, 0, c.GetInnerRadius(),
					c.GetLength() / 2, 0.0 * deg, 360.0 * deg);
			auto const logicInner = new G4LogicalVolume(solidInner,
					nist->FindOrBuildMaterial(ntubeInnerMaterial), sInner);
			logicInner->SetVisAttributes(
					G4VisAttributes(repository::Colours::Air()));
			PlaceComponent(logicWorld, logicInner, zPos, c.GetLength());
		}

		{
			G4String const sOuter = util::NameBuilder::Make(c.GetDefaultName(),
					"outer");
			auto const solidOuter = new G4Tubs(sOuter, c.GetOuterRadius(),
					worldRadius, c.GetLength() / 2, 0.0 * deg, 360.0 * deg);
			auto const logicOuter = new G4LogicalVolume(solidOuter,
					nist->FindOrBuildMaterial(wallMaterial), sOuter);
			logicOuter->SetVisAttributes(
					G4VisAttributes(repository::Colours::Concrete()));
			PlaceComponent(logicWorld, logicOuter, zPos, c.GetLength());
		}

		zPos += c.GetLength();

		G4double const wall1Length = wallLength / 2 - c.GetLength();

		// Concrete wall, first part
		{
			G4String const sInner = util::NameBuilder::Make("ntube", "3.1",
					"inner");
			auto const solidInner = new G4Tubs(sInner, 0, c.GetOuterRadius(),
					wall1Length / 2, 0.0 * deg, 360.0 * deg);
			auto const logicInner = new G4LogicalVolume(solidInner,
					nist->FindOrBuildMaterial(ntubeInnerMaterial), sInner);
			logicInner->SetVisAttributes(
					G4VisAttributes(repository::Colours::Air()));
			PlaceComponent(logicWorld, logicInner, zPos, wall1Length);
		}

		{
			G4String const sOuter = util::NameBuilder::Make("ntube", "3.1",
					"outer");
			auto const solidOuter = new G4Tubs(sOuter, c.GetOuterRadius(),
					worldRadius, wall1Length / 2, 0.0 * deg, 360.0 * deg);
			auto const logicOuter = new G4LogicalVolume(solidOuter,
					nist->FindOrBuildMaterial(wallMaterial), sOuter);
			logicOuter->SetVisAttributes(
					G4VisAttributes(repository::Colours::Concrete()));
			PlaceComponent(logicWorld, logicOuter, zPos, wall1Length);
		}

		zPos += wall1Length;

	}

	{
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating collimator #4\n";
		}

		component::CollimatorC4 const c;
		G4double const wall2Length = wallLength / 2 - c.GetLength();

		// Concrete wall, second part
		{
			G4String const sInner = util::NameBuilder::Make("ntube", "3.2",
					"inner");
			auto const solidInner = new G4Tubs(sInner, 0, c.GetOuterRadius(),
					wall2Length / 2, 0.0 * deg, 360.0 * deg);
			auto const logicInner = new G4LogicalVolume(solidInner,
					nist->FindOrBuildMaterial(ntubeInnerMaterial), sInner);
			logicInner->SetVisAttributes(
					G4VisAttributes(repository::Colours::Air()));
			PlaceComponent(logicWorld, logicInner, zPos, wall2Length);
		}

		{
			G4String const sOuter = util::NameBuilder::Make("ntube", "3.2",
					"outer");
			auto const solidOuter = new G4Tubs(sOuter, c.GetOuterRadius(),
					worldRadius, wall2Length / 2, 0.0 * deg, 360.0 * deg);
			auto const logicOuter = new G4LogicalVolume(solidOuter,
					nist->FindOrBuildMaterial(wallMaterial), sOuter);
			logicOuter->SetVisAttributes(
					G4VisAttributes(repository::Colours::Concrete()));
			PlaceComponent(logicWorld, logicOuter, zPos, wall2Length);
		}

		zPos += wall2Length;

		auto const logicC4 = c.AsCylinder();
		PlaceCollimator(logicWorld, logicC4, zPos, c.GetLength());

		{
			G4String const sInner = util::NameBuilder::Make(c.GetDefaultName(),
					"inner");
			auto const solidInner = new G4Tubs(sInner, 0, c.GetInnerRadius(),
					c.GetLength() / 2, 0.0 * deg, 360.0 * deg);
			auto const logicInner = new G4LogicalVolume(solidInner,
					nist->FindOrBuildMaterial(ntubeInnerMaterial), sInner);
			logicInner->SetVisAttributes(
					G4VisAttributes(repository::Colours::Air()));
			PlaceComponent(logicWorld, logicInner, zPos, c.GetLength());
		}

		{
			G4String const sOuter = util::NameBuilder::Make(c.GetDefaultName(),
					"outer");
			auto const solidOuter = new G4Tubs(sOuter, c.GetOuterRadius(),
					worldRadius, c.GetLength() / 2, 0.0 * deg, 360.0 * deg);
			auto const logicOuter = new G4LogicalVolume(solidOuter,
					nist->FindOrBuildMaterial(wallMaterial), sOuter);
			logicOuter->SetVisAttributes(
					G4VisAttributes(repository::Colours::Concrete()));
			PlaceComponent(logicWorld, logicOuter, zPos, c.GetLength());
		}

		zPos += c.GetLength();

		// second flange
		PlaceComponent(logicWorld, MakeFlange(3, 2), zPos,
				ntubeFlangeThickness);
		zPos += ntubeFlangeThickness;

	}

	{
		// Neutron tube #4 and collimator #5

		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "Beam5: creating collimator #5 of " << c5Material
					<< " with diameter " << c5Diameter / mm << " mm" << G4endl;
		}

		component::CollimatorC5 const c(c5Diameter, c5Material);

		// first flange
		PlaceComponent(logicWorld, MakeFlange(4, 1), zPos,
				ntubeFlangeThickness);
		zPos += ntubeFlangeThickness;

		{
			// neutron tube #4

			G4String const sOuter = util::NameBuilder::Make("ntube", 4,
					"outer");
			auto const solidOuter = new G4Tubs(sOuter, ntubeInnerRadius,
					ntubeOuterRadius, ntube4Length / 2, 0.0 * deg, 360.0 * deg);
			auto const logicOuter = new G4LogicalVolume(solidOuter,
					nist->FindOrBuildMaterial(ntubeMaterial), sOuter);
			logicOuter->SetVisAttributes(
					G4VisAttributes(repository::Colours::Aluminium()));
			PlaceComponent(logicWorld, logicOuter, zPos, ntube4Length);
		}

		G4double const innerLength = ntube4Length - c.GetLength();

		{
			// neutron tube #4 inner space

			G4String const sInner = util::NameBuilder::Make("ntube", 4,
					"inner");
			auto const solidInner = new G4Tubs(sInner, 0, ntubeInnerRadius,
					innerLength / 2, 0.0 * deg, 360.0 * deg);
			auto const logicInner = new G4LogicalVolume(solidInner,
					nist->FindOrBuildMaterial(ntubeInnerMaterial), sInner);
			logicInner->SetVisAttributes(
					G4VisAttributes(repository::Colours::Air()));
			PlaceComponent(logicWorld, logicInner, zPos, innerLength);
		}

		zPos += innerLength;

		auto const logicC5 = c.AsCylinder();
		PlaceCollimator(logicWorld, logicC5, zPos, c.GetLength());

		{
			G4String const sInner = util::NameBuilder::Make(c.GetDefaultName(),
					"inner");
			auto const solidInner = new G4Tubs(sInner, 0, c.GetInnerRadius(),
					c.GetLength() / 2, 0.0 * deg, 360.0 * deg);
			auto const logicInner = new G4LogicalVolume(solidInner,
					nist->FindOrBuildMaterial(ntubeInnerMaterial), sInner);
			logicInner->SetVisAttributes(
					G4VisAttributes(repository::Colours::Air()));
			PlaceComponent(logicWorld, logicInner, zPos, c.GetLength());
		}

		zPos += c.GetLength();

		// second flange
		PlaceComponent(logicWorld, MakeFlange(4, 2), zPos,
				ntubeFlangeThickness);
		zPos += ntubeFlangeThickness;
	}

	zPos = 37.4 * m;

	{
		// neutron tube #5
		AddNTube(logicWorld, ntube5Length, zPos, 5);
	}

	if (!detector) {
		detector = MakeDefaultDetector();
	}

	if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
		G4cout << "Beam5: creating detector\n";
	}

	{
		// Detector
		G4String const name = "detector";
		const auto solidTarget = new G4Tubs(name, 0, worldRadius, 5 * mm,
				0.0 * deg, 360.0 * deg);
		const auto logicTarget = new G4LogicalVolume(solidTarget,
				nist->FindOrBuildMaterial("G4_Galactic"), name);
		logicTarget->SetVisAttributes(G4VisAttributes(G4Colour::Green()));

		const auto sdMan = G4SDManager::GetSDMpointer();
		sdMan->AddNewDetector(detector);
		logicTarget->SetSensitiveDetector(detector);

		PlaceComponent(logicWorld, logicTarget, detectorZPosition, 10. * mm);
	}

	return physWorld;

}

G4bool Beam5::GetHasSpallationTarget() const {

	return hasSpallationTarget;

}

void Beam5::SetHasSpallationTarget(G4bool const v) {

	hasSpallationTarget = v;

}

G4double Beam5::GetXAngle() const {

	return xAngle;

}

void Beam5::SetXAngle(G4double const aAngle) {

	this->xAngle = aAngle;

}

void Beam5::SetYAngle(G4double const aAngle) {

	this->yAngle = aAngle;

}

G4double Beam5::GetYAngle() const {

	return yAngle;

}

G4double Beam5::GetDetectorZPosition() const {

	return detectorZPosition;

}

void Beam5::SetDetectorZPosition(G4double const pos) {

	detectorZPosition = pos;

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

G4double Beam5::GetC5Diameter() const {

	return c5Diameter;

}

void Beam5::SetC5Diameter(G4double const aDiameter) {

	this->c5Diameter = aDiameter;

}

G4String const& Beam5::GetC5Material() const {

	return c5Material;

}

void Beam5::SetC5Material(G4String const& aMaterial) {

	c5Material = aMaterial;

}

G4VSensitiveDetector* Beam5::GetDetector() const {

	return detector;

}

void Beam5::PlaceComponent(G4LogicalVolume* const world,
		G4LogicalVolume* const component, G4double const position,
		G4double const componentLength, G4bool const checkOverlaps) {

	G4RotationMatrix* const noRotation = nullptr;
	G4bool const single = false;
	G4int const numOfCopies = 0;

	new G4PVPlacement(noRotation,
			G4ThreeVector(0, 0,
					0.5 * (zeroPosition - worldLength) + position
							+ componentLength / 2), component,
			component->GetName(), world, single, numOfCopies, checkOverlaps);

}

void Beam5::PlaceCollimator(G4LogicalVolume* const world,
		G4LogicalVolume* const collimator, G4double const position,
		G4double const collimatorLength) {

	PlaceComponent(world, collimator, position, collimatorLength);

}

G4VSolid* Beam5::MakeCylinder(G4String const &name, G4double const len) {

	return new G4Tubs(name, 0.0, worldRadius, 0.5 * len, 0.0 * deg, 360.0 * deg);

}

G4VSensitiveDetector* Beam5::MakeDefaultDetector() {

	return new isnp::detector::Basic;

}

G4LogicalVolume* Beam5::MakeFlange(G4int const ntubeNo, G4int const flangeNo) {

	auto const nist = G4NistManager::Instance();

	G4String const sFlange = util::NameBuilder::Make("ntube", ntubeNo, "flange",
			flangeNo);
	auto const solidFlange = new G4Tubs(sFlange, 0, ntubeOuterRadius,
			ntubeFlangeThickness / 2, 0.0 * deg, 360.0 * deg);
	auto const logicFlange = new G4LogicalVolume(solidFlange,
			nist->FindOrBuildMaterial(ntubeFlangeMaterial), sFlange);
	logicFlange->SetVisAttributes(
			G4VisAttributes(repository::Colours::Aluminium()));
	return logicFlange;

}

void Beam5::AddNTube(G4LogicalVolume* const logicWorld,
		G4double const tubeLength, G4double const zPos, G4int const ntubeNo) {

	auto const nist = G4NistManager::Instance();

	{
		PlaceComponent(logicWorld, MakeFlange(ntubeNo, 1), zPos,
				ntubeFlangeThickness);
	}

	G4double const innerLength = tubeLength - ntubeFlangeThickness * 2;
	G4double const innerPos = zPos + ntubeFlangeThickness;

	{
		G4String const sInner = util::NameBuilder::Make("ntube", ntubeNo,
				"inner");
		auto const solidInner = new G4Tubs(sInner, 0, ntubeInnerRadius,
				innerLength / 2, 0.0 * deg, 360.0 * deg);
		auto const logicInner = new G4LogicalVolume(solidInner,
				nist->FindOrBuildMaterial(ntubeInnerMaterial), sInner);
		logicInner->SetVisAttributes(
				G4VisAttributes(repository::Colours::Air()));
		PlaceComponent(logicWorld, logicInner, innerPos, innerLength);
	}

	{
		G4String const sOuter = util::NameBuilder::Make("ntube", ntubeNo,
				"outer");
		auto const solidOuter = new G4Tubs(sOuter, ntubeInnerRadius,
				ntubeOuterRadius, innerLength / 2, 0.0 * deg, 360.0 * deg);
		auto const logicOuter = new G4LogicalVolume(solidOuter,
				nist->FindOrBuildMaterial(ntubeMaterial), sOuter);
		logicOuter->SetVisAttributes(
				G4VisAttributes(repository::Colours::Aluminium()));
		PlaceComponent(logicWorld, logicOuter, innerPos, innerLength);
	}

	{
		PlaceComponent(logicWorld, MakeFlange(ntubeNo, 2),
				zPos + tubeLength - ntubeFlangeThickness, ntubeFlangeThickness);
	}

}

}

}

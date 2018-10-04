#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4Torus.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4PVPlacement.hh>
#include <G4SubtractionSolid.hh>

#include "isnp/facility/component/SpallationTarget.hh"
#include "isnp/facility/component/SpallationTargetMessenger.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

namespace component {

G4Transform3D SpallationTarget::transform;

SpallationTarget::SpallationTarget() :
		util::Box(200.0 * mm, 50.0 * mm, 400.0 * mm), messenger(
				std::make_unique < SpallationTargetMessenger > (*this)), coolerInnerRadius(
				7. * mm), coolerOuterRadius(7.5 * mm), coolerTorusMinRadius(
				60. * mm), hasCooler(true) {
}

void SpallationTarget::Place(G4LogicalVolume* const destination,
		G4Transform3D const& transform) {

	G4bool const single = false;
	G4int const numOfCopies = 0;
	G4bool const checkOverlaps = true;
	G4Transform3D const zeroTransform;

	SetTransform(transform);

	using namespace util;

	auto const nist = G4NistManager::Instance();

	G4VSolid* solidTarget = new G4Box(NameBuilder::Make("spallation", "target"),
			GetHalfWidth(), GetHalfHeight(), GetHalfLength());

	G4Transform3D const coolerTransform = G4RotateX3D(90. * deg);

	if (GetHasCooler()) {
		auto const solidCoolerVolume = new G4DisplacedSolid("",
				new G4Torus("", 0. * mm, coolerOuterRadius,
						coolerTorusMinRadius, 0. * deg, 360. * deg),
				coolerTransform);
		solidTarget = new G4SubtractionSolid(solidTarget->GetName(),
				solidTarget, solidCoolerVolume);
	}

	const auto logicTarget = new G4LogicalVolume(solidTarget,
			nist->FindOrBuildMaterial("G4_Pb"), solidTarget->GetName());
	logicTarget->SetVisAttributes(G4VisAttributes(repository::Colours::Lead()));
//	logicTarget->SetVisAttributes(
//			G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.1)));

	if (GetHasCooler()) {
		auto const coolerName = NameBuilder::Make(solidTarget->GetName(),
				"cooler");

		{
			// cooler inner volume
			auto const solid = new G4DisplacedSolid(
					NameBuilder::Make(coolerName, "inner"),
					new G4Torus("", 0., coolerInnerRadius, coolerTorusMinRadius,
							0. * deg, 360. * deg), coolerTransform);
			auto const logic = new G4LogicalVolume(solid,
					nist->FindOrBuildMaterial("G4_WATER"), solid->GetName());
			logic->SetVisAttributes(
					G4VisAttributes(repository::Colours::Water()));
			new G4PVPlacement(zeroTransform, logic, logic->GetName(),
					logicTarget, single, numOfCopies, checkOverlaps);
		}

		{
			// cooler tube
			auto const solid = new G4DisplacedSolid(
					NameBuilder::Make(coolerName, "outer"),
					new G4Torus("", coolerInnerRadius, coolerOuterRadius,
							coolerTorusMinRadius, 0. * deg, 360. * deg),
					coolerTransform);
			auto const logic = new G4LogicalVolume(solid,
					nist->FindOrBuildMaterial("G4_Cu"), solid->GetName());
			logic->SetVisAttributes(
					G4VisAttributes(repository::Colours::Copper()));
			new G4PVPlacement(zeroTransform, logic, logic->GetName(),
					logicTarget, single, numOfCopies, checkOverlaps);
		}
	}

	new G4PVPlacement(transform, logicTarget, logicTarget->GetName(),
			destination, single, numOfCopies, checkOverlaps);

}

G4bool SpallationTarget::GetHasCooler() const {

	return hasCooler;

}

void SpallationTarget::SetHasCooler(G4bool const v) {

	hasCooler = v;

}

}

}

}

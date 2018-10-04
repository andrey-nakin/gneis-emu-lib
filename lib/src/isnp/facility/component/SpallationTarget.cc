#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4Torus.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4PVPlacement.hh>
#include <G4SubtractionSolid.hh>
#include <G4ExtrudedSolid.hh>
#include <G4Tubs.hh>

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
				60. * mm), supportMaterial("DUR_AMG3"), hasCooler(true) {
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

	{
		// face cut
		std::vector<G4TwoVector> polygon;
		polygon.push_back(G4TwoVector(-100. * mm, -300. * mm));
		polygon.push_back(G4TwoVector(200. * mm, -300. * mm));
		polygon.push_back(G4TwoVector(200. * mm, 0. * mm));

		std::vector<G4ExtrudedSolid::ZSection> zsections;
		zsections.push_back(
				G4ExtrudedSolid::ZSection(-50. * mm, G4TwoVector(), 1.0));
		zsections.push_back(
				G4ExtrudedSolid::ZSection(50. * mm, G4TwoVector(), 1.0));

		G4Transform3D const t = G4RotateX3D(90. * deg);
		auto const face = new G4DisplacedSolid("",
				new G4ExtrudedSolid("", polygon, zsections), t);

		solidTarget = new G4SubtractionSolid(solidTarget->GetName(),
				solidTarget, face);
	}

	{
		// holes
		G4Transform3D const t = G4RotateX3D(90. * deg);

		auto const solid = new G4DisplacedSolid("",
				new G4Tubs("", 0., 5. * mm, GetHalfHeight() + 1. * mm,
						0.0 * deg, 360.0 * deg), t);

		auto const hole1 = new G4DisplacedSolid("", solid,
				G4TranslateZ3D(-140. * mm));
		auto const hole2 = new G4DisplacedSolid("", solid,
				G4TranslateZ3D(140. * mm));

		solidTarget = new G4SubtractionSolid(solidTarget->GetName(),
				solidTarget, hole1);
		solidTarget = new G4SubtractionSolid(solidTarget->GetName(),
				solidTarget, hole2);
	}

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

	{
		// support
		auto const supMaterial = nist->FindOrBuildMaterial(supportMaterial);

		auto const holeSolid = new G4DisplacedSolid("",
				new G4Tubs("", 0., 5. * mm, GetHalfHeight(), 0.0 * deg,
						360.0 * deg), G4RotateX3D(90. * deg));

		{
			// screw 1
			auto const hole = new G4DisplacedSolid("", holeSolid,
					G4TranslateZ3D(-140. * mm));
			auto const logic = new G4LogicalVolume(hole, supMaterial,
					NameBuilder::Make(solidTarget->GetName(), "screw1"));
			logic->SetVisAttributes(
					G4VisAttributes(repository::Colours::Aluminium()));
			new G4PVPlacement(zeroTransform, logic, logic->GetName(),
					logicTarget, single, numOfCopies, checkOverlaps);
		}

		{
			// screw 2
			auto const hole = new G4DisplacedSolid("", holeSolid,
					G4TranslateZ3D(140. * mm));
			auto const logic = new G4LogicalVolume(hole, supMaterial,
					NameBuilder::Make(solidTarget->GetName(), "screw2"));
			logic->SetVisAttributes(
					G4VisAttributes(repository::Colours::Aluminium()));
			new G4PVPlacement(zeroTransform, logic, logic->GetName(),
					logicTarget, single, numOfCopies, checkOverlaps);
		}

		{
			// plane
			auto const solid = new G4Box("", GetHalfWidth() + 5. * mm, 5. * mm,
					GetHalfLength() + 5. * mm);
			auto const logic = new G4LogicalVolume(solid, supMaterial,
					solid->GetName());
			logic->SetVisAttributes(
					G4VisAttributes(repository::Colours::Aluminium()));
			new G4PVPlacement(G4TranslateY3D(-30. * mm), logic,
					logic->GetName(), logicTarget, single, numOfCopies,
					checkOverlaps);
		}
	}

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

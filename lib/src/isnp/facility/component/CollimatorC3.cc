#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4SubtractionSolid.hh>
#include <G4Tubs.hh>

#include "isnp/facility/component/CollimatorC3.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

namespace component {

CollimatorC3::CollimatorC3() :
		innerDiameter(120. * mm), outerDiameter(160. * mm), length(600. * mm) {

}

G4LogicalVolume* CollimatorC3::AsCylinder() const {

	return AsCylinder(GetDefaultName());

}

G4LogicalVolume* CollimatorC3::AsCylinder(const G4String &name) const {

	return MakeLogical(
			MakeCylinder(name, GetLength(), GetOuterRadius(),
					GetInnerDiameter()));

}

G4LogicalVolume* CollimatorC3::Instance(G4VSolid* const outer) const {

	return Instance(GetDefaultName(), outer);

}

G4LogicalVolume* CollimatorC3::Instance(const G4String &name,
		G4VSolid* const outer) const {

	const auto aperture = new G4Tubs(name, 0.0, HalfOf(GetInnerDiameter()),
			HalfOf(GetLength()) + 1. * mm, 0.0 * deg, 360.0 * deg);
	const auto solid = new G4SubtractionSolid(name, outer, aperture);

	return MakeLogical(solid);

}

G4String CollimatorC3::GetDefaultName() {
	return util::NameBuilder::Make("c", "3");
}

G4LogicalVolume* CollimatorC3::MakeLogical(G4VSolid * const solid) {

	const auto nist = G4NistManager::Instance();

	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("G4_STAINLESS-STEEL"), solid->GetName());
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Steel()));

	return logic;
}

}

}

}

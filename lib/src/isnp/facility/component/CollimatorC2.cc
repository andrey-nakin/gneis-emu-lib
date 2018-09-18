#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>

#include "isnp/facility/component/CollimatorC2.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

namespace component {

CollimatorC2::CollimatorC2() :
		aperture(100. * mm, 210. * mm, 710. * mm) {
}

G4LogicalVolume* CollimatorC2::AsCylinder(G4double const outerRadius) const {

	return AsCylinder(GetDefaultName(), outerRadius);

}

G4LogicalVolume* CollimatorC2::AsCylinder(const G4String &name,
		G4double const outerRadius) const {

	return Instance(name,
			MakeCylinder(util::NameBuilder::Make(name, "Outer"),
					aperture.GetLength(), outerRadius));

}

G4LogicalVolume* CollimatorC2::Instance(G4VSolid* const outer) const {

	return Instance(GetDefaultName(), outer);

}

G4LogicalVolume* CollimatorC2::Instance(const G4String &name,
		G4VSolid* const outer) const {

	const auto nist = G4NistManager::Instance();

	const auto solid = SolidWithAperture(name, outer, aperture);
	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("G4_STAINLESS-STEEL"), name);
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Steel()));

	return logic;

}

G4String CollimatorC2::GetDefaultName() {

	return util::NameBuilder::Make("c", "2");

}

}

}

}

#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>

#include "isnp/facility/component/CollimatorC1.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

namespace component {

CollimatorC1::CollimatorC1() :
		aperture(180. * mm, 140. * mm, 400. * mm) {

}

G4LogicalVolume* CollimatorC1::AsCylinder(G4double const outerRadius) const {

	return AsCylinder(GetDefaultName(), outerRadius);

}

G4LogicalVolume* CollimatorC1::AsCylinder(const G4String &name,
		G4double const outerRadius) const {

	return Instance(name,
			MakeCylinder(util::NameBuilder::Make(name, "Outer"),
					aperture.GetLength(), outerRadius));

}

G4LogicalVolume* CollimatorC1::Instance(G4VSolid* const outer) const {

	return Instance(GetDefaultName(), outer);

}

G4LogicalVolume* CollimatorC1::Instance(const G4String &name,
		G4VSolid* const outer) const {

	const auto nist = G4NistManager::Instance();

	const auto solid = SolidWithAperture(name, outer, aperture);
	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("G4_BRASS"), name);
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Brass()));

	return logic;

}

G4String CollimatorC1::GetDefaultName() {

	return util::NameBuilder::Make("c", "1");

}

}

}

}

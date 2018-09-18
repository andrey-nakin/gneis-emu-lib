#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4SubtractionSolid.hh>
#include <G4Tubs.hh>

#include "isnp/facility/component/CylindricComponent.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

namespace component {

CylindricComponent::CylindricComponent(G4double const aInnerDiameter,
		G4double const aOuterDiameter, G4double const aLength,
		G4String const& aMaterial, G4Colour const& aColor) :
		innerDiameter(aInnerDiameter), outerDiameter(aOuterDiameter), length(
				aLength), material(aMaterial), color(aColor) {

}

CylindricComponent::~CylindricComponent() {

}

G4LogicalVolume* CylindricComponent::AsCylinder() const {

	return AsCylinder(GetDefaultName());

}

G4LogicalVolume* CylindricComponent::AsCylinder(const G4String &name) const {

	return MakeLogical(
			MakeCylinder(name, GetLength(), GetOuterRadius(),
					GetInnerDiameter()));

}

G4LogicalVolume* CylindricComponent::MakeLogical(G4VSolid * const solid) const {

	const auto nist = G4NistManager::Instance();

	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial(material), solid->GetName());
	logic->SetVisAttributes(G4VisAttributes(color));

	return logic;
}

}

}

}

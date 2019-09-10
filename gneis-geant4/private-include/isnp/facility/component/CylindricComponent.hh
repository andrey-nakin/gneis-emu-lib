#ifndef isnp_facility_component_CylindricComponent_hh
#define isnp_facility_component_CylindricComponent_hh

#include <G4LogicalVolume.hh>
#include <G4VSolid.hh>
#include <G4Colour.hh>
#include "BoxComponent.hh"

namespace isnp {

namespace facility {

namespace component {

/**
 * Third collimator on beams #1 - #5
 */
class CylindricComponent: private BoxComponent {
public:

	CylindricComponent(G4double innerDiameter, G4double outerDiameter,
			G4double length, G4String const& material, G4Colour const& color);
	virtual ~CylindricComponent();

	G4LogicalVolume* AsCylinder() const;
	G4LogicalVolume* AsCylinder(const G4String &name) const;

	virtual G4String GetDefaultName() const = 0;

	G4double GetInnerDiameter() const {

		return innerDiameter;

	}

	G4double GetInnerRadius() const {

		return GetInnerDiameter() / 2;

	}

	G4double GetOuterDiameter() const {

		return outerDiameter;

	}

	G4double GetOuterRadius() const {

		return GetOuterDiameter() / 2;

	}

	G4double GetLength() const {

		return length;

	}

private:

	G4double const innerDiameter, outerDiameter, length;
	G4String const material;
	G4Colour const color;

	G4LogicalVolume* MakeLogical(G4VSolid *solid) const;

};

}

}

}

#endif	//	isnp_facility_component_CylindricComponent_hh

#include <G4UnitsTable.hh>
#include <G4UImanager.hh>
#include <G4RotationMatrix.hh>

#include "isnp/util/Convert.hh"

namespace isnp {

namespace util {

Convert::Convert() {
}

G4ThreeVector Convert::StringsToVector(G4String const &x, G4String const &y,
		G4String const &z, G4String const &units) {

	G4ThreeVector result;

	if (!x.isNull() && !y.isNull() && !z.isNull() && !units.isNull()) {
		auto const unitValue = G4UnitDefinition::GetValueOf(units);

		result.setX(std::stof(x) * unitValue);
		result.setY(std::stof(y) * unitValue);
		result.setZ(std::stof(z) * unitValue);
	}

	return result;

}

G4ThreeVector Convert::CommandToVector(const char* const cmd) {

	auto const uiManager = G4UImanager::GetUIpointer();

	return StringsToVector(uiManager->GetCurrentStringValue(cmd, 1),
			uiManager->GetCurrentStringValue(cmd, 2),
			uiManager->GetCurrentStringValue(cmd, 3),
			uiManager->GetCurrentStringValue(cmd, 4));

}

G4Transform3D Convert::VectorsToTransform(G4ThreeVector const rotation,
		G4ThreeVector const translation) {

	G4RotationMatrix rotm = G4RotationMatrix();
	rotm.rotateX(rotation.getX());
	rotm.rotateY(rotation.getY());
	rotm.rotateZ(rotation.getZ());
	return G4Transform3D(rotm, translation);

}

}

}

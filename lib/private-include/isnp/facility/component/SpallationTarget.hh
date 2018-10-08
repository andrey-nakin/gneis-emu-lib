#ifndef isnp_facility_component_SpallationTarget_hh
#define isnp_facility_component_SpallationTarget_hh

#include <memory>

#include <G4Transform3D.hh>
#include <G4LogicalVolume.hh>
#include "BoxComponent.hh"
#include "isnp/util/Box.hh"
#include "isnp/util/Singleton.hh"

namespace isnp {

namespace facility {

namespace component {

class SpallationTargetMessenger;

/**
 * Class encapsulates an information about the lead target
 * used as source of neutrons in the spallation process.
 */
class SpallationTarget final : private BoxComponent,
		public util::Box,
		public util::Singleton<SpallationTarget> {

public:

	static G4Transform3D GetTransform() {
		return transform;
	}

	static void SetTransform(G4Transform3D const& t) {
		transform = t;
	}

	static void SetTransform(G4Transform3D && t) {
		transform = t;
	}

	void Place(G4LogicalVolume* destination);

	G4bool GetHasCooler() const;
	void SetHasCooler(G4bool v);

	G4ThreeVector GetRotation() const;
	void SetRotation(G4ThreeVector v);

	G4ThreeVector GetPosition() const;
	void SetPosition(G4ThreeVector v);

private:

	friend class util::Singleton<SpallationTarget>;

	SpallationTarget();

	std::unique_ptr<SpallationTargetMessenger> const messenger;
	G4double const coolerInnerRadius, coolerOuterRadius, coolerTorusMinRadius;
	G4String const supportMaterial;
	G4bool hasCooler;
	G4ThreeVector rotation, position;

	static G4Transform3D transform;

};

}

}

}

#endif	//	isnp_facility_component_SpallationTarget_hh

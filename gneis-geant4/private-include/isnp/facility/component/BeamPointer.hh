#ifndef isnp_facility_component_BeamPointer_hh
#define isnp_facility_component_BeamPointer_hh

#include <memory>

#include <G4ThreeVector.hh>
#include "isnp/util/Singleton.hh"

namespace isnp {

namespace facility {

namespace component {

class BeamPointerMessenger;

class BeamPointer: public util::Singleton<BeamPointer> {
public:

	G4ThreeVector GetRotation() const;
	void SetRotation(G4ThreeVector v);

	G4ThreeVector GetPosition() const;
	void SetPosition(G4ThreeVector v);

private:

	friend class util::Singleton<BeamPointer>;

	BeamPointer();

	std::unique_ptr<BeamPointerMessenger> const messenger;
	G4ThreeVector rotation, position;

};

}

}

}

#endif	//	isnp_facility_component_BeamPointer_hh

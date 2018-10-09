#include <G4SystemOfUnits.hh>

#include "isnp/facility/component/BeamPointer.hh"
#include "isnp/facility/component/BeamPointerMessenger.hh"

namespace isnp {

namespace facility {

namespace component {

BeamPointer::BeamPointer() :
		messenger(std::make_unique < BeamPointerMessenger > (*this)) {
}

G4ThreeVector BeamPointer::GetRotation() const {

	return rotation;

}

void BeamPointer::SetRotation(G4ThreeVector const v) {

	std::cerr << "ttt SetRotation " << v / deg << "\n";
	rotation = v;

}

G4ThreeVector BeamPointer::GetPosition() const {

	return position;

}

void BeamPointer::SetPosition(G4ThreeVector const v) {

	position = v;

}

}

}

}

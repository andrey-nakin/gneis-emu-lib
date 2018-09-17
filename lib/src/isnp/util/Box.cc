#include "isnp/util/Box.hh"

namespace isnp {

namespace util {

Box::Box(G4double const aWidth, G4double const aHeight, G4double const aLength) :
		width(aWidth), height(aHeight), length(aLength) {

}

G4double Box::GetWidth() const {

	return width;

}

G4double Box::GetHalfWidth() const {

	return HalfOf(GetWidth());

}

G4double Box::GetHeight() const {

	return height;

}

G4double Box::GetHalfHeight() const {

	return HalfOf(GetHeight());

}

G4double Box::GetLength() const {

	return length;

}

G4double Box::GetHalfLength() const {

	return HalfOf(GetLength());

}

G4double Box::HalfOf(G4double const v) {

	return v / 2;

}

}

}

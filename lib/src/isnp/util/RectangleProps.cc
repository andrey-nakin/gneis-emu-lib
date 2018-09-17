#include "isnp/util/RectangleProps.hh"

namespace isnp {

namespace util {

RectangleProps::RectangleProps(G4double const aXWidth, G4double const aYWidth) :
		xWidth(aXWidth), yWidth(aYWidth), xHalfWidth(aXWidth / 2), yHalfWidth(
				aYWidth / 2) {
}

}

}

#ifndef isnp_util_RectangleProps_hh
#define isnp_util_RectangleProps_hh

#include <G4Types.hh>

namespace isnp {

namespace util {

class RectangleProps {
public:

	RectangleProps(G4double aXWidth, G4double aYWidth);

	G4double GetXWidth() const {

		return xWidth;

	}

	void SetXWidth(G4double const aXWidth) {

		xWidth = aXWidth;
		xHalfWidth = aXWidth / 2;

	}

	G4double GetXHalfWidth() const {

		return xHalfWidth;

	}

	void SetXHalfWidth(G4double const aXHalfWidth) {

		xWidth = aXHalfWidth * 2;
		xHalfWidth = aXHalfWidth;

	}

	G4double GetYWidth() const {

		return yWidth;

	}

	void SetYWidth(G4double const aYWidth) {

		yWidth = aYWidth;
		yHalfWidth = aYWidth / 2;

	}

	G4double GetYHalfWidth() const {

		return yHalfWidth;

	}

	void SetYHalfWidth(G4double const aYHalfWidth) {

		yWidth = aYHalfWidth * 2;
		yHalfWidth = aYHalfWidth;

	}

private:

	G4double xWidth, yWidth, xHalfWidth, yHalfWidth;

};

}

}

#endif	//	isnp_util_GaussEllipse_hh

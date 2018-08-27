#ifndef isnp_dist_GaussEllipse_hh
#define isnp_dist_GaussEllipse_hh

#include <G4Types.hh>
#include "isnp/dist/AbstractDistribution.hh"
#include "isnp/util/PropertyHolder.hh"

namespace isnp {

namespace dist {

class GaussEllipseProps {
public:

	GaussEllipseProps(G4double aXWidth, G4double aYWidth);

	G4double GetXWidth() const {

		return xWidth;

	}

	void SetXWidth(G4double const aXWidth) {

		xWidth = aXWidth;

	}

	G4double GetYWidth() const {

		return yWidth;

	}

	void SetYWidth(G4double const aYWidth) {

		yWidth = aYWidth;

	}

private:

	G4double xWidth, yWidth;

};

class GaussEllipse: public AbstractDistribution, public util::PropertyHolder<
		GaussEllipseProps> {

public:

	using util::PropertyHolder<GaussEllipseProps>::PropertyHolder;

	G4ThreeVector Generate() const override;

};

}

}

#endif	//	isnp_dist_GaussEllipse_hh

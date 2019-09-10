#ifndef isnp_dist_GaussEllipse_hh
#define isnp_dist_GaussEllipse_hh

#include <G4Types.hh>
#include "isnp/dist/AbstractDistribution.hh"
#include "isnp/util/PropertyHolder.hh"
#include "isnp/util/RectangleProps.hh"

namespace isnp {

namespace dist {

class GaussEllipseProps: public util::RectangleProps {
public:

	using util::RectangleProps::RectangleProps;

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

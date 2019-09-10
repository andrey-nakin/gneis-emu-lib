#ifndef isnp_dist_UniformRectangle_hh
#define isnp_dist_UniformRectangle_hh

#include <G4Types.hh>
#include "isnp/dist/AbstractDistribution.hh"
#include "isnp/util/PropertyHolder.hh"
#include "isnp/util/RectangleProps.hh"

namespace isnp {

namespace dist {

class UniformRectangleProps: public util::RectangleProps {
public:

	using util::RectangleProps::RectangleProps;

};

class UniformRectangle: public AbstractDistribution,
		public util::PropertyHolder<UniformRectangleProps> {
public:

	using util::PropertyHolder<UniformRectangleProps>::PropertyHolder;

	G4ThreeVector Generate() const override;

};

}

}

#endif	//	isnp_dist_UniformRectangle_hh

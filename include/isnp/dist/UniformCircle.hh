#ifndef isnp_dist_UniformCircle_hh
#define isnp_dist_UniformCircle_hh

#include <G4Types.hh>
#include "isnp/dist/AbstractDistribution.hh"
#include "isnp/util/PropertyHolder.hh"

namespace isnp {

namespace dist {

class UniformCircleProps {
public:

	UniformCircleProps(G4double aDiameter);

	G4double GetDiameter() const {
		return diameter;
	}

	void SetDiameter(G4double const v) {
		diameter = v;
	}

private:

	G4double diameter;

};

class UniformCircle: public AbstractDistribution, public util::PropertyHolder<
		UniformCircleProps> {
public:

	using util::PropertyHolder<UniformCircleProps>::PropertyHolder;

	G4ThreeVector Generate() const override;

};

}

}

#endif	//	isnp_dist_UniformCircle_hh

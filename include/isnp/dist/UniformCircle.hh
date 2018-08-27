#ifndef isnp_dist_UniformCircle_hh
#define isnp_dist_UniformCircle_hh

#include <G4Types.hh>
#include "isnp/dist/AbstractDistribution.hh"

namespace isnp {

namespace dist {

class UniformCircle: public AbstractDistribution {
public:

	class Props {
	public:

		Props(G4double aDiameter);

		G4double GetDiameter() const {
			return diameter;
		}

		void SetDiameter(G4double const v) {
			diameter = v;
		}

	private:

		G4double diameter;

	};

	UniformCircle(const Props& aProps);

	G4ThreeVector Generate() const override;

	Props const& GetProps() const {

		return props;

	}

	Props& GetProps() {

		return props;

	}

private:

	Props props;

};

}

}

#endif	//	isnp_dist_UniformCircle_hh

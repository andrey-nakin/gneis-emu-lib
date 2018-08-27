#ifndef isnp_dist_UniformCircle_hh
#define isnp_dist_UniformCircle_hh

#include <G4Types.hh>
#include <G4ThreeVector.hh>

namespace isnp {

namespace dist {

class UniformCircle {
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
	virtual ~UniformCircle();

	G4ThreeVector Generate() const;

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

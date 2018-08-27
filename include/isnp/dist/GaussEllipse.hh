#ifndef isnp_dist_GaussEllipse_hh
#define isnp_dist_GaussEllipse_hh

#include <G4Types.hh>
#include <G4ThreeVector.hh>

namespace isnp {

namespace dist {

class GaussEllipse {
public:

	class Props {
	public:

		Props(G4double aXWidth, G4double  aYWidth);

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

	GaussEllipse(const Props& aProps);
	virtual ~GaussEllipse();

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

#endif	//	isnp_dist_GaussEllipse_hh

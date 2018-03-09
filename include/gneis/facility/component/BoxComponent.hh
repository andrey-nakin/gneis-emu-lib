#ifndef BoxComponent_hh
#define BoxComponent_hh

#include <G4LogicalVolume.hh>

namespace gneis {

namespace facility {

namespace component {

/**
 * Class encapsulates an information about a box-like component.
 */
class BoxComponent {
protected:

	BoxComponent(BoxComponent const&) = delete;
	BoxComponent& operator=(BoxComponent const&) = delete;

	static G4double HalfOf(G4double v);

};

}

}

}

#endif	//	BoxComponent_hh

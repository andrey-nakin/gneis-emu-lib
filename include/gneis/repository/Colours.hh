#ifndef colors_hh
#define colors_hh

#include <G4Colour.hh>

namespace gneis {

namespace repository {

/**
 * Collections of standard colors
 */
class Colours final {
public:

	Colours() = delete;

	static G4Colour Lead();
	static G4Colour Brass();
	static G4Colour Steel();
	static G4Colour Concrete();

private:

	static G4Colour FromRGB(short red, short green, short blue);

};

}

}

#endif	//	colors_hh

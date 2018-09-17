#include "isnp/repository/Colours.hh"

namespace isnp {

namespace repository {

G4Colour Colours::Lead() {
	return FromRGB(159, 157, 153);
}

G4Colour Colours::Brass() {
	return FromRGB(218, 162, 15);
}

G4Colour Colours::Bronze() {
	return FromRGB(205, 127, 50);
}

G4Colour Colours::Steel() {
	return FromRGB(188, 197, 204);
}

G4Colour Colours::Aluminium() {
	return FromRGB(136, 137, 139);
}

G4Colour Colours::Concrete() {
	return FromRGB(127, 128, 118);
}

G4Colour Colours::FromRGB(short const red, short const green,
		short const blue) {
	const G4double m = 1.0 / 255.0;
	return G4Colour(m * red, m * green, m * blue);
}

}

}

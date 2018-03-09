#include "gneis/repository/Colours.hh"

G4Colour gneis::repository::Colours::Lead() {
	return FromRGB(159, 157, 153);
}

G4Colour gneis::repository::Colours::Brass() {
	return FromRGB(218, 162, 15);
}

G4Colour gneis::repository::Colours::Steel() {
	return FromRGB(188, 197, 204);
}

G4Colour gneis::repository::Colours::Concrete() {
	return FromRGB(127, 128, 118);
}

G4Colour gneis::repository::Colours::FromRGB(short const red, short const green, short const blue) {
	const G4double m = 1.0 / 255.0;
	return G4Colour(m * red, m * green, m * blue);
}

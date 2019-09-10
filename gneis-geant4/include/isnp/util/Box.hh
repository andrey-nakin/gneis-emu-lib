#ifndef isnp_util_Box_hh
#define isnp_util_Box_hh

#include <G4Types.hh>

namespace isnp {

namespace util {

class Box {
public:

	Box(G4double width, G4double height, G4double length);

	G4double GetWidth() const;
	G4double GetHalfWidth() const;

	G4double GetHeight() const;
	G4double GetHalfHeight() const;

	G4double GetLength() const;
	G4double GetHalfLength() const;

private:

	G4double width, height, length;

	static G4double HalfOf(G4double);

};

}

}

#endif	//	isnp_util_Box_hh

#ifndef gneis_testutil_Stat_hh
#define gneis_testutil_Stat_hh

#include <functional>
#include <G4Types.hh>

namespace gneis {

namespace testutil {

class Stat {
public:

	Stat();

	Stat& operator+=(G4double value);

	G4double GetMean() const;
	G4double GetMeanStd() const;
	G4double GetStd() const;
	G4double GetVar() const;
	G4double GetMin() const;
	G4double GetMax() const;

	bool Is(G4double value) const;

private:

	unsigned count;
	G4double sum, sum2;
	G4double minValue, maxValue;

};

}

}

#endif	//	gneis_testutil_Stat_hh

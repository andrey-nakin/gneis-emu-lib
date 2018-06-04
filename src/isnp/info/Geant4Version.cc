#include <algorithm>
#include <sstream>
#include <G4Version.hh>
#include "isnp/info/Geant4Version.hh"

namespace isnp {

namespace info {

const std::vector<int> Geant4Version::Get() {
	std::vector<int> version;

	version.push_back(G4VERSION_NUMBER / 100);
	version.push_back(G4VERSION_NUMBER / 10 % 10);
	version.push_back(G4VERSION_NUMBER % 10);

	return version;
}

const G4String Geant4Version::GetAsString() {
	const std::vector<int> ver = Get();
	std::stringstream s;
	bool first = true;

	std::for_each(ver.begin(), ver.end(), [&s, &first](int n) {
		if (first) {
			first = false;
		} else {
			s << '.';
		}
		s << n;
	});

	return G4String(s.str());
}

bool Geant4Version::Matches(const int major, const int minor, const int patch) {

	const std::vector<int> ver = Get();

	if (ver.size() < 1) {
		return false;
	}

	if (ver[0] < major) {
		return false;
	}
	if (ver[0] > major) {
		return true;
	}

	if (minor >= 0) {
		if (ver.size() < 2) {
			return false;
		}
		if (ver[1] < minor) {
			return false;
		}
		if (ver[1] > minor) {
			return true;
		}
	}

	if (patch >= 0) {
		if (ver.size() < 3) {
			return false;
		}
		if (ver[2] < patch) {
			return false;
		}
		if (ver[2] > patch) {
			return true;
		}
	}

	return true;
}

const G4String Geant4Version::GetDateAsString() {
	return G4Date;
}

}

}

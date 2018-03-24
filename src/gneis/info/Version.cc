#include <algorithm>
#include <sstream>
#include "gneis/info/Version.hh"

const std::vector<int> gneis::info::Version::Get() {
	std::vector<int> version;

#ifdef	GNEISEMULIB_MAJOR_VERSION
	version.push_back(GNEISEMULIB_MAJOR_VERSION);
#else
	version.push_back(-1);
#endif
#ifdef	GNEISEMULIB_MINOR_VERSION
	version.push_back(GNEISEMULIB_MINOR_VERSION);
#else
	version.push_back(-1);
#endif
#ifdef	GNEISEMULIB_PATCH_VERSION
	version.push_back(GNEISEMULIB_PATCH_VERSION);
#else
	version.push_back(-1);
#endif

	return version;
}

const G4String gneis::info::Version::GetAsString() {
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

bool gneis::info::Version::Matches(const int major, const int minor,
		const int patch) {

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
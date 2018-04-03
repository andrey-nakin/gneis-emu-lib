#include <algorithm>
#include <sstream>
#include "isnp/info/Version.hh"

const std::vector<int> isnp::info::Version::Get() {
	std::vector<int> version;

#ifdef	ISNPEMULIB_VERSION_MAJOR
	version.push_back(ISNPEMULIB_VERSION_MAJOR);
#else
	version.push_back(-1);
#endif
#ifdef	ISNPEMULIB_VERSION_MINOR
	version.push_back(ISNPEMULIB_VERSION_MINOR);
#else
	version.push_back(-1);
#endif
#ifdef	ISNPEMULIB_VERSION_PATCH
	version.push_back(ISNPEMULIB_VERSION_PATCH);
#else
	version.push_back(-1);
#endif

	return version;
}

const G4String isnp::info::Version::GetAsString() {
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

bool isnp::info::Version::Matches(const int major, const int minor,
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

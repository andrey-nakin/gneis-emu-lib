#include "isnp/util/FileNameBuilder.hh"

G4String isnp::util::FileNameBuilder::commonSuffix = "";

G4String isnp::util::FileNameBuilder::Make(char const* const base, char const* const suffix) {
	return Make(G4String(base), suffix);
}

G4String isnp::util::FileNameBuilder::Make(G4String const& base, char const* const suffix) {
	G4String result = base;

	if (!commonSuffix.isNull()) {
		result += '.';
		result += commonSuffix;
	}

	if (suffix) {
		result += suffix;
	}

	return result;
}

void isnp::util::FileNameBuilder::SetCommonSuffix(G4String const& s) {
	commonSuffix = s;
}

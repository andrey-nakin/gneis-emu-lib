#include "gneis/util/NameBuilder.hh"

G4String gneis::util::NameBuilder::Make(const char *parent, const char *child) {
	return Make(G4String(parent), child);
}

G4String gneis::util::NameBuilder::Make(G4String const &parent, const char *child) {
	return Make(parent, G4String(child));
}

G4String gneis::util::NameBuilder::Make(G4String const &parent, G4String const &child) {
	return parent + GetSeparator() + child;
}

G4String gneis::util::NameBuilder::GetSeparator() {
	return ":";
}

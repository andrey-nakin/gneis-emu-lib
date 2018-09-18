#include "isnp/util/NameBuilder.hh"

G4String isnp::util::NameBuilder::Make(const char *parent, const char *child) {
	return Make(G4String(parent), child);
}

G4String isnp::util::NameBuilder::Make(const char *s1, const char *s2,
		const char *s3) {

	G4String s = "";
	s += s1;
	s += GetSeparator();
	s += s2;
	s += GetSeparator();
	s += s3;
	return s;

}

G4String isnp::util::NameBuilder::Make(const char *s1, int const s2,
		const char *s3) {

	G4String s = "";
	s += s1;
	s += GetSeparator();
	s += s2;
	s += GetSeparator();
	s += s3;
	return s;

}

G4String isnp::util::NameBuilder::Make(const char *s1, const char *s2,
		const char *s3, const char *s4) {

	G4String s = "";
	s += s1;
	s += GetSeparator();
	s += s2;
	s += GetSeparator();
	s += s3;
	s += GetSeparator();
	s += s4;
	return s;

}

G4String isnp::util::NameBuilder::Make(const char *s1, int const s2,
		const char *s3, int const s4) {

	G4String s = "";
	s += s1;
	s += GetSeparator();
	s += s2;
	s += GetSeparator();
	s += s3;
	s += GetSeparator();
	s += s4;
	return s;

}

G4String isnp::util::NameBuilder::Make(G4String const &parent,
		const char *child) {
	return Make(parent, G4String(child));
}

G4String isnp::util::NameBuilder::Make(G4String const &parent,
		G4String const &child) {
	return parent + GetSeparator() + child;
}

G4String isnp::util::NameBuilder::GetSeparator() {
	return ":";
}

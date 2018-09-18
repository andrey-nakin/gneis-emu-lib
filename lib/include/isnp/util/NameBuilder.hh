#ifndef NameBuilder_hh
#define NameBuilder_hh

#include <G4String.hh>

namespace isnp {

namespace util {

/**
 * Construction of composite names.
 */
class NameBuilder final {
public:

	NameBuilder() = delete;

	static G4String Make(const char *parent, const char *child);
	static G4String Make(const char *s1, const char *s2, const char *s3);
	static G4String Make(const char *s1, int s2, const char *s3);
	static G4String Make(const char *s1, const char *s2, const char *s3, const char *s4);
	static G4String Make(const char *s1, int s2, const char *s3, int s4);
	static G4String Make(G4String const &parent, const char *child);
	static G4String Make(G4String const &parent, G4String const &child);

private:

	static G4String GetSeparator();

};

}

}

#endif	//	NameBuilder_hh

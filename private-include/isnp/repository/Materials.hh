#ifndef isnp_repository_Materials_hh
#define isnp_repository_Materials_hh

#include <G4Colour.hh>

namespace isnp {

namespace repository {

/**
 * Collections of standard colors
 */
class Materials final {
public:

	~Materials();

	static Materials* GetInstance();

private:

	Materials();

	void CreateMaterials();

};

}

}

#endif	//	isnp_repository_Materials_hh

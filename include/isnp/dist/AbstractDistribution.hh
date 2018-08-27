#ifndef isnp_dist_AbstractDistribution_hh
#define isnp_dist_AbstractDistribution_hh

#include <G4ThreeVector.hh>
#include "isnp/util/NonCopyable.hh"

namespace isnp {

namespace dist {

class AbstractDistribution: public util::NonCopyable {
public:

	virtual G4ThreeVector Generate() const = 0;

};

}

}

#endif	//	isnp_dist_AbstractDistribution_hh

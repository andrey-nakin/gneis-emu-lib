#ifndef isnp_dist_AbstractDistribution_hh
#define isnp_dist_AbstractDistribution_hh

#include <G4ThreeVector.hh>

namespace isnp {

namespace dist {

class AbstractDistribution {

	AbstractDistribution(AbstractDistribution&) = delete;
	AbstractDistribution(const AbstractDistribution&) = delete;
	AbstractDistribution(volatile AbstractDistribution&) = delete;
	AbstractDistribution(const volatile AbstractDistribution&) = delete;

	AbstractDistribution& operator=(AbstractDistribution&) = delete;
	AbstractDistribution& operator=(const AbstractDistribution&) = delete;
	AbstractDistribution& operator=(volatile AbstractDistribution&) = delete;
	AbstractDistribution& operator=(const volatile AbstractDistribution&) = delete;

protected:

	AbstractDistribution();

public:

	virtual ~AbstractDistribution();

	virtual G4ThreeVector Generate() const = 0;

};

}

}

#endif	//	isnp_dist_AbstractDistribution_hh

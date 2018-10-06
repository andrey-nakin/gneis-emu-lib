#include <cmath>
#include <sstream>

#include <G4RunManager.hh>
#include <QGSP_INCLXX_HP.hh>
#include <G4SystemOfUnits.hh>

#include <gtest/gtest.h>

#include <isnp/generator/Resampling.hh>
#include "isnp/testutil/Stat.hh"
#include "isnp/testutil/SampleData.hh"

namespace isnp {

namespace generator {

TEST(Resampling, Generic) {

	using namespace isnp::testutil;

	std::stringstream s;
	s << SampleData_txt;

	Resampling resampling;
	resampling.SetVerboseLevel(1);
	resampling.Load(s);

	Stat energy, dirX, dirY, dirZ;
	G4Transform3D const zeroTransform;

	for (int i = 0; i < 1000000; i++) {
		G4Event event;
		resampling.GeneratePrimaries(&event);
		auto const v = event.GetPrimaryVertex(0);
		auto const p = v->GetPrimary();

		energy += p->GetKineticEnergy();

		dirX += p->GetMomentumDirection().getX();
		dirY += p->GetMomentumDirection().getY();
		dirZ += p->GetMomentumDirection().getZ();
	}

	EXPECT_TRUE(energy.Is(64.9908 * MeV));
	EXPECT_NEAR(0.380429 * MeV, energy.GetMin(), 0.5e-6 * MeV);
	EXPECT_NEAR(715.122 * MeV, energy.GetMax(), 0.5e-3 * MeV);
	EXPECT_NEAR(142.758 * MeV, energy.GetStd(), 0.5e0 * MeV);

//	EXPECT_TRUE(energy.Is(1.73510E-004));

}

}

}

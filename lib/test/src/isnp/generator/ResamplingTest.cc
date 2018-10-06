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

	Stat energy;
	G4Transform3D const zeroTransform;

	for (int i = 0; i < 1000000; i++) {
		G4Event event;
		resampling.GeneratePrimaries(&event);
		auto const v = event.GetPrimaryVertex(0);
		auto const p = v->GetPrimary();

		energy += p->GetKineticEnergy();
//		x += event.
//		y += pos.getY();
//		z += pos.getZ();
//		r += std::sqrt(pos.getX() * pos.getX() + pos.getY() * pos.getY());
	}

	EXPECT_TRUE(energy.Is(64.9908 * MeV));
	EXPECT_NEAR(0.380429 * MeV, energy.GetMin(), 0.5e-6 * MeV);
	EXPECT_NEAR(715.122 * MeV, energy.GetMax(), 0.5e-3 * MeV);
	EXPECT_NEAR(142.758 * MeV, energy.GetStd(), 0.5e0 * MeV);
//
//	EXPECT_TRUE(y.Is(0.0 * cm));
//	EXPECT_NEAR(-2 * cm, y.GetMin(), 0.001 * cm);
//	EXPECT_NEAR(2 * cm, y.GetMax(), 0.001 * cm);
//	EXPECT_NEAR(1.0 * cm, y.GetStd(), 0.001 * cm);
//
//	EXPECT_DOUBLE_EQ(-200.0 * mm, z.GetMean());
//
//	EXPECT_NEAR(2 * cm, r.GetMax(), 0.01 * cm);
//	EXPECT_NEAR(0.47 * cm, r.GetStd(), 0.01 * cm);

}

}

}

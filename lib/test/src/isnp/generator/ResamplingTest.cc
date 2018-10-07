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

	Stat energy, dirX, dirY, dirZ, posX, posY, posZ;
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

		posX += v->GetPosition().getX();
		posY += v->GetPosition().getY();
		posZ += v->GetPosition().getZ();
	}

	EXPECT_TRUE(energy.Is(64.9908 * MeV));
	EXPECT_NEAR(0.380429 * MeV, energy.GetMin(), 0.5e-6 * MeV);
	EXPECT_NEAR(715.122 * MeV, energy.GetMax(), 0.5e-3 * MeV);
	EXPECT_NEAR(142.758 * MeV, energy.GetStd(), 0.5e0 * MeV);

	EXPECT_NEAR(1.7E-004, dirX.GetMean(), 2e-5);
	EXPECT_NEAR(-2.61548E-002, dirX.GetMin(), 0.5e-7);
	EXPECT_NEAR(2.54515E-002, dirX.GetMax(), 0.5e-7);

	EXPECT_NEAR(2.5E-004, dirY.GetMean(), 2e-5);
	EXPECT_NEAR(-2.46073E-002, dirY.GetMin(), 0.5e-7);
	EXPECT_NEAR(2.54980E-002, dirY.GetMax(), 0.5e-7);

	EXPECT_NEAR(9.99392E-001, dirZ.GetMin(), 0.5e-6);
	EXPECT_NEAR(9.99998E-001, dirZ.GetMax(), 0.5e-6);

	EXPECT_NEAR(-1.15125E+002 * mm, posX.GetMean(), 1. * mm);
	EXPECT_NEAR(-1.80748E+002 * mm, posX.GetMin(), 1. * mm);
	EXPECT_NEAR(7.06796E+001 * mm, posX.GetMax(), 1. * mm);
	EXPECT_NEAR(4.91067E+001 * mm, posX.GetStd(), 1. * mm);

	EXPECT_NEAR(4.43247E-001 * mm, posY.GetMean(), 1. * mm);
	EXPECT_NEAR(-2.70766E+001 * mm, posY.GetMin(), 1. * mm);
	EXPECT_NEAR(2.59510E+001 * mm, posY.GetMax(), 1. * mm);
	EXPECT_NEAR(1.54153E+001 * mm, posY.GetStd(), 1. * mm);

	EXPECT_EQ(0. * mm, posZ.GetMin());
	EXPECT_EQ(0. * mm, posZ.GetMax());
}

}

}

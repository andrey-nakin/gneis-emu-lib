#include <cmath>
#include <sstream>

#include <G4UImanager.hh>
#include <G4RunManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4RotationMatrix.hh>

#include <gtest/gtest.h>

#include <isnp/generator/Resampling.hh>
#include "isnp/testutil/Stat.hh"
#include "isnp/testutil/SampleData.hh"
#include "isnp/facility/component/BeamPointer.hh"

namespace isnp {

namespace generator {

static const char* const data =
		"Type\tTotalEnergy\tKineticEnergy\tTime\tDirectionX\tDirectionY\tDirectionZ\tPositionX\tPositionY\tPositionZ\n" "neutron\t940.401\t1000.00\t2000\t0.500000\t0.250000\t0.829156\t100.000\t200.000\t300.000";

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

TEST(Resampling, ChangePosition) {

	using namespace isnp::testutil;

	std::stringstream s;
	s << data;

	Resampling resampling;
	resampling.SetVerboseLevel(1);
	resampling.Load(s);

	{
		G4Event event;
		resampling.GeneratePrimaries(&event);
		auto const v = event.GetPrimaryVertex(0);
		auto const p = v->GetPrimary();

		EXPECT_NEAR(1000.0 * MeV, p->GetKineticEnergy(), 0.5e-2);

		EXPECT_NEAR(0.500000, p->GetMomentumDirection().getX(), 0.5e-6);
		EXPECT_NEAR(0.250000, p->GetMomentumDirection().getY(), 0.5e-6);
		EXPECT_NEAR(0.829156, p->GetMomentumDirection().getZ(), 0.5e-6);

		EXPECT_NEAR(-80.9068 * mm, v->GetPosition().getX(), 1.e-3 * mm);
		EXPECT_NEAR(109.547 * mm, v->GetPosition().getY(), 1.e-3 * mm);
		EXPECT_EQ(0. * mm, v->GetPosition().getZ() * mm);
	}

	resampling.SetPosition(G4ThreeVector(400., 500., 600.) * mm);

	{
		G4Event event;
		resampling.GeneratePrimaries(&event);
		auto const v = event.GetPrimaryVertex(0);
		auto const p = v->GetPrimary();

		EXPECT_NEAR(1000.0 * MeV, p->GetKineticEnergy(), 0.5e-2);

		EXPECT_NEAR(0.500000, p->GetMomentumDirection().getX(), 0.5e-6);
		EXPECT_NEAR(0.250000, p->GetMomentumDirection().getY(), 0.5e-6);
		EXPECT_NEAR(0.829156, p->GetMomentumDirection().getZ(), 0.5e-6);

		EXPECT_NEAR(-80.9068 * mm + 400.0 * mm, v->GetPosition().getX(),
				1.e-3 * mm);
		EXPECT_NEAR(109.547 * mm + 500.0 * mm, v->GetPosition().getY(),
				1.e-3 * mm);
		EXPECT_EQ(0. * mm + 600.0 * mm, v->GetPosition().getZ());
	}
}

TEST(Resampling, DetectBeamTransform) {

	using namespace isnp::testutil;

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility basicSpallation"));

	Resampling resampling;
	resampling.SetVerboseLevel(1);

	{
		std::stringstream s;
		s << data;
		resampling.Load(s);
	}

	auto const facility = facility::component::BeamPointer::GetInstance();
	EXPECT_TRUE(facility != nullptr);

	auto const savedRotation = facility->GetRotation();
	auto const savedPosition = facility->GetPosition();

	{
		EXPECT_EQ(0,
				uiManager->ApplyCommand(
						"/isnp/facility/component/beamPointer/rotation 0 45 0 deg"));
		EXPECT_EQ(0,
				uiManager->ApplyCommand(
						"/isnp/facility/component/beamPointer/position 400 500 600 mm"));

		G4Event event;
		resampling.GeneratePrimaries(&event);
		auto const v = event.GetPrimaryVertex(0);
		auto const p = v->GetPrimary();

		G4ThreeVector dir(0.500000, 0.250000, 0.829156);
		G4RotationMatrix rotm = G4RotationMatrix();
		rotm.rotateY(45 * deg);
		dir.transform(rotm);

		EXPECT_NEAR(dir.getX(), p->GetMomentumDirection().getX(), 0.5e-6);
		EXPECT_NEAR(dir.getY(), p->GetMomentumDirection().getY(), 0.5e-6);
		EXPECT_NEAR(dir.getZ(), p->GetMomentumDirection().getZ(), 0.5e-6);

		EXPECT_NEAR(-80.9068 * mm * sin(45. * deg) + 400.0 * mm,
				v->GetPosition().getX(), 1.e-3 * mm);
		EXPECT_NEAR(109.547 * mm + 500.0 * mm, v->GetPosition().getY(),
				1.e-3 * mm);
		EXPECT_NEAR(80.9068 * mm * sin(45. * deg) + 600.0 * mm,
				v->GetPosition().getZ(), 1.e-3 * mm);
	}

	facility->SetPosition(savedPosition);
	facility->SetRotation(savedRotation);

}

}

}

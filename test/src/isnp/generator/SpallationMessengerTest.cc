#include <cmath>

#include <G4RunManager.hh>
#include <QGSP_INCLXX_HP.hh>
#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>

#include <gtest/gtest.h>

#include <isnp/generator/Spallation.hh>

namespace isnp {

namespace generator {

constexpr G4double GET_CURRENT_DOUBLE_VALUE_DELTA = 1.e-6;

TEST(SpallationMessenger, GetDiameter)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(40 * mm, uiManager->GetCurrentDoubleValue("/isnp/spallation/gun/diameter"), GET_CURRENT_DOUBLE_VALUE_DELTA);
	spallation.GetUniformCircle().GetProps().SetDiameter(50 * mm);
	EXPECT_NEAR(50 * mm, uiManager->GetCurrentDoubleValue("/isnp/spallation/gun/diameter"), GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(SpallationMessenger, SetDiameter)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(40 * mm, spallation.GetUniformCircle().GetProps().GetDiameter());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/spallation/gun/diameter 50 mm"));
	EXPECT_DOUBLE_EQ(50 * mm, spallation.GetUniformCircle().GetProps().GetDiameter());

}

TEST(SpallationMessenger, GetXWidth)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(200 * mm, uiManager->GetCurrentDoubleValue("/isnp/spallation/gun/xWidth"), GET_CURRENT_DOUBLE_VALUE_DELTA);
	spallation.GetGeProps().SetXWidth(300 * mm);
	EXPECT_NEAR(300 * mm, uiManager->GetCurrentDoubleValue("/isnp/spallation/gun/xWidth"), GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(SpallationMessenger, SetXWidth)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(200 * mm, spallation.GetGeProps().GetXWidth());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/spallation/gun/xWidth 300 mm"));
	EXPECT_DOUBLE_EQ(300 * mm, spallation.GetGeProps().GetXWidth());

}

TEST(SpallationMessenger, GetYWidth)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(50 * mm, uiManager->GetCurrentDoubleValue("/isnp/spallation/gun/yWidth"), GET_CURRENT_DOUBLE_VALUE_DELTA);
	spallation.GetGeProps().SetYWidth(20 * mm);
	EXPECT_NEAR(20 * mm, uiManager->GetCurrentDoubleValue("/isnp/spallation/gun/yWidth"), GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(SpallationMessenger, SetYWidth)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(50 * mm, spallation.GetGeProps().GetYWidth());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/spallation/gun/yWidth 20 mm"));
	EXPECT_DOUBLE_EQ(20 * mm, spallation.GetGeProps().GetYWidth());

}

TEST(SpallationMessenger, GetPositionX)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(0 * mm, uiManager->GetCurrentDoubleValue("/isnp/spallation/gun/positionX"), GET_CURRENT_DOUBLE_VALUE_DELTA);
	spallation.SetPositionX(5 * mm);
	EXPECT_NEAR(5 * mm, uiManager->GetCurrentDoubleValue("/isnp/spallation/gun/positionX"), GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(SpallationMessenger, SetPositionX)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(0 * mm, spallation.GetPositionX());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/spallation/gun/positionX 5 mm"));
	EXPECT_DOUBLE_EQ(5 * mm, spallation.GetPositionX());

}

TEST(SpallationMessenger, GetPositionY)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_NEAR(0 * mm, uiManager->GetCurrentDoubleValue("/isnp/spallation/gun/positionY"), GET_CURRENT_DOUBLE_VALUE_DELTA);
	spallation.SetPositionY(5 * mm);
	EXPECT_NEAR(5 * mm, uiManager->GetCurrentDoubleValue("/isnp/spallation/gun/positionY"), GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(SpallationMessenger, SetPositionY)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_DOUBLE_EQ(0 * mm, spallation.GetPositionY());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/spallation/gun/positionY 5 mm"));
	EXPECT_DOUBLE_EQ(5 * mm, spallation.GetPositionY());

}

TEST(SpallationMessenger, GetVerboseLevel)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(1, uiManager->GetCurrentIntValue("/isnp/spallation/gun/verbose"));
	spallation.SetVerboseLevel(0);
	EXPECT_EQ(0, uiManager->GetCurrentIntValue("/isnp/spallation/gun/verbose"));

}

TEST(SpallationMessenger, SetVerboseLevel)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(1, spallation.GetVerboseLevel());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/spallation/gun/verbose 2"));
	EXPECT_EQ(2, spallation.GetVerboseLevel());
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/spallation/gun/verbose -1"));
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/spallation/gun/verbose 4"));

}

TEST(SpallationMessenger, GetMode)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ("UniformCircle", uiManager->GetCurrentStringValue("/isnp/spallation/gun/mode"));
	spallation.SetMode(Spallation::Mode::GaussianEllipse);
	EXPECT_EQ("GaussianEllipse", uiManager->GetCurrentStringValue("/isnp/spallation/gun/mode"));
	spallation.SetMode(Spallation::Mode::UniformRectangle);
	EXPECT_EQ("UniformRectangle", uiManager->GetCurrentStringValue("/isnp/spallation/gun/mode"));

}

TEST(SpallationMessenger, SetMode)
{

	Spallation spallation;
	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(Spallation::Mode::UniformCircle, spallation.GetMode());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/spallation/gun/mode GaussianEllipse"));
	EXPECT_EQ(Spallation::Mode::GaussianEllipse, spallation.GetMode());
	EXPECT_EQ(500, uiManager->ApplyCommand("/isnp/spallation/gun/mode badValue"));
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/spallation/gun/mode UniformCircle"));
	EXPECT_EQ(Spallation::Mode::UniformCircle, spallation.GetMode());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/spallation/gun/mode UniformRectangle"));
	EXPECT_EQ(Spallation::Mode::UniformRectangle, spallation.GetMode());

}

}

}

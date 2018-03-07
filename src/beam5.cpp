#include "beam5.hpp"

#include <G4RunManager.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4Cons.hh>
#include <G4Orb.hh>
#include <G4Sphere.hh>
#include <G4Trd.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>
#include <G4SDManager.hh>

Beam5::Beam5() :
		G4VUserDetectorConstruction() {
}

Beam5::~Beam5() {
}

G4VPhysicalVolume* Beam5::Construct() {
	return nullptr;
}

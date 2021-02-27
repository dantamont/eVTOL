/*
  @file main.cpp
  @author Dante tufano
  @date 2/26/2021
  @brief File driving the eVTOL application
 
  This is a more interesting description
  @see https://www.jobyaviation.com/
 */

#include <core/diagnostics/JLogger.h>
#include <apps/eVTOL/sim/JScene.h>

using namespace joby;

int main(int argc, char *argv[])
{
    Logger::LogInfo("Running eVTOL application");

    // Create the scene
    // NOTE: In production code, I would have this be entirely data-driven,
    // loading in a JSON file describing the scene, the different companies, their
    // vehicle specifications, the number of vehicles in the simulation, the
    // number of chargers, etc.
    Scene scene;
    scene.setChargerCount(3);
    scene.addCompany("Alpha",   Aircraft{ 120.0, 320.0, 0.6, 1.6, 4, 0.25 });
    scene.addCompany("Beta",    Aircraft{ 100, 100, 0.2, 1.5, 5, 0.1 });
    scene.addCompany("Charlie", Aircraft{ 160, 220, 0.8, 2.2, 3, 0.05 });
    scene.addCompany("Delta",   Aircraft{ 90, 120, 0.62, 0.8, 2, 0.22 });
    scene.addCompany("Echo",    Aircraft{ 30, 150, 0.3, 5.8, 2, 0.61 });

    // Simulate
    //Simulator sim;
    //sim.simulate(scene);

    // Vehicle metrics viewer?
	
    return 0;
}

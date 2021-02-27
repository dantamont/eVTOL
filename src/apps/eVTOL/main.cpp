/*
  @file main.cpp
  @author Dante tufano
  @date 2/26/2021
  @brief File driving the eVTOL application
 
  This is a more interesting description
  @see https://www.jobyaviation.com/
 */

#include <core/diagnostics/JLogger.h>

int main(int argc, char *argv[])
{
    joby::Logger::LogInfo("Running eVTOL application");

    // Initialize vehicles via JSON

    // Initialize chargers via JSON

    // Vehicle metrics viewer?
	

    // Loop
    double t = 0.0;
    double dt = 0.01;

    double currentTime = hires_time_in_seconds();
    double accumulator = 0.0;

    //State previous;
    //State current;

    while (!quit)
    {
        double newTime = time();
        double frameTime = newTime - currentTime;
        if (frameTime > 0.25)
            frameTime = 0.25;
        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= dt)
        {
            //previousState = currentState;
            integrate(currentState, t, dt);
            t += dt;
            accumulator -= dt;
        }

        const double alpha = accumulator / dt;

        //State state = currentState * alpha +
        //    previousState * (1.0 - alpha);

        //render(state);
    }

    return 0;
}

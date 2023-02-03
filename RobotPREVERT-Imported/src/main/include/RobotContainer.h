#pragma once

#include "Constants.h"
#include <frc2/command/Command.h>
#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>

#include "subsystems/Drivetrain.h"

#include "commands/Drive.h"

class RobotContainer
{
public:
    RobotContainer();
    Drivetrain m_Drivetrain;

private:
    void ConfigureButtonBindings();

    frc::Joystick m_DriverRightJoystick{DRIVER_JOYSTICK_RIGHT_ID};
};
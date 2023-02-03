// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"
#include <iostream>

#define TRACKWIDTH 0.61f
#define HALF_TRACKWIDTH (TRACKWIDTH / 2.0f)

#define AMAX 5.1 // Acceleration Max  au PIF .. à définir aux encodeurs
#define VMAX 3.4 // vitesse Max  théorique (3,395472 sur JVN-DT) .. à vérifier aux encodeurs
#define WMAX                     \
  (((2.0 * VMAX) / TRACKWIDTH) / \
   1.7) // vitesse angulaire Max theorique    .. à modifier avec Garice

#define NABS(a) (((a) < 0) ? -(a) : (a))     // VALEUR ABSOLUE
#define NMAX(a, b) (((a) > (b)) ? (a) : (b)) // Max
#define NMIN(a, b) (((a) < (b)) ? (a) : (b)) // Min

Drivetrain::Drivetrain()
{
  m_MotorRight.SetInverted(true);
  m_MotorRightFollow.SetInverted(true);
  m_MotorLeft.SetInverted(false);
  m_MotorLeftFollow.SetInverted(false);

  m_MotorRightFollow.Follow(m_MotorRight);
  m_MotorLeftFollow.Follow(m_MotorLeft);

  m_MotorRight.ConfigVoltageCompSaturation(12);
  m_MotorRightFollow.ConfigVoltageCompSaturation(12);
  m_MotorLeft.ConfigVoltageCompSaturation(12);
  m_MotorLeftFollow.ConfigVoltageCompSaturation(12);

}

void Drivetrain::Drive(float forward, float turn)
{
  double v = forward * VMAX;
  double w = turn * WMAX;

  double left_wheel = v + (w * HALF_TRACKWIDTH);
  double right_wheel = v - (w * HALF_TRACKWIDTH);

  double k;
  k = 1.0 / (NMAX(VMAX, NMAX(NABS(left_wheel), NABS(right_wheel))));
  left_wheel *= k;
  right_wheel *= k;

  m_MotorRight.Set(ctre::phoenix::motorcontrol::TalonSRXControlMode::PercentOutput, left_wheel); //
  m_MotorLeft.Set(ctre::phoenix::motorcontrol::TalonSRXControlMode::PercentOutput, right_wheel); // 
  std::cout << left_wheel << std::endl;
  std::cout << right_wheel << std::endl;
}

void Drivetrain::Periodic()
{
  // m_MotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.3);
}
// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Drive.h"
#include "lib/Utils.h"
#include <iostream>

Drive::Drive(std::function<double()> forward, std::function<double()> turn, std::function<double()> slide, Drivetrain *pdrivetrain)
    : m_Forward(forward), m_Turn(turn), m_Slide(slide), m_pDrivetrain(pdrivetrain)
{
  AddRequirements(m_pDrivetrain);
}

void Drive::Initialize()
{
}

void Drive::Execute()
{
  double forward = utils::Deadband(m_Forward());
  double turn = utils::Deadband(m_Turn());
  double slide = std::abs(m_Slide());
  forward *= slide;
  turn *= 0.5;
  std::cout << "forward: " << forward << " turn: " << turn << " slide: " << slide << std::endl;

  m_pDrivetrain->Drive(forward, turn);
}

void Drive::End(bool interrupted) {}

bool Drive::IsFinished()
{
  return false;
}
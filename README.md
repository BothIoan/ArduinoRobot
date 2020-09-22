# ArduinoRobot

## Description

__The code part of an arduino based game.__ Through the "Arduino Bluetooth RC Car" phone app, that provides an GUI complete with controllers, you send an bluetooth signal to your robot.
The signal can be interpreted as movement (wheels & DC motors) or shooting a laser (a laser diode attached to the robot). The robot also has a light sensor attached to it.

The game is intended for two or more robots. Each robot has 3 Life points. If your robot is struck by the laser of another robot, the sensor will register the hit and one life point will be lost.
After 3 hits your robot is out of the game. (The robot makes one specific sound for shooting, and another one for being hit).

///////////////////////////////////////////////////////////
//  DeviceManager.cpp
//  Implementation of the Class DeviceManager
//  Created on:      2016/06/15 8:26:02
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "DeviceManager.h"

namespace etrobo
{

/**
 * 初期化処理を実行する。
 */
DeviceManager::DeviceManager() :
        _communicator(new Communicator()),
        _body(new Body()),
        _sensor(new Sensor()),
        _leftMotor(new Motor(Motor::Type::LEFT)),
        _rightMotor(new Motor(Motor::Type::RIGHT)),
        _backMotor(new Motor(Motor::Type::BACK))
{
}

/**
 * 通信処理を実行するオブジェクトを返す。
 * @return デバイス制御オブジェクト
 */
Communicator* DeviceManager::getCommunicator()
{
  return _communicator.get();
}

/**
 * EV3本体を制御するオブジェクトを返す。
 * @return デバイス制御オブジェクト
 */
Body* DeviceManager::getBody()
{
  return _body.get();
}

/**
 * センサを制御するオブジェクトを返す。
 * @return デバイス制御オブジェクト
 */
Sensor* DeviceManager::getSensor()
{
  return _sensor.get();
}

/**
 * 左モーターを制御するオブジェクトを返す。
 * @return デバイス制御オブジェクト
 */
Motor* DeviceManager::getLeftMotor()
{
  return _leftMotor.get();
}

/**
 * 右モーターを制御するオブジェクトを返す。
 * @return デバイス制御オブジェクト
 */
Motor* DeviceManager::getRightMotor()
{
  return _rightMotor.get();
}

/**
 * 後ろモーターを制御するオブジェクトを返す。
 * @return デバイス制御オブジェクト
 */
Motor* DeviceManager::getBackMotor()
{
  return _backMotor.get();
}

} // namespace etrobo

///////////////////////////////////////////////////////////
//  DeviceManager.h
//  Implementation of the Class DeviceManager
//  Created on:      2016/06/15 8:26:02
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_86DEF00D_9F4F_47e5_8B41_141690016C44__INCLUDED_)
#define EA_86DEF00D_9F4F_47e5_8B41_141690016C44__INCLUDED_

#include "device/Communicator.h"
#include "device/Body.h"
#include "device/Sensor.h"
#include "device/Motor.h"
#include <memory>

namespace etrobo
{

/**
 * デバイスを管理するクラス。
 */
class DeviceManager
{
private:
  /**
   * 通信制御オブジェクト。
   */
  std::unique_ptr<Communicator> _communicator;

  /**
   * 本体制御オブジェクト。
   */
  std::unique_ptr<Body> _body;

  /**
   * センサ制御オブジェクト。
   */
  std::unique_ptr<Sensor> _sensor;

  /**
   * 左モーター制御オブジェクト。
   */
  std::unique_ptr<Motor> _leftMotor;

  /**
   * 右モーター制御オブジェクト。
   */
  std::unique_ptr<Motor> _rightMotor;

  /**
   * 後ろモーター制御オブジェクト。
   */
  std::unique_ptr<Motor> _backMotor;

public:
  /**
   * 初期化処理を実行する。
   */
  DeviceManager();

  /**
   * オブジェクトの複製を禁止。
   */
  DeviceManager(const DeviceManager& deviceManager) = delete;

  /**
   * オブジェクトの複製を禁止。
   */
  DeviceManager& operator=(const DeviceManager& deviceManager) = delete;

  /**
   * 終了う処理を実行する。
   */
  virtual ~DeviceManager() = default;

  /**
   * 通信処理を実行するオブジェクトを返す。
   * @return デバイス制御オブジェクト
   */
  Communicator* getCommunicator();

  /**
   * EV3本体を制御するオブジェクトを返す。
   * @return デバイス制御オブジェクト
   */
  Body* getBody();

  /**
   * センサを制御するオブジェクトを返す。
   * @return デバイス制御オブジェクト
   */
  Sensor* getSensor();

  /**
   * 左モーターを制御するオブジェクトを返す。
   * @return デバイス制御オブジェクト
   */
  Motor* getLeftMotor();

  /**
   * 右モーターを制御するオブジェクトを返す。
   * @return デバイス制御オブジェクト
   */
  Motor* getRightMotor();

  /**
   * 後ろモーターを制御するオブジェクトを返す。
   * @return デバイス制御オブジェクト
   */
  Motor* getBackMotor();

};

} // namespace etrobo

#endif // !defined(EA_86DEF00D_9F4F_47e5_8B41_141690016C44__INCLUDED_)

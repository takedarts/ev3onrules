///////////////////////////////////////////////////////////
//  Sensor.cpp
//  Implementation of the Class Sensor
//  Created on:      2016/06/22 10:56:03
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "Sensor.h"
#include "Config.h"
#include <ev3api.h>

namespace etrobo
{

/**
 * 初期化処理を実行する。
 */
Sensor::Sensor() :
    _cacheGyroRate(false),
    _cacheGyroAngle(false),
    _cacheLightAmbient(false),
    _cacheLightReflect(false),
    _cacheSonarDistance(false),
    _cacheTouchPressed(false),
    _gyroRate(0),
    _gyroAngle(0),
    _lightAmbient(0),
    _lightReflect(0),
    _sonarDistance(0),
    _touchPressed(false)
{
  // センサを接続
  ev3_sensor_config(GYRO_SENSOR_PORT, GYRO_SENSOR);
  ev3_sensor_config(LIGHT_SENSOR_PORT, COLOR_SENSOR);
  ev3_sensor_config(SONAR_SENSOR_PORT, ULTRASONIC_SENSOR);
  ev3_sensor_config(TOUCH_SENSOR_PORT, TOUCH_SENSOR);

  // 光センサを反射光観測モードに設定
  ev3_color_sensor_get_reflect(LIGHT_SENSOR_PORT);
}

/**
 * キャッシュとして保存されているデータを消去する。
 */
void Sensor::clearCache()
{
  _cacheGyroRate = false;
  _cacheGyroAngle = false;
  _cacheLightAmbient = false;
  _cacheLightReflect = false;
  _cacheSonarDistance = false;
  _cacheTouchPressed = false;
}

/**
 * ジャイロセンサで観測した角速度を返す。
 * @return 角速度(単位は度)
 */
int16_t Sensor::getGyroRate()
{
  if (!_cacheGyroRate) {
    _gyroRate = ev3_gyro_sensor_get_rate(GYRO_SENSOR_PORT);
    _cacheGyroRate = true;
  }

  return _gyroRate;
}

/**
 * ジャイロセンサで観測した角位置を返す。
 * @return 角位置(単位は度)
 */
int16_t Sensor::getGyroAngle()
{
  if (!_cacheGyroAngle) {
    _gyroAngle = ev3_gyro_sensor_get_angle(GYRO_SENSOR_PORT);
    _cacheGyroAngle = true;
  }

  return _gyroAngle;
}

/**
 * ジャイロセンサの設定値をリセットする。
 */
void Sensor::resetGyro()
{
  ev3_gyro_sensor_reset(GYRO_SENSOR_PORT);
  _cacheGyroAngle = false;
  _cacheGyroRate = false;
}

/**
 * 環境光の強さを返す。
 * @return 環境光の強さ
 */
uint8_t Sensor::getLightAmbient()
{
  if (!_cacheLightAmbient) {
    _lightAmbient = ev3_color_sensor_get_ambient(LIGHT_SENSOR_PORT);
    _cacheLightAmbient = true;
  }

  return _lightAmbient;
}

/**
 * LEDライトの反射光の強さを返す。
 * @return 反射光の強さ
 */
uint8_t Sensor::getLightReflect()
{
  if (!_cacheLightReflect) {
    _lightReflect = ev3_color_sensor_get_reflect(LIGHT_SENSOR_PORT);
    _cacheLightReflect = true;
  }

  return _lightReflect;
}

/**
 * 超音波センサで観測した距離の値を返す。
 * @return 観測した距離
 */
int16_t Sensor::getSonarDistance()
{
  if (!_cacheSonarDistance) {
    _sonarDistance = ev3_ultrasonic_sensor_get_distance(SONAR_SENSOR_PORT);
    _cacheSonarDistance = true;
  }

  return _sonarDistance;
}

/**
 * タッチセンサが押されていればtrueを返す。
 * @return タッチセンサが押されていればtrue
 */
bool Sensor::isTouchPressed()
{
  if (!_cacheTouchPressed) {
    if (ev3_touch_sensor_is_pressed(TOUCH_SENSOR_PORT)) {
      _touchPressed = true;
    }
    else {
      _touchPressed = false;
    }

    _cacheTouchPressed = true;
  }

  return _touchPressed;
}

} // namespace etrobo


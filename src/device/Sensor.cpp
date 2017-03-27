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
Sensor::Sensor()
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
 * ジャイロセンサで観測した角速度を返す。
 * @return 角速度(単位は度)
 */
int16_t Sensor::getGyroRate()
{
  return ev3_gyro_sensor_get_rate(GYRO_SENSOR_PORT);
}

/**
 * ジャイロセンサで観測した角位置を返す。
 * @return 角位置(単位は度)
 */
int16_t Sensor::getGyroAngle()
{
  return ev3_gyro_sensor_get_angle(GYRO_SENSOR_PORT);
}

/**
 * ジャイロセンサの設定値をリセットする。
 */
void Sensor::resetGyro()
{
  ev3_gyro_sensor_reset(GYRO_SENSOR_PORT);
}

/**
 * 環境光の強さを返す。
 * @return 環境光の強さ
 */
uint8_t Sensor::getLightAmbient()
{
  return ev3_color_sensor_get_ambient(LIGHT_SENSOR_PORT);
}

/**
 * LEDライトの反射光の強さを返す。
 * @return 反射光の強さ
 */
uint8_t Sensor::getLightReflect()
{
  return ev3_color_sensor_get_reflect(LIGHT_SENSOR_PORT);
}

/**
 * 超音波センサで観測した距離の値を返す。
 * @return 観測した距離
 */
int16_t Sensor::getSonarDistance()
{
  return ev3_ultrasonic_sensor_get_distance(SONAR_SENSOR_PORT);
}

/**
 * タッチセンサが押されていればtrueを返す。
 * @return タッチセンサが押されていればtrue
 */
bool Sensor::isTouchPressed()
{
  if (ev3_touch_sensor_is_pressed(TOUCH_SENSOR_PORT)) {
    return true;
  }
  else {
    return false;
  }
}

} // namespace etrobo


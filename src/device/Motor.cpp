///////////////////////////////////////////////////////////
//  Motor.cpp
//  Implementation of the Class Motor
//  Created on:      2016/06/15 11:34:37
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "Motor.h"
#include "Config.h"
#include <ev3api.h>

namespace etrobo
{

/**
 * 初期化処理を実行する。
 * @param type 接続位置
 */
Motor::Motor(Type type) :
    _cacheCount(false),
    _cachePower(false),
    _count(0),
    _power(0)
{
  if (type == Type::LEFT) {
    _port = LEFT_MOTOR_PORT;
  }
  else if (type == Type::RIGHT) {
    _port = RIGHT_MOTOR_PORT;
  }
  else {
    _port = BACK_MOTOR_PORT;
  }

  ev3_motor_config(_port, LARGE_MOTOR);
  ev3_motor_reset_counts(_port);
}

/**
 * 終了処理を実行する。
 */
Motor::~Motor()
{
  ev3_motor_set_power(_port, 0);
  ev3_motor_stop(_port, true);
}

/**
 * キャッシュとして保存されているデータを消去する。
 */
void Motor::clearCache()
{
  _cacheCount = false;
  _cachePower = false;
}

/**
 * モーターの回転角度の計測値を0に設定する。
 */
void Motor::resetCount()
{
  ev3_motor_reset_counts(_port);
  _cacheCount = false;
}

/**
 * モーターの回転角度の計測値を返す。
 * 反対方向に回転している場合は負の値を返す。
 * @return 回転角度(単位はdegree)
 */
int32_t Motor::getCount()
{
  if (!_cacheCount) {
    _count = ev3_motor_get_counts(_port);
    _cacheCount = true;
  }

  return _count;
}

/**
 * モーターの回転力を返す。
 * 逆回転している場合は負の数を返す。
 * @return 回転力
 */
int32_t Motor::getPower()
{
  if (!_cachePower) {
    _power = ev3_motor_get_power(_port);
    _cachePower = true;
  }

  return _power;
}

/**
 * モーターの回転力を設定する。
 * powerに負の値を設定すると逆方向に回転する。
 * brakeにtrueを設定すると回転を停止させようとする。
 * powerに0以外の値を設定した場合、brakeにtrueを設定しても無視する。
 * @param power 回転力(-100以上, 100以下)
 * @param brake 回転を停止させるならtrue
 */
void Motor::setPower(int32_t power, bool brake)
{
  if (power != 0) {
    ev3_motor_set_power(_port, power);
  }
  else {
    ev3_motor_set_power(_port, 0);
    ev3_motor_stop(_port, brake);
  }
}

/**
 * 指定された角度だけモーターを回転させる。
 * degreeで指定された角度までpowerの回転力で回転させる。
 * 反対方向に回転させる場合はdegreeに負の角度を設定する。
 * blockingにtrueを設定した場合、このメソッドの処理は回転が終了するまで終了しない。
 * @param degree 回転角度(単位はdegree)
 * @param power 回転力(0以上,100以下)
 * @param blocking 回転終了まで待機するならtrue
 */
void Motor::setRotate(int32_t degree, uint32_t power, bool blocking)
{
  ev3_motor_rotate(_port, degree, power, blocking);
}

} // namespace etrobo

///////////////////////////////////////////////////////////
//  Sensor.h
//  Implementation of the Class Sensor
//  Created on:      2016/06/22 10:56:02
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_67BA1150_0BD5_43ec_8ED2_E34FB8318563__INCLUDED_)
#define EA_67BA1150_0BD5_43ec_8ED2_E34FB8318563__INCLUDED_

#include <stdint.h>

namespace etrobo
{

/**
 * センサから観測データを取得するためのクラス。
 */
class Sensor
{
public:
  /**
   * 初期化処理を実行する。
   */
  Sensor();

  /**
   * オブジェクトの複製を禁止。
   */
  Sensor(const Sensor& sensor) = delete;

  /**
   * オブジェクトの複製を禁止。
   */
  Sensor& operator=(const Sensor& sensor) = delete;

  /**
   * 終了処理を実行
   */
  virtual ~Sensor() = default;

  /**
   * キャッシュとして保存されているデータを消去する。
   */
  void clearCache();

  /**
   * ジャイロセンサで観測した角速度を返す。
   * @return 角速度(単位は度)
   */
  int16_t getGyroRate();

  /**
   * ジャイロセンサで観測した角位置を返す。
   * @return 角位置(単位は度)
   */
  int16_t getGyroAngle();

  /**
 * ジャイロセンサの設定値をリセットする。
   */
  void resetGyro();

  /**
   * 光センサで観測した環境光の強さを返す。
   * @return 環境光の強さ
   */
  uint8_t getLightAmbient();

  /**
   * 光センサで観測したLEDライトの反射光の強さを返す。
   * @return 反射光の強さ
   */
  uint8_t getLightReflect();

  /**
   * 超音波センサで観測した距離の値を返す。
   * @return 観測した距離
   */
  int16_t getSonarDistance();

  /**
   * タッチセンサが押されていればtrueを返す。
   * @return タッチセンサが押されていればtrue
   */
  bool isTouchPressed();

private:
  /**
   * ジャイロセンサで観測した角速度のキャッシュされているならtrue。
   */
  bool _cacheGyroRate;

  /**
   * ジャイロセンサで観測した角度のキャッシュされているならtrue。
   */
  bool _cacheGyroAngle;

  /**
   * 光センサで観測した環境光の強さのキャッシュされているならtrue。
   */
  bool _cacheLightAmbient;

  /**
   * 光センサで観測したLEDライトの反射光の強さのキャッシュされているならtrue。
   */
  bool _cacheLightReflect;

  /**
   * 超音波センサで観測した距離のキャッシュされているならtrue。
   */
  bool _cacheSonarDistance;

  /**
   * タッチセンサの状態がキャッシュされているならtrue。
   */
  bool _cacheTouchPressed;

  /**
   * ジャイロセンサで観測した角速度。
   */
  int16_t _gyroRate;

  /**
   * ジャイロセンサで観測した角度。
   */
  int16_t _gyroAngle;

  /**
   * 光センサで観測した環境光の強さ。
   */
  uint8_t _lightAmbient;

  /**
   * 光センサで観測したLEDライトの反射光の強さ。
   */
  uint8_t _lightReflect;

  /**
   * 超音波センサで観測した距離。
   */
  int16_t _sonarDistance;

  /**
   * タッチセンサが押されていればtrue。
   */
  bool _touchPressed;
};

} // namespace etrobo

#endif // !defined(EA_67BA1150_0BD5_43ec_8ED2_E34FB8318563__INCLUDED_)

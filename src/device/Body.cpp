///////////////////////////////////////////////////////////
//  Body.cpp
//  Implementation of the Class Body
//  Created on:      2016/06/22 19:03:55
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "Body.h"
#include <sstream>

namespace etrobo
{

/**
 * 初期化処理を実行する。
 */
Body::Body() :
    _cacheBatteryVoltage(false),
    _cacheBatteryCurrent(false),
    _batteryVoltage(0),
    _batteryCurrent(0)
{
}

/**
 * キャッシュとして保存されているデータを消去する。
 */
void Body::clearCache()
{
  _cacheBatteryVoltage = false;
  _cacheBatteryCurrent = false;
}

/**
 * 現在のシステム時間を返す。
 * @return システム時間
 */
uint64_t Body::getTime()
{
  SYSTIM time;

  get_tim(&time);

  return (uint64_t) time;
}

/**
 * 性能評価用のシステム時間を返す。
 * @return システム時間
 */
uint64_t Body::getProcessTime()
{
  SYSUTM time;

  get_utm(&time);

  return (uint64_t) time;
}

/**
 * バッテリの電圧を返す。
 * @return 電圧値(単位:mV)
 */
uint32_t Body::getBatteryVoltage()
{
  if (!_cacheBatteryVoltage) {
    _batteryVoltage = ev3_battery_voltage_mV();
    _cacheBatteryVoltage = true;
  }

  return _batteryVoltage;
}

/**
 * バッテリの電流を返す。
 * @return 電流値(単位:mA)
 */
uint32_t Body::getBatteryCurrent()
{
  if (!_cacheBatteryCurrent) {
    _batteryCurrent = ev3_battery_current_mA();
    _cacheBatteryCurrent = true;
  }

  return _batteryCurrent;
}

/**
 * 本体の指定されたボタンが押されていればtrueを返す。
 * @param button 確認するボタン
 * @return 押されていればtrue
 */
bool Body::isButtonPressed(Button button)
{
  if (ev3_button_is_pressed((button_t) button)) {
    return true;
  }
  else {
    return false;
  }
}

/**
 * 本体のLEDライトの色を設定する。
 * @param color LEDライトの色
 */
void Body::setLedColor(Color color)
{
  ev3_led_set_color((ledcolor_t) color);
}

/**
 * 音を鳴らす。
 * @param frequency 周波数
 * @param duration 鳴らす時間(単位:ms)
 * @param volume 音の大きさ(0-100)
 */
void Body::playSpeakerTone(uint16_t frequency, int32_t duration, uint8_t volume)
{
  ev3_speaker_set_volume(volume);
  ev3_speaker_play_tone(frequency, duration);
}

/**
 * LCDに文字を出力する。
 * @param str 出力文字列
 * @param x 出力座標(X座標)
 * @param y 出力座標(Y座標)
 */
void Body::drawLcdString(const char* str, int32_t x, int32_t y)
{
  ev3_lcd_draw_string(str, x, y);
}

/**
 * LCDに整数を出力する。
 * @param val 出力する整数
 * @param num 出力する桁数
 * @param x 出力座標(X座標)
 * @param y 出力座標(Y座標)
 */
void Body::drawLcdInt(int64_t val, uint8_t num, int32_t x, int32_t y)
{
  std::ostringstream oss;

  oss.setf(std::ios::right);
  oss.fill(' ');
  oss.width(num);
  oss << val;

  ev3_lcd_draw_string(oss.str().data(), x, y);
}

} // namespace etrobo

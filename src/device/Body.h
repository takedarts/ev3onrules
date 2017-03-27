///////////////////////////////////////////////////////////
//  Body.h
//  Implementation of the Class Body
//  Created on:      2016/06/22 19:03:55
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_84872514_F709_450c_B5A5_25189EA1C425__INCLUDED_)
#define EA_84872514_F709_450c_B5A5_25189EA1C425__INCLUDED_

#include <ev3api.h>
#include <stdint.h>

namespace etrobo
{

/**
 * EV3の本体を制御するためのクラス。
 */
class Body
{
public:

  /**
   * 本体のボタンの設定値。
   */
  enum class Button
  {
    /**
     * 左ボタン。
     */
    LEFT = LEFT_BUTTON,

    /**
     * 右ボタン。
     */
    RIGHT = RIGHT_BUTTON,

    /**
     * 上ボタン。
     */
    UP = UP_BUTTON,

    /**
     * 下ボタン。
     */
    DOWN = DOWN_BUTTON,

    /**
     * 中央ボタン。
     */
    ENTER = ENTER_BUTTON,

    /**
     * 戻るボタン。
     */
    BACK = BACK_BUTTON,
  };

  /**
   * LEDの色の設定値。
   */
  enum class Color
  {
    /**
     * 消灯。
     */
    OFF = LED_OFF,

    /**
     * 赤色。
     */
    RED = LED_RED,

    /**
     * 緑色。
     */
    GREEN = LED_GREEN,

    /**
     * オレンジ色。
     */
    ORANGE = LED_ORANGE,
  };

public:
  /**
   * 初期化処理を実行する。
   */
  Body() = default;

  /**
   * オブジェクトの複製を禁止。
   */
  Body(const Body& body) = delete;

  /**
   * オブジェクトの複製を禁止。
   */
  Body& operator=(const Body& body) = delete;

  /**
   * 終了処理を実行する。
   */
  virtual ~Body() = default;

  /**
   * 現在のシステム時間を返す。
   * @return システム時間
   */
  uint64_t getTime();

  /**
   * 性能評価用のシステム時間を返す。
   * @return システム時間
   */
  uint64_t getProcessTime();

  /**
   * バッテリの電圧を返す。
   * @return 電圧値(単位:mV)
   */
  uint32_t getBatteryVoltage();

  /**
   * バッテリの電流を返す。
   * @return 電流値(単位:mA)
   */
  uint32_t getBatteryCurrent();

  /**
   * 本体の指定されたボタンが押されていればtrueを返す。
   * @param button 確認するボタン
   * @return 押されていればtrue
   */
  bool isButtonPressed(Button button);

  /**
   * 本体のLEDライトの色を設定する。
   * @param color LEDライトの色
   */
  void setLedColor(Color color);

  /**
   * 音を鳴らす。
   * @param frequency 周波数
   * @param duration 鳴らす時間(単位:ms)
   * @param volume 音の大きさ(0-100)
   */
  void playSpeakerTone(uint16_t frequency, int32_t duration, uint8_t volume);

  /**
   * LCDに文字を出力する。
   * @param str 出力文字列
   * @param x 出力座標(X座標)
   * @param y 出力座標(Y座標)
   */
  void drawLcdString(const char* str, int32_t x, int32_t y);

  /**
   * LCDに整数を出力する。
   * @param val 出力する整数
   * @param num 出力する桁数
   * @param x 出力座標(X座標)
   * @param y 出力座標(Y座標)
   */
  void drawLcdInt(int64_t val, uint8_t num, int32_t x, int32_t y);
};

} // namespace etrobo

#endif // !defined(EA_84872514_F709_450c_B5A5_25189EA1C425__INCLUDED_)

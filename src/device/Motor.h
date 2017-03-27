///////////////////////////////////////////////////////////
//  Motor.h
//  Implementation of the Class Motor
//  Created on:      2016/06/15 11:34:37
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_E3CFEAAD_C0A0_4255_931C_872DE9E30DCB__INCLUDED_)
#define EA_E3CFEAAD_C0A0_4255_931C_872DE9E30DCB__INCLUDED_

#include <stdint.h>
#include <ev3api.h>

namespace etrobo
{

/**
 * モーターの動作を制御するクラス。
 */
class Motor
{
public:
  /**
   * モーターの設置位置。
   */
  enum class Type
  {
    /**
     * 左モーター。
     */
    LEFT,

    /**
     * 右モーター。
     */
    RIGHT,

    /**
     * 後ろモーター。
     */
    BACK,
  };

private:
  /**
   * 接続ポート。
   */
  motor_port_t _port;

public:
  /**
   * 初期化処理を実行する。
   * @param type 接続位置
   */
  Motor(Type type);

  /**
   * オブジェクトの複製を禁止。
   */
  Motor(const Motor& motor) = delete;

  /**
   * オブジェクトの複製を禁止。
   */
  Motor& operator=(const Motor&) = delete;

  /**
   * 終了処理を実行する。
   */
  virtual ~Motor();

  /**
   * モーターの回転角度の計測値を0に設定する。
   */
  void resetCount();

  /**
   * モーターの回転角度の計測値を返す。
   * 反対方向に回転している場合は負の値を返す。
   * @return 回転角度(単位はdegree)
   */
  int32_t getCount();

  /**
   * モーターの回転力を返す。
   * 逆回転している場合は負の数を返す。
   * @return 回転力
   */
  int32_t getPower();

  /**
   * モーターの回転力を設定する。
   * powerに負の値を設定すると逆方向に回転する。
   * brakeにtrueを設定すると回転を停止させようとする。
   * powerに0以外の値を設定した場合、brakeにtrueを設定しても無視する。
   * @param power 回転力(-100以上, 100以下)
   * @param brake 回転を停止させるならtrue
   */
  void setPower(int32_t power, bool brake = false);

  /**
   * 指定された角度だけモーターを回転させる。
   * degreeで指定された角度までpowerの回転力で回転させる。
   * 反対方向に回転させる場合はdegreeに負の角度を設定する。
   * blockingにtrueを設定した場合、このメソッドの処理は回転が終了するまで終了しない。
   * @param degree 回転角度(単位はdegree)
   * @param power 回転力(0以上,100以下)
   * @param blocking 回転終了まで待機するならtrue
   */
  void setRotate(int32_t degree, uint32_t power, bool blocking = false);
};

} // namespace etrobo

#endif // !defined(EA_E3CFEAAD_C0A0_4255_931C_872DE9E30DCB__INCLUDED_)

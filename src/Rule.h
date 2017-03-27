///////////////////////////////////////////////////////////
//  Rule.h
//  Implementation of the Class Rule
//  Created on:      2016/06/15 8:27:17
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_CDF790FE_C9EC_4d14_887A_52D524418695__INCLUDED_)
#define EA_CDF790FE_C9EC_4d14_887A_52D524418695__INCLUDED_

#include "DeviceManager.h"
#include <stdint.h>
#include "FilterManager.h"

namespace etrobo
{

/**
 * アプリケーションの実行ルールクラス。
 * EV3WAYを動かすためにはこのクラスを継承したクラスを実装すること。
 */
class Rule
{
private:
  /**
   * このクラスのルール番号。
   */
  uint32_t _number;

public:
  /**
   * 初期化処理を実行する。
   * @param number このクラスのルール番号
   */
  Rule(uint32_t number);

  /**
   * 終了処理を実行する。
   */
  virtual ~Rule() = default;

  /**
   * このクラスのルール番号(ルールの識別番号)を返す。
   * @return ルール番号
   */
  uint32_t getNumber();

  /**
   * 開始処理を実行する。
   * 実行ルールが変更されたとき、runが実行されるまでに1回だけ実行される。
   * @param filterManager フィルタ管理オブジェクト
   * @param deviceManager デバイス管理オブジェクト
   */
  virtual void init(FilterManager* filterManager, DeviceManager* deviceManager) = 0;

  /**
   * 制御処理を実行する。
   * @param filterManager フィルタ管理オブジェクト
   * @param deviceManager デバイス管理オブジェクト
   */
  virtual void run(FilterManager* filterManager, DeviceManager* deviceManager) = 0;

  /**
   * このルールが実行可能状態であるかを確認する。
   * このルールを実行すべき状態の場合は自分のルール番号を返す。
   * 他のルールを実行すべき状態の場合はそのルールの番号を返す。
   * 実行すべきルールが存在しない場合(制御終了の場合)は-1を返す。
   * @param filterManager フィルタ管理オブジェクト
   * @param deviceManager デバイス管理オブジェクト
   * @return 次に実行するルール番号
   */
  virtual int32_t next(FilterManager* filterManager, DeviceManager* deviceManager) = 0;

};

} // namespace etrobo

#endif // !defined(EA_CDF790FE_C9EC_4d14_887A_52D524418695__INCLUDED_)

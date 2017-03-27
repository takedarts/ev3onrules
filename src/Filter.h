///////////////////////////////////////////////////////////
//  Data.h
//  Implementation of the Class Data
//  Created on:      2016/06/21 12:28:14
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_B0708EE7_4527_4854_9B50_55604588A374__INCLUDED_)
#define EA_B0708EE7_4527_4854_9B50_55604588A374__INCLUDED_

#include "FilterManager.h"
#include "DeviceManager.h"

namespace etrobo
{

/**
 * アプリケーションのフィルタクラス。
 * アプリケーション全体で必要な処理はこのクラスを継承したクラスを実装すること。
 */
class Filter
{
private:
  /**
   * フィルタ番号。
   */
  uint32_t _number;

public:
  /**
   * 初期化処理を実行する。
   * @param number フィルタ番号
   */
  Filter(uint32_t number);

  /**
   * 終了処理を実行する。
   */
  virtual ~Filter() = default;

  /**
   * このフィルタの識別番号を返す。
   * @return フィルタ番号
   */
  uint32_t getNumber();

  /**
   * このフィルタの処理を更新する。
   * @param filterManager フィルタ管理オブジェクト
   * @param deviceManager デバイス管理オブジェクト
   */
  virtual void run(FilterManager* filterManager, DeviceManager* deviceManager) = 0;

};

} // namespace etrobo

#endif // !defined(EA_B0708EE7_4527_4854_9B50_55604588A374__INCLUDED_)

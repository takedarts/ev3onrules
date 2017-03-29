///////////////////////////////////////////////////////////
//  Controller.h
//  Implementation of the Class Controller
//  Created on:      2016/06/15 8:25:03
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_FE6DA9D3_5A58_44ea_B1A2_FEA0E02FC754__INCLUDED_)
#define EA_FE6DA9D3_5A58_44ea_B1A2_FEA0E02FC754__INCLUDED_

#include "RuleManager.h"
#include "DeviceManager.h"
#include "Rule.h"
#include <memory>
#include "FilterManager.h"

namespace etrobo
{

/**
 * 全体の制御を実行するクラス。
 */
class Controller
{
private:
  /**
   * ルール管理オブジェクト。
   */
  std::unique_ptr<RuleManager> _ruleManager;

  /**
   * デバイス管理オブジェクト。
   */
  std::unique_ptr<DeviceManager> _deviceManager;

  /**
   * フィルタ管理オブジェクト。
   */
  std::unique_ptr<FilterManager> _filterManager;

  /**
   * 実行中のルールオブジェクト。
   */
  Rule* _rule;

  /**
   * 初期化を実行するならtrue。
   */
  bool _initialize;

public:
  /**
   * 初期化処理を実行する。
   */
  Controller();

  /**
   * オブジェクトの複製を禁止。
   */
  Controller(const Controller& controller) = delete;

  /**
   * オブジェクトの複製を禁止。
   */
  Controller& operator=(const Controller&) = delete;

  /**
   * 終了処理を実行する。
   */
  virtual ~Controller() = default;

  /**
   * 制御処理を実行する。
   * 制御を継続して実行する場合はtrueを返す。
   * @return 制御を継続する場合はtrue
   */
  bool run();

  /**
   * 通信処理を実行する。
   */
  void communicate();

  /**
   * 制御を終了する。
   */
  void close();
};

} // namespace etrobo

#endif // !defined(EA_FE6DA9D3_5A58_44ea_B1A2_FEA0E02FC754__INCLUDED_)

///////////////////////////////////////////////////////////
//  Controller.cpp
//  Implementation of the Class Controller
//  Created on:      2016/06/15 8:25:03
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "Controller.h"
#include "Exception.h"
#include "Config.h"

namespace etrobo
{

/**
 * 初期化処理を実行する。
 */
Controller::Controller() :
    _ruleManager(new RuleManager()),
    _deviceManager(new DeviceManager()),
    _filterManager(new FilterManager()),
    _rule(_ruleManager->getRule(0)),
    _initialize(true)
{
}

/**
 * 制御処理を実行する。
 * 制御を継続して実行する場合はtrueを返す。
 * @return 制御を継続する場合はtrue
 */
bool Controller::run()
{
  // 前回のキャッシュを消去
  _deviceManager->clearCache();

  // フィルタの処理を実行
  _filterManager->perform(_deviceManager.get());

  // 実行ルールを確認
  if (_rule == nullptr) {
    return false;
  }

  if (_initialize) {
    _rule->init(_filterManager.get(), _deviceManager.get());
    _initialize = false;
  }

  // 実行ルールを確認
  uint32_t number = _rule->next(_filterManager.get(), _deviceManager.get());

  // ルール変更なら、ルールオブジェクトを取り出す
  if (number != _rule->getNumber()) {
    _rule = _ruleManager->getRule(number);
    _initialize = true;
  }

  // 対象ルールが無いなら終了
  if (_rule == nullptr) {
    return false;
  }

  // ルール実行
  _rule->run(_filterManager.get(), _deviceManager.get());

  return true;
}

/**
 * 通信処理を実行する。
 */
void Controller::communicate()
{
  if (_deviceManager->getCommunicator()->isEnabled()) {
    _deviceManager->getCommunicator()->communicate();
  }
}

/**
 * 制御を終了する。
 */
void Controller::close()
{
  if (_deviceManager->getCommunicator()->isEnabled()) {
    _deviceManager->getCommunicator()->close();
  }
}

}
// namespace etrobo

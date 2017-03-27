///////////////////////////////////////////////////////////
//  RuleManager.cpp
//  Implementation of the Class RuleManager
//  Created on:      2016/06/15 8:27:26
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "RuleManager.h"
#include "Factory.h"

namespace etrobo
{

/**
 * 初期化処理を実行する。
 */
RuleManager::RuleManager()
{
  _ruleList = Factory::createRuleObjects();

  for (const auto rule : _ruleList) {
    _ruleMap[rule->getNumber()] = rule;
  }
}

/**
 * 終了処理を実行する。
 */
RuleManager::~RuleManager()
{
  for (const auto rule : _ruleList) {
    delete rule;
  }
}

/**
 * 指定された識別番号のルールオブジェクトを返す。
 * 対象となるルールが存在しない場合はnullptrを返す。
 * @param number ルール番号
 * @return ルールオブジェクト
 */
Rule* RuleManager::getRule(uint32_t number)
{
  auto it = _ruleMap.find(number);

  if(it != _ruleMap.end()){
    return it->second;
  }
  else{
    return nullptr;
  }
}

} // namespace etrobo

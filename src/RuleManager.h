///////////////////////////////////////////////////////////
//  RuleManager.h
//  Implementation of the Class RuleManager
//  Created on:      2016/06/15 8:27:26
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_06C96522_8D3E_4426_9EF6_2143729633E0__INCLUDED_)
#define EA_06C96522_8D3E_4426_9EF6_2143729633E0__INCLUDED_

#include "Rule.h"
#include <stdint.h>
#include <vector>
#include <map>

namespace etrobo
{

/**
 * ルール管理オブジェクト。
 */
class RuleManager
{
private:
  /**
   * ルールを管理するためのリストオブジェクト。
   */
  std::vector<Rule*> _ruleList;

  /**
   * ルールを検索するためのマップオブジェクト。
   */
  std::map<int, Rule*> _ruleMap;

public:
  /**
   * 初期化処理を実行する。
   */
  RuleManager();

  /**
   * オブジェクトの複製を禁止。
   */
  RuleManager(const RuleManager& ruleManager) = delete;

  /**
   * オブジェクトの複製を禁止。
   */
  RuleManager& operator=(const RuleManager& ruleManager) = delete;

  /**
   * 終了処理を実行する。
   */
  virtual ~RuleManager();

  /**
   * 指定された識別番号のルールオブジェクトを返す。
   * 対象となるルールが存在しない場合はnullptrを返す。
   * @param number ルール番号
   * @return ルールオブジェクト
   */
  Rule* getRule(uint32_t number);

};

} // namespace etrobo

#endif // !defined(EA_06C96522_8D3E_4426_9EF6_2143729633E0__INCLUDED_)

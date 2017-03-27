///////////////////////////////////////////////////////////
//  Factory.h
//  Implementation of the Class Factory
//  Created on:      2016/06/22 10:57:33
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_9F73DB96_60B4_4638_A315_56DC3CD3BC88__INCLUDED_)
#define EA_9F73DB96_60B4_4638_A315_56DC3CD3BC88__INCLUDED_

#include <vector>

#include "Filter.h"
#include "Rule.h"

namespace etrobo
{

/**
 * ルールオブジェクトとデータオブジェクトを生成するクラス。
 * 実装はビルド時にスクリプトで自動生成される。
 */
class Factory
{
public:
  /**
   * ルールオブジェクトの一覧を作成する。
   * @return ルールオブジェクトの一覧
   */
  static std::vector<Rule*> createRuleObjects();

  /**
   * フィルタオブジェクトの一覧を作成する。
   * @return フィルタオブジェクトの一覧
   */
  static std::vector<Filter*> createFilterObjects();

private:
  /**
   * 初期化処理を行う。
   */
  Factory() = default;

  /**
   * 終了処理を行う。
   */
  virtual ~Factory() = default;

};

} // namespace etrobo

#endif // !defined(EA_9F73DB96_60B4_4638_A315_56DC3CD3BC88__INCLUDED_)

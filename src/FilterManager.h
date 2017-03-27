///////////////////////////////////////////////////////////
//  FilterManager.h
//  Implementation of the Class FilterManager
//  Created on:      2016/06/21 12:28:03
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_42E4CD92_FAED_4c45_BC26_D15DE5784862__INCLUDED_)
#define EA_42E4CD92_FAED_4c45_BC26_D15DE5784862__INCLUDED_

#include "DeviceManager.h"
#include <vector>
#include <map>

namespace etrobo
{

// プロトタイプ宣言(循環インクルードへの対策)
class Filter;

/**
 * フィルタを管理するクラス。
 */
class FilterManager
{
private:
  /**
   * フィルタを管理するためのリストオブジェクト。
   */
  std::vector<Filter*> _filterList;

  /**
   * フィルタを検索するためのマップオブジェクト。
   */
  std::map<int, Filter*> _filterMap;

public:
  /**
   * 初期化処理を実行する。
   */
  FilterManager();

  /**
   * オブジェクトの複製を禁止。
   */
  FilterManager(const FilterManager& filterManager) = delete;

  /**
   * オブジェクトの複製を禁止。
   */
  FilterManager& operator=(const FilterManager& filterManager) = delete;

  /**
   * 終了処理を実行する。
   */
  virtual ~FilterManager();

  /**
   * 指定された識別番号のフィルタを返す。
   * 識別番号のフィルタが存在しない場合はnullptrを返す。
   * @param number フィルタ番号
   * @return フィルタオブジェクト
   */
  Filter* getFilter(uint32_t number);

  /**
   * すべてのフィルタの処理を実行する。
   * @param deviceManager デバイス管理オブジェクト
   */
  void perform(DeviceManager* deviceManager);
};

} // namespace etrobo

#endif // !defined(EA_42E4CD92_FAED_4c45_BC26_D15DE5784862__INCLUDED_)

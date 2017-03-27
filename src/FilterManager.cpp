///////////////////////////////////////////////////////////
//  DataManager.cpp
//  Implementation of the Class DataManager
//  Created on:      2016/06/21 12:28:04
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "Factory.h"
#include "FilterManager.h"

namespace etrobo
{

/**
 * 初期化処理を実行する。
 */
FilterManager::FilterManager()
{
  _filterList = Factory::createFilterObjects();

  for (const auto data : _filterList) {
    _filterMap[data->getNumber()] = data;
  }
}

/**
 * 終了処理を実行する。
 */
FilterManager::~FilterManager()
{
  for (const auto data : _filterList) {
    delete data;
  }
}

/**
 * 指定された識別番号のフィルタを返す。
 * 識別番号のフィルタが存在しない場合はnullptrを返す。
 * @param number フィルタ番号
 * @return フィルタオブジェクト
 */
Filter* FilterManager::getFilter(uint32_t number)
{
  auto it = _filterMap.find(number);

  if (it != _filterMap.end()) {
    return it->second;
  }
  else {
    return nullptr;
  }
}

/**
 * すべてのフィルタの処理を実行する。
 * @param deviceManager デバイス管理オブジェクト
 */
void FilterManager::perform(DeviceManager* deviceManager)
{
  for (const auto filter : _filterList) {
    filter->run(this, deviceManager);
  }
}

} // namespace etrobo

///////////////////////////////////////////////////////////
//  Data.cpp
//  Implementation of the Class Data
//  Created on:      2016/06/21 12:28:15
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "Filter.h"

namespace etrobo
{

/**
 * 初期化処理を実行する。
 * @param number フィルタ番号
 */
Filter::Filter(uint32_t number) :
    _number(number)
{
}

/**
 * このフィルタの識別番号を返す。
 * @return フィルタ番号
 */
uint32_t Filter::getNumber()
{
  return _number;
}

} // namespace etrobo

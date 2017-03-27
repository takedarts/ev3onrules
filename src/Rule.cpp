///////////////////////////////////////////////////////////
//  Rule.cpp
//  Implementation of the Class Rule
//  Created on:      2016/06/15 8:27:17
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "Rule.h"

namespace etrobo
{

/**
 * 初期化処理を実行する。
 * @param number このクラスのルール番号
 */
Rule::Rule(uint32_t number) :
    _number(number)
{
}

/**
 * このクラスのルール番号(ルールの識別番号)を返す。
 * @return ルール番号
 */
uint32_t Rule::getNumber()
{
  return _number;
}

} // namespace etrobo

///////////////////////////////////////////////////////////
//  Exception.cpp
//  Implementation of the Class Exception
//  Created on:      2016/06/21 23:03:31
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "Exception.h"

namespace etrobo
{

/**
 * 初期化処理を実行する。
 * @param what 例外の原因
 */
Exception::Exception(const char* what) :
    _what(what)
{
}

/**
 * 初期化処理を実行する。
 * @param what 例外の原因
 */
Exception::Exception(const std::string what) :
    _what(what)
{
}

/**
 * 例外の原因を返す。
 * @return 例外の原因
 */
const char* Exception::what() const throw ()
{
  return _what.data();
}

} // namespace etrobo

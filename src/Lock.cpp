///////////////////////////////////////////////////////////
//  Lock.cpp
//  Implementation of the Class Lock
//  Created on:      2016/06/23 18:53:04
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "Lock.h"
#include "Exception.h"
#include <ev3api.h>
#include "module_cfg.h"

namespace etrobo
{

/**
 * タスクの切り替えを禁止する。
 */
Lock::Lock()
{
  if (loc_mtx(MTX) != E_OK) {
    throw Exception("failed at loc_mtx(MTX)");
  }
}

/**
 * タスクの切り替え禁止を終了する。
 */
Lock::~Lock()
{
  if (unl_mtx(MTX) != E_OK) {
    throw Exception("failed at unl_mtx(MTX)");
  }
}

}
// namespace etrobo


///////////////////////////////////////////////////////////
//  Lock.h
//  Implementation of the Class Lock
//  Created on:      2016/06/23 18:53:04
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_9A58E213_5B1A_4ff5_B093_858EA8A1F3F1__INCLUDED_)
#define EA_9A58E213_5B1A_4ff5_B093_858EA8A1F3F1__INCLUDED_

namespace etrobo
{

/**
 * 排他制御を実行するクラス。
 * このクラスのオブジェクトを生成するとタスクの切り替えを禁止する。
 */
class Lock
{
public:
  /**
   * タスクの切り替えを禁止する。
   */
  Lock();

  /**
   * タスクの切り替え禁止を終了する。
   */
  virtual ~Lock();

};

} // namespace etrobo

#endif // !defined(EA_9A58E213_5B1A_4ff5_B093_858EA8A1F3F1__INCLUDED_)

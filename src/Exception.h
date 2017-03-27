///////////////////////////////////////////////////////////
//  Exception.h
//  Implementation of the Class Exception
//  Created on:      2016/06/21 23:03:31
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_A064FA66_7A4E_4e2f_993A_92AD8198FA25__INCLUDED_)
#define EA_A064FA66_7A4E_4e2f_993A_92AD8198FA25__INCLUDED_

#include <string>
#include <exception>

namespace etrobo
{

/**
 * 例外クラス。
 */
class Exception: public std::exception
{
private:
  /**
   * 例外の原因。
   */
  std::string _what;

public:
  /**
   * 初期化処理を実行する。
   * @param what 例外の原因
   */
  Exception(const char* what);

  /**
   * 初期化処理を実行する。
   * @param what 例外の原因
   */
  Exception(const std::string what);

  /**
   * 終了処理を実行する。
   */
  virtual ~Exception() = default;

  /**
   * 例外の原因を返す。
   * @return 例外の原因
   */
  virtual const char* what() const throw () override;
};

} // namespace etrobo

#endif // !defined(EA_A064FA66_7A4E_4e2f_993A_92AD8198FA25__INCLUDED_)

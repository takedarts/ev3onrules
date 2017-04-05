///////////////////////////////////////////////////////////
//  Communicator.h
//  Implementation of the Class Communicator
//  Created on:      2016/06/21 18:17:58
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_D86AD588_078B_4cdf_A560_3777A7302509__INCLUDED_)
#define EA_D86AD588_078B_4cdf_A560_3777A7302509__INCLUDED_

#include "ByteBuffer.h"
#include <stdint.h>
#include <memory>

namespace etrobo
{

/**
 * 通信を行うためのクラス。
 */
class Communicator
{
private:
  /**
   * 受信データを管理するバッファ。
   */
  std::unique_ptr<ByteBuffer> _buffer;

public:
  /**
   * 初期化処理を実行する。
   */
  Communicator();

  /**
   * オブジェクトの複製を禁止。
   */
  Communicator(const Communicator& communicator) = delete;

  /**
   * オブジェクトの複製を禁止。
   */
  Communicator& operator=(const Communicator& communicator) = delete;

  /**
   * 終了処理を実行する。
   */
  virtual ~Communicator();

  /**
   * 通信機能が有効になっているならtrueを返す。
   * @return 通信可能ならtrue
   */
  bool isEnabled();

  /**
   * 通信が行われているならばtrueを返す。
   * @return 通信中ならばtrue
   */
  bool isConnected();

  /**
   * 通信処理を終了する。
   */
  void close();

  /**
   * 受信データを取得する。
   * @param data 受信データを設定するバッファ
   * @param length バッファの長さ
   * @return 受信したデータの長さ
   */
  int32_t read(char* data, uint32_t length);

  /**
   * データを送信する。
   * @param data 送信データ
   * @param length 送信データの長さ
   * @return 送信したデータの長さ
   */
  int32_t write(const char* data, uint32_t length);

  /**
   * 通信処理を実行する。
   */
  void communicate();

private:
  /**
   * 通信処理が終了していればtrue。
   */
  bool _closed;
};

} // namespace etrobo

#endif // !defined(EA_D86AD588_078B_4cdf_A560_3777A7302509__INCLUDED_)

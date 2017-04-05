///////////////////////////////////////////////////////////
//  Communicator.cpp
//  Implementation of the Class Communicator
//  Created on:      2016/06/21 18:17:58
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "Communicator.h"
#include "Bluetooth.h"
#include "Config.h"
#include <ev3api.h>

namespace etrobo
{

/**
 * 初期化処理を実行する。
 */
Communicator::Communicator() :
    _buffer(new ByteBuffer(BUFFER_SIZE)),
    _closed(false)
{
}

/**
 * 終了処理を実行する。
 */
Communicator::~Communicator()
{
  close();
}

/**
 * 通信機能が有効になっているならtrueを返す。
 * @return 通信可能ならtrue
 */
bool Communicator::isEnabled()
{
  return bluetooth_is_enabled();
}

/**
 * 通信が行われているならばtrueを返す。
 * @return 通信中ならばtrue
 */
bool Communicator::isConnected()
{
  return bluetooth_is_connected();
}

/**
 * 通信処理を終了する。
 */
void Communicator::close()
{
  _closed = true;

  if (bluetooth_is_connected()) {
    bluetooth_close();
  }
}

/**
 * 受信データを取得する。
 * @param data 受信データを設定するバッファ
 * @param length バッファの長さ
 * @return 受信したデータの長さ
 */
int32_t Communicator::read(char* data, uint32_t length)
{
  return _buffer->read(data, length);
}

/**
 * データを送信する。
 * @param data 送信データ
 * @param length 送信データの長さ
 * @return 送信したデータの長さ
 */
int32_t Communicator::write(const char* data, uint32_t length)
{
  if (bluetooth_is_connected()) {
    return bluetooth_send(data, length);
  }
  else {
    return 0;
  }
}

/**
 * 通信処理を実行する。
 */
void Communicator::communicate()
{
  while (!_closed) {
    // 接続確認
    if (!bluetooth_is_connected()) {
      tslp_tsk(100);
      continue;
    }

    // 受信
    char datum;
    uint32_t size = bluetooth_receive(&datum, 1);

    // 通信切断
    if (size == 0) {
      tslp_tsk(100);
      continue;
    }

    // バッファに登録
    _buffer->write(&datum, 1);
  }
}

} // namespace etrobo

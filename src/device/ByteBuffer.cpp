///////////////////////////////////////////////////////////
//  ByteBuffer.cpp
//  Implementation of the Class ByteBuffer
//  Created on:      2016/06/23 12:25:08
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#include "ByteBuffer.h"
#include "../Lock.h"
#include <algorithm>
#include <memory>
#include <string.h>

namespace etrobo
{

/**
 * 初期化処理を実行する。
 * @param size バッファの大きさ
 */
ByteBuffer::ByteBuffer(uint32_t size) :
        _buffer(new uint8_t[size]),
        _size(size),
        _offset(0),
        _length(0)
{
}

/**
 * データを読み込む。
 * @param data 読み込んだデータを設定するバッファ
 * @param length バッファの長さ
 * @return 読み込んだデータの長さ
 */
int32_t ByteBuffer::read(uint8_t* data, uint32_t length)
{
  // データの長さを確認
  length = std::min(length, _length);

  // 値を保存(戻り値で使う)
  uint32_t ret = length;

  // 読み込み開始
  std::unique_ptr<Lock> lock(new Lock());

  // 読み込み(コピー動作は最大2回必要)
  while (length > 0) {
    // 読み込む長さを計算
    uint32_t len = std::min(length, _size - _offset);

    // 読み込み
    memcpy(data, _buffer.get() + _offset, sizeof(uint8_t) * len);

    // 読み込み位置を更新
    _offset += len;

    if (_offset >= _size) {
      _offset -= _size;
    }

    // データの長さを更新
    _length -= len;

    // 読み込みバッファを更新
    length -= len;
    data += len;
  }

  return ret;
}

/**
 * データを書き込む。
 * @param data 書き込むデータが設定されているバッファ
 * @param length 書き込むデータの長さ
 * @return 書き込まれたデータの長さ
 */
int32_t ByteBuffer::write(const uint8_t* data, uint32_t length)
{
  // データの長さを確認
  length = std::min(length, _size - _length);

  // 値を保存(戻り値で使う)
  uint32_t ret = length;

  // 書き込み開始
  std::unique_ptr<Lock> lock(new Lock());

  // 書き込み(コピー動作は最大2回必要)
  while (length > 0) {
    // 書き込み位置を計算
    uint32_t off = _offset + _length;

    if (off >= _size) {
      off -= _size;
    }

    // 書き込む長さを計算
    uint32_t len = std::min(length, _size - off);

    // 書き込み
    memcpy(_buffer.get() + off, data, sizeof(uint8_t) * len);

    // データの長さを更新
    _length += len;

    // 書き込みデータを更新
    length -= len;
    data += len;
  }

  return ret;
}

} // namespace etrobo

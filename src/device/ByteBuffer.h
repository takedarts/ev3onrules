///////////////////////////////////////////////////////////
//  ByteBuffer.h
//  Implementation of the Class ByteBuffer
//  Created on:      2016/06/23 12:25:08
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////

#if !defined(EA_296DD358_6EA4_4bad_9C0B_18832A732547__INCLUDED_)
#define EA_296DD358_6EA4_4bad_9C0B_18832A732547__INCLUDED_

#include <stdint.h>
#include <memory>

namespace etrobo
{

/**
 * タスク間でデータのやり取りを行うためのバッファクラス。
 */
class ByteBuffer
{
private:
  /**
   * データを格納するバッファ。
   */
  std::unique_ptr<char[]> _buffer;

  /**
   * バッファの大きさ。
   */
  uint32_t _size;

  /**
   * バッファの先頭位置。
   */
  uint32_t _offset;

  /**
   * バッファに格納されているデータの長さ。
   */
  uint32_t _length;

public:
  /**
   * 初期化処理を実行する。
  * @param size バッファの大きさ
   */
  ByteBuffer(uint32_t size);

  /**
   * オブジェクトの複製を禁止。
   */
  ByteBuffer(const ByteBuffer& byteBuffer) = delete;

  /**
   * オブジェクトの複製を禁止。
   */
  ByteBuffer operator=(const ByteBuffer& byteBuffer) = delete;

  /**
   * 終了処理を実行する。
   */
  virtual ~ByteBuffer() = default;

  /**
   * データを読み込む。
   * @param data 読み込んだデータを設定するバッファ
   * @param length バッファの長さ
   * @return 読み込んだデータの長さ
   */
  int32_t read(char* data, uint32_t length);

  /**
   * データを書き込む。
   * @param data 書き込むデータが設定されているバッファ
   * @param length 書き込むデータの長さ
   * @return 書き込まれたデータの長さ
   */
  int32_t write(const char* data, uint32_t length);

};

} // namespace etrobo

#endif // !defined(EA_296DD358_6EA4_4bad_9C0B_18832A732547__INCLUDED_)

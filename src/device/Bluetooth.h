///////////////////////////////////////////////////////////
//  Bluetooth.h
//  Implementation of Bluetooth Functions
//  Created on:      2016/06/23
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////
#ifndef DEVICE_BLUETOOTH_H_
#define DEVICE_BLUETOOTH_H_

#include <stdint.h>

namespace etrobo
{

/**
 * Bluetoothによる通信が有効になっている場合trueを返す。
 * @return Bluetooth通信が有効であればtrue
 */
bool bluetooth_is_enabled();

/**
 * Bluetoothの通信を終了する。
 */
void bluetooth_close();

/**
 * Bluetoothが通信中であればtureを返す。
 * @return 通信中であればtrue
 */
bool bluetooth_is_connected();

/**
 * Bluetoothによって受信したデータを取得する。
 * 通信が終了している場合は-1を返す。
 * @param data 受信データを設定するバッファ
 * @param length バッファの長さ
 * @return バッファに設定されたデータの長さ
 */
uint32_t bluetooth_receive(uint8_t* data, uint32_t length);

/**
 * Bluetoothによって指定されたデータを送信する。
 * @param data 送信データが設定されたバッファ
 * @param length 送信データの長さ
 * @return 送信されたデータの長さ
 */
uint32_t bluetooth_send(const uint8_t* data, uint32_t length);

} // namespace etrobo

#endif /* DEVICE_BLUETOOTH_H_ */

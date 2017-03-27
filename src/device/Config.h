///////////////////////////////////////////////////////////
// Config.h
//  Configuration file
//  Created on:      2016/06/22
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////
#ifndef DEVICE_CONFIG_H_
#define DEVICE_CONFIG_H_

// 通信処理を行うなら1に設定
#define BLUETOOH_ENABLE     1

// 通信処理で使用するバッファの大きさ
#define BUFFER_SIZE         2048

// モーターの接続ポート
#define LEFT_MOTOR_PORT     EV3_PORT_C
#define RIGHT_MOTOR_PORT    EV3_PORT_B
#define BACK_MOTOR_PORT     EV3_PORT_A

// センサの接続ポート
#define GYRO_SENSOR_PORT    EV3_PORT_4
#define LIGHT_SENSOR_PORT   EV3_PORT_3
#define SONAR_SENSOR_PORT   EV3_PORT_2
#define TOUCH_SENSOR_PORT   EV3_PORT_1

#endif /* DEVICE_CONFIG_H_ */

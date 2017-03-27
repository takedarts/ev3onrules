///////////////////////////////////////////////////////////
// app.h
//  Implementation of Bootstrap
//  Created on:      2016/06/20
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////
#ifndef APP_H_
#define APP_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 起動タスク。
 */
void boot_task(intptr_t unused);

/**
 * 制御タスク。
 */
void run_task(intptr_t unused);

/**
 * 通信タスク。
 */
void com_task(intptr_t unused);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APP_H_ */

///////////////////////////////////////////////////////////
// app.h
//  Implementation of Bootstrap
//  Created on:      2016/06/20
//  Original author: Atsushi TAKEDA
///////////////////////////////////////////////////////////
#include "app.h"
#include "Controller.h"
#include "Exception.h"
#include "Config.h"
#include <ev3api.h>
#include <stdio.h>

#include "module_cfg.h"

// リンクエラーへの一時的対策
// gnuarmのlibstdc++が__dso_handleを必要としているため
void* __dso_handle;

#ifdef __cplusplus
extern "C"
{
#endif

using namespace etrobo;

/**
 * 実行オブジェクト。
 */
static Controller* controller = nullptr;

/**
 * 制御タスクと通信タスクを開始する。
 */
static void start()
{
  // 制御タスクを起動
  if (act_tsk(RUN_TASK) != E_OK) {
    throw Exception("failed at act_tsk(RUN_TASK)");
  }

  // 通信タスクを起動
  if (act_tsk(COM_TASK) != E_OK) {
    throw Exception("failed at act_tsk(COM_TASK)");
  }
}

/**
 * 制御タスクと通信タスクが終了するまで待機する。
 */
static void join()
{
  FLGPTN flag;

  if (wai_flg(FLG, 0x11, TWF_ANDW, &flag) != E_OK) {
    throw Exception("wai_flg(MAIN_FLG, 0x11)");
  }
}

/**
 * 起動処理を実行する。
 */
void boot()
{
  // LEDで状態を表示
  ev3_led_set_color(LED_RED);

  // オブジェクトを生成
  std::unique_ptr<Controller> ptr(new Controller());

  controller = ptr.get();

  // 動作開始
  start();

  // 動作中
  ev3_led_set_color(LED_GREEN);

  // 待機
  join();

  // 終了
  ev3_led_set_color(LED_RED);
}

/**
 * 制御処理を実行する。
 */
void run()
{
  // 制御処理を実行(4ms間隔で実行)
  SYSTIM last_time;
  bool time_over = false;

  get_tim(&last_time);

  while (true) {
    // 制御実行
    if (!controller->run()) {
      break;
    }

    // 時間を計測
    SYSTIM curr_time;

    get_tim(&curr_time);

    // 経過時間から待機時間を計算
    // 待機時間が1以上(正常動作)の場合はLEDを緑に設定
    // 待機時間が0以下(計算時間超過)の場合はLEDをオレンジに設定
    SYSTIM elapsed_time = curr_time - last_time;

    if (elapsed_time < INTERVAL) {
      tslp_tsk(INTERVAL - elapsed_time);
      last_time = last_time + INTERVAL;

      if (time_over) {
        ev3_led_set_color(LED_GREEN);
        time_over = false;
      }
    }
    else {
      last_time = curr_time;

      if (!time_over) {
        ev3_led_set_color(LED_ORANGE);
        time_over = true;
      }
    }
  }

  // 終了フラグをセット
  if (set_flg(FLG, 0x01) != E_OK) {
    throw Exception("failed at set_flg(MAIN_FLG, 0x01)");
  }

  // 制御を終了
  controller->close();

  printf("end control\n");
}

/**
 * 通信処理を実行する。
 */
void com()
{
  // 通信処理を実行
  controller->communicate();

  // 終了フラグをセット
  if (set_flg(FLG, 0x10) != E_OK) {
    throw Exception("failed at set_flg(MAIN_FLG, 0x10)");
  }

  printf("end communication\n");
}

/**
 * 起動タスク。
 */
void boot_task(intptr_t unused)
{
  // 起動処理を実行
  try {
    boot();
  } catch (const Exception& e) {
    printf("error(main_task): %s\n", e.what());
  } catch (...) {
    printf("error(main_task): unknown\n");
  }

  // タスク終了
  ext_tsk();
}

/**
 * 制御タスク。
 */
void run_task(intptr_t unused)
{
  // 制御処理を実行
  try {
    run();
  } catch (const Exception& e) {
    printf("error(run_task): %s\n", e.what());
  } catch (...) {
    printf("error(run_task): unknown");
  }

  // タスク終了
  ext_tsk();
}

/**
 * 通信タスク。
 */
void com_task(intptr_t unused)
{
  // 通信処理を実行
  try {
    com();
  } catch (const Exception& e) {
    printf("error(com_task): %s\n", e.what());
  } catch (...) {
    printf("error(com_task): unknown");
  }

  // タスク終了
  ext_tsk();
}

#ifdef __cplusplus
} /* extern "C" */
#endif

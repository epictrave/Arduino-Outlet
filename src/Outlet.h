/**
 * @file Outlet.h
 * @brief 콘센트 제어
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */

#ifndef OUTLET_H_
#define OUTLET_H_

#include <Arduino.h>
#include <config.h>

// Debug
#ifndef OUTLET_DEBUG_PORT
#define OUTLET_DEBUG_PORT Serial
#endif

#ifdef OUTLET_DEBUG
#define print(...) OUTLET_DEBUG_PORT.print(__VA_ARGS__)
#define printf(...) OUTLET_DEBUG_PORT.printf(__VA_ARGS__)
#define println(...) OUTLET_DEBUG_PORT.println(__VA_ARGS__)

#else
#define print(...)
#define printf(...)
#define println(...)
#endif

/**
 * @brief 콘센트 제어
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
/**
 * @struct OutletInfo
 * @brief 콘센트 정보
 * @date 2019-10-24
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
typedef struct OutletInfo {
  /** 핀 번호 */
  uint8_t pin;
  /** 콘센트 상태 */
  bool state;
  /** 이전 콘센트 상태 */
  bool last_state;
} OutletInfo;

class Outlet {
 private:
  // 콘센트 상태 변화 flag
  bool _is_outlet_changed = false;
  // 콘센트 상태
  OutletInfo *_outlets;

  // outlet number;
  size_t _outlet_num;

  void setOultet(int number, bool is_on);
  void setOutletByPin(int pin, bool is_on);

 public:
  Outlet(int outlet_pins[], size_t outlet_num);
  ~Outlet(void);

  void rollbackOutletState(void);
  void saveOutletState(void);

  void setOutletState(int number, bool is_on);
  void syncOutlet(void);

  bool getCurrentOutletState(int idx);
  bool getLastOutletState(int idx);

  void turnOnOutlet(int idx);
  void turnOffOutlet(int idx);
  void setOutletChangeFlag(bool is_outlet_changed);
  bool getOutletChangeFlag(void);
};

#endif /** OUTLET_H_ **/
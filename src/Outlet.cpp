/**
 * @file Outlet.cpp
 * @brief 콘센트 제어
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */

#include <Outlet.h>

/**
 * @fn Outlet:Outlet(int outlet_pins[], size_t outlet_num)
 * @brief 콘센트 제어 생성자
 * @param outlet_pins 콘센트 핀
 * @param outlet_num 콘센트 수
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
Outlet::Outlet(int outlet_pins[], size_t outlet_num) {
  _outlet_num = outlet_num;
  _outlets = (OutletInfo *)malloc(sizeof(OutletInfo) * _outlet_num);
  // 콘센트 IO pins 초기화
  for (int i = 0; i < _outlet_num; i++) {
    _outlets[i].pin = outlet_pins[i];
    _outlets[i].state = _outlets[i].last_state = false;
    pinMode(_outlets[i].pin, OUTPUT);
    digitalWrite(_outlets[i].pin, LOW);
  }
}
/**
 * @fn Outlet::~Outlet(void)
 * @brief 콘센트 제어 소멸자
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
Outlet::~Outlet(void) { free(_outlets); }

/**
 * @fn void Outlet::rollbackOutletState(void)
 * @brief 콘센트 이전 상태로 복구
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Outlet::rollbackOutletState(void) {
  for (int i = 0; i < _outlet_num; i++) {
    _outlets[i].state = _outlets[i].last_state;
  }
}

/**
 * @fn void Outlet::saveOutletState(void)
 * @brief 이전 콘센트 상태를 현재 콘센트 상태로 업데이트로 저장
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Outlet::saveOutletState(void) {
  for (int i = 0; i < _outlet_num; i++) {
    _outlets[i].last_state = _outlets[i].state;
  }
}

/**
 * @fn void Outlet::setOutletState(int idx, bool is_on)
 * @brief 현재 콘센트 상태 설정
 * @param idx 설정할 콘센트 번호
 * @param is_on 설정할 콘센트 전원 상태
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Outlet::setOutletState(int idx, bool is_on) {
  _outlets[idx].state = is_on;
}

/**
 * @fn bool Outlet::getCurrentOutletState(int idx)
 * @brief 현재 콘센트 상태 가져오기
 * @param idx 상태 가져올 콘센트 번호
 * @return 현재 콘센트 상태 (true : On | false : Off)
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
bool Outlet::getCurrentOutletState(int idx) { return _outlets[idx].state; }

/**
 * @fn bool Outlet::getLastOutletState(int idx)
 * @brief 이전 콘센트 상태 가져오기
 * @param idx 상태 가져올 콘센트 번호
 * @return 이전 콘센트 상태 (true : On | false : Off)
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
bool Outlet::getLastOutletState(int idx) { return _outlets[idx].last_state; }

/**
 * @fn void Outlet::setOutletByPin(int pin, bool is_on)
 * @brief 상태에 따른 콘센트 설정
 * @param pin 콘센트 핀
 * @param is_on 콘센트 전원 상태
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Outlet::setOutletByPin(int pin, bool is_on) {
  if (is_on) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}

/**
 * @fn void Outlet::setOultet(int outlet_idx, bool is_on)
 * @brief 콘센트 조작
 * @param outlet_idx 콘센트 번호
 * @param is_on 콘센트 전원 상태
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Outlet::setOultet(int outlet_idx, bool is_on) {
  int pin = _outlets[outlet_idx].pin;
  setOutletByPin(pin, is_on);
}

/**
 * @fn void Outlet::turnOnOutlet(int idx)
 * @brief 콘센트 켜기
 * @param idx 켤 콘센트 번호
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Outlet::turnOnOutlet(int idx) {
  printf("[Outlet] %d번 콘센트 켜짐.\n", idx + 1);
  setOultet(idx, true);
}

/**
 * @fn void Outlet::turnOffOutlet(int idx)
 * @brief 콘센트 끄기
 * @param idx 끌 콘센트 번호
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Outlet::turnOffOutlet(int idx) {
  printf("[Outlet] %d번 콘센트 꺼짐.\n", idx + 1);
  setOultet(idx, false);
}

/**
 * @fn void Outlet::syncOutlet(void)
 * @brief 콘센트 상태 동기화
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Outlet::syncOutlet(void) {
  for (int i = 0; i < _outlet_num; i++) {
    if (_outlets[i].state) {
      turnOnOutlet(i);
    } else {
      turnOffOutlet(i);
    }
  }
}

/**
 * @fn void Outlet::setOutletChangeFlag(bool is_outlet_changed)
 * @brief 콘센트 상태 변경 플래그 설정
 * @param is_outlet_changed 상태 변경 여부
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Outlet::setOutletChangeFlag(bool is_outlet_changed) {
  _is_outlet_changed = is_outlet_changed;
}

/**
 * @fn bool Outlet::getOutletChangeFlag(void)
 * @brief 콘센트 상태 변경 플래그 가져오기
 * @return 콘센트 상태 변경 여부 (true : 상태 변경됨 | false : 상태 유지함)
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
bool Outlet::getOutletChangeFlag(void) { return _is_outlet_changed; }

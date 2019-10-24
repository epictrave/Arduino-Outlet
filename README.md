# Arduino-Outlet

Control Outlet(relay module) in Arduino.

## Support platform

- esp8226
- esp32

## Usage

```cpp
Outlet outlet = Outlet();
void setup() {
  int outlet_pins[2] = {1, 2};
  Outelt outlet = Outlet(outlet_pins, 2);
}

void loop() {
  if(first oultet should turn on) {
    outlet.setOutletState(0, true);
  }
  if(first oultet should turn off) {
    outlet.setOutletState(0, false);
  }
  if(second oultet should turn on) {
    outlet.setOutletState(1, true);
  }
  if(second oultet should turn off) {
    outlet.setOutletState(1, false);
  }

  if(something goes wrong) {
    outlet.rollbackOutletState();
  } else {
    outlet.syncOutlet();
  }

  //OR just want to turn on / off, use turnOnOutlet, turnOffOutlet
    if(first oultet turn on) {
    outlet.turnOnOutlet(0);
  }
  if(first oultet turn off) {
    outlet.turnOnOutlet(0);
  }
  if(second oultet turn on) {
    outlet.turnOffOutlet(1);
  }
  if(second oultet turn off) {
    outlet.turnOffOutlet(1);
  }
}
```

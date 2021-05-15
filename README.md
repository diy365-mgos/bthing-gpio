# bThings GPIO Library
## Overview
This Mongoose-OS library allows you to easily attach a [bThing](https://github.com/diy365-mgos/bthing) to GPIO.
## GET STARTED
Build up your own device in few minutes just starting from the following sample. Start including following libraries into your `mos.yml` file.
```yaml
libs:
  - origin: https://github.com/diy365-mgos/bthing-gpio
```
## C/C++ API Reference
### mgos_bthing_gpio_attach
```c
bool mgos_bthing_gpio_attach(mgos_bthing_t thing, bool active_high, bool init_gpio);
```
Attaches a *bThing* to the specified GPIO. Returns `true` on success, or `false` otherwise.

|Property||
|--|--|
|thing|A *bThing*.|
|active_high|`true` if GPIO is on when output is high (1).|
|init_gpio|`true` to initialize GPIO [mode](https://mongoose-os.com/docs/mongoose-os/api/core/mgos_gpio.h.md#mgos_gpio_set_mode) and [pull](https://mongoose-os.com/docs/mongoose-os/api/core/mgos_gpio.h.md#mgos_gpio_set_pull).|

**Remarks**

If `init_gpio` is `true`, the GPIO is initialized according the *bThing* type and the `active_high` value.

|active_high|MGOS_BTHING_TYPE_SENSOR|MGOS_BTHING_TYPE_ACTUATOR|
|--|--|--|
|`true`|MGOS_GPIO_MODE_INPUT<br>MGOS_GPIO_PULL_DOWN|MGOS_GPIO_MODE_OUTPUT<br>MGOS_GPIO_PULL_DOWN|
|`false`|MGOS_GPIO_MODE_INPUT<br>MGOS_GPIO_PULL_UP|MGOS_GPIO_MODE_OUTPUT<br>MGOS_GPIO_PULL_UP|
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).

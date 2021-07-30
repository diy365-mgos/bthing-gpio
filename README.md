# bThings GPIO Library
## Overview
Mongoose-OS library that allows you to easily attach a [bThing](https://github.com/diy365-mgos/bthing) to a GPIO.
## C/C++ API Reference
### mgos_bthing_gpio_attach
```c
bool mgos_bthing_gpio_attach(mgos_bthing_t thing, int pin,
                             bool active_high, enum mgos_gpio_pull_type pull);
```
Initializes a GPIO and attaches it to a bThing. Returns `true` on success, or `false` otherwise.

|Parameter||
|--|--|
|thing|A bThing.|
|pin|The GPIO pin.|
|active_high|`true` if GPIO is on when output is high (1).|
|pull|[GPIO pull type](https://mongoose-os.com/docs/mongoose-os/api/core/mgos_gpio.h.md#mgos_gpio_set_pull) or `MGOS_BTHING_GPIO_PULL_AUTO`.|

**Remarks**

If the `pull` parameter is `MGOS_BTHING_GPIO_PULL_AUTO`, the [GPIO pull type](https://mongoose-os.com/docs/mongoose-os/api/core/mgos_gpio.h.md#mgos_gpio_set_pull) is initialized according the `active_high` value:

|active_high value|GPIO pull type|
|--|--|
|`true`|MGOS_GPIO_PULL_DOWN|
|`false`|MGOS_GPIO_PULL_UP|

The [GPIO mode](https://mongoose-os.com/docs/mongoose-os/api/core/mgos_gpio.h.md#mgos_gpio_set_mode) is initialized according the bThing type:

|bThing type|GPIO mode|
|--|--|
|MGOS_BTHING_TYPE_SENSOR|MGOS_GPIO_MODE_INPUT|
|MGOS_BTHING_TYPE_ACTUATOR|MGOS_GPIO_MODE_OUTPUT|
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).

# bThings GPIO Library
## Overview
This Mongoose-OS library allows you to easily a [bThing](https://github.com/diy365-mgos/bthing) to GPIO.
## GET STARTED
Build up your own device in few minutes just starting from the following sample. Start including following libraries into your `mos.yml` file.
```yaml
libs:
  - origin: https://github.com/diy365-mgos/bthing-gpio
```
## C/C++ API Reference
### mgos_bthing_gpio_attach
```c
bool mgos_bthing_gpio_attach(mgos_bthing_t thing, int pin, enum mgos_gpio_pull_type pull);
```
Attaches a *bThing* to the specified GPIO. Returns `true` on success, or `false` otherwise.

|Property||
|--|--|
|thing|A *bThing*.|
|pin|The GPIO pin.|
|pull|The GPIO pull type: `MGOS_GPIO_PULL_UP` or `MGOS_GPIO_PULL_DOWN`.|
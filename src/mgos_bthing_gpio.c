#include "mgos.h"
#include "mgos_bthing.h"

#ifdef MGOS_HAVE_MJS
#include "mjs.h"
#endif

struct mg_bthing_gpio_cfg {
  int pin;
  bool active_high;
};

#if MGOS_BTHING_HAVE_SENSORS
bool mg_bthing_gpio_get_state_cb(mgos_bthing_t thing, mgos_bvar_t state, void *userdata) {
  struct mg_bthing_gpio_cfg *cfg = (struct mg_bthing_gpio_cfg *)userdata;
  if (thing && state && cfg) {
    bool gpio_is_on = mgos_gpio_read(cfg->pin);
    mgos_bvar_set_bool(state, (cfg->active_high ? gpio_is_on : !gpio_is_on));
    return true;
  }
  return false;
}
#endif // MGOS_BTHING_HAVE_SENSORS

#if MGOS_BTHING_HAVE_ACTUATORS
bool mg_bthing_gpio_set_state_cb(mgos_bthing_t thing, mgos_bvarc_t state, void *userdata) {
  struct mg_bthing_gpio_cfg *cfg = (struct mg_bthing_gpio_cfg *)userdata;
  if (thing && cfg && (mgos_bvar_get_type(state) == MGOS_BVAR_TYPE_BOOL)) {
    bool gpio_set_on = mgos_bvar_get_bool(state);
    mgos_gpio_write(cfg->pin, (cfg->active_high == MGOS_GPIO_PULL_UP ? !gpio_set_on : gpio_set_on));
    return true;
  }
  return false;
}
#endif // MGOS_BTHING_HAVE_ACTUATORS

bool mgos_bthing_gpio_attach(mgos_bthing_t thing, int pin, bool active_high, bool init_gpio) {
  #if MGOS_BTHING_HAVE_SENSORS

  if (init_gpio) {
    enum mgos_gpio_pull_type pull = (active_high ? MGOS_GPIO_PULL_DOWN : MGOS_GPIO_PULL_UP);
    if (mgos_bthing_is_typeof(thing, MGOS_BTHING_TYPE_ACTUATOR)) {
      if (!mgos_gpio_set_pull(pin, pull)) return false;
      if (!mgos_gpio_setup_output(pin, (active_high ? false : true))) return false;
    } else if (mgos_bthing_is_typeof(thing, MGOS_BTHING_TYPE_SENSOR)) {
      if (!mgos_gpio_setup_input(pin, pull)) return false;
    }
  }
  
  char set_count = 0;
  struct mg_bthing_gpio_cfg *cfg = calloc(1, sizeof(struct mg_bthing_gpio_cfg));
  cfg->pin = pin;
  cfg->active_high = active_high;
 
  if (mgos_bthing_is_typeof(thing, MGOS_BTHING_TYPE_SENSOR)) {
    if(mgos_bthing_on_get_state(thing, mg_bthing_gpio_get_state_cb, cfg)) ++set_count;
  }

  #if MGOS_BTHING_HAVE_ACTUATORS
  if (mgos_bthing_is_typeof(thing, MGOS_BTHING_TYPE_ACTUATOR) && (set_count > 0)) {
    if (!mgos_bthing_on_set_state(thing, mg_bthing_gpio_set_state_cb, cfg)) {
      mgos_bthing_on_get_state(thing, NULL, NULL);
    }
  }
  
  if (!set_count) free(cfg);
  return (set_count > 0);

  #endif // MGOS_BTHING_HAVE_ACTUATORS
  #endif //MGOS_BTHING_HAVE_SENSORS

  return false;
}


bool mgos_bthing_gpio_init() {
  return true;
}
//
//  pointing_device_custom.c
//  
//
//  Created by Carter Dotson on 5/18/25.
//

#include "pointing_device.h"

#ifdef POINTING_DEVICE_DRIVER_PS2
#    include "ps2_mouse.h"

void pointing_device_driver_init(void) {
    ps2_mouse_init();
}

report_mouse_t pointing_device_driver_task(void) {
    return ps2_mouse_task();
}

#endif

#ifdef POINTING_DEVICE_DRIVER_AZOTEQ_IQS5XX
#    include "drivers/sensors/azoteq_iqs5xx.h"

void pointing_device_driver_init(void) {
    azoteq_iqs5xx_init();
}

report_mouse_t pointing_device_driver_task(void) {
    return azoteq_iqs5xx_get_report();
}
#endif



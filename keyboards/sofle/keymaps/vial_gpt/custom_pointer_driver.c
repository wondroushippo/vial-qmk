//
//  custom_pointer_driver.c
//  
//
//  Created by Carter Dotson on 5/18/25.
//
#include "quantum/pointing_device.h"
#include "ps2_mouse.h"
#include "i2c_azoteq_iqs5xx.h"

// runs once at startup
void pointing_device_init(void) {
    #ifdef MASTER_LEFT
        ps2_mouse_init();
    #endif
    #ifdef MASTER_RIGHT
        azoteq_iqs5xx_init();
    #endif
}

// runs every POINTING_DEVICE_DELAY_MS
void pointing_device_task(void) {
    #ifdef MASTER_LEFT
        int8_t x = 0, y = 0, wheel = 0;
        ps2_mouse_task();  // harvest new PS/2 data
        if (ps2_mouse_has_report()) {
            ps2_mouse_read(&x, &y, &wheel);
            pointing_device_move(x, y);
            pointing_device_scroll(wheel);
        }
    #endif

    #ifdef MASTER_RIGHT
        int8_t rx = 0, ry = 0;
        azoteq_iqs5xx_task();  // harvest new I²C data
        if (azoteq_iqs5xx_has_report()) {
            azoteq_iqs5xx_read_xy(&rx, &ry);
            pointing_device_move(rx, ry);
        }
    #endif
}


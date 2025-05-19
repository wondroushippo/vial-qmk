//
//  pointing_devices.c
//  
//
//  Created by Carter Dotson on 5/18/25.
//
#include "pointing_device.h"
#include "split_util.h"
#include "ps2_mouse.h"
//#include "azoteq_iqs5xx.h"  // Now works because of INCLUDE_PATHS

#define POINTING_DEVICE_DRIVER_azoteq_iqs5xx
#include "azoteq_iqs5xx.h"

void pointing_device_driver_init(void) {
    if (is_keyboard_left()) {
        ps2_mouse_init();
    } else {
        azoteq_iqs5xx_init();  // No device type setting needed
    }
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (is_keyboard_left()) {
        // Convert motion to scroll
        mouse_report.h = mouse_report.x;
        mouse_report.v = -mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
        mouse_report.buttons = 0;
    } else {
        // Optionally scale scroll on the touchpad
        float scroll_scale = 0.25f;
        mouse_report.h = (int8_t)((float)mouse_report.h * scroll_scale);
        mouse_report.v = (int8_t)((float)mouse_report.v * scroll_scale);
    }
    return mouse_report;
}

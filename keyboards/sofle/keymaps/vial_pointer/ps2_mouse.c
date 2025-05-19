//
//  ps2_mouse.c
//  
//
//  Created by Carter Dotson on 5/18/25.
//
//lines 8 to 45 are old logic
//#include "ps2_mouse.h"
//#include "ps2.h"
//#include "print.h"
//#include "pointing_device.h"
//#include "wait.h"
//
//#define PS2_MOUSE_READ_RETRIES 3
//
//static report_mouse_t current_report = {0};
//
//void ps2_mouse_init(void) {
//    ps2_host_init();
//    ps2_host_send(0xFF);  // Reset
//    wait_ms(100);
//    ps2_host_send(0xF4);  // Enable data reporting
//}
//
//report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
//    return current_report;
//}
//
//void ps2_mouse_task(void) {
//    static uint8_t packet[3];
//    static uint8_t index = 0;
//
//    int8_t data;
//    if (ps2_host_receive(&data)) {
//        packet[index++] = (uint8_t)data;
//        if (index >= 3) {
//            index = 0;
//            current_report.buttons = (packet[0] & 0x01 ? MOUSE_BTN1 : 0) |
//                                     (packet[0] & 0x02 ? MOUSE_BTN2 : 0) |
//                                     (packet[0] & 0x04 ? MOUSE_BTN3 : 0);
//            current_report.x = (int8_t)packet[1];
//            current_report.y = -(int8_t)packet[2];  // Invert Y for screen convention
//        }
//    }
//}
#include "ps2_mouse.h"
#include "ps2.h"
#include "print.h"
#include "pointing_device.h"
#include "wait.h"

static report_mouse_t current_report = {0};

void ps2_mouse_init(void) {
    ps2_host_init();
    wait_ms(100);
    ps2_host_send(0xFF);  // Reset
    wait_ms(100);
    ps2_host_send(0xF4);  // Enable data reporting
    wait_ms(20);
}

void ps2_mouse_task(void) {
    static uint8_t packet[3];
    static uint8_t index = 0;

    int8_t data;
    if (ps2_host_receive(&data)) {
        packet[index++] = (uint8_t)data;

        if (index == 3) {
            index = 0;

            current_report.buttons = 0;
            if (packet[0] & 0x01) current_report.buttons |= MOUSE_BTN1; // Left
            if (packet[0] & 0x02) current_report.buttons |= MOUSE_BTN2; // Right
            if (packet[0] & 0x04) current_report.buttons |= MOUSE_BTN3; // Middle

            current_report.x = (int8_t)packet[1];
            current_report.y = -(int8_t)packet[2]; // Invert Y to match screen coordinates
        }
    }
}


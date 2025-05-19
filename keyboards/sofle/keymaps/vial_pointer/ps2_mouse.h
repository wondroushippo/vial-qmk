//
//  ps2_mouse.h
//  
//
//  Created by Carter Dotson on 5/18/25.
//
#pragma once

#include "report.h"
#include "quantum.h"

void ps2_mouse_init(void);
void ps2_mouse_task(void);  // ✅ This is the critical line


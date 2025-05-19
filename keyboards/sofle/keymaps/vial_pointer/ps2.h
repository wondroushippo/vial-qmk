//
//  ps2.h
//  
//
//  Created by Carter Dotson on 5/18/25.
//

#pragma once

void ps2_host_init(void);
void ps2_host_send(uint8_t data);
bool ps2_host_receive(int8_t* data);

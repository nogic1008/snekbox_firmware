#ifndef _PADUEX_U_H_
#define _PADUEX_U_H_

#include <stdint.h>

#include "tusb.h"

#include "common_types.h"

#define PADUEX_U_VID 0x4D47
#define PADUEX_U_PID 0x5772

#define PADUEX_U_REPORT_SIZE 11

#pragma pack(push, 1)

typedef struct
{
    uint8_t axis_y;  // Not used on PADUEX-U
    uint8_t axis_x;  // Not used on PADUEX-U
    uint8_t axis_ry; // Not used on PADUEX-U
    uint8_t axis_rx; // Not used on PADUEX-U
    uint8_t axis_rz; // Not used on PADUEX-U
    uint8_t axis_z;  // Not used on PADUEX-U
    uint32_t buttons;
    uint8_t hat_and_padding; // Not used on PADUEX-U
} paduex_u_report_t;

#pragma pack(pop)

_Static_assert(sizeof(paduex_u_report_t) == PADUEX_U_REPORT_SIZE, "paduex_u_report_t size error");

bool is_PADUEX_U(uint8_t dev_addr);

void processPADUEX_U(uint8_t const *report, uint16_t len);

#endif

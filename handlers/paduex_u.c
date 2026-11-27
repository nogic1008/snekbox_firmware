#include "paduex_u.h"

bool is_PADUEX_U(uint8_t dev_addr)
{
    uint16_t vid, pid;
    tuh_vid_pid_get(dev_addr, &vid, &pid);

    return (vid == PADUEX_U_VID && pid == PADUEX_U_PID);
}

#define PADUEX_U_BTN_UP TU_BIT(1)    // Button 2
#define PADUEX_U_BTN_RIGHT TU_BIT(3) // Button 4
#define PADUEX_U_BTN_DOWN TU_BIT(5)  // Button 6
#define PADUEX_U_BTN_LEFT TU_BIT(7)  // Button 8

static uint32_t read_u32_le(uint8_t const *data)
{
    return ((uint32_t)data[0]) | ((uint32_t)data[1] << 8) | ((uint32_t)data[2] << 16) | ((uint32_t)data[3] << 24);
}

void processPADUEX_U(uint8_t const *report, uint16_t len)
{
    uint32_t buttons = 0;

    if (len == PADUEX_U_REPORT_SIZE + 1 && report[0] == 0x00)
    {
        // [0]=ReportID slot(0x00), [1..6]=axes, [7..10]=buttons, [11]=hat/pad.
        buttons = read_u32_le(report + 7);
    }
    else if (len == PADUEX_U_REPORT_SIZE)
    {
        // Some host stacks may pass payload only (no report-id byte in callback data).
        // [0..5]=axes, [6..9]=buttons, [10]=hat/pad.
        buttons = read_u32_le(report + 6);
    }
    else
    {
        reset_report();
        return;
    }

    reset_report();

    input_report.short_report.dpad_up = (buttons & PADUEX_U_BTN_UP) != 0;
    input_report.short_report.dpad_right = (buttons & PADUEX_U_BTN_RIGHT) != 0;
    input_report.short_report.dpad_down = (buttons & PADUEX_U_BTN_DOWN) != 0;
    input_report.short_report.dpad_left = (buttons & PADUEX_U_BTN_LEFT) != 0;
}

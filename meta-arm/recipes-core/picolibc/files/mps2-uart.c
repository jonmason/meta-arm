// SPDX-License-Identifier: MIT

#include <stdint.h>
#include <stdlib.h>

#define UART0_BASE 0x40004000u
#define UART_DATA (*(volatile uint32_t *)(UART0_BASE + 0x0u))
#define UART_STATE (*(volatile uint32_t *)(UART0_BASE + 0x4u))
#define UART_CTRL (*(volatile uint32_t *)(UART0_BASE + 0x8u))
#define UART_BAUDDIV (*(volatile uint32_t *)(UART0_BASE + 0x10u))
#define UART_TXFULL 1u
#define UART_TXEN 1u

int main(void)
{
    static const char message[] = "hello, world\n";

    UART_BAUDDIV = 434u;  /* 50 MHz / 115200 baud */
    UART_CTRL = UART_TXEN;
    for (const char *c = message; *c; ++c) {
        while (UART_STATE & UART_TXFULL) {
        }
        UART_DATA = (uint32_t)*c;
    }
    while (UART_STATE & UART_TXFULL) {
    }
    exit(0);
}

#ifndef MACROS_MOUSE_H
#define MACROS_MOUSE_H

/**
 * @ingroup mouse
 * @{
 */

#define MOUSE_IRQ 12

#define LB BIT(0)
#define RB BIT(1)
#define MB BIT(2)
#define XMSB BIT(4)
#define YMSB BIT(5)
#define XOVFL BIT(6)
#define YOVFL BIT(7)

#define ACK 0xFA
#define NACK 0xFE
#define ERROR 0xFC

#define WRITE_BYTE_TO_MOUSE 0xD4

#define ENABLE_DATA_REPORTING 0xF4
#define DISABLE_DATA_REPORTING 0xF5
#define SET_STREAM_MODE 0xEA

#define MOUSE_CONTROL_REG 0x64
#define MOUSE_IBF 0x60
#define MOUSE_OBF 0x60

#define INIT 0
#define LINE 1
#define BETWEEN 2
#define RIGHT_LINE 3
#define TOLERANCE 5

/**
 * @}
 */

#endif /* MACROS_MOUSE_H */

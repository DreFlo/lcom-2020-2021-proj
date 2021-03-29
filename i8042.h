#ifndef I8042_H
#define I8042_H

#define ESC 0x81
#define SPACE_MAKE 0x39
#define SPACE_BREAK 0xB9
#define W_MAKE 0x11
#define W_BREAK 0x91
#define A_MAKE 0x1E
#define A_BREAK 0x9E
#define S_MAKE 0x1F
#define S_BREAK 0x9F
#define D_MAKE 0x20
#define D_BREAK 0xA0

#define IN_BUF 0x64 /* Input buffer register */
#define OUT_BUF 0x60 /* Output buffer register */
#define STAT_REG 0x64 /* Status register */

#define KBD_IRQ 1

#define DELAY_US    20000

#define OBF BIT(0)
#define IBF BIT(1)
#define AUX BIT(5)
#define TIMEOUT BIT(6)
#define PARITY BIT(7)

#define FIRST_OF_TWO_BYTES 0xE0

#define MAKECODE BIT(7)

#define ARG 0x60
#define READ_CMB 0x20
#define WRITE_CMB 0x60

#define MSB 0x0F

#define is_ipc_notify(ipc_status) (IPC_STATUS_CALL(ipc_status) == NOTIFY)
#define is_notify(a)    ((unsigned) ((a) - NOTIFY_MESSAGE) < 0x100)
#define is_ipc_asynch(ipc_status) \
    (is_ipc_notify(ipc_status) || IPC_STATUS_CALL(ipc_status) == SENDA)

#endif /* I8042_H */

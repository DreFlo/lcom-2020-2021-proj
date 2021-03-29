#ifndef G_MACROS_H
#define G_MACROS_H

/**
 * @ingroup graphics
 * @{
 */

#define VBE_INTERRUPT 0x10              /** @brief VBE INTERUPT ADDRESS */
#define VBE_CALL 0x4F00                 /** @brief VBE CALL SPECIFIER */
#define VBE_MODE_INFO 0x0001            /** @brief VBE GET INFO FUNCTION */
#define VBE_SET_MODE 0x0002             /** @brief VBE SET MODE FUNCTION */
#define VBE_LINEAR 1<<14                /** @brief VBE LINEAR MEMORY ARRANGEMENT */
#define VBE_SUCCESS_CALL 0x00           /** @brief VBE CALL WAS SUCCESFUL */
#define VBE_FUNC_SUP 0x4F               /** @brief VBE FUNCTION SUPPORTED */

#define VBE_D_600p 0x115                /** @brief VBE MODE USED */

/**
 * @}
 */

#endif /* G_MACROS_H */

/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined (__GNUC__)
 /* Add an explicit reference to the floating point printf library to allow
 the usage of floating point conversion specifier. */
 asm (".global _printf_float");
 /* For GCC compiler revise _write() function for printf functionality */
 int _write(int file, char *ptr, int len)
 {
 int i;
 for (i = 0; i < len; i++)
 {
 UART_UartPutChar(*ptr++);
 }

 return(len);
 }
#elif defined(__ARMCC_VERSION)
 /* For MDK/RVDS compiler revise fputc() function for printf functionality */
 struct __FILE
 {
 int handle;
 };
 enum
 {
STDIN_HANDLE,
 STDOUT_HANDLE,
 STDERR_HANDLE
 };
 FILE __stdin = {STDIN_HANDLE};
 FILE __stdout = {STDOUT_HANDLE};
 FILE __stderr = {STDERR_HANDLE};
 int fputc(int ch, FILE *file)
 {
 int ret = EOF;
 switch(file->handle)
 {
 case STDOUT_HANDLE:
 SCB_UartPutChar(ch);
 ret = ch;
 break;
 case STDERR_HANDLE:
 ret = ch;
 break;
 default:
 file = file;
 break;
 }
 return(ret);
 }
#elif defined (__ICCARM__)
 /* For IAR compiler revise __write() function for printf functionality */
 size_t __write(int handle, const unsigned char * buffer, size_t size)
 {
 size_t nChars = 0;
 for (/* Empty */; size != 0; --size)
 {
 SCB_UartPutChar(*buffer++);
 ++nChars;
 }
 return (nChars);
 }
#endif /* (__GNUC__) */


/* [] END OF FILE */

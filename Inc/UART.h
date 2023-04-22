#ifndef UART_H_
#define UART_H_

void sendUART(uint8_t TxBufferUartLocal[]);
void sendUART_SNversion(void);
void sendAsciiGit(void);
void sendTimeUart(void);

#endif //UART_H_

#ifndef UART_H_
#define UART_H_

#define BLOCK_DELAY_UART_MS  50 //t(sec)=(FRAME/BOUND+MINT)*N = (10/115200+0.00001)*100 = 19 мс

void sendUART(uint8_t TxBufferUartLocal[]);
void sendUART_SNversion(void);

#endif //UART_H_

#include "BLUETOOTH.h"

/*****************  发送一个字符 **********************/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /* 发送一个字节数据到USARTx */
    USART_SendData(pUSARTx, ch);

    /* 等待发送完毕 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
        ;
}

/*****************  接受一个字符 **********************/
unsigned char USARTGetByte(USART_TypeDef *pUSARTx, unsigned char *GetData)
{
    if (USART_GetFlagStatus(pUSARTx, USART_FLAG_RXNE) == RESET)
    {
        return 0; //没有收到数据
    }
    *GetData = USART_ReceiveData(pUSARTx);
    return 1; //收到数据
}

void USARTSendString(USART_TypeDef *pUSARTx, char *String)
{
    for (int i = 0; String[i]; i++)
        Usart_SendByte(pUSARTx, String[i]);
}

/*****************  进行收发测试 **********************/
void USARTTest(USART_TypeDef *pUSARTx)
{
    unsigned char i = 0;

    while (1)
    {
        while (USARTGetByte(pUSARTx, &i))
        {
            Usart_SendByte(pUSARTx, i);
        }
    }
}

/*****************  转化为string  **********************/
void ShortTo0xString(char *str, short x)
{
    unsigned short t = x;
    str[0] = '0';
    str[1] = 'x';
    for (int i = 5; i >= 2; i--)
    {
        if (t % 16 >= 10)
            str[i] = t % 16 - 10 + 'A';
        else
            str[i] = t % 16 + '0';
        t /= 16;
    }
    str[6] = 0;
}

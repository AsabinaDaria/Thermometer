#include "main.h"


void port_ini(void)
{
	PORTD=0x00;
	DDRD=0xFF;
}

int main(void)
{
	unsigned int tt=0; //переменная для хранения температуры
	port_ini(); //Инициализируем порты
	I2C_Init(); //Инициализируем шину I2C
	LCD_ini();  //Инициализируем дисплей
	clearlcd(); //Очистим дисплей
	while(1)
	{
		I2C_SendByteByADDR(0,0b11010000);	//переходим на адрес 0
		_delay_ms(200);
		I2C_StartCondition(); //Отправим условие START
		I2C_SendByte(0b11010001); //отправим в устройство бит чтения
		setpos(0,0); //Ставим курсор на начало координат
		tt = converttemp(dt_check()); //измеряем температуру
		sendcharlcd('t');
		sendcharlcd(' ');
		sendcharlcd('=');
		sendcharlcd(' ');
		sendcharlcd(tt/10+0x30);//Преобразуем число в код числа
		sendcharlcd(tt%10+0x30);//Преобразуем число в код числа
		sendcharlcd('*');
		sendcharlcd('C');
	}
}
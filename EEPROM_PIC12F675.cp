#line 1 "D:/danie/Documentos/Proteus     Arduino/MikroC PRO for PIC/Sketchs PICs/EEPROM/EEPROM_PIC12F675.c"
#line 1 "d:/danie/documentos/proteus     arduino/mikroc pro for pic/sketchs pics/eeprom/eeprom.h"

char EEPROM_write(char dat, unsigned char addr);
char EEPROM_read(unsigned char addr);



char EEPROM_write(char dat, unsigned char addr)
{
 EECON1.WREN = 0x01;
 INTCON.GIE = 0x00;
 EEADR = addr > 0x7F ? addr = 0x7F : addr;
 EEDAT = dat;
 EECON2 = 0x55;
 EECON2 = 0xAA;
 EECON1.WR = 0x01;
 while (EECON1.WR)

 if (EECON1.WRERR)
 {
 EECON1.WREN = 0x00;
 INTCON.GIE = 0x01;
 return 0x01;
 }

 else
 {
 EECON1.WREN = 0x00;
 INTCON.GIE = 0x01;
 return 0x00;
 }
}



char EEPROM_read(unsigned char addr)
{
 EEADR = addr > 0x7F ? addr = 0x7F : addr;
 EECON1.RD = 0x01;
 return EEDAT;
}
#line 4 "D:/danie/Documentos/Proteus     Arduino/MikroC PRO for PIC/Sketchs PICs/EEPROM/EEPROM_PIC12F675.c"
void reg_config();



void main()
{

 reg_config();
 while (1)
 {

 }
}



void reg_config()
{

 OPTION_REG.NOT_GPPU = 0x01;


 EECON1.WREN = 0x00;


 CMCON = 0x07;


 ANSEL = 0x00;


 TRISIO.TRISIO0 = 0x00;
 TRISIO.TRISIO1 = 0x00;


 GPIO.F0 = 0x00;
 GPIO.F1 = 0x00;
}

#include "EEPROM.h"

// Prot�tipo de fun��es
void reg_config();                                                              // Configura��o de registros


// Fun��o principal
void main()
{
  // Setup.
  reg_config();
  while (1)
  {
    // Loop.
  }
}


// Desenvolvimento reg_config()
void reg_config()
{
  // OPTION_REG register
  OPTION_REG.NOT_GPPU = 0x01;                                                   // PULL-UPS INTERNOS DESABILITADOS

  // EECON1 register
  EECON1.WREN = 0x00;                                                           // Inibe inicialmente escritas na EEPROM

  // CMCON register
  CMCON = 0x07;                                                                 // Desabilita comparadores internos

  // ANSEL register
  ANSEL = 0x00;                                                                 // Configura todos GPIO's como Digital I/O

  // TRISIO register
  TRISIO.TRISIO0 = 0x00;                                                        // Configura GPIO 0 como sa�da digital
  TRISIO.TRISIO1 = 0x00;                                                        // Configura GPIO 1 como sa�da digital

  // GPIO register
  GPIO.F0 = 0x00;                                                               // Inicia GPIO 0 como LOW
  GPIO.F1 = 0x00;                                                               // Inicia GPIO 1 como LOW
}
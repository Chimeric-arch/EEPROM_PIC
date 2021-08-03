#ifndef EEPROM_H
#define EEPROM_H
#endif

// Prot�tipo de fun��es
char EEPROM_write(char dat, unsigned char addr);                                // Fun��o de escrita na mem�ria EEPROM
char EEPROM_read(unsigned char addr);                                           // Fun��o de leitura da mem�ria EEPROM


// Desenvolvimento EEPROM_write()
char EEPROM_write(char dat, unsigned char addr)
{
  EECON1.WREN = 0x01;                                                           // Habilita ciclo de escrita
  INTCON.GIE  = 0x00;                                                           // Desabilita temporariamente interrup��o por perif�ricos
  EEADR       = addr > 0x7F ? addr = 0x7F : addr;                               // Carrega registro com endere�o da mem�ria
  EEDAT       =  dat;                                                           // Carrega registro com os dados a serem escritos
  EECON2      = 0x55;                                                           // Sequ�ncia determinada pelo datasheet
  EECON2      = 0xAA;                                                           // Sequ�ncia determinada pelo datasheet
  EECON1.WR   = 0x01;                                                           // Inicia ciclo de escrita
  while (EECON1.WR)                                                             // Espera t�rmino do ciclo de escrita

  if (EECON1.WRERR)                                                             // Se opera��o incompleta
  {
    EECON1.WREN = 0x00;                                                         // Desabilita cliclo de escrita
    INTCON.GIE  = 0x01;                                                         // Reabilita interrup��o por perif�ricos
    return 0x01;                                                                // Opera��o de escrita foi encerrada prematuramente
  }

  else                                                                          // Se opera��o completa
  {
    EECON1.WREN = 0x00;                                                         // Desabilita cliclo de escrita
    INTCON.GIE  = 0x01;                                                         // Reabilita interrup��o por perif�ricos
    return 0x00;                                                                // Opera��o de escrita foi encerrada com sucesso
  }
}


// Desenvolvimento EEPROM_read()
char EEPROM_read(unsigned char addr)
{
  EEADR     = addr > 0x7F ? addr = 0x7F : addr;                                 // Carrega registro com endere�o da mem�ria
  EECON1.RD = 0x01;                                                             // Inicia ciclo de leitura
  return EEDAT;                                                                 // Retorna byte de leitura
}
#ifndef EEPROM_H
#define EEPROM_H
#endif

// Protótipo de funções
char EEPROM_write(char dat, unsigned char addr);                                // Função de escrita na memória EEPROM
char EEPROM_read(unsigned char addr);                                           // Função de leitura da memória EEPROM


// Desenvolvimento EEPROM_write()
char EEPROM_write(char dat, unsigned char addr)
{
  EECON1.WREN = 0x01;                                                           // Habilita ciclo de escrita
  INTCON.GIE  = 0x00;                                                           // Desabilita temporariamente interrupção por periféricos
  EEADR       = addr > 0x7F ? addr = 0x7F : addr;                               // Carrega registro com endereço da memória
  EEDAT       =  dat;                                                           // Carrega registro com os dados a serem escritos
  EECON2      = 0x55;                                                           // Sequência determinada pelo datasheet
  EECON2      = 0xAA;                                                           // Sequência determinada pelo datasheet
  EECON1.WR   = 0x01;                                                           // Inicia ciclo de escrita
  while (EECON1.WR)                                                             // Espera término do ciclo de escrita

  if (EECON1.WRERR)                                                             // Se operação incompleta
  {
    EECON1.WREN = 0x00;                                                         // Desabilita cliclo de escrita
    INTCON.GIE  = 0x01;                                                         // Reabilita interrupção por periféricos
    return 0x01;                                                                // Operação de escrita foi encerrada prematuramente
  }

  else                                                                          // Se operação completa
  {
    EECON1.WREN = 0x00;                                                         // Desabilita cliclo de escrita
    INTCON.GIE  = 0x01;                                                         // Reabilita interrupção por periféricos
    return 0x00;                                                                // Operação de escrita foi encerrada com sucesso
  }
}


// Desenvolvimento EEPROM_read()
char EEPROM_read(unsigned char addr)
{
  EEADR     = addr > 0x7F ? addr = 0x7F : addr;                                 // Carrega registro com endereço da memória
  EECON1.RD = 0x01;                                                             // Inicia ciclo de leitura
  return EEDAT;                                                                 // Retorna byte de leitura
}

_EEPROM_write:

;eeprom.h,11 :: 		char EEPROM_write(char dat, unsigned char addr)
;eeprom.h,13 :: 		EECON1.WREN = 0x01;                                                           // Habilita ciclo de escrita
	BSF        EECON1+0, 2
;eeprom.h,14 :: 		INTCON.GIE  = 0x00;                                                           // Desabilita temporariamente interrupção por periféricos
	BCF        INTCON+0, 7
;eeprom.h,15 :: 		EEADR       = addr > 0x7F ? addr = 0x7F : addr;                               // Carrega registro com endereço da memória
	MOVF       FARG_EEPROM_write_addr+0, 0
	SUBLW      127
	BTFSC      STATUS+0, 0
	GOTO       L_EEPROM_write0
	MOVLW      127
	MOVWF      FARG_EEPROM_write_addr+0
	MOVLW      127
	MOVWF      R1+0
	GOTO       L_EEPROM_write1
L_EEPROM_write0:
	MOVF       FARG_EEPROM_write_addr+0, 0
	MOVWF      R1+0
L_EEPROM_write1:
	MOVF       R1+0, 0
	MOVWF      EEADR+0
;eeprom.h,16 :: 		EEDAT       =  dat;                                                           // Carrega registro com os dados a serem escritos
	MOVF       FARG_EEPROM_write_dat+0, 0
	MOVWF      EEDAT+0
;eeprom.h,17 :: 		EECON2      = 0x55;                                                           // Sequência determinada pelo datasheet
	MOVLW      85
	MOVWF      EECON2+0
;eeprom.h,18 :: 		EECON2      = 0xAA;                                                           // Sequência determinada pelo datasheet
	MOVLW      170
	MOVWF      EECON2+0
;eeprom.h,19 :: 		EECON1.WR   = 0x01;                                                           // Inicia ciclo de escrita
	BSF        EECON1+0, 1
;eeprom.h,20 :: 		while (EECON1.WR)                                                             // Espera término do ciclo de escrita
	BTFSS      EECON1+0, 1
	GOTO       L_EEPROM_write3
;eeprom.h,22 :: 		if (EECON1.WRERR)                                                             // Se operação incompleta
	BTFSS      EECON1+0, 3
	GOTO       L_EEPROM_write4
;eeprom.h,24 :: 		EECON1.WREN = 0x00;                                                         // Desabilita cliclo de escrita
	BCF        EECON1+0, 2
;eeprom.h,25 :: 		INTCON.GIE  = 0x01;                                                         // Reabilita interrupção por periféricos
	BSF        INTCON+0, 7
;eeprom.h,26 :: 		return 0x01;                                                                // Operação de escrita foi encerrada prematuramente
	MOVLW      1
	MOVWF      R0+0
	GOTO       L_end_EEPROM_write
;eeprom.h,27 :: 		}
L_EEPROM_write4:
;eeprom.h,31 :: 		EECON1.WREN = 0x00;                                                         // Desabilita cliclo de escrita
	BCF        EECON1+0, 2
;eeprom.h,32 :: 		INTCON.GIE  = 0x01;                                                         // Reabilita interrupção por periféricos
	BSF        INTCON+0, 7
;eeprom.h,33 :: 		return 0x00;                                                                // Operação de escrita foi encerrada com sucesso
	CLRF       R0+0
	GOTO       L_end_EEPROM_write
;eeprom.h,34 :: 		}
L_EEPROM_write3:
;eeprom.h,35 :: 		}
L_end_EEPROM_write:
	RETURN
; end of _EEPROM_write

_EEPROM_read:

;eeprom.h,39 :: 		char EEPROM_read(unsigned char addr)
;eeprom.h,41 :: 		EEADR     = addr > 0x7F ? addr = 0x7F : addr;                                 // Carrega registro com endereço da memória
	MOVF       FARG_EEPROM_read_addr+0, 0
	SUBLW      127
	BTFSC      STATUS+0, 0
	GOTO       L_EEPROM_read6
	MOVLW      127
	MOVWF      FARG_EEPROM_read_addr+0
	MOVLW      127
	MOVWF      R1+0
	GOTO       L_EEPROM_read7
L_EEPROM_read6:
	MOVF       FARG_EEPROM_read_addr+0, 0
	MOVWF      R1+0
L_EEPROM_read7:
	MOVF       R1+0, 0
	MOVWF      EEADR+0
;eeprom.h,42 :: 		EECON1.RD = 0x01;                                                             // Inicia ciclo de leitura
	BSF        EECON1+0, 0
;eeprom.h,43 :: 		return EEDAT;                                                                 // Retorna byte de leitura
	MOVF       EEDAT+0, 0
	MOVWF      R0+0
;eeprom.h,44 :: 		}
L_end_EEPROM_read:
	RETURN
; end of _EEPROM_read

_main:

;EEPROM_PIC12F675.c,8 :: 		void main()
;EEPROM_PIC12F675.c,11 :: 		reg_config();
	CALL       _reg_config+0
;EEPROM_PIC12F675.c,12 :: 		while (1)
L_main8:
;EEPROM_PIC12F675.c,15 :: 		}
	GOTO       L_main8
;EEPROM_PIC12F675.c,16 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_reg_config:

;EEPROM_PIC12F675.c,20 :: 		void reg_config()
;EEPROM_PIC12F675.c,23 :: 		OPTION_REG.NOT_GPPU = 0x01;                                                   // PULL-UPS INTERNOS DESABILITADOS
	BSF        OPTION_REG+0, 7
;EEPROM_PIC12F675.c,26 :: 		EECON1.WREN = 0x00;                                                           // Inibe inicialmente escritas na EEPROM
	BCF        EECON1+0, 2
;EEPROM_PIC12F675.c,29 :: 		CMCON = 0x07;                                                                 // Desabilita comparadores internos
	MOVLW      7
	MOVWF      CMCON+0
;EEPROM_PIC12F675.c,32 :: 		ANSEL = 0x00;                                                                 // Configura todos GPIO's como Digital I/O
	CLRF       ANSEL+0
;EEPROM_PIC12F675.c,35 :: 		TRISIO.TRISIO0 = 0x00;                                                        // Configura GPIO 0 como saída digital
	BCF        TRISIO+0, 0
;EEPROM_PIC12F675.c,36 :: 		TRISIO.TRISIO1 = 0x00;                                                        // Configura GPIO 1 como saída digital
	BCF        TRISIO+0, 1
;EEPROM_PIC12F675.c,39 :: 		GPIO.F0 = 0x00;                                                               // Inicia GPIO 0 como LOW
	BCF        GPIO+0, 0
;EEPROM_PIC12F675.c,40 :: 		GPIO.F1 = 0x00;                                                               // Inicia GPIO 1 como LOW
	BCF        GPIO+0, 1
;EEPROM_PIC12F675.c,41 :: 		}
L_end_reg_config:
	RETURN
; end of _reg_config

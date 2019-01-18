/**
  ******************************************************************************
  * @file    hal.c 
  * @author  <Ihre Name>
  * @date    <Datum der Probeklausur>
  * @brief   Diese Datei gehört zur GS Probeklausur WS 2018-19 SchiffeVersenken
	*          Dieses Modul kapselt den Zugriff auf die Hardware.
  ******************************************************************************
  */

#include "hal.h"
#include <stdint.h>
#include <stdbool.h>
#include "TI_memory_map.h"
#include "mytimer.h"

// Der Zugriff auf die Schalter ist softwaremässig entprellt.
// Ein Taster prellt maximal DELTA_PRELLEN us
// Wenn ein Schalter prellt, werden maximal ANZAHL_LESEVERSUCHE_PRELLEN 
// Zugriffe auf den Schalter durchgefuehrt.

#define DELTA_PRELLEN   							20 // us
#define ANZAHL_LESEVERSUCHE_PRELLEN		5


/**
* @brief Diese Funktion fuehrt die Initialisierung der Hardware durch, die von den
*        in Init_TI_Board() umgesetzten Standardeinstellungen abweicht.
* @param None
* @retval None
*/
void initHal(void) {
}
 
/**
* @brief Diese Funktion setzt die oberen 8 an Port G angeschlossenen LEDs
*        gemaess dem in v uebergebenen Wert.
* @param v Wert, der binaer auf den LEDs ausgegeben wird.
* @retval None
*/
void setzeLEDHighByte(const unsigned char v) {
	int zahl = v;
	
	char binary[8];
	int rest;
	for (int i = 0; i < 8; i++) {
		rest = zahl % 2;
		binary[i] = '0' + rest;
		zahl = zahl / 2;
	}
	
	int led = 8;
	for (int i = 0; i < 8; i++) {
		if (binary[i] == ('0' + 1)) {
			GPIOG->BSRRL = (0x01 << (led + i));
		}
		else if (binary[i] == ('0' + 0)) {
			GPIOG->BSRRH = (0x01 << (led + i));
		}
	}
	
}

/**
* @brief Diese Funktion liest den in taster uebergebenen Taster aus.
*        Der Zugriff auf den Taster wird softwareseitig entprellt.
*        Es werden maximal ANZAHL_LESEVERSUCHE_PRELLEN Leseversuche
*        durchgefuehrt. 
*        Die Prelldauer eines Tasters betraegt maximal DELTA_PRELLEN us.
* @param taster Nummer des Tasters, der ausgelesen wird.
* @retval true, wenn der Taster gedrueckt ist. Ansonsten und im Fehlerfall
*         (nicht zulaessiger Taster oder Anzahl Leseversuche ueberschritten)
*         ist der Rueckgabewerte false.
*/
bool leseTaster(const unsigned char taster) {
	bool wertSchalter;
	
	for (int i = 0; i < ANZAHL_LESEVERSUCHE_PRELLEN; i++) {
		wertSchalter = (0x01 << taster) != (GPIOE->IDR & (0x01 << taster));
		sleep(DELTA_PRELLEN);
		if (wertSchalter == (0x01 << taster) != (GPIOE->IDR & (0x01 << taster))) {
			break;
		}
	}
	
	return wertSchalter;
}
// EOF

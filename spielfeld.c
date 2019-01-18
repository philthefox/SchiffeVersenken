/**
  ******************************************************************************
  * @file    spielfeld.c 
  * @author  <Ihre Name>
  * @date    <Datum der Probeklausur>
  * @brief   Diese Datei gehört zur GS Probeklausur WS 2018-19 SchiffeVersenken
	*          Dieses Modul implementiert die Darstellung des 
	*          Spielfelds auf dem TFT Displays.
	*          Das linke obere Feld (ohne Rand) des Spielfelds hat die 
	*          Koordinaten (0,0).
  ******************************************************************************
  */
#include "spielfeld.h"
#include "general.h"
#include "tft.h"

#define WASSER                           ' '
#define TREFFER_BOOT                     '*'  // Farbe rot      
#define TREFFER_WASSER					         '+'  // Farbe weiss
#define ZIEL_KANONE                      '0'  // Farbe gelb
#define RAHMEN													 'X'  // Farbe weiss

/**
* @brief Diese Funktion druckt auf dem Spielfeld an der Position zeile, spalte
*        die Darstellung von Wasser - ein Leerzeichen.
* @param zeile Zeilenposition
* @param spalte Spaltenposition 
* @retval none
*/
void printWasser(const unsigned char zeile, const unsigned char spalte){
	TFT_gotoxy(zeile + 1, spalte + 1);
	TFT_putc(' ');
}

/**
* @brief Diese Funktion druckt auf dem Spielfeld an der Position zeile, spalte
*        die Darstellung eines Treffers eines Bootselements - ein roter *.
* @param zeile Zeilenposition
* @param spalte Spaltenposition
* @retval none
*/
void printTrefferBoot(const unsigned char zeile, const unsigned char spalte){
	TFT_gotoxy(zeile + 1, spalte + 1);
	TFT_set_font_color(RED);
	TFT_putc('*');
}

/**
* @brief Diese Funktion druckt auf dem Spielfeld an der Position zeile, spalte
*        die Darstellung eines Schluss ins Wasser - ein weisses +.
* @param zeile Zeilenposition
* @param spalte Spaltenposition
* @retval none
*/
void printTrefferWasser(const unsigned char zeile, const unsigned char spalte){
	TFT_gotoxy(zeile + 1, spalte + 1);
	TFT_set_font_color(WHITE);
	TFT_putc('+');
}

/**
* @brief Diese Funktion druckt auf dem Spielfeld an der Position zeile, spalte
*        die Darstellung, dass die Kanone auf dieses Feld zielt - ein gelbes O.
* @param zeile Zeilenposition
* @param spalte Spaltenposition
* @retval none
*/
void printPositionKanone(const unsigned char zeile, const unsigned char spalte){
	TFT_gotoxy(zeile + 1, spalte + 1);
	TFT_set_font_color(YELLOW);
	TFT_putc('O');
}

/**
* @brief Diese Funktion initialisiert das TFT Display und das Spielfeld.
*        Das Spielfeld ist ein Window mit dem Font FONT6x8.
*        Der Curser wird ausgeschaltet.
*        Das Spielfelds wird mit weissen X umrandet. Das ganze Spielfeld wird 
*        mit der Darstellung von Wasser gefüllt.
* @param none
* @retval none
*/
void initSpielfeld(void){
	TFT_Init();
	
	// Umrandung des Spielfelds mit weissen X
	TFT_set_font_color(WHITE);
	for (int i = 0; i < 8; i++) {
		TFT_gotoxy(3, 3 + i);
		TFT_putc('X');
		TFT_gotoxy(10, 3 + i);
		TFT_putc('X');
		TFT_gotoxy(3 + i, 3);
		TFT_putc('X');
		TFT_gotoxy(3 + i, 10);
		TFT_putc('X');
	}
	
	TFT_set_window(FONT6x8, 4, 4, 6, 6);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			printWasser(i, j);
		}
	}
}
// EOF

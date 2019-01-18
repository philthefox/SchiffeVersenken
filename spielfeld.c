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
#define ABSTAND_RAND_X		5
#define ABSTAND_RAND_Y		5

/**
* @brief Diese Funktion druckt auf dem Spielfeld an der Position zeile, spalte
*        die Darstellung von Wasser - ein Leerzeichen.
* @param zeile Zeilenposition
* @param spalte Spaltenposition 
* @retval none
*/
void printWasser(const unsigned char zeile, const unsigned char spalte){
	TFT_gotoxy(zeile + 1, spalte + 1);
	TFT_putc(WASSER);
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
	TFT_putc(TREFFER_BOOT);
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
	TFT_putc(TREFFER_WASSER);
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
	TFT_putc(ZIEL_KANONE);
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
	TFT_cursor_off();
	TFT_gotoxy(3, 2);
	TFT_puts("Schiffe versenken");
	TFT_gotoxy(ABSTAND_RAND_X + ANZ_SPALTEN_SPIELFELD + 5, ABSTAND_RAND_Y);
	TFT_puts("S5: Kanone hoch");
	TFT_gotoxy(ABSTAND_RAND_X + ANZ_SPALTEN_SPIELFELD + 5, ABSTAND_RAND_Y + 1);
	TFT_puts("S2: Kanone runter");
	TFT_gotoxy(ABSTAND_RAND_X + ANZ_SPALTEN_SPIELFELD + 5, ABSTAND_RAND_Y + 2);
	TFT_puts("S1: Kanone nach rechts");
	TFT_gotoxy(ABSTAND_RAND_X + ANZ_SPALTEN_SPIELFELD + 5, ABSTAND_RAND_Y + 3);
	TFT_puts("S6: Kanone nach links");
	TFT_gotoxy(ABSTAND_RAND_X + ANZ_SPALTEN_SPIELFELD + 5, ABSTAND_RAND_Y + 4);
	TFT_puts("S3: Kanonenschuss");
	TFT_gotoxy(ABSTAND_RAND_X + ANZ_SPALTEN_SPIELFELD + 5, ABSTAND_RAND_Y + 5);
	TFT_puts("S7: Neues Spiel");
	
	// Umrandung des Spielfelds mit weissen X
	TFT_set_font_color(WHITE);
	for (int i = 0; i < ANZ_SPALTEN_SPIELFELD + 2; i++) {
		TFT_gotoxy(ABSTAND_RAND_X, ABSTAND_RAND_Y + i);
		TFT_putc(RAHMEN);
		TFT_gotoxy(ABSTAND_RAND_X + ANZ_ZEILEN_SPIELFELD + 1, ABSTAND_RAND_Y + i);
		TFT_putc(RAHMEN);
		TFT_gotoxy(ABSTAND_RAND_X + i, ABSTAND_RAND_Y);
		TFT_putc(RAHMEN);
		TFT_gotoxy(ABSTAND_RAND_X + i, ABSTAND_RAND_Y + ANZ_SPALTEN_SPIELFELD + 1);
		TFT_putc(RAHMEN);
	}
	
	TFT_set_window(FONT6x8, ABSTAND_RAND_X + 1, ABSTAND_RAND_Y + 1, ANZ_ZEILEN_SPIELFELD, ANZ_SPALTEN_SPIELFELD);
	spielfeldZuruecksetzen();
}

void spielfeldZuruecksetzen() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			printWasser(i, j);
		}
	}
}
// EOF

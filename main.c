/**
  ******************************************************************************
  * @file    main.c 
  * @author  <Ihre Name>
  * @date    <Datum der Probeklausur>
  * @brief   Diese Datei gehört zur GS Probeklausur WS 2018-19 SchiffeVersenken
	*          Diese Datei steuert das Spiel gemaess direct digital control.
	*          Weiterhin enthaelt Sie die Testfunktionen für die Teilaufgaben.
  ******************************************************************************
  */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "spielfeld.h"
#include "TI_Lib.h"
#include "tft.h"
#include "logik.h"
#include "mytimer.h"
#include "hal.h"

// Am Anfang jedes Durchlaufs durch die Super Loop wir das 
// Spiel um DELAY_SUPER_LOOP us verzoegert, damit bei anhaltendem
// Druecken eines Tasters, die Kanone sich nicht zu schnell bewegt.
#define  DELAY_SUPER_LOOP			(100*1000)   // us 

/**
  * @brief  Rudimentaerer Test der Module hal und mytimer
  * @param  None
  */
void testA3(void){
	 initHal();
	 initMyTimer();
	
	 // Warte bis Taster LINKS_TASTER gedrueckt wird
	 while (!leseTaster(LINKS_TASTER)){ }
	 // Ausgabe auf den LEDs
	 setzeLEDHighByte(1);
	 // Warte bis Taster HOCH_TASTER gedrueckt und anschliessend loggelassen wird
	 while (!leseTaster(HOCH_TASTER)){ }
	 while (leseTaster(HOCH_TASTER)){ }
	 setzeLEDHighByte(2);
	 // Warte 10 Sekunden
	 sleep(10*1000*1000);
	 // Loesche die LEDs
	 setzeLEDHighByte(0);
	 // Warte 5 Sekunden
	 sleep(5*1000*1000);	 
	 // Setze alle LEDs
	 setzeLEDHighByte(255);
}

/**
  * @brief  Rudimentaerer Test des Moduls spielfeld
  * @param  None
  */
void testA4(void){
	 initMyTimer();
	 initSpielfeld();
	 // Spielfeld mit weißen Rahmen sollte auf dem TFT darstellt werden
	 sleep(5*1000*1000); // Warte 5 Sekunden
	 printTrefferBoot(0, 0);
	 // oben links wird eine Treffer angezeigt
	 sleep(5*1000*1000); // Warte 5 Sekunden
	 printTrefferBoot(0, 5);
	 printTrefferBoot(5, 0);
	 printTrefferBoot(5, 5);
	 // in allen vier Ecken wird ein Treffer angezeigt
	 sleep(5*1000*1000); // Warte 5 Sekunden
	
	 printTrefferBoot(3, 3);
   printWasser(0, 0);
   printWasser(0, 5);
   printWasser(5, 0);
   printWasser(5, 5);
   // Treffer Boot an der Position 3 3 
	 sleep(5*1000*1000); // Warte 5 Sekunden
	 printPositionKanone(3, 3);
   printWasser(0, 0);
   // Ziel Kanone an der Position 3 3 
	 sleep(5*1000*1000); // Warte 5 Sekunden
	 printTrefferWasser(3, 3);
   // Treffer Wasser an der Position 3 3 
	 sleep(5*1000*1000); // Warte 5 Sekunden
}


/**
  * @brief  Rudimentaerer Test des Moduls logik
  * @param  None
  */
void testA5(void){
	 initMyTimer();
	 initSpielfeld();
	 initSpiel();
	
	 // Gehe zum Feld (5,5) 
	 // Die Zielposition wandert nach rechts und nach unten
	 sleep(1*1000*1000);
	 bewegeKanone(rechts); sleep(1*1000*1000);
	 bewegeKanone(rechts); sleep(1*1000*1000);
	 bewegeKanone(rechts); sleep(1*1000*1000);
	 bewegeKanone(rechts); sleep(1*1000*1000);
	 bewegeKanone(rechts); sleep(1*1000*1000);
	 bewegeKanone(rechts); sleep(1*1000*1000);
	
	 bewegeKanone(runter); sleep(1*1000*1000);
	 bewegeKanone(runter); sleep(1*1000*1000);
	 bewegeKanone(runter); sleep(1*1000*1000);
	 bewegeKanone(runter); sleep(1*1000*1000);
	 bewegeKanone(runter); sleep(1*1000*1000);
	 bewegeKanone(runter); sleep(1*1000*1000);
	 bewegeKanone(runter); sleep(1*1000*1000);
	 bewegeKanone(runter); sleep(1*1000*1000);
	 // Schieße das Boot an der Position (5,5) ab
	 schussKanone();
	 // An der Position (5,5) muss ein Abschuss angezeigt werden
	 sleep(5*1000*1000);
	 bewegeKanone(rechts); bewegeKanone(rechts);
	 bewegeKanone(rechts); bewegeKanone(rechts);
	 bewegeKanone(rechts); bewegeKanone(rechts);
	 bewegeKanone(runter); bewegeKanone(runter);
	 bewegeKanone(runter); bewegeKanone(runter);
	 bewegeKanone(runter); bewegeKanone(runter);
	 bewegeKanone(runter); bewegeKanone(runter);
	 bewegeKanone(hoch); 
	 schussKanone();
	 // An der Position (4,5) wird ein Schuss ins Wasser angezeigt
	 sleep(5*1000*1000);	
}

/**
  * @brief  Diese Funktion steuert das Spiel gemaess direct digital control.
  * @param  None
  */
static void ddc(void) {
	// Initialisierungen
	bool reset_taster = false;
	bool hoch_taster = false;
	bool runter_taster = false;
	bool links_taster = false;
	bool rechts_taster = false;
	bool schuss_taster = false;
	int anzahlSchuesse = 0;
	initMyTimer();
	initSpielfeld();
	initSpiel();
	
	while (1) { // super loop
		// Einlesen der Taster
		reset_taster = leseTaster(RESET_TASTER);
		hoch_taster = leseTaster(HOCH_TASTER);
		runter_taster = leseTaster(RUNTER_TASTER);
		links_taster = leseTaster(LINKS_TASTER);
		rechts_taster = leseTaster(RECHTS_TASTER);
		schuss_taster = leseTaster(SCHUSS_TASTER);
		
		// Update des Zustands
		if (reset_taster) {
			spielfeldZuruecksetzen();
			initSpiel();
			anzahlSchuesse = 0;
		}
		if (hoch_taster) {
			bewegeKanone(hoch);
		}
		if (runter_taster) {
			bewegeKanone(runter);
		}
		if (links_taster) {
			bewegeKanone(links);
		}
		if (rechts_taster) {
			bewegeKanone(rechts);
		}
		if (schuss_taster) {
			schussKanone();
			anzahlSchuesse++;
		}
		
		// Treiben der Aktoren
		setzeLEDHighByte(anzahlSchuesse);
		printSpielfeld();
		
		// Warten, wenn Taster gedrueckt wurde
		if (reset_taster || hoch_taster || runter_taster || links_taster || rechts_taster || schuss_taster) {
			sleep(200*1000);
		}
	}	 
}	

/**
  * @brief  Main program
  * @param  None
  */

int main(void) {
	Init_TI_Board();
	ddc();
	return 0;
}
// EOF

/**
  ******************************************************************************
  * @file    spielfeld.h 
  * @author  <Ihre Name>
  * @date    <Datum der Probeklausur>
  * @brief   Diese Datei gehört zur GS Probeklausur WS 2018-19 SchiffeVersenken
	*          Interface des Moduls spielfeld, das das Spielfeld auf dem 
	*          TFT Display darstellt.
  ******************************************************************************
  */

#ifndef _SPIELFELD_H
#define _SPIELFELD_H

void initSpielfeld(void);

void spielfeldZuruecksetzen();

void printWasser(const unsigned char x, const unsigned char y);

void printTrefferBoot(const unsigned char x, const unsigned char y);

void printTrefferWasser(const unsigned char x, const unsigned char y);

void printPositionKanone(const unsigned char x, const unsigned char y);

#endif
// EOF

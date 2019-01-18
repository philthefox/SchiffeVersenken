/**
  ******************************************************************************
  * @file    hal.h 
  * @author  <Ihre Name>
  * @date    <Datum der Probeklausur>
  * @brief   Diese Datei gehört zur GS Probeklausur WS 2018-19 SchiffeVersenken
	*          Interface des Moduls hal, das  den Zugriff auf die Hardware kapselt.
  ******************************************************************************
  */

#ifndef _HAL_H
#define _HAL_H
#include <stdbool.h>

// Zuweisung der Pins der Taster, die an Port E angeschlossen sind.
#define RESET_TASTER						7
#define HOCH_TASTER  						5
#define RUNTER_TASTER 					2
#define LINKS_TASTER   					6
#define RECHTS_TASTER  					1
#define SCHUSS_TASTER           3 

void initHal(void);

void setzeLEDHighByte(const unsigned char v);

bool leseTaster(const unsigned char taster);

#endif
// EOF

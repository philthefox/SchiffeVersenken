/**
  ******************************************************************************
  * @file    logik.h 
  * @author  <Ihre Name>
  * @date    <Datum der Probeklausur>
  * @brief   Diese Datei gehört zur GS Probeklausur WS 2018-19 SchiffeVersenken
	*          Interface des Moduls logik.
  ******************************************************************************
  */

#ifndef _LOGIK_H
#define _LOGIK_H
#include "general.h"

void initSpiel(void);

void bewegeKanone(const enum richtung r);

void schussKanone(void);
#endif
//EOF

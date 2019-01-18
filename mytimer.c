/**
  ******************************************************************************
  * @file    mytimer.c 
  * @author  <Ihre Name>
  * @date    <Datum der Probeklausur>
  * @brief   Diese Datei gehört zur GS Probeklausur WS 2018-19 SchiffeVersenken
	*          Das Modul mytimer implementiert einfache Timer Funktionen.
	*          Es basiert auf dem Modul timer.
  ******************************************************************************
  */
	
#include "mytimer.h"
#include "timer.h"

/**
* @brief Initialisierung des Moduls mytimer und der verwendeten Module.
* @param None
* @retval None
*/
void initMyTimer(void) {
	timerinit();
}

/**
* @brief Diese Funktion verzögert die Ausführung um delay Mikrosekunden.
* @param delay Mikrosekunden, um die Funktion verzoegert.
*        delay * CONVERT2US muss kleiner als UINT32_MAX sein. Dies wird 
*        nicht ueberprueft.
* @retval None
*/
void sleep(const uint32_t delay){
	uint32_t initialTime = getTimeStamp();
	uint32_t actualTime = getTimeStamp();
	while (actualTime - initialTime < delay) {
		actualTime = getTimeStamp();
	}
}
// EOF

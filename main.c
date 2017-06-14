/******************************************************************************
 *
 * Project: Hindernisumfahrung mit dem RP6
 * File:    main.c
 *
 * Ingenieurorientierte Programmierung
 * Dr. Alexander Kling
 *
 * Carsten Bevermann
 * Christoph Geitner
 * Jens Reimer
 * Marc T�pker
 *
 *****************************************************************************/

//#include <avr/io.h>
#include "RP6RobotBaseLib.h"

int destination = 1000;

enum state_model
{
    IDLE,
    BUMPER_LEFT,
    BUMPER_RIGHT,
    MOVE_TO_DESTINATION,
} state;


void bumperActive(void)
{
    if (bumper_left)
    {
        stop();
        state = BUMPER_LEFT;
    }
    if (bumper_right)
    {
        stop();
        state = BUMPER_RIGHT;
    }
}

void stateModel(void)
{
	switch(state)
	{
		case IDLE:
		     stop();
		break;

		case MOVE_TO_DESTINATION:
             move(200, FWD, DIST_MM(destination),true);

            if(isMovementComplete())
			{
                state = IDLE;
			}
        break;

		case BUMPER_LEFT:
		    do{
            move(150, BWD, DIST_CM(10), true);
            rotate(150, RIGHT, 90, true); // um 180� nach links drehen
            move(150, FWD, DIST_CM(10), true);
            rotate(150, LEFT, 90, true); // um 180� nach links drehen
            stop();
		    }
		    while(isMovementComplete()!=1);
		break;

        case BUMPER_RIGHT:
            do{
            move(150, BWD, DIST_CM(10), true);
            rotate(150, LEFT, 90, true); // um 180� nach links drehen
            move(150, FWD, DIST_CM(10), true);
            rotate(150, RIGHT, 90, true); // um 180� nach links drehen
            stop();
            }
            while(isMovementComplete()!=1);
		break;

	}
}

int main(void)
{
	initRobotBase();
	mSleep(1000);
	powerON();
	//initial value
    state = MOVE_TO_DESTINATION;


	BUMPERS_setStateChangedHandler(bumperActive);
	while(true)
	{
		stateModel();
		task_RP6System();
		if(isMovementComplete()==1&&state!=IDLE)
            state = MOVE_TO_DESTINATION;
	}
	return 0;
}

/******************** End of file <main.c> ***********************************/

/*****************************************************************************/
/*                                                                           */
/* Assignment: CS 460 Project 1                                              */
/* Author: Dr. Watts                                                         */
/* Date: September 2022                                                      */
/* Modified by:                                                              */
/* Date:                                                                     */
/* Description: This file contains the driver program for Project 1.         */
/*                                                                           */
/*****************************************************************************/

#include <iostream>
#include "SetLimits.h"
#include "SyntacticalAnalyzer.h"

int main (int argc, char * argv[])
{
	if (argc < 2)
	{
		printf ("format: proj1 <filename>\n");
		exit (1);
	}
	//SetLimits ();
	SyntacticalAnalyzer parser (argv[1]);

	return 0;
}

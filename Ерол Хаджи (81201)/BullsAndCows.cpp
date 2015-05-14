//============================================================================
// Name        : BullsAndCows.cpp
// Author      : Erol Hadzhi 81201
// Date        : 11.05.15
//============================================================================

#include "BullsAndCows.h"
#include <stdexcept>
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

void BullsAndCows::init()  // main use to assign null to the pointers
{
	sizeOfContainer = 0;
	numbersContainer = 0;
	numberOfGuesses = 0;
	message = 0;
	win = false;
}

bool isContainerComptable(int* container,int sizeOfContainer)  // checks if an array's first cell!=0 && all cells are different
{
	bool flag=0;
	if( *(container)>=1 && *(container)<=9)
	{
		flag=1;
		for(int i=1;i<sizeOfContainer;i++)
		{
			for(int j=(i-1);j>=0;j--)
			{
				if( *(container+i) == *(container+j) )
					flag=0;
			}
		}
	}
	return flag;
}

void populate_container(int* container,int size)
{
	while( !isContainerComptable(container,size) )
	{
		srand (time(NULL));
		for(int i=0;i<size;i++)
			*(container+i) = rand() % 10;
	}
}

BullsAndCows::BullsAndCows(int size)
{
	init();
	setContainerSize(size);
	int random_container[size];
	populate_container(random_container,size);
	setContainer(random_container);
	message = new char[50];

}

BullsAndCows::BullsAndCows(int* container, int size)
{
	init();
	setContainerSize(size);
	setContainer(container);
	setMessage(0,0);
}

BullsAndCows::~BullsAndCows()
{
	delete[] numbersContainer;
	delete[] message;
}

void BullsAndCows::setContainerSize(int size)
{
	if(size >=2 && size<=4)
		sizeOfContainer=size;
	else
		throw invalid_argument("Size must be 2,3 or 4");
}

void BullsAndCows::setContainer(int* container)
{
	if( isContainerComptable(container,sizeOfContainer) )
		{
			delete[] numbersContainer;
			numbersContainer = new int[sizeOfContainer];
			for(int i=0;i<sizeOfContainer;i++)
			{
				*(numbersContainer+i)=*(container+i);
			}
		}
		else
			throw invalid_argument("Not a comptable container");
}

void BullsAndCows::setMessage(int bulls, int cows)
{
	delete[] message;
	if(bulls == 4)
	{
		win = true;
		char msg[] = "Congratualtions! You made a right guess!";
		message = new char[41];
		strcpy(message,msg);
	}
	else
	{
		char msg[] = "Cows:x    Bulls:y";
		*(msg + 5) = cows+48;
		*(msg +16) = bulls+48;
		message = new char[16];
		strcpy(message,msg);
	}
}

bool BullsAndCows::isInsideContainer(int digit)
{
	for(int i=0;i<sizeOfContainer;i++)
	{
		if( digit== *(numbersContainer+i) )
			return 1;
	}
	return 0;
}

bool BullsAndCows::CowElement(int position, int value)
{
	return (isInsideContainer(value) && (*(numbersContainer+position) != value) );
}

bool BullsAndCows::BullElement(int position, int value)
{
	return (isInsideContainer(value) && (*(numbersContainer+position) == value) );
}

void numberToContainer(int number,int* container,int containerSize)
{
	int i;
	i = (containerSize-1);
	while(number != 0)
	{
		*(container+i)=(number%10);
		i--;
		number/=10;
	}
}

char* BullsAndCows::TryToGuess(int myGuess)
{
	int myGuessContainer[sizeOfContainer],cows=0,bulls=0;

		numberToContainer(myGuess,myGuessContainer,sizeOfContainer);

		if( isContainerComptable(myGuessContainer,sizeOfContainer))
		{
			for(int i=0;i<sizeOfContainer;i++)
			{
				if(BullElement(i,*(myGuessContainer+i)) )
					bulls++;
				if(CowElement(i,*(myGuessContainer+i)) )
					cows++;
			}
		}
		else
			throw invalid_argument("Not a comptable container");
		setMessage(bulls,cows);
		return message;
}

void BullsAndCows::Start()
{
	int myGuess;
	do
	{
		cout<<"Enter your guess : "; cin>>myGuess;
		cout<<TryToGuess(myGuess)<<endl;
	}
	while( win == 0 );
}

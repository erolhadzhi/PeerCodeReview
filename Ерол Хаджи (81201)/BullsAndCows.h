//============================================================================
// Name        : BullsAndCows.h
// Author      : Erol Hadzhi 81201
// Date        : 11.05.15
//============================================================================

#ifndef BULLSANDCOWS_H_
#define BULLSANDCOWS_H_

class BullsAndCows
{
private:
	int sizeOfContainer;  // 2,3,or 4
	int* numbersContainer;
	int numberOfGuesses;
	char* message;
	bool win;
	bool CowElement(int position,int value);
	bool BullElement(int position,int value);
public:
	BullsAndCows(int size);
	BullsAndCows(int* arr,int size);
	~BullsAndCows();

	void init();
	void setContainerSize(int size);
	void setContainer(int* container);
	void setMessage(int bulls,int cows);

	bool isInsideContainer(int digit);
	char* TryToGuess(int myGuess);
	void Start();

};

#endif /* BULLSANDCOWS_H_ */

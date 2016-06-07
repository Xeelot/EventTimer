// EventTracker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>

#define MAX_EVENTS 10

struct Event
{
	Event(time_t time): eventTime(time), next(NULL), prev(NULL) {}
	time_t eventTime;
	Event* next;
	Event* prev;
};

class EventTracker
{
public:
	EventTracker(): head(NULL), tail(NULL), eventCount(0) {}
	~EventTracker() {}
	void recordEvent(time_t hack);
	int checkEvents(time_t secs, time_t hack);
	void printEvents();
private:
	Event* head;
	Event* tail;
	int eventCount;
};

void EventTracker::recordEvent(time_t hack)
{
	// Get the current clock time
	//time_t currentTime;
	//time(&currentTime);
	// Check for a null head pointer
	if (head == NULL)
	{
		// Create the first node
		//head = new Event(currentTime);
		head = new Event(hack);
		tail = head;
		eventCount++;
	}
	else
	{
		// Keep track of current tail, create a new tail, adjust links
		Event* temp = tail;
		//tail->next = new Event(currentTime);
		tail->next = new Event(hack);
		tail = tail->next;
		tail->prev = temp;
		eventCount++;
	}
	// Check for the max amount of events
	if (eventCount > MAX_EVENTS)
	{
		// Step the head node forward, delete the old head node
		Event* temp = head;
		head = head->next;
		delete temp;
		eventCount--;
	}
}

int EventTracker::checkEvents(time_t secs, time_t hack)
{
	// Start by getting the current time
	//time_t currentTime;
	//time(&currentTime);
	// Setup counter for loop
	Event* temp = tail;
	bool continueSearch = true;
	int count = 0;
	// Loop through events until reaching the end or finding a time that is too old
	while ((temp != NULL) && continueSearch)
	{
		continueSearch = (hack - secs) <= temp->eventTime;
		if (continueSearch)
		{
			count++;
		}
		temp = temp->prev;
	}
	return count;
}

void EventTracker::printEvents()
{
	Event* temp = head;
	std::cout << "Events: ";
	while (temp != NULL)
	{
		std::cout << temp->eventTime << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	EventTracker test;
	int retVal = 0;
	test.printEvents();
	retVal = test.checkEvents(3, 10);
	std::cout << "Empty Check: " << retVal << std::endl;
	test.recordEvent(10);
	test.recordEvent(12);
	test.recordEvent(14);
	test.printEvents();
	retVal = test.checkEvents(3, 20);
	std::cout << "Too Far check: " << retVal << std::endl;
	retVal = test.checkEvents(3, 16);
	std::cout << "One check: " << retVal << std::endl;
	retVal = test.checkEvents(3, 17);
	std::cout << "Equal check: " << retVal << std::endl;
	test.recordEvent(16);
	test.recordEvent(18);
	test.recordEvent(20);
	test.recordEvent(22);
	test.recordEvent(24);
	test.recordEvent(26);
	test.recordEvent(28);
	test.recordEvent(30);
	test.printEvents();
	retVal = test.checkEvents(100, 40);
	std::cout << "Negative check: " << retVal << std::endl;

	system("PAUSE");
	return 0;
}


//
// Created by Kim Simoski on 21.11.2022.
//

#ifndef NUPPROJECT_TIMESEGMENTMESSAGE_H
#define NUPPROJECT_TIMESEGMENTMESSAGE_H


#include "SegmentDataMessage.h"

namespace messagesLib {

    //!!!Bezeichner überdenken. Gemeint ist eine Nachricht, die Daten zu einem Ziel (bestimmtes Segment in bestimmter Spalte in bestimmter Reihe eines bestimmten Regals (eines bestimmten Regalpaares) mit benötigter sequentieller Zeit/benötigten Zeiten dahin beinhaltet!
    /*
     * The class TimeSegmentMessage represents a message containing the address and the needed time to get there from a certain point.
     * The class contains the class SegmentDataMessage which represents a message containing the address of a segment (which contains a container of items) of a shelf in the inventory.
     * The class TimeSegmentMessage is used for getting the fastest to reach segment in the inventory in reservation processes, input and output.
     */
    class TimeSegmentMessage {
        // attributes
    private:
        double neededTimeWithoutWaitingInQueueInSeconds;
        int shelfPairNumber; //!!! Kann mit Suchmechanismus in ShelfPair auch wegrationalisiert werden, da sie aus einander hergeleitet werden können!!!

        SegmentDataMessage segmentDataMessage;

        // constructor
    public:
        TimeSegmentMessage(double neededTimeWithoutWaitingInQueueInSeconds, unsigned int shelfPairNumber, unsigned int shelfNumber,
                           unsigned long long int row, unsigned long long int column);

        TimeSegmentMessage(double neededTimeWithoutWaitingInQueueInSeconds, const SegmentDataMessage& segmentDataMessage);

        TimeSegmentMessage();

        // getters and setters
    public:
        [[nodiscard]] double getNeededTimeWithoutWaitingInQueueInSeconds() const;

        [[nodiscard]] unsigned int getShelfPairNumber() const; //!!! Kann mit Suchmechanismus in ShelfPair auch wegrationalisiert werden, da sie aus einander hergeleitet werden können!!!

        unsigned int getShelfNumber();

        unsigned long long int getRow();

        unsigned long long int getColumn();

        SegmentDataMessage getSegmentDataMessage();


        // methods
    public:
        std::string toString();

        void print();
    };
}


#endif //NUPPROJECT_TIMESEGMENTMESSAGE_H

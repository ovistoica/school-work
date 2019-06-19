/* Copyright 2018 <Stoica George-Ovidiu>
  Copy this a baby duck will cry */
#include<string>
#include<sstream>
#include "Deque.h"
#include "Stack.h"

#ifndef ROBOT_H_
#define ROBOT_H_

// Struct for the issued commands
typedef struct Command {
    char type;
    int x;
    int y;
    int nr_boxes;
    int priority;
    int exTime;
    friend std::ostream& operator<<(std::ostream &out, const Command &command);
}Command;

std::ostream& operator<<(std::ostream &out, const Command &command) {
    (command.type == 'G') ? out << "GET " : out << "DROP ";
    out << command.x << " " << command.y << " " << command.nr_boxes;
    return out;
}

class Robot {
    int robotID;
    int nrBoxes;
    Deque<Command> toExecute;  // The Deque for commands to be executed

 public:
    /**
    * Constructors for the Robot class
    */
    Robot(): robotID(-1), nrBoxes(0) {}
    explicit Robot(int ID): robotID(ID), nrBoxes(0) {}

    void setID(int ID) {
        robotID = ID;
    }

    /**
    * Adds a command to the robot's queue in respect to it's priority
    */
    void addCommand(const Command c) {
        (c.priority)? toExecute.push_back(c) : toExecute.push_front(c);
    }

    /**
    * Pop last command inserted in Queue. Used for UNDO
    */
    void popLastCommand(int priority) {
        (priority) ? toExecute.pop_back() : toExecute.pop_front();
    }

    /**
    * Updates the time for every command in the Queue
    */
    void updateTime() {
        unsigned int size = toExecute.getSize();
        while (size) {
            Command temp = toExecute.getFront();
            toExecute.pop_front();
            ++temp.exTime;
            toExecute.push_back(temp);
            --size;
        }
    }


    /**
    * Returns a string with the commands to be executed
    * @return A string with the commands from commandQueue
    */
    void printCommands() {
        if (!toExecute.isEmpty()) {
            std::cout << robotID << ": ";
            toExecute.printDeq();
        }
    }

    /**
    * Execute the last command in the commandQueue
    * @return The command executed or a command with type '0' if there was
    * no command to execute
    */
    Command executeCommand(int **map) {
        if (toExecute.isEmpty()) {
            // Can't return NULL so I return '0' type
            Command no_command;
            no_command.type = '0';
            return no_command;
        }

        Command c = toExecute.getFront();
        toExecute.pop_front();

        if (c.type == 'G') {
            return takeBoxes(&c, map);
        } else {
            return dropBoxes(&c, map);
        }
    }

    /**
    * Execute ADD_GET_BOX command. Helper for executeCommand
    * @return The command executed
    */
    Command takeBoxes(Command *c, int **map) {
        if (c->nr_boxes > map[c->x][c->y]) {
            c->nr_boxes = map[c->x][c->y];
        }
        this->nrBoxes += c->nr_boxes;
        map[c->x][c->y] -= c->nr_boxes;
        return *c;
    }

    /**
    * Execute ADD_DROP_BOX command. Helper for executeCommand
    * @return The command executed
    */
    Command dropBoxes(Command *c, int **map) {
        if (c->nr_boxes > this->nrBoxes) {
            c->nr_boxes = this->nrBoxes;
        }
        this->nrBoxes -= c->nr_boxes;
        map[c->x][c->y] += c->nr_boxes;
        return *c;
    }

    /**
    * Undo the execution of Command c
    */
    void undoCommand(Command *c, int **map) {
        c->exTime = 0;

        // If type is Get, drop that number of boxes and reverse
        if (c->type == 'G') {
            dropBoxes(c, map);
        } else {
            takeBoxes(c, map);
        }

        toExecute.push_front(*c);
    }

    Deque<Command> getCommands() {
        return toExecute;
    }

    /**
    * Returns the number of boxes of this robot
    * @return nrBoxes
    */
    int getBoxes() {
        return nrBoxes;
    }

    /**
    * Checks if there are no commands in the robot's Deque
    * @return True if toExecute is empty, False otherwise
    */
    bool noCommands() {
        return toExecute.isEmpty();
    }
};
#endif  // ROBOT_H_

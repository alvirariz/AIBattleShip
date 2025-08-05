#pragma once
#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <string>
#include "constant.h"

 int Board1[row][column] = { 0 };

class Computer {
private:
    int x, y;              
    char pos;              

   
    bool isValidPlacement(int length) {
        if (pos == 'H') {
            if (y + length - 1 > 10) return false; 
            for (int i = 0; i < length; ++i) {
                if (Board1[x][y + i] == 1) return false; 
            }
        }
        else { 
            if (x + length - 1 >= 10) return false; 
            for (int i = 0; i < length; ++i) {
                if (Board1[x + i][y] == 1) return false; 
            }
        }
        return true;
    }

    
    void placeShip(int length) {
        if (pos == 'H') {
            for (int i = 0; i < length; ++i) {
                Board1[x][y + i] = 1; 
            }
        }
        else { 
            for (int i = 0; i < length; ++i) {
                Board1[x + i][y] = 1; 
            }
        }
    }

    
    void generateRandomPosition() {
        x = rand() % 10;  
        y = rand() % 10;  
        pos = (rand() % 2 == 0) ? 'H' : 'V'; 
    }

    void printBoard() {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                std::cout << Board1[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

public:
  
    Computer() {
        srand(static_cast<unsigned int>(time(NULL))); 

    
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                Board1[i][j] = 0;
            }
        }
    }

   
    ~Computer() {}

   
    void resetgame() {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                Board1[i][j] = 0;
            }
        }
    }

    
    void Update_Coord(int shipIndex) {
    
        int shipLengths[] = { 5, 4, 3, 3, 2 };
        int length = shipLengths[shipIndex - 1];

        int maxAttempts = 100;
        int attempts = 0;

        while (attempts < maxAttempts) {
            generateRandomPosition();

            if (isValidPlacement(length)) {
                placeShip(length);
                break; 
            }
            attempts++;
        }

        if (attempts == maxAttempts) {
            std::cerr << "Failed to place ship \n";
        }

        printBoard(); 
    }
};

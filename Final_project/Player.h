#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "constant.h"
int Board[row][column];
int ship_size[] = { 5,4,3,3,2 };

class Player {
private:
    int x, y;
    std::string Cord;
    char pos;
    bool ai;

public:
    
    Player() {
        Cord = "";
        pos = 'H';
        x = 0;
        y = 0;
        ai = false;
    }

 
    
    ~Player() {}

   
    void resetgame() {
        for (int x = 0; x < column; x++) {
            for (int y = 0; y < row; y++) {
                Board[y][x] = 0;
            }
        }
    }

    
    void Draw(int z, sf::RenderWindow& window) {
        const int cellSize = 40;
        const int offset = 50;

        
        sf::Font font, matrixFont;
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
        matrixFont.loadFromFile("C:/Windows/Fonts/consola.ttf");

        // Background - Matrix-style grid
        sf::RectangleShape backgroundGrid(sf::Vector2f(window.getSize().x, window.getSize().y)); //f means float 
        backgroundGrid.setFillColor(sf::Color(0, 0, 0, 255)); // Black
        window.draw(backgroundGrid);

        // Bright green border around the grid
        sf::RectangleShape gridBorder(sf::Vector2f((column - 2) * cellSize, (row - 2) * cellSize));
        gridBorder.setPosition(offset, offset);
        gridBorder.setFillColor(sf::Color::Transparent);
        gridBorder.setOutlineColor(sf::Color(0, 255, 0)); //green
        gridBorder.setOutlineThickness(2);
        window.draw(gridBorder);

        // Matrix-style green grid overlay
        for (int x = 0; x < window.getSize().x; x += 20) {
            for (int y = 0; y < window.getSize().y; y += 20) {
                sf::Text gridChar("0", matrixFont, 15);
                gridChar.setPosition(x, y);
                gridChar.setFillColor(sf::Color(0, 255, 0, 50)); // Trs green
                window.draw(gridChar);
            }
        }

       
        std::string shipName;
        switch (z + 1) {
        case 1: shipName = "CARRIER_PROTOCOL: 5 BLOCKS"; break;
        case 2: shipName = "BATTLESHIP_SENTINEL: 4 BLOCKS"; break;
        case 3: shipName = "CRUISER_PHANTOM: 3 BLOCKS"; break;
        case 4: shipName = "SUBMARINE_SPECTRE 3 BLOCKS"; break;
        case 5: shipName = "DESTROYER_WRAITH: 2 BLOCKS"; break;
        default: shipName = "UNIDENTIFIED_VESSEL"; break;
        }

        // Placing ship message
        sf::Text placingText("PLACING SHIP:", matrixFont, 20);
        placingText.setPosition(470, 50);
        placingText.setFillColor(sf::Color(0, 255, 0)); // green
        window.draw(placingText);

        // Ship name display
        sf::Text shipNameText(shipName, matrixFont, 20);
        shipNameText.setPosition(470, 80);
        shipNameText.setFillColor(sf::Color(0, 255, 0)); // green
        window.draw(shipNameText);

        // Mission Dialogue Box
        sf::RectangleShape dialogueBox(sf::Vector2f(400, 200));
        dialogueBox.setPosition(450, 120);
        dialogueBox.setFillColor(sf::Color(0, 0, 0, 200)); // black
        dialogueBox.setOutlineColor(sf::Color(0, 255, 0)); // green 
        dialogueBox.setOutlineThickness(2);
        window.draw(dialogueBox);

        // Mission Text
        sf::Text missionText("MISSION DIRECTIVE:", matrixFont, 20);
        missionText.setPosition(470, 140);
        missionText.setFillColor(sf::Color(0, 255, 0)); // green
        window.draw(missionText);

        sf::Text missionDetails(
            "Agent, a rogue admiral has vanished\n"
            "with a fleet of deadly warships.\n"
            "Your mission: track them down,\n"
            "outmaneuver his forces, and stop him.\n"
            "The world is counting on you to act.\n"
            "Deploy smart, strike hard, and win.\n"
            "Show them who truly rules the seas.\n"
            "Good luck, Agent!",
            matrixFont, 14);
        missionDetails.setPosition(470, 170);
        missionDetails.setFillColor(sf::Color(0, 255, 0, 200)); // trs green
        window.draw(missionDetails);

        // Instruction Box
        sf::RectangleShape instructionBox(sf::Vector2f(400, 100));
        instructionBox.setPosition(450, 330);
        instructionBox.setFillColor(sf::Color(0, 0, 0, 200)); // black
        instructionBox.setOutlineColor(sf::Color(0, 255, 0)); //  green 
        instructionBox.setOutlineThickness(2);
        window.draw(instructionBox);

        // Instruction Text
        sf::Text instructions(
            "INSTRUCTIONS:\n"
            "R: Rotate Ship\n"
            "Mouse Click: Select\n"
            "Enter: Confirm Placement",
            matrixFont, 14);
        instructions.setPosition(470, 350);
        instructions.setFillColor(sf::Color(0, 255, 0, 200)); // trs green
        window.draw(instructions);

        // Game board grid
        for (int i = 0; i < row - 2; ++i) {
            for (int j = 0; j < column - 2; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(offset + j * cellSize, offset + i * cellSize);

                // Matrix-style cell coloring
                if (Board[i][j] == 0) {
                    cell.setFillColor(sf::Color(0, 70, 0, 100)); // Drk green
                }
                else if (Board[i][j] == 1) {
                    cell.setFillColor(sf::Color(0, 255, 0, 150)); // brt green
                }
                
                window.draw(cell);
            }
        }
    }


    void AutoGenerateCoord() {
        x = 1 + (rand() % 10);
        y = 1 + (rand() % 10);
        pos = (rand() % 2 == 0) ? 'H' : 'V';
        ai = true;
    }


    void Input_Coord(const int z, sf::RenderWindow& window) {
        bool correct_coord = false;
        bool orientationSelected = false;
        sf::Font font;
        int error_count = 0;

       
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");

        sf::Text userInput("", font, 20);
        userInput.setPosition(50, 550);
        userInput.setFillColor(sf::Color::Cyan);

        sf::Text errorMsg("", font, 20);
        errorMsg.setPosition(50, 500);
        errorMsg.setFillColor(sf::Color::Red);

        const int gridSize = 40;
        const int gridWidth = 10;
        const int gridHeight = 10;
        const sf::Vector2f gridOffset(50, 50);

        sf::Vector2i hoveredCell(-1, -1);

        while (window.isOpen() && (!correct_coord || !orientationSelected)) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (!correct_coord) {
                    // Handle mouse hover
                    if (event.type == sf::Event::MouseMoved) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        int gridX = (mousePos.y - static_cast<int>(gridOffset.y)) / gridSize;
                        int gridY = (mousePos.x - static_cast<int>(gridOffset.x)) / gridSize;

                        if (gridX >= 0 && gridX < gridHeight && gridY >= 0 && gridY < gridWidth) {
                            hoveredCell = sf::Vector2i(gridX, gridY);
                        }
                        else {
                            hoveredCell = sf::Vector2i(-1, -1);
                        }
                    }

                    // Handle mouse clicks
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left && hoveredCell.x != -1) {
                            x = hoveredCell.x;
                            y = hoveredCell.y;
                            Cord = std::string(1, 'A' + x) + std::to_string(y);
                            correct_coord = true;
                            std::cout << "Clicked on grid cell: " << Cord << std::endl;
                        }
                    }
                }
                else if (!orientationSelected) {
                    // Handle orientation selection
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                        pos = (pos == 'H') ? 'V' : 'H';
                        std::cout << "Orientation switched to: " << pos << std::endl;
                    }
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                        // Check for placement validity
                        if ((pos == 'H' && y > gridWidth - ship_size[z]) || (pos == 'V' && x > gridHeight - ship_size[z])) {
                            orientationSelected = false;
                            errorMsg.setString("Invalid placement! Adjust position or orientation.");
                            correct_coord = false;
                            std::cout << "Invalid placement for selected orientation.\n";
                        }
                        else {
                            orientationSelected = true;
                            errorMsg.setString("");
                            std::cout << pos << std::endl;
                        }
                    }
                }
            }

            window.clear();
            Draw(z, window);
           
            for (int i = 0; i < gridWidth; ++i) {
                for (int j = 0; j < gridHeight; ++j) {
                    sf::RectangleShape cell(sf::Vector2f(gridSize - 1, gridSize - 1));
                    cell.setPosition(gridOffset.x + j * gridSize, gridOffset.y + i * gridSize);

                    if (hoveredCell == sf::Vector2i(i, j)) {
                        cell.setFillColor(sf::Color(100, 100, 255, 128)); // Hgl hover
                    }
                    else {
                        cell.setFillColor(sf::Color(0, 0, 0, 0)); 
                    }

                    if (correct_coord && pos == 'H' && i == x && j >= y && j < y + ship_size[z]) {
                        cell.setFillColor(sf::Color(255, 0, 0, 128)); // Highlight horizontal
                    }
                    else if (correct_coord && pos == 'V' && j == y && i >= x && i < x + ship_size[z]) {
                        cell.setFillColor(sf::Color(255, 0, 0, 128)); // Highlight vertical
                    }

                    cell.setOutlineThickness(1);
                    cell.setOutlineColor(sf::Color::Black);
                    window.draw(cell);
                }
            }

            window.draw(userInput);
            window.draw(errorMsg);
            window.display();
        }
    }

    
    void Update_Coord(int i, sf::RenderWindow& window) {
        bool repeat_input = false;

        while (true) {
            if (Board[x][y] == 1) { // checking if first coordinate is free for ship
                if (ai)
                    AutoGenerateCoord();
                else {
                    Input_Coord(i, window);
                }
            }
            break;
        }


        while (true) { // It will stop if it's okay to put ship into board
            if (pos == 'V') { // VERTICAL POSITION **************************************************************
                if (i == 1) { // first ship (which is 5 ship long)
                    if (x < 6) { // Ship wouldn't pass a bottom border
                        if (Board[x + 1][y] == 0 && Board[x + 2][y] == 0 && Board[x + 3][y] == 0 && Board[x + 4][y] == 0) { //Checking if 5 long ship coordinates are free for ship
                            Board[x][y] = 1;
                            Board[x + 1][y] = 1;
                            Board[x + 2][y] = 1;
                            Board[x + 3][y] = 1;
                            Board[x + 4][y] = 1;
                            break;
                        }
                        else {
                            repeat_input = true;
                        }
                    }
                    else {//ship passes a border
                        repeat_input = true;
                    }
                }
                else if (i == 2) {
                    if (x < 7) { // Ship wouldn't pass a bottom border
                        if (Board[x + 1][y] == 0 && Board[x + 2][y] == 0 && Board[x + 3][y] == 0) { //Checking if 3 long ship coordinates are free for ship
                            Board[x][y] = 1;
                            Board[x + 1][y] = 1;
                            Board[x + 2][y] = 1;
                            Board[x + 3][y] = 1;
                            break;
                        }
                        else {
                            repeat_input = true;
                        }
                    }
                    else {
                        repeat_input = true;
                    }
                }
                else if (i == 3 || i == 4) { // 3 ship long
                    if (x < 8) { // Ship wouldn't pass a bottom border
                        if (Board[x + 1][y] == 0 && Board[x + 2][y] == 0) { //Checking if 3 long ship coordinates are free for ship
                            Board[x][y] = 1;
                            Board[x + 1][y] = 1;
                            Board[x + 2][y] = 1;
                            break;
                        }
                        else {
                            repeat_input = true;
                        }
                    }
                    else {
                        repeat_input = true;
                    }
                }
                else if (i == 5) { // 2 ship long
                    if (x < 9) { // Ship wouldn't pass a bottom border
                        if (Board[x + 1][y] == 0) { //Checking if 3 long ship coordinates are free for ship
                            Board[x][y] = 1;
                            Board[x + 1][y] = 1;
                            break;
                        }
                        else {
                            repeat_input = true;
                        }
                    }
                    else {
                        repeat_input = true;
                    }
                }

            }
            else if (pos == 'H') { // HORIZONTAL POSITION **************************************************************
                if (i == 1) {
                    if (y < 6) { // Ship wouldn't pass a RIGHT border
                        if (Board[x][y + 1] == 0 && Board[x][y + 2] == 0 && Board[x][y + 3] == 0 && Board[x][y + 4] == 0) { //Checking if 4 long ship coordinates are free for ship
                            Board[x][y] = 1;
                            Board[x][y + 1] = 1;
                            Board[x][y + 2] = 1;
                            Board[x][y + 3] = 1;
                            Board[x][y + 4] = 1;
                            break;
                        }
                        else {
                            repeat_input = true;
                        }
                    }
                    else { //ship passes a border
                        repeat_input = true;
                    }
                }
                else if (i == 2) { //4 ship
                    if (y < 7) { // Ship wouldn't pass a RIGHT border
                        if (Board[x][y + 1] == 0 && Board[x][y + 2] == 0 && Board[x][y + 3] == 0) { //Checking if 3 long ship coordinates are free for ship
                            Board[x][y] = 1;
                            Board[x][y + 1] = 1;
                            Board[x][y + 2] = 1;
                            Board[x][y + 3] = 1;
                            break;
                        }
                        else {
                            repeat_input = true;
                        }
                    }
                    else {
                        repeat_input = true;
                    }
                }

                else if (i == 3 || i == 4) {// 3 ship
                    if (y < 8) { // Ship wouldn't pass a RIGHT border
                        if (Board[x][y + 1] == 0 && Board[x][y + 2] == 0) { //Checking if 3 long ship coordinates are free for ship
                            Board[x][y] = 1;
                            Board[x][y + 1] = 1;
                            Board[x][y + 2] = 1;
                            break;

                        }
                        else {
                            repeat_input = true;
                        }

                    }
                    else {
                        repeat_input = true;
                    }
                }
                else if (i == 5) {//
                    if (y < 9) { // Ship wouldn't pass a RIGHT border
                        if (Board[x][y + 1] == 0) { //Checking if 2 long ship coordinates are free for ship
                            Board[x][y] = 1;
                            Board[x][y + 1] = 1;
                            break;
                        }
                        else {
                            repeat_input = true;
                        }
                    }
                    else {
                        repeat_input = true;
                    }
                }
            }
            if (repeat_input) {
                if (ai)
                    AutoGenerateCoord();
                else {
                    Input_Coord(i, window);
                }
            }
        }
    }
};
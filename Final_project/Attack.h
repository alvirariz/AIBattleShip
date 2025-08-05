#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>


extern int Count_Player = 0;
extern int Count_Computer = 0;
extern int Score_Computer = 100;
extern int Score_Player = 100;

class Attack {
private:
    int x, y;            
    std::string Cord;    

    sf::Color GetCellColor(int value, bool isComputerBoard = false) {
        switch (value) {
        case 0: return sf::Color(0, 50, 100, 100); // Water
        case 3: return sf::Color(255, 0, 0, 150);  // Hit
        case 4: return sf::Color(100, 100, 100, 150); // Miss
        case 1: return isComputerBoard ? sf::Color(0, 50, 100, 100) : sf::Color(0, 255, 0, 150); // Ship
        default: return sf::Color::Black; 
        }
    }

public:
    Attack() : x(0), y(0), Cord("") {}

    Attack(int a, int b, std::string c) : x(a), y(b), Cord(c) {}

    ~Attack() {}

    void AutoGenerateCoord() {
        x = 1 + (rand() % 10);
        y = 1 + (rand() % 10);
    }

    void resetgame() {
        Count_Player = 0;
        Count_Computer = 0;
        Score_Computer = 100;
        Score_Player = 100;
    }

    void InputCoord(sf::RenderWindow& window) {
        sf::Font font;
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Error loading font" << std::endl;
            return;
        }

        bool correctCoord = false;

        sf::Text prompt("Click on a grid cell to select coordinates:", font, 20);
        prompt.setFillColor(sf::Color::White);
        prompt.setPosition(10, 10);

        // Grid properties
        const int gridSize = 30;  
        const int gridWidth = 10; 
        const int gridHeight = 10; 
        const sf::Vector2f gridOffset(440, 160); 

        sf::RectangleShape hoverCell(sf::Vector2f(gridSize - 2, gridSize - 2)); 
        hoverCell.setFillColor(sf::Color(255, 0, 0, 128)); // red
        hoverCell.setOutlineThickness(1);
        hoverCell.setOutlineColor(sf::Color::White);

        while (!correctCoord && window.isOpen()) {
            sf::Event event;
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

            int hoverX = -1, hoverY = -1; 

            // mouse is over
            if (worldPos.x >= gridOffset.x && worldPos.y >= gridOffset.y) {
                hoverY = (worldPos.y - gridOffset.y) / gridSize; 
                hoverX = (worldPos.x - gridOffset.x) / gridSize; 
               /* std::cout << hoverX << std::endl;*/

                // hover is within boundary
                if (hoverX < 0 || hoverX >= gridWidth || hoverY < 0 || hoverY >= gridHeight) {
                    hoverX = hoverY = -1; 
                }
            }

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                   
                    if (hoverX >= 0 && hoverX < gridWidth && hoverY >= 0 && hoverY < gridHeight) { // validation
                        y = hoverX;                      
                        x = hoverY;                      
                        Cord = std::to_string(x) + "," + std::to_string(y); // Store coordinates as "x,y"
                        correctCoord = true;
                    }
                }
            }

            
            window.clear();
            window.draw(prompt);

            // grid
            for (int i = 0; i < gridWidth; ++i) {
                for (int j = 0; j < gridHeight; ++j) {
                    sf::RectangleShape cell(sf::Vector2f(gridSize - 1, gridSize - 1));
                    cell.setPosition(gridOffset.x + i * gridSize, gridOffset.y + j * gridSize);
                    cell.setFillColor(sf::Color(0, 0, 0, 0)); // Transparent fill
                    cell.setOutlineThickness(0);
                    cell.setOutlineColor(sf::Color::Black);
                    window.draw(cell);
                }
            }

 

            DrawShooting(window);
            window.display();
        }

        if (correctCoord) {
            std::cout << "Selected coordinates: " << Cord << " (X: " << x << ", Y: " << y << ")" << std::endl;
        }
    }

    void DrawShooting(sf::RenderWindow& window) {
        sf::Font font;
        sf::Font matrixFont;
        const int cellSize = 30;
        const int gridSize = 10;
        const int gridSpacing = 70;
        const int offsetXPlayer = 70;
        const int offsetXComputer = offsetXPlayer + gridSize * cellSize + gridSpacing;
        const int offsetY = 160;

        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
        matrixFont.loadFromFile("C:/Windows/Fonts/consola.ttf"); 

        // Background - Matrix-style grid
        sf::RectangleShape backgroundGrid(sf::Vector2f(window.getSize().x, window.getSize().y));
        backgroundGrid.setFillColor(sf::Color(0, 0, 0, 255)); // Black 
        window.draw(backgroundGrid);

        sf::RectangleShape dialogueBox(sf::Vector2f(800, 80));
        dialogueBox.setPosition(window.getSize().x / 2 - 400, 500);
        dialogueBox.setFillColor(sf::Color(0, 0, 0, 200)); // Translucent black
        dialogueBox.setOutlineColor(sf::Color(0, 255, 255)); // Cyan 
        dialogueBox.setOutlineThickness(2);
        window.draw(dialogueBox);

        // Dialogue Text
        sf::Text dialogueText("Attention, Now you must defeat the comp-I mean the ROGUE ADMIRAL SHIPS!\nAvenge your fleet and show no mercy! *winks dramatically*", font, 18);
        dialogueText.setPosition(dialogueBox.getPosition().x + 20, dialogueBox.getPosition().y + 10);
        dialogueText.setFillColor(sf::Color(0, 255, 255)); // Cyan 
        window.draw(dialogueText);

     
        for (int x = 0; x < window.getSize().x; x += 20) {
            for (int y = 0; y < window.getSize().y; y += 20) {
                sf::Text gridChar("0", matrixFont, 15);
                gridChar.setPosition(x, y);
                gridChar.setFillColor(sf::Color(0, 255, 0, 50)); // Trsprt green
                window.draw(gridChar);
            }
        }

        
        sf::RectangleShape gridBorder(sf::Vector2f(gridSize * cellSize, gridSize * cellSize));
        gridBorder.setFillColor(sf::Color::Transparent);
        gridBorder.setOutlineColor(sf::Color(0, 255, 0)); // green
        gridBorder.setOutlineThickness(2);

        
        gridBorder.setPosition(offsetXPlayer, offsetY);
        window.draw(gridBorder);

        
        gridBorder.setPosition(offsetXComputer, offsetY);
        window.draw(gridBorder);


        sf::RectangleShape scoreBox(sf::Vector2f(800, 50));
        scoreBox.setPosition(window.getSize().x / 2 - 400, 20);
        scoreBox.setFillColor(sf::Color(0, 0, 0, 200)); // Trsp black
        scoreBox.setOutlineColor(sf::Color(0, 255, 0)); // green 
        scoreBox.setOutlineThickness(2);
        window.draw(scoreBox);


        sf::Text playerScoreText("Player Score: " + std::to_string(Score_Player), matrixFont, 20);
        playerScoreText.setPosition(scoreBox.getPosition().x + 20, scoreBox.getPosition().y + 10);
        playerScoreText.setFillColor(sf::Color(0, 255, 0)); // green
        window.draw(playerScoreText);

        sf::Text computerScoreText("Admiral Score:" + std::to_string(Score_Computer), matrixFont, 20);
        computerScoreText.setPosition(scoreBox.getPosition().x + 420, scoreBox.getPosition().y + 10);
        computerScoreText.setFillColor(sf::Color(0, 255, 0)); // green
        window.draw(computerScoreText);

        
        for (int i = 0; i < gridSize; ++i) {
            sf::Text columnLabel(std::to_string(i), matrixFont, 20);
            columnLabel.setFillColor(sf::Color(0, 255, 0)); // green
            columnLabel.setPosition(offsetXPlayer + i * cellSize + cellSize / 2 - 5, offsetY - 30);
            window.draw(columnLabel);
            columnLabel.setPosition(offsetXComputer + i * cellSize + cellSize / 2 - 5, offsetY - 30);
            window.draw(columnLabel);
        }

        char letter = 'A';
        for (int i = 0; i < gridSize; ++i) {
            
            sf::Text rowLabel(std::string(1, letter), matrixFont, 20);
            rowLabel.setFillColor(sf::Color(0, 255, 0)); // green
            rowLabel.setPosition(offsetXPlayer - 30, offsetY + i * cellSize + cellSize / 2 - 10);
            window.draw(rowLabel);
            rowLabel.setPosition(offsetXComputer - 30, offsetY + i * cellSize + cellSize / 2 - 10);
            window.draw(rowLabel);

           
            for (int j = 0; j < gridSize; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(offsetXPlayer + j * cellSize, offsetY + i * cellSize);
                cell.setFillColor(GetCellColor(Board[i][j]));
                window.draw(cell);
            }

            // Draw cells for Computer grid
            for (int j = 0; j < gridSize; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(offsetXComputer + j * cellSize, offsetY + i * cellSize);
                cell.setFillColor(GetCellColor(Board1[i][j], true));
                window.draw(cell);
            }

            ++letter;
        }
    }

    void UpdatePlayerGrid() {
        srand((unsigned int)time(NULL)); // Seed

        static int originX = -1, originY = -1;
        static int exploreX = -1, exploreY = -1;
        static int currentDirection = 0;        
        static bool exploring = false;          

        bool attacked = false; 

        while (!attacked) {
            if (!exploring) { 
               
                x = rand() % 10; 
                y = rand() % 10; 
            }
            else {
                // Exploration logic
                switch (currentDirection) {
                case 0: exploreX--; break; // Up
                case 1: exploreY++; break; // Right
                case 2: exploreX++; break; // Down
                case 3: exploreY--; break; // Left
                }

                x = exploreX;
                y = exploreY;
            }

            
            if (x < 0 || x >= 10 || y < 0 || y >= 10 || Board[x][y] == 3 || Board[x][y] == 4) {
                if (exploring) {
                    
                    currentDirection = (currentDirection + 1) % 4;

                    // Reset
                    if (currentDirection == 0) {
                        exploring = false;
                        originX = -1;
                        originY = -1;
                    }

                   
                    exploreX = originX;
                    exploreY = originY;
                }
                continue;
            }

            
            if (Board[x][y] == 1) { //Hit
                Board[x][y] = 3; 
                Count_Computer++;
                attacked = true;

                if (!exploring) {
         
                    originX = x;
                    originY = y;
                    exploreX = x;
                    exploreY = y;
                    exploring = true;
                }
                else {
                   
                    exploreX = x;
                    exploreY = y;
                }
            }
            else if (Board[x][y] == 0) { // Miss
                Board[x][y] = 4; 
                Score_Computer--;
                attacked = true;

                if (exploring) {
                   
                    currentDirection = (currentDirection + 1) % 4;

                    
                    if (currentDirection == 0) {
                        exploring = false;
                        originX = -1;
                        originY = -1;
                    }

                   
                    exploreX = originX;
                    exploreY = originY;
                }
            }
        }
    }

    void UpdateComputerGrid(sf::RenderWindow& window) {
        while (true) {
            if (Board1[x][y] != 3 && Board1[x][y] != 4) {
                if (Board1[x][y] == 1) {
                    Board1[x][y] = 3; // Hit
                 
                    Count_Player++;
                }
                else if (Board1[x][y] == 0) {
                    Board1[x][y] = 4; // Miss
                    Score_Player--;
                }
                break;
            }
            else {
                InputCoord(window);
               
                //AutoGenerateCoord();
            }
        }
    }
};

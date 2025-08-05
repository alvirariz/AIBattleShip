#include <iostream>
#include <String>
#include "Player.h"
#include "Computer.h"
#include "Attack.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>

using namespace std;
const int numofships = 5;
Player Player1[numofships];
Computer player2[numofships];
Attack turn[100];

void topthree(string& name);
void Game(sf::RenderWindow& window, sf::Font& font);
void leaderboard(sf::RenderWindow& window, sf::Font& font);

void InitializeShips(sf::RenderWindow& window, sf::Font& font) {

    for (int shipNum = 0; shipNum < numofships; ++shipNum) {
        Player1[shipNum].Draw(shipNum, window); 
        Player1[shipNum].Input_Coord(shipNum, window); 
        //Player1[shipNum].AutoGenerateCoord();     // Ease of code innit, so ohio!
        Player1[shipNum].Update_Coord(shipNum + 1, window);
        player2[shipNum].Update_Coord(shipNum + 1);

        
        sf::sleep(sf::seconds(0.5f));
    }
}
void GameLoop(sf::RenderWindow& window, sf::Font& font) {
    int turnCount = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        turn[turnCount].DrawShooting(window);
        turn[turnCount].InputCoord(window);    
        //turn[turnCount].AutoGenerateCoord();  // this is for debugging and ease of coding rgfdghrhgdfjdx!!!
        turn[turnCount].UpdateComputerGrid(window); 
        turn[turnCount].UpdatePlayerGrid();  

        //win condition
        if (Count_Computer == 17 || Count_Player == 17) {
            break;
        }

      
        window.display();

       
        turnCount++;
    }
}
void EndGame(sf::RenderWindow& window, sf::Font& font) {
   
    std::vector<sf::Text> backgroundGridTexts;
    for (int x = 0; x < window.getSize().x; x += 20) {
        for (int y = 0; y < window.getSize().y; y += 20) {
            sf::Text gridChar("0", font, 15);
            gridChar.setPosition(x, y);
            gridChar.setFillColor(sf::Color(0, 255, 0, 50)); // green
            backgroundGridTexts.push_back(gridChar);
        }
    }

    
    sf::RectangleShape endTextBackground;

    
    sf::Text endText;
    endText.setFont(font);
    endText.setCharacterSize(20);
    endText.setFillColor(sf::Color(0, 255, 0)); // green

    sf::Text instructionText;
    instructionText.setFont(font);
    instructionText.setCharacterSize(25);
    instructionText.setFillColor(sf::Color(0, 200, 0)); // dark green

    
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color(0, 255, 0)); // green
    inputText.setPosition(50, 300);

    std::string playerName;

    // Determine the winner
    if (Count_Computer == 17 && Count_Player < 17) {
        endText.setString("Mission Failed, Agent.\nThe rogue admiral has escaped.\nYour forces were outmaneuvered, and the seas remain in chaos.\nBut this isn't the end. Regroup, learn, and try again.\nThe world still needs you.");
        instructionText.setString("TOTAL COMPROMISE: " + std::to_string(Score_Computer) + " UNITS");
        endText.setFillColor(sf::Color::Red);
    }
    else if (Count_Player == 17) {
        endText.setString("Mission Accomplished, Agent!\nThe rogue admiral has been stopped.\nYour tactical brilliance has saved the seas.\nThe world owes you a debt of gratitude.\nVictory is yours!");
        instructionText.setString("press any key to continue");
    }

    
    endText.setPosition(
        window.getSize().x / 2 - endText.getGlobalBounds().width / 2, 60);

   
    endTextBackground.setSize(sf::Vector2f(
        endText.getGlobalBounds().width + 40,
        endText.getGlobalBounds().height + 60
    ));
    endTextBackground.setPosition(
        window.getSize().x / 2 - endTextBackground.getGlobalBounds().width / 2,
        40
    );
    endTextBackground.setFillColor(sf::Color(0, 50, 0, 100)); // Semi-transparent bright green
    endTextBackground.setOutlineThickness(2);
    endTextBackground.setOutlineColor(sf::Color(0, 255, 0, 255)); // Bright green outline

   
    instructionText.setPosition(
        window.getSize().x / 2 - instructionText.getGlobalBounds().width / 2, 300);

    
    bool playerWon = (Count_Player == 17);
    bool nameEntered = !playerWon;

    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            
            if (playerWon && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !playerName.empty()) {
                    // Handle backspace
                    playerName.pop_back();
                }
                else if (event.text.unicode == '\r') {
                    // Handle enter key
                    nameEntered = true;
                }
                else if (event.text.unicode < 128 && playerName.size() < 20) {
                    // Append character
                    playerName += static_cast<char>(event.text.unicode);
                }
                inputText.setString("ENTER OPERATOR NAME: " + playerName);
                inputText.setPosition(
                    window.getSize().x / 2 - inputText.getGlobalBounds().width / 2,
                    400
                );
            }
        }

      
        window.clear(sf::Color(0, 10, 0)); // blackish greeen

        
        for (const auto& gridChar : backgroundGridTexts) {
            window.draw(gridChar);
        }

        
        window.draw(endTextBackground);

        
        window.draw(endText);
        window.draw(instructionText);

        if (playerWon && !nameEntered) {
            window.draw(inputText);
        }

        window.display();

        
        if (nameEntered || (!playerWon && window.waitEvent(event))) {
            break;
        }
    }

    
    if (playerWon && nameEntered) {
        topthree(playerName); 
    }

    
    sf::sleep(sf::seconds(5.0f));
}

void Menu(sf::RenderWindow& window, sf::Font& font) {
    sf::Font matrixFont;
    matrixFont.loadFromFile("C:/Windows/Fonts/consola.ttf");

    // Background - Matrix-style grid
    sf::RectangleShape backgroundGrid(sf::Vector2f(window.getSize().x, window.getSize().y));
    backgroundGrid.setFillColor(sf::Color(0, 0, 0, 255)); // Black

    // Create matrix-style background overlay
    std::vector<sf::Text> backgroundGridTexts;
    for (int x = 0; x < window.getSize().x; x += 20) {
        for (int y = 0; y < window.getSize().y; y += 20) {
            sf::Text gridChar("0", matrixFont, 15);
            gridChar.setPosition(x, y);
            gridChar.setFillColor(sf::Color(0, 255, 0, 50)); // Trsprt green
            backgroundGridTexts.push_back(gridChar);
        }
    }

    // Title with matrix-style effect
    sf::Text title("BATTLESHIP", font, 60);
    title.setFillColor(sf::Color(0, 255, 0)); // green
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 50);

    // Create menu options with matrix styling
    sf::Text playOption("PLAY", matrixFont, 40);
    playOption.setFillColor(sf::Color(0, 255, 0)); // green
    playOption.setPosition(800 / 2 - playOption.getGlobalBounds().width / 2, 200);

    sf::Text leaderboardOption("LEADERBOARD", matrixFont, 40);
    leaderboardOption.setFillColor(sf::Color(0, 255, 0)); //  green
    leaderboardOption.setPosition(800 / 2 - leaderboardOption.getGlobalBounds().width / 2, 300);

    // Create rectangles (boxes) around text
    sf::RectangleShape playBox(sf::Vector2f(playOption.getGlobalBounds().width + 30, playOption.getGlobalBounds().height + 30));
    playBox.setPosition(playOption.getPosition().x - 10, playOption.getPosition().y - 5);
    playBox.setFillColor(sf::Color::Transparent);
    playBox.setOutlineColor(sf::Color(0, 255, 0)); // Green 
    playBox.setOutlineThickness(2);

    sf::RectangleShape leaderboardBox(sf::Vector2f(leaderboardOption.getGlobalBounds().width + 30, leaderboardOption.getGlobalBounds().height + 30));
    leaderboardBox.setPosition(leaderboardOption.getPosition().x - 10, leaderboardOption.getPosition().y - 5);
    leaderboardBox.setFillColor(sf::Color::Transparent);
    leaderboardBox.setOutlineColor(sf::Color(0, 255, 0)); // Green
    leaderboardBox.setOutlineThickness(2);

    // Create glowing boxes (slightly larger, transparent rectangles)
    sf::RectangleShape playBoxGlow(sf::Vector2f(playBox.getSize().x + 10, playBox.getSize().y + 10)); // Larger than the normal box
    playBoxGlow.setPosition(playBox.getPosition().x - 5, playBox.getPosition().y - 5);
    playBoxGlow.setFillColor(sf::Color(100, 255, 100, 100)); // light green
    playBoxGlow.setOutlineColor(sf::Color(100, 255, 100, 150)); // Glow color
    playBoxGlow.setOutlineThickness(3);

    sf::RectangleShape leaderboardBoxGlow(sf::Vector2f(leaderboardBox.getSize().x + 10, leaderboardBox.getSize().y + 10)); // Larger than the normal box
    leaderboardBoxGlow.setPosition(leaderboardBox.getPosition().x - 5, leaderboardBox.getPosition().y - 5);
    leaderboardBoxGlow.setFillColor(sf::Color(100, 255, 100, 100)); // light green
    leaderboardBoxGlow.setOutlineColor(sf::Color(100, 255, 100, 150)); // Glow color
    leaderboardBoxGlow.setOutlineThickness(3);

    sf::Text playOptionGlow = playOption;
    playOptionGlow.setFillColor(sf::Color(100, 255, 100, 100)); // green glow
    playOptionGlow.setPosition(playOption.getPosition());

    sf::Text leaderboardOptionGlow = leaderboardOption;
    leaderboardOptionGlow.setFillColor(sf::Color(100, 255, 100, 100)); //green glow
    leaderboardOptionGlow.setPosition(leaderboardOption.getPosition());

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); 


            } 

            
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

            // Reset colors
            playOption.setFillColor(sf::Color(0, 255, 0));
            leaderboardOption.setFillColor(sf::Color(0, 255, 0));

            //highlighting while moving the cursor
            if (playOption.getGlobalBounds().contains(mousePosF)) {
                playOption.setFillColor(sf::Color::White);
            }
            if (leaderboardOption.getGlobalBounds().contains(mousePosF)) {
                leaderboardOption.setFillColor(sf::Color::White);

            }

            
            if (event.type == sf::Event::MouseButtonPressed) {
                if (playOption.getGlobalBounds().contains(mousePosF)) {
                    std::cout << "Play selected" << std::endl;
                    Game(window, font);
                    

                }
                else if (leaderboardOption.getGlobalBounds().contains(mousePosF)) {
                    std::cout << "Leaderboard selected" << std::endl;
                    leaderboard(window, font);
                   

                }
            }
        }

       
        window.clear(sf::Color::Black);

   
        window.draw(backgroundGrid);
        for (const auto& text : backgroundGridTexts) {
            window.draw(text);
        }

       
        window.draw(playBoxGlow);
        window.draw(leaderboardBoxGlow);

        
        window.draw(playOptionGlow);
        window.draw(leaderboardOptionGlow);

       
        window.draw(title);
        window.draw(playOption);
        window.draw(leaderboardOption);

       
        window.draw(playBox);
        window.draw(leaderboardBox);

        window.display();
        Player1->resetgame();
        player2->resetgame();
        turn->resetgame();
    }
}


void leaderboard(sf::RenderWindow& window, sf::Font& font) {
    std::ifstream file("ScoreBoard.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening ScoreBoard.txt" << std::endl;
        return;
    }

    // Read scores into a vector
    std::vector<std::pair<std::string, int>> scores;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int score;
        if (iss >> score >> name) {
            scores.emplace_back(name, score);
        }
    }
    file.close();

   
    std::sort(scores.begin(), scores.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        });

    // background
    std::vector<sf::Text> backgroundGridTexts;
    for (int x = 0; x < window.getSize().x; x += 20) {
        for (int y = 0; y < window.getSize().y; y += 20) {
            sf::Text gridChar("0", font, 15);
            gridChar.setPosition(x, y);
            gridChar.setFillColor(sf::Color(0, 255, 0, 50)); // Translucent green
            backgroundGridTexts.push_back(gridChar);
        }
    }

    
    window.clear(sf::Color(0, 10, 0)); // Almost black with a hint of green

 
    for (const auto& gridChar : backgroundGridTexts) {
        window.draw(gridChar);
    }

   
    sf::Text title("LEADERBOARD", font, 60);
    title.setFillColor(sf::Color(0, 255, 0)); // Bright green
    title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 20); // centralises the text

 
    sf::Text titleOutline = title;
    titleOutline.setFillColor(sf::Color(0, 100, 0, 150)); // Darker green outline
    titleOutline.move(2, 2);

    window.draw(titleOutline);
    window.draw(title);

    
    float startY = 150.0f;
    for (size_t i = 0; i < scores.size() && i < 3; ++i) {
        sf::Text entry;
        entry.setFont(font);
        entry.setCharacterSize(35);

        sf::Color rankColors[] = {
            sf::Color(0, 255, 0),// - Bright Green
            sf::Color(0, 200, 100),//- Slightly darker green
            sf::Color(0, 150, 50), //- Even darker green
        };

        entry.setFillColor(rankColors[i]);

        // Rank formatting with matrix-like effect
        std::string rankString = "[" + std::to_string(i + 1) + "] " +
            scores[i].first + " : " +
            std::to_string(scores[i].second);
        entry.setString(rankString);

        
        entry.setPosition(window.getSize().x / 2 - entry.getGlobalBounds().width / 2, startY + i * 50);
        window.draw(entry);
    }

    
    sf::Text backText("PRESS [ESC] TO RETURN", font, 25);
    backText.setFillColor(sf::Color(0, 180, 0)); // green
    backText.setPosition(window.getSize().x / 2 - backText.getGlobalBounds().width / 2, startY + 250);
    window.draw(backText);

    window.display();

    
    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            break;
        }
    }
}
void topthree(string& name) {

    std::ifstream file("ScoreBoard.txt");

    // Read scores into a vector
    std::vector<std::pair<std::string, int>> scores;
    std::string line;
    while (std::getline(file, line)) { // reads the whole first line basically 
        std::istringstream iss(line); // this helps in breaking the string 
        std::string name;
        int score;
        if (iss >> score >> name) {
            scores.emplace_back(name, score);
        }
    }
    file.close();

    
    std::sort(scores.begin(), scores.end(), [](auto& a, auto& b) {
        return a.second > b.second; });

    if (scores.size() < 3 || Score_Player > scores.back().second) {
        if (scores.size() == 3) {
            scores.pop_back(); // Rmv the lwst scr if alr 3
        }
        scores.emplace_back(name, Score_Player);

     
        std::sort(scores.begin(), scores.end(), [](auto& a, auto& b) {
            return a.second > b.second;});

      
        std::ofstream outFile("ScoreBoard.txt");
        for (int i = 0; i < 3 && i < scores.size(); ++i) {
            outFile << scores[i].second << " " << scores[i].first << "\n";
        }
        outFile.close();
    }
}


void Game(sf::RenderWindow& window, sf::Font& font) {
    InitializeShips(window, font);
    GameLoop(window, font);
    EndGame(window, font);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Battleship Game");
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    
    Menu(window, font);


    return 0;


}



/*
 * rain.cpp
 * Produces something similar to the "matrix rain" code effect seen in the movies
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

void run(sf::Text**& arr, const int& arrNum, const int& characters, 
    const sf::Font& font, sf::RenderWindow& window, char n[], const int& height, 
    const int& width);

int main()
{
    //load the custom font, exit if can't
    sf::Font font;
    if(!font.loadFromFile("matrix_code.ttf"))
    {
        std::cout << "Can't load the font" << std::endl;
        return -1;
    } 
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Matrix Rain"); 
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Matrix Rain", sf::Style::Fullscreen);
    sf::VideoMode current = sf::VideoMode::getDesktopMode();

    int height = current.height;        //height of the window
    int width = current.width;          //width of the window
    int charSizeRange = 15;             //the range of sizes for the lines
    int charSizeBase = 15;              //avg size of lines - charSizeRange/2
    sf::Time t = sf::seconds(0.12f);    //how fast the characters scroll down
    int space = 30;                     //space between characters
    int characters = 30;                //number of characters per line
    int arrNum = current.width/15;      //number of lines to display on the screen
    sf::Text** arr = new sf::Text*[arrNum]; //array to hold the lines
    
    //ASCII chars to use from the custom font
    //50, 54, 57, 97-125
    char n[31];
    for(int i = 0, j = 97; j <= 125; ++i, ++j)
        n[i] = j;
    n[28] = 50;
    n[29] = 54;
    n[30] = 57; 

    //create array of arrays of sf::Text
    for(int i = 0; i < arrNum; ++i)
    {   
        arr[i] = new sf::Text[characters];
        
        //each line spawns at a random x coordinate
        int xCoord = rand() % current.width;       
        //the y coordinate starts above the screen 
        int nextY = 0 - rand() % (current.height*3);
        int charSize = rand() % charSizeRange + charSizeBase;
        for(int j = 0; j < characters; ++j)
        {
            //assign characters from the char n[] array
            arr[i][j].setFont(font);
            char temp = n[i];
            arr[i][j].setString(temp);
            
            arr[i][j].setCharacterSize(charSize);
            
            //set the colors of the characters
            //note: changing the length of the lines may require changes here
            if(j <= 2)
                arr[i][j].setColor(sf::Color::White);
            else if (j <= 4)
                arr[i][j].setColor(sf::Color(102,255,102));//lighter green
            else if (j <= 8)
                arr[i][j].setColor(sf::Color(51,255,51));//light green
            else if (j >= characters - 5)
                arr[i][j].setColor(sf::Color(0,102,0)); //darker green
            else if (j >= characters - 9)
                arr[i][j].setColor(sf::Color(0,153,0)); //dark green
            else
                arr[i][j].setColor(sf::Color::Green);
            
            //set where the character is, and increment the y-coordinate for 
            //the next character 
            arr[i][j].setPosition(xCoord, nextY);///2 - 300, nextY);
            nextY -= charSize;
            //nextY -= space;
        }
    }//end for i

    //main loop
    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        
        //update the lines
        run(arr, arrNum, characters, font, window, n, height, width);
        
        //check if user wants to close the program
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        
        //draw to screen and wait t seconds
        window.display();
        sf::sleep(t);
    }//end main loop

}


/*
 * Function to move the lines down the screen, randomize the characters,  and 
 * draw them. Will also check if the have gone off the screen and re-position 
 * above the screen if needed.
 */
void run(sf::Text**& arr, const int& arrNum, const int& characters, 
    const sf::Font& font, sf::RenderWindow& window, char n[], const int& height, 
    const int& width)
{
    //Iterate through each line...
    for(int i = 0; i < arrNum; ++i)
    {
        int space = arr[i][0].getCharacterSize();

        //...and each character...
        for(int j = 0; j < characters; ++j)
        {
            //...switching to a new character...
            int newChar = rand() % characters;
            arr[i][j].setString(n[newChar]);
            //...and moving it down the screen.
            arr[i][j].move(0, space);
            window.draw(arr[i][j]);
        }

        //Get the position of the last character...
        sf::Vector2f position = arr[i][characters-1].getPosition();
        //...and check if it is way out of bounds. If so, move the line back 
        //above the top of the screen.
        if ( position.y >= height + (space * 3) )
        {
            int xCoord = rand() % width;
            sf::Vector2u windowSize = window.getSize();
            //int nextY = 0 - rand() % (windowSize.y/2);
            int nextY = 0 - rand() % (windowSize.y);
            for (int j = 0; j < characters; j++)
            {
                arr[i][j].setPosition(xCoord, nextY);
                nextY -= space;
            }
        }//end if
    
    }//end for i
}


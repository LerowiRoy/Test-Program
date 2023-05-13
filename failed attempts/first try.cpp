/*
    Objective:
        Create a line that has its position A in the center of the window and its position B will follow 
        the mouse cursor. The line will stretch and rotate accordingly in order to acchieve this.
*/

#include<SFML/Graphics.hpp>
#include<string>
#include<math.h>


#define PI 3.14159265358979323846


int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Radians and Degrees Example", sf::Style::Default);
    sf::Event event;

    sf::RectangleShape line;
    line.setSize(sf::Vector2f(1.f, 1.f));
    line.setFillColor(sf::Color::White);
    line.setOrigin(0.f, 0.f);
    line.setPosition(
        window.getSize().x / 2,
        window.getSize().y / 2
    );

    sf::Font font; font.loadFromFile("font/FutilePro.ttf");
    sf::Text text; 
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    //numeric variables
    std::string windowText;
    float adjacent = 0.f;
    float opposite = 0.f;
    float hypotenuse = 0.f;

    float ratio = 0.f;
    float radian = 0.f;
    float angle = 0.f;
    float angle_cw = 0.f;

    float temp = 0.f;

    //flags
    bool negative_x = false;
    bool negative_y = false;


    while (window.isOpen()){
        //update
        while (window.pollEvent(event)){
            //--closing the window
            if ((event.type == sf::Event::Closed) || (event.key.code == sf::Keyboard::Escape))
                window.close();
        }
        
        //update
        {
            //--obtain mouse position
            sf::Vector2f mousePosition = window.mapPixelToCoords( sf::Mouse::getPosition(window) );

            //--set flags
            negative_x = (mousePosition.x < line.getGlobalBounds().left)? true : false;
            negative_y = (mousePosition.y > line.getGlobalBounds().top)? true : false;
            
            //--obtain right-triangle values
            adjacent = mousePosition.x - line.getGlobalBounds().left;
            adjacent = (adjacent < 0)? adjacent * -1 : adjacent;

            opposite = mousePosition.y - line.getGlobalBounds().top;
            opposite = (opposite < 0)? opposite * -1 : opposite;
            
            hypotenuse = sqrt(opposite * opposite + adjacent * adjacent);
            
            //--obtain ratio, angle and radian
            ratio = opposite / hypotenuse;
            radian = asin(ratio);
            angle = radian / PI * 180;

            //--obtain angle variants 
            if (negative_x && negative_y){
                angle += 180;

            }else if (negative_x){
                angle = 180 - angle;

            }else if (negative_y){
                angle = 360 - angle;

            }

            angle_cw = 360 - angle;

            //--modify line
            line.setSize(sf::Vector2f(hypotenuse, 1));
            line.setRotation(angle_cw);

            //--set text
            windowText.clear();
            windowText.append("adjacent   = "); windowText.append( (negative_x)? "-" : "" );
                windowText.append(std::to_string(adjacent));   windowText.append("px\n");
            windowText.append("opposite   = "); windowText.append( (negative_y)? "-" : "" );
                windowText.append(std::to_string(opposite));   windowText.append("px\n");
            windowText.append("hypotenuse = "); windowText.append(std::to_string(hypotenuse)); windowText.append("px\n");

            windowText.append("ratio  = "); windowText.append(std::to_string(ratio)); windowText.append("\n");
            windowText.append("angle  = "); windowText.append(std::to_string(angle)); windowText.append("\n");
            windowText.append("radian = "); windowText.append(std::to_string(radian)); windowText.append("\n");

            text.setString(windowText);
        }

        //render
        window.clear();
        window.draw(line);
        window.draw(text);
        window.display();
    }

}
/*
    Errors are happening on the update and are mainly caused by:
    ´sf::RectangleShape line´
    when it is trying to rotate more than 90°. 

    
    located from -> 67 to 98
*/

#include<SFML/Graphics.hpp>
#include<cmath>
#include<string>

#define PI 3.14159265358979323846

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Radians & Degrees Examples", sf::Style::Default);
    window.setFramerateLimit(60);
    sf::Event event;

    sf::RectangleShape line;
    line.setFillColor(sf::Color::White);
    line.setPosition(
        window.getSize().x / 2,
        window.getSize().y / 2
    );
    line.setSize(sf::Vector2f(1, 1));

    sf::Font font; font.loadFromFile("font/FutilePro.ttf");
    sf::Text valuesText; 
    valuesText.setFont(font);
    valuesText.setCharacterSize(20);
    valuesText.setFillColor(sf::Color::White);

    sf::Text polarityText;
    polarityText.setFont(font);
    polarityText.setCharacterSize(20);
    polarityText.setFillColor(sf::Color::White);
    polarityText.setString("x = 00");
    polarityText.move(
        window.getSize().x - polarityText.getGlobalBounds().width,
        0
    );

    //variables
    float adjacent = 0.f;
    float opposite = 0.f;
    float hypotenuse = 0.f;

    float ratio = 0.f;
    float temp_angle = 0.f;
    float angle = 0.f;
    float radian = 0.f;

    bool xIsNegative = false;
    bool yIsNegative = false;

    std::string contentText_1;
    std::string contentText_2;

    while (window.isOpen())
    {
        //--handle input--//
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed) || (event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        //--update--//
        {
            //--obtain triangle values 
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            adjacent = mousePosition.x - line.getGlobalBounds().left;
            opposite = (mousePosition.y - line.getGlobalBounds().top) * -1;
            hypotenuse = sqrt((adjacent * adjacent) + (opposite * opposite));

            //--polarity flags
            xIsNegative = (mousePosition.x < line.getGlobalBounds().left)? true : false;
            yIsNegative = (mousePosition.y > line.getGlobalBounds().top)? true : false;

            //--obtain angle from radian
            ratio = opposite / hypotenuse;
            radian = asinf(ratio);
            temp_angle = radian / PI * 180;

            //--adapt for angles outside from 270 -> 360
            if (xIsNegative && yIsNegative){
                angle = 180 + ( temp_angle * -1 );

            }else if(xIsNegative){
                angle = 180 - temp_angle;

            }else if(yIsNegative){
                angle = 360 - ( temp_angle * -1 );
                
            }else{
                angle = temp_angle;
            }

            //--change line's angle counterclockwise
            line.setSize(sf::Vector2f(hypotenuse, 1)); 
            line.setRotation(360.f - angle);                 //<<----------- ERROR/BUG/WTFisGOINGonHERE

            //--modify text 
            contentText_1.clear();
            contentText_1.append("adjacent = "); contentText_1.append(std::to_string(adjacent)); contentText_1.append("\n");
            contentText_1.append("opposite = "); contentText_1.append(std::to_string(opposite)); contentText_1.append("\n");
            contentText_1.append("hypotenuse = "); contentText_1.append(std::to_string(hypotenuse)); contentText_1.append("\n");
            contentText_1.append("\n");


            contentText_1.append("ratio = "); contentText_1.append(std::to_string(ratio)); contentText_1.append("\n");
            contentText_1.append("angle = "); contentText_1.append(std::to_string(angle)); contentText_1.append("\n");
            contentText_1.append("radian = "); contentText_1.append(std::to_string(radian)); contentText_1.append("\n");
            contentText_1.append("\n");

            valuesText.setString(contentText_1);

            contentText_2.clear();
            contentText_2.append("x "); 
                contentText_2.append( (xIsNegative)? "-" : "+" ); contentText_2.append("\n");
            contentText_2.append("y "); 
                contentText_2.append( (yIsNegative)? "-" : "+" ); contentText_2.append("\n");

            polarityText.setString(contentText_2);
        }

        //--render--//
        window.clear();
            window.draw(valuesText);
            window.draw(polarityText);
            window.draw(line);
        window.display();
    }
}
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <sstream>
using namespace sf;
int mainmenu();
int pvscom();

bool intersects (const RectangleShape & rect1,const RectangleShape & rect2)
{
    FloatRect r1=rect1.getGlobalBounds();
    FloatRect r2=rect2.getGlobalBounds();
    return r1.intersects (r2);
}

int clamp (const int x, const int a, const int b)
{
    return std::min(std::max(a,x),b);
}
int main()
{
    pvscom();
    return 0;
}

int pvscom()
{
    int count1=0;
    int apppw=640;
    int appph=150;
    const int width = 640;
    const int height= 480;
    const int borderSize= 12;
    const int margin = 50;
    const int moveDistance = 5;

    VideoMode videoMode(width, height);

    Font font;
    if(!font.loadFromFile("Steronite.ttf"))
        throw("Could not load the font");


    RenderWindow window(videoMode,"Pong SFML 2");
    RectangleShape top;
    RectangleShape left;
    RectangleShape right;
    RectangleShape bottom;
//////////////////////////////////////////////////////////////////////  BOUNDRIES ////////////////////////////////////////////////////////////////
    // setting up all items
    top.setPosition(0, 0);
    top.setSize(Vector2f(width, borderSize));

    left.setPosition(-borderSize, 0);
    left.setSize(Vector2f(borderSize, height));

    right.setPosition(width, 0);
    right.setSize(Vector2f(borderSize, height));

    bottom.setPosition(0, height-borderSize);
    bottom.setSize(Vector2f(width, borderSize));

    top.setFillColor(Color(100,100,100));
    top.setOutlineColor(Color::Blue);
    top.setOutlineThickness(3);

    left.setFillColor(Color(100,100,100));
    left.setOutlineColor(Color::Blue);
    left.setOutlineThickness(3);

    right.setFillColor(Color(100,100,100));
    right.setOutlineColor(Color::Blue);
    right.setOutlineThickness(3);

    bottom.setFillColor(Color(100,100,100));
    bottom.setOutlineColor(Color::Blue);
    bottom.setOutlineThickness(3);

//////////////////////////////////////////////////////////////////////////   BALL  ////////////////////////////////////////////////////////////////

    RectangleShape ball;
    ball.setPosition(width/2, height/2);
    ball.setSize(Vector2f(20, 20));
    ball.setFillColor(Color::Red);
    sf::Texture balltexture;
    balltexture.loadFromFile("ball.png");
    ball.setTexture(&balltexture);

    Vector2<float> ballSpeed(0.5,0.5);

//////////////////////////////////////////////////////////////////////////   PLAYER  ////////////////////////////////////////////////////////////////

    RectangleShape player1;
    player1.setSize(Vector2f(borderSize, 90));
    player1.setPosition(margin-borderSize, height/2-25);
    player1.setFillColor(Color(0,122,245));
    player1.setOutlineColor(Color::Blue);
    player1.setOutlineThickness(3);

    RectangleShape player2;
    player2.setSize(Vector2f(borderSize, 90));
    player2.setPosition(width-margin, height/2-25);
    player2.setFillColor(Color(0,122,245));
    player2.setOutlineColor(Color::Blue);
    player2.setOutlineThickness(3);

    RectangleShape middleLine;
    middleLine.setFillColor(Color(100,100,100,30));
    middleLine.setOutlineColor(Color(0,0,100,30));
    middleLine.setOutlineThickness(2);
    middleLine.setPosition(width/2, 0);
    middleLine.setSize(Vector2f(0, height));
//////////////////////////////////////////////////////////////////////////   YELLOW COLOUR GROUND  ////////////////////////////////////////////////////////////////
    RectangleShape colors;
    colors.setFillColor(Color::Yellow);
    colors.setFillColor(Color::Red);
    colors.setOutlineColor(Color::Yellow);
    colors.setOutlineThickness(width);
    colors.setPosition(width/2, 0);
    colors.setSize(Vector2f(0, height));

//////////////////////////////////////////////////////////////////////////   MENU SCREEN TEXTS  ////////////////////////////////////////////////////////////////

    Text play("PING PONG GAME",font,55);
    play.setPosition(width/2-play.getGlobalBounds().width/2,100);
    play.setFillColor(Color::Red);

    Text playo("PLAY ONLINE",font,35);
    playo.setPosition(width/2-playo.getGlobalBounds().width/2,200);
    playo.setFillColor(Color::Green);

    Text playc("PLAY WITH COMPUTER",font,35);
    playc.setPosition(width/2-playc.getGlobalBounds().width/2,250);
    playc.setFillColor(Color::Blue);

    Text playd("PLAY WITH FRIEND",font,35);
    playd.setPosition(width/2-playd.getGlobalBounds().width/2,300);
    playd.setFillColor(Color::Blue);

    Text playn("QUIT",font,35);
    playn.setPosition(width/2-playn.getGlobalBounds().width/2,350);
    playn.setFillColor(Color::Blue);

//////////////////////////////////////////////////////////////////////////   END SCREEN  ////////////////////////////////////////////////////////////////

    Text won("You have won this game.\n\n Congratulations !",font,20);
    won.setPosition(width/2-won.getGlobalBounds().width/2,height/2-won.getGlobalBounds().height/2);
    won.setFillColor(Color::Green);

    Text lost("You have lost this game, \n better luck next time!",font,20);
    lost.setPosition(width/2-lost.getGlobalBounds().width/2,height/2-lost.getGlobalBounds().height/2);
    lost.setFillColor(Color::Red);

    Text won1("Player 1 won this game",font,20);
    won1.setPosition(width/2-lost.getGlobalBounds().width/2,height/2-won1.getGlobalBounds().height/2);
    won1.setFillColor(Color::Red);

    Text won2("Player 2 won this game",font,20);
    won2.setPosition(width/2-lost.getGlobalBounds().width/2,height/2-won2.getGlobalBounds().height/2);
    won2.setFillColor(Color::Red);

//////////////////////////////////////////////////////////////////////////   SCORE BOARD  ////////////////////////////////////////////////////////////////

    Text score("0   0",font,50);
    score.setPosition(width/2-score.getGlobalBounds().width/2,40);
    score.setFillColor(Color(0,0,100,50));

//////////////////////////////////////////////////////////////////////////   MAIN LOGIC  ////////////////////////////////////////////////////////////////

    unsigned int p1Score=0, p2Score=0;

    enum states {INTRO, OPLAYING, SPLAYING, DPLAYING, PWON, P1LOST, P2WON, P1WON};

    int gameState=INTRO;

    while (window.isOpen())
    {
        window.clear(Color::White);
        switch(gameState)
        {
            case INTRO:
                window.draw(play);
                window.draw(playo);
                window.draw(playc);
                window.draw(playd);
                window.draw(playn);
                break;

            case OPLAYING:
                window.draw(colors);
                window.draw(middleLine);
                window.draw(left);
                window.draw(right);
                window.draw(player1);
                window.draw(player2);
                window.draw(ball);
                window.draw(score);
                window.draw(top);
                window.draw(bottom);
                break;

            case SPLAYING:
                window.draw(colors);
                window.draw(middleLine);
                window.draw(left);
                window.draw(right);
                window.draw(player1);
                window.draw(player2);
                window.draw(ball);
                window.draw(score);
                window.draw(top);
                window.draw(bottom);
                break;

            case DPLAYING:
                window.draw(colors);
                window.draw(middleLine);
                window.draw(left);
                window.draw(right);
                window.draw(player1);
                window.draw(player2);
                window.draw(ball);
                window.draw(score);
                window.draw(top);
                window.draw(bottom);
                break;


            case PWON:
                window.draw(won);
                break;

            case P1LOST:
                window.draw(lost);
                break;

            case P1WON:
                window.draw(won1);
                break;

            case P2WON:
                window.draw(won2);
                break;
        }
        window.display();

//////////////////////////////////////////////////////////////////////////   EVENT HANDLING  ////////////////////////////////////////////////////////////////

        Event event;
        while (window.pollEvent(event))
        {
            if ( (event.type == Event::Closed) ||
            ((event.type == Event::KeyPressed) && (event.key.code==Keyboard::Escape)) )
                window.close();
            else
            if ((event.type == Event::KeyPressed) && (gameState == INTRO) && (event.key.code==Keyboard::Down))
            {
            if(count1<4){
                if(count1==0)
                {
                   count1=count1+1;
                   playo.setFillColor(Color::Blue);
                   playc.setFillColor(Color::Green);

                }
                else if(count1==1)
                {
                   count1=count1+1;
                   playc.setFillColor(Color::Blue);
                   playd.setFillColor(Color::Green);

                }
                else if(count1==2)
                {
                   count1=count1+1;
                   playd.setFillColor(Color::Blue);
                   playn.setFillColor(Color::Green);

                }
            }
            }
            else
            if ((event.type == Event::KeyPressed) && (gameState == INTRO) && (event.key.code==Keyboard::Up))
            {
                if(count1>0)
                {
                if(count1==1)
                {
                   count1=count1-1;
                   playc.setFillColor(Color::Blue);
                   playo.setFillColor(Color::Green);

                }
                else if(count1==2)
                {
                   count1=count1-1;
                   playd.setFillColor(Color::Blue);
                   playc.setFillColor(Color::Green);
                }
                else if(count1==3)
                {
                   count1=count1-1;
                   playn.setFillColor(Color::Blue);
                   playd.setFillColor(Color::Green);

                }
                }
            }
        }

        if ((event.type == Event::KeyPressed) && (gameState == INTRO) && (event.key.code==Keyboard::RShift))
            {
                if(count1==1)
                {
                    gameState=SPLAYING;
                }
                else if(count1==2)
                {
                    gameState=DPLAYING;
                }
                else if(count1==3)
                {
                    window.close();
                }
            }

///////////////////////////////////////////////////////ONLINE/////////////////////////////////////////////////////////////////
            if (gameState==OPLAYING)
            {
            // move player2 pad
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                player2.move(0,-moveDistance/5.0);
            }else
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                player2.move(0,moveDistance/5.0);
            }
            // move player 1 pad
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                player1.move(0,-moveDistance/5.0);
            }else
            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                player1.move(0,moveDistance/5.0);
            }
            // block players pad inside the play area
            if ( intersects(player1,bottom) || intersects(player1,top) )
            {
                FloatRect t=top.getGlobalBounds();
                FloatRect b=bottom.getGlobalBounds();
                Vector2f p=player1.getPosition();
                p.y=clamp(p.y,t.top+t.height+5,b.top-player1.getSize().y-5);
                player1.setPosition(p);
            }
            if ( intersects(player2,bottom) || intersects(player2,top) )
            {
                FloatRect t=top.getGlobalBounds();
                FloatRect b=bottom.getGlobalBounds();
                Vector2f p=player2.getPosition();
                p.y=clamp(p.y,t.top+t.height+5,b.top-player2.getSize().y-5);
                player2.setPosition(p);
            }
            // ball collides with top and bottom
            if (intersects(ball,top))
            {
                FloatRect t=top.getGlobalBounds();
                FloatRect b=ball.getGlobalBounds();
                ballSpeed.y=-ballSpeed.y;
                int u = t.top + t.height - b.top;
                ball.move(0,3*u);
            }
            if ( intersects(ball,bottom) )
            {
                FloatRect bot= bottom.getGlobalBounds();
                FloatRect b= ball.getGlobalBounds();
                ballSpeed.y=-ballSpeed.y;
                int u = bot.top - b.height - b.top;
                ball.move(0,2*u);
            }
            // ball collides with player1 and player2
            if (intersects(ball,player1))
            {
                FloatRect p= player1.getGlobalBounds();
                FloatRect b= ball.getGlobalBounds();
                ballSpeed.x= -ballSpeed.x;
                ballSpeed.y= (b.top+b.height/2 - p.top - p.height/2) / 100;
                int u = p.left +  p.width - b.left;
                b.left = p.left +  p.width + u;
                ball.setPosition(b.left,b.top);
                //increase ball speed by 1%
                ballSpeed.x=ballSpeed.x*1.02;
                ballSpeed.y=ballSpeed.y*1.02;
            }

            if ( intersects(ball,player2) )
            {
                FloatRect p=player2.getGlobalBounds();
                FloatRect b=ball.getGlobalBounds();
                ballSpeed.x=-ballSpeed.x;
                ballSpeed.y= (b.top+b.height/2 - p.top - p.height/2) / 100;
                int u = b.left + b.width - p.left;
                b.left = p.left -  b.width - u;
                ball.setPosition(b.left,b.top);
                //increase ball speed by 1%
                ballSpeed.x=ballSpeed.x*1.02;
                ballSpeed.y=ballSpeed.y*1.02;
            }

            // check for scoring
            if (intersects(ball,left))
            {
                p2Score++;
                std::stringstream str;
                str << p1Score << "   " << p2Score;
                score.setString(str.str());
                score.setPosition(width/2-score.getGlobalBounds().width/2,40);
                FloatRect p=player2.getGlobalBounds();
                FloatRect b=ball.getGlobalBounds();
                ball.setPosition(p.left-b.width-5, height/2);
                ballSpeed.x=-0.9;
                ballSpeed.y=0.9;

            }

            if (intersects(ball,right))
            {
                p1Score++;
                std::stringstream str;
                str << p1Score << "   " << p2Score;
                score.setString(str.str());
                score.setPosition(width/2-score.getGlobalBounds().width/2,40);
                FloatRect p=player1.getGlobalBounds();
                FloatRect b=ball.getGlobalBounds();
                ball.setPosition(p.left+p.width+5, height/2);
                ballSpeed.x=0.5;
                ballSpeed.y=0.5;
            }
            // detect if game is over
            if (p1Score >=11 && p1Score >= p2Score +2)
                gameState=P1WON;

            if (p2Score >=11 && p2Score >= p1Score +2)
                gameState=P2WON;


            ball.move(ballSpeed.x,ballSpeed.y);

            }



//////////////////////////////////////////////////////////////////////////   PLAYER VS COMPUTER  ////////////////////////////////////////////////////////////////

        if (gameState==SPLAYING)
        {
        // auto move player2 pad
        if (ball.getPosition().y < player2.getPosition().y)
            player2.move(0, -moveDistance/4.0);
        else if(ball.getPosition().y+ball.getSize().y > player2.getPosition().y+player2.getSize().y)
            player2.move(0, moveDistance/10.0);
        // move player 1 pad
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            player1.move(0,-moveDistance/5.0);
        }else
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            player1.move(0,moveDistance/5.0);
        }
        // block players pad inside the play area
        if ( intersects(player1,bottom) || intersects(player1,top) )
        {
            FloatRect t=top.getGlobalBounds();
            FloatRect b=bottom.getGlobalBounds();
            Vector2f p=player1.getPosition();
            p.y=clamp(p.y,t.top+t.height+5,b.top-player1.getSize().y-5);
            player1.setPosition(p);
        }
        if ( intersects(player2,bottom) || intersects(player2,top) )
        {
            FloatRect t=top.getGlobalBounds();
            FloatRect b=bottom.getGlobalBounds();
            Vector2f p=player2.getPosition();
            p.y=clamp(p.y,t.top+t.height+5,b.top-player2.getSize().y-5);
            player2.setPosition(p);
        }
        // ball collides with top and bottom
        if (intersects(ball,top))
        {
            FloatRect t=top.getGlobalBounds();
            FloatRect b=ball.getGlobalBounds();
            ballSpeed.y=-ballSpeed.y;
            int u = t.top + t.height - b.top;
            ball.move(0,3*u);
        }
        if ( intersects(ball,bottom) )
        {
            FloatRect bot= bottom.getGlobalBounds();
            FloatRect b= ball.getGlobalBounds();
            ballSpeed.y=-ballSpeed.y;
            int u = bot.top - b.height - b.top;
            ball.move(0,2*u);
        }
        // ball collides with player1 and player2
        if (intersects(ball,player1))
        {
            FloatRect p= player1.getGlobalBounds();
            FloatRect b= ball.getGlobalBounds();
            ballSpeed.x= -ballSpeed.x;
            ballSpeed.y= (b.top+b.height/2 - p.top - p.height/2) / 100;
            int u = p.left +  p.width - b.left;
            b.left = p.left +  p.width + u;
            ball.setPosition(b.left,b.top);
            //increase ball speed by 1%
            ballSpeed.x=ballSpeed.x*1.02;
            ballSpeed.y=ballSpeed.y*1.02;
        }

        if ( intersects(ball,player2) )
        {
            FloatRect p=player2.getGlobalBounds();
            FloatRect b=ball.getGlobalBounds();
            ballSpeed.x=-ballSpeed.x;
            ballSpeed.y= (b.top+b.height/2 - p.top - p.height/2) / 100;
            int u = b.left + b.width - p.left;
            b.left = p.left -  b.width - u;
            ball.setPosition(b.left,b.top);
            //increase ball speed by 1%
            ballSpeed.x=ballSpeed.x*1.02;
            ballSpeed.y=ballSpeed.y*1.02;
        }

        // check for scoring
        if (intersects(ball,left))
        {
            p2Score++;
            std::stringstream str;
            str << p1Score << "   " << p2Score;
            score.setString(str.str());
            score.setPosition(width/2-score.getGlobalBounds().width/2,40);
            FloatRect p=player2.getGlobalBounds();
            FloatRect b=ball.getGlobalBounds();
            ball.setPosition(p.left-b.width-5, height/2);
            ballSpeed.x=-0.9;
            ballSpeed.y=0.9;

        }

        if (intersects(ball,right))
        {
            p1Score++;
            std::stringstream str;
            str << p1Score << "   " << p2Score;
            score.setString(str.str());
            score.setPosition(width/2-score.getGlobalBounds().width/2,40);
            FloatRect p=player1.getGlobalBounds();
            FloatRect b=ball.getGlobalBounds();
            ball.setPosition(p.left+p.width+5, height/2);
            ballSpeed.x=0.5;
            ballSpeed.y=0.5;
        }
        // detect if game is over
        if (p1Score >=11 && p1Score >= p2Score +2)
            gameState=PWON;

        if (p2Score >=11 && p2Score >= p1Score +2)
            gameState=P1LOST;


        ball.move(ballSpeed.x,ballSpeed.y);

        }

//////////////////////////////////////////////////////////////////////////   PLAYER VS PLAYER  ////////////////////////////////////////////////////////////////


        else if (gameState==DPLAYING)
        {
        // move player2 pad
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            player2.move(0,-moveDistance/5.0);
        }else
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            player2.move(0,moveDistance/5.0);
        }
        // move player 1 pad
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            player1.move(0,-moveDistance/5.0);
        }else
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            player1.move(0,moveDistance/5.0);
        }
        // block players pad inside the play area
        if ( intersects(player1,bottom) || intersects(player1,top) )
        {
            FloatRect t=top.getGlobalBounds();
            FloatRect b=bottom.getGlobalBounds();
            Vector2f p=player1.getPosition();
            p.y=clamp(p.y,t.top+t.height+5,b.top-player1.getSize().y-5);
            player1.setPosition(p);
        }
        if ( intersects(player2,bottom) || intersects(player2,top) )
        {
            FloatRect t=top.getGlobalBounds();
            FloatRect b=bottom.getGlobalBounds();
            Vector2f p=player2.getPosition();
            p.y=clamp(p.y,t.top+t.height+5,b.top-player2.getSize().y-5);
            player2.setPosition(p);
        }
        // ball collides with top and bottom
        if (intersects(ball,top))
        {
            FloatRect t=top.getGlobalBounds();
            FloatRect b=ball.getGlobalBounds();
            ballSpeed.y=-ballSpeed.y;
            int u = t.top + t.height - b.top;
            ball.move(0,3*u);
        }
        if ( intersects(ball,bottom) )
        {
            FloatRect bot= bottom.getGlobalBounds();
            FloatRect b= ball.getGlobalBounds();
            ballSpeed.y=-ballSpeed.y;
            int u = bot.top - b.height - b.top;
            ball.move(0,2*u);
        }
        // ball collides with player1 and player2
        if (intersects(ball,player1))
        {
            FloatRect p= player1.getGlobalBounds();
            FloatRect b= ball.getGlobalBounds();
            ballSpeed.x= -ballSpeed.x;
            ballSpeed.y= (b.top+b.height/2 - p.top - p.height/2) / 100;
            int u = p.left +  p.width - b.left;
            b.left = p.left +  p.width + u;
            ball.setPosition(b.left,b.top);
            //increase ball speed by 1%
            ballSpeed.x=ballSpeed.x*1.02;
            ballSpeed.y=ballSpeed.y*1.02;
        }

        if ( intersects(ball,player2) )
        {
            FloatRect p=player2.getGlobalBounds();
            FloatRect b=ball.getGlobalBounds();
            ballSpeed.x=-ballSpeed.x;
            ballSpeed.y= (b.top+b.height/2 - p.top - p.height/2) / 100;
            int u = b.left + b.width - p.left;
            b.left = p.left -  b.width - u;
            ball.setPosition(b.left,b.top);
            //increase ball speed by 1%
            ballSpeed.x=ballSpeed.x*1.02;
            ballSpeed.y=ballSpeed.y*1.02;
        }

        // check for scoring
        if (intersects(ball,left))
        {
            p2Score++;
            std::stringstream str;
            str << p1Score << "   " << p2Score;
            score.setString(str.str());
            score.setPosition(width/2-score.getGlobalBounds().width/2,40);
            FloatRect p=player2.getGlobalBounds();
            FloatRect b=ball.getGlobalBounds();
            ball.setPosition(p.left-b.width-5, height/2);
            ballSpeed.x=-0.9;
            ballSpeed.y=0.9;

        }

        if (intersects(ball,right))
        {
            p1Score++;
            std::stringstream str;
            str << p1Score << "   " << p2Score;
            score.setString(str.str());
            score.setPosition(width/2-score.getGlobalBounds().width/2,40);
            FloatRect p=player1.getGlobalBounds();
            FloatRect b=ball.getGlobalBounds();
            ball.setPosition(p.left+p.width+5, height/2);
            ballSpeed.x=0.5;
            ballSpeed.y=0.5;
        }
        // detect if game is over
        if (p1Score >=11 && p1Score >= p2Score +2)
            gameState=P1WON;

        if (p2Score >=11 && p2Score >= p1Score +2)
            gameState=P2WON;


        ball.move(ballSpeed.x,ballSpeed.y);

        }
    }
    return 0;
}

// Interactive mandelbrot

// including required libraries and headers

#include "DynamicDeque.cpp"
#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// Width of the window
const int W = 1920;

// Height of the window
const int H = 1080;

// setting max iterations and other global variables
int max_iter = 128;
double zoom = 1.0;
double min_re = -2.5, max_re = 1;
double min_im = -1, max_im = 1;

// to open help page
bool help_open = false;

// to check animation
bool play_from_start = false;

// computes v + t(u - v)
// t should be a value between 0 and 1
Color linear_interpolation(const Color &v, const Color &u, double a)
{
    auto const b = 1 - a;
    return Color(b * v.r + a * u.r, b * v.g + a * u.g, b * v.b + a * u.b);
}

int main(void)
{
    // load window and its elements
    RenderWindow window(VideoMode(W, H), "Mandelbrot");

    // loading image
    Image image;
    image.create(W, H);

    // initialising texture
    Texture texture;

    // initialising sprite
    Sprite sprite;

    // initialising font
    Font font;
    font.loadFromFile("arial.ttf");

    // initialising the text to be displayed
    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);

    // Dequeue used for storing the keyboard operations
    DynamicDequeue queue;

    // run a loop till the window remains open
    while (window.isOpen())
    {
        // initialise event
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // if window is closed by any method
                window.close();
            }

            // function to zoom by value z
            auto X_zoom = [&](double z)
            {
                // center is preserved
                double cr = min_re + (max_re - min_re) / 2;
                double ci = min_im + (max_im - min_im) / 2;

                // zoom
                double tminr = cr - (max_re - min_re) / 2 / z;
                max_re = cr + (max_re - min_re) / 2 / z;
                min_re = tminr;

                double tmini = ci - (max_im - min_im) / 2 / z;
                max_im = ci + (max_im - min_im) / 2 / z;
                min_im = tmini;
            };

            // text events for keys other than arrows and letters on keyboard
            if (event.type == Event::TextEntered)
            {

                //- to zoom out
                if (event.text.unicode == '-')
                {
                    X_zoom(1.0 / 5);
                    zoom /= 5;
                    queue.insertRear(2);
                }

                //+ to zoom in
                if (event.text.unicode == '=')
                {
                    X_zoom(5);
                    zoom *= 5;
                    queue.insertRear(1);
                }

                //< to decrease iterations
                if (event.text.unicode == ',')
                {
                    max_iter /= 2;
                    if (max_iter < 1)
                        max_iter - 1;
                    queue.insertRear(4);
                }

                //> to increase iterations
                if (event.text.unicode == '.')
                {
                    max_iter *= 2;
                    queue.insertRear(3);
                }

                // assume no other keys are pressed
            }

            // arrows and Escape keys
            if (event.type == Event::KeyPressed)
            {

                // for moving by delta_w and delta_h
                double delta_w = (max_re - min_re) * 0.3;
                double delta_h = (max_im - min_im) * 0.3;

                // open help page using H
                if (event.key.code == Keyboard::H)
                {
                    help_open = true;
                }

                // close help page using C
                if (help_open == true)
                {
                    if (event.key.code == Keyboard::C)
                    {
                        help_open = false;
                    }
                }

                // R for reset
                if (event.key.code == Keyboard::R)
                {
                    max_iter = 128;
                    zoom = 1.0;
                    min_re = -2.5, max_re = 1;
                    min_im = -1, max_im = 1;
                    queue.erase();
                }

                // P for play from start
                if (event.key.code == Keyboard::P)
                {
                    // firstly reset the whole animation
                    max_iter = 128;
                    zoom = 1.0;
                    min_re = -2.5, max_re = 1;
                    min_im = -1, max_im = 1;

                    // turn on play_from_start flag
                    play_from_start = true;
                }

                // U for Undo last operation
                if (event.key.code == Keyboard::U)
                {
                    int num = queue.removeRear();
                    // reverse the operation
                    if (num % 2 == 0)
                    {
                        num -= 1;
                    }
                    else
                    {
                        num += 1;
                    }

                    if (num == 1)
                    {
                        // zoom in
                        X_zoom(5);
                        zoom *= 5;
                    }
                    if (num == 2)
                    {
                        // zoom out
                        X_zoom(1.0 / 5);
                        zoom /= 5;
                    }
                    if (num == 3)
                    {
                        // increase iterations
                        max_iter *= 2;
                    }
                    if (num == 4)
                    {
                        // decrease iterations
                        max_iter /= 2;
                    }
                    if (num == 5)
                    {
                        // left arrow
                        min_re -= delta_w, max_re -= delta_w;
                    }

                    if (num == 6)
                    {
                        // right arrow
                        min_re += delta_w, max_re += delta_w;
                    }

                    if (num == 7)
                    {
                        // up arrow
                        min_im -= delta_h, max_im -= delta_h;
                    }

                    if (num == 8)
                    {
                        // down arrow
                        min_im += delta_h, max_im += delta_h;
                    }
                }

                // Press Q to close
                if (event.key.code == Keyboard::Q)
                {
                    window.close();
                    break;
                }

                // all arrow keys
                if (event.key.code == Keyboard::Left)
                {
                    min_re -= delta_w, max_re -= delta_w;
                    queue.insertRear(5);
                }

                if (event.key.code == Keyboard::Right)
                {
                    min_re += delta_w, max_re += delta_w;
                    queue.insertRear(6);
                }

                if (event.key.code == Keyboard::Up)
                {
                    min_im -= delta_h, max_im -= delta_h;
                    queue.insertRear(7);
                }

                if (event.key.code == Keyboard::Down)
                {
                    min_im += delta_h, max_im += delta_h;
                    queue.insertRear(8);
                }

                if (event.key.code == Keyboard::A)
                {
                    min_re -= delta_w, max_re -= delta_w;
                    queue.insertRear(5);
                }

                if (event.key.code == Keyboard::D)
                {
                    min_re += delta_w, max_re += delta_w;
                    queue.insertRear(6);
                }

                if (event.key.code == Keyboard::W)
                {
                    min_im -= delta_h, max_im -= delta_h;
                    queue.insertRear(7);
                }

                if (event.key.code == Keyboard::S)
                {
                    min_im += delta_h, max_im += delta_h;
                    queue.insertRear(8);
                }
            }

            // Left and Right click events
            if (event.type == Event::MouseButtonPressed)
            {
                auto Y_zoom = [&](double z)
                {
                    // mouse point will be new center point
                    double cr = min_re + (max_re - min_re) * event.mouseButton.x / W;
                    double ci = min_im + (max_im - min_im) * event.mouseButton.y / H;

                    // zoom
                    double tminr = cr - (max_re - min_re) / 2 / z;
                    max_re = cr + (max_re - min_re) / 2 / z;
                    min_re = tminr;

                    double tmini = ci - (max_im - min_im) / 2 / z;
                    max_im = ci + (max_im - min_im) / 2 / z;
                    min_im = tmini;
                };

                if (event.mouseButton.button == Mouse::Left)
                {

                    Y_zoom(5);
                    zoom *= 5;
                    queue.insertRear(1);
                }
                if (event.mouseButton.button == Mouse::Right)
                {
                    Y_zoom(1.0 / 5);
                    zoom /= 5;
                    queue.insertRear(2);
                }
            }

            // mouse events
            if (event.type == Event::MouseWheelScrolled)
            {
                if (event.MouseWheelScrolled)
                {
                    if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel)
                    {
                        // if up scroll increase no of iterations
                        if (event.mouseWheelScroll.delta > 0)
                        {
                            max_iter *= 2;
                            queue.insertRear(3);
                        }
                        // if down scroll decrease no of iterations
                        else
                        {
                            max_iter /= 2;
                            queue.insertRear(4);
                        }
                        // cant make max_iter less than 1
                        if (max_iter < 1)
                        {
                            max_iter = 1;
                            queue.removeRear();
                        }
                    }
                }
            }
        }

#pragma omp parallel for

        // make different window for help page
        if (help_open)
        {
            // clear previous screen
            window.clear();

            // string for text
            string str;
            str = "\t\t Help Page\n";

            // centering the text
            FloatRect textRect = text.getLocalBounds();

            str = str + "\nKeyBoard Controls:\n";
            str = str + " Use Arrow keys or WASD to move the screen\n";
            str = str + " Press > to double iterations\n";
            str = str + " Press < to half the iterations\n";
            str = str + " Press + to zoom in\n";
            str = str + " Press - to zoom out\n";

            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition(window.getView().getCenter());

            str = str + " Press R to reset mandelbrot\n";
            str = str + " Press U to undo last move";
            str = str + " Press P to play all operations from start\n";

            str = str + "Mouse Controls:\n";
            str = str + " Scroll Up to double iterations\n";
            str = str + " Scroll down to half the iterations\n";
            str = str + " Left Click to zoom in\n";
            str = str + " Right Click to zoom out\n";
            str = str + "Press C Key to close help page";

            text.setString(str);
            window.draw(text);
        }

        else if (event.type != Event::MouseMoved)
        {
            // only one calculation
            int no_of_operations = 1;

            if (play_from_start)
            {
                // repeat as many times as size of dequeue operations
                no_of_operations = queue.size();
            }

            while (no_of_operations-- > 0)
            {

                auto X_zoom = [&](double z)
                {
                    // center is preserved
                    double cr = min_re + (max_re - min_re) / 2;
                    double ci = min_im + (max_im - min_im) / 2;

                    // zoom
                    double tminr = cr - (max_re - min_re) / 2 / z;
                    max_re = cr + (max_re - min_re) / 2 / z;
                    min_re = tminr;

                    double tmini = ci - (max_im - min_im) / 2 / z;
                    max_im = ci + (max_im - min_im) / 2 / z;
                    min_im = tmini;
                };

                double delta_w = (max_re - min_re) * 0.3;
                double delta_h = (max_im - min_im) * 0.3;

                window.clear();
                if (play_from_start)
                {
                    int num = (queue.getPosition(queue.size() - no_of_operations));
                    if (num == 1)
                    {
                        X_zoom(5);
                        zoom *= 5;
                    }
                    if (num == 2)
                    {
                        X_zoom(1.0 / 5);
                        zoom /= 5;
                    }
                    if (num == 3)
                    {
                        max_iter *= 2;
                    }
                    if (num == 4)
                    {
                        max_iter /= 2;
                    }
                    if (num == 5)
                    {
                        min_re -= delta_w, max_re -= delta_w;
                    }

                    if (num == 6)
                    {
                        min_re += delta_w, max_re += delta_w;
                    }

                    if (num == 7)
                    {
                        min_im -= delta_h, max_im -= delta_h;
                    }

                    if (num == 8)
                    {
                        min_im += delta_h, max_im += delta_h;
                    }
                }

                for (int y = 0; y < H; y++)
                    for (int x = 0; x < W; x++)
                    {
                        double cr = min_re + (max_re - min_re) * x / W;
                        double ci = min_im + (max_im - min_im) * y / H;
                        double re = 0, im = 0;
                        int iter;
                        for (iter = 0; iter < max_iter; iter++)
                        {
                            double tr = re * re - im * im + cr;
                            im = 2 * re * im + ci;
                            re = tr;
                            if (re * re + im * im > 2 * 2)
                                break;
                        }
                        int r = 1.0 * (max_iter - iter) / max_iter * 0xff;
                        int g = r, b = r;

                        static const vector<Color> colors{
                            {0, 7, 100},
                            {32, 107, 203},
                            {237, 255, 255},
                            {255, 170, 0},
                            {0, 2, 0},
                        };

                        // decide color of each pixel
                        static const auto max_color = colors.size() - 1;
                        if (iter == max_iter)
                            iter = 0;
                        double mu = 1.0 * iter / max_iter;
                        // scale mu to be in the range of colors
                        mu *= max_color;
                        auto i_mu = static_cast<size_t>(mu);
                        auto color1 = colors[i_mu];
                        auto color2 = colors[min(i_mu + 1, max_color)];
                        Color c = linear_interpolation(color1, color2, mu - i_mu);

                        // set color of each pixel
                        image.setPixel(x, y, Color(c));
                    }

                // load objects
                texture.loadFromImage(image);
                sprite.setTexture(texture);
                window.draw(sprite);

                // display window if not final operation
                if (no_of_operations != 0)
                    window.display();
            }

            // change text location back to top left if centered
            FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

            char str[100];
            sprintf(str, "max iter:%d\nzoom:x%2.2lf\n Press H for Help Page\n Press Q to quit", max_iter, zoom);
            text.setString(str);
            window.draw(text);

            // turn off play_from_start flag for re-use
            play_from_start = false;
        }

        // display window
        window.display();
    }
    return 0;
}
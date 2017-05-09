//
// Created by zulus on 29.04.17.
//

#include <ConsoleGraphic/GraphicPlane.h>
#include <pbconsole.h>
#include "ConsoleGraphic/GraphicPlane.h"

using namespace progbase;
using namespace console;
#define EMPTY_SYMBOL ' '

GraphicPlane::GraphicPlane(int width, int heigth, CursorAttributes defaultColorBG, CursorAttributes defaultColorFG) {
    if (width > 0) {
        this->width = width;
    } else {
        this->width = DEFAULT_WIDTH;
    }
    if (heigth > 0) {
        this->heigth = heigth;
    } else {
        this->heigth = DEFAULT_HEIGHT;
    }
    this->defaultColorBG = defaultColorBG;
    this->defaultColorFG = defaultColorFG;
    this->userBuffer = new Dot *[heigth];
    this->consoleBuffer = new Dot *[heigth];
    for (int i = 0; i < heigth; i++) {
        userBuffer[i] = new Dot[width];
        consoleBuffer[i] = new Dot[width];
    }
    clear(defaultColorBG, defaultColorFG);
}

void GraphicPlane::prepare() {
    Console::setSize(heigth, width);
    Console::hideCursor();
    clear();
}

void GraphicPlane::clear() {
    Console::setCursorAttribute(defaultColorBG);
    Console::setCursorAttribute(defaultColorFG);
    for (int y = 0; y < heigth; y++) {
        for (int x = 0; x < width; x++) {
            consoleBuffer[y][x].colorBG = defaultColorBG;
            consoleBuffer[y][x].colorFG = defaultColorFG;
            consoleBuffer[y][x].symbol = EMPTY_SYMBOL;
            userBuffer[y][x].colorBG = defaultColorBG;
            userBuffer[y][x].colorFG = defaultColorFG;
            userBuffer[y][x].symbol = EMPTY_SYMBOL;
            Console::setCursorPosition(y + 1, x + 1);
            putchar(EMPTY_SYMBOL);
        }
    }
}

void GraphicPlane::clear(CursorAttributes colorBG, CursorAttributes colorFG) {
    for (int y = 0; y < heigth; y++) {
        for (int x = 0; x < width; x++) {
            consoleBuffer[y][x].colorBG = colorBG;
            consoleBuffer[y][x].colorFG = colorFG;
            consoleBuffer[y][x].symbol = EMPTY_SYMBOL;
            userBuffer[y][x].colorBG = colorBG;
            userBuffer[y][x].colorFG = colorFG;
            userBuffer[y][x].symbol = EMPTY_SYMBOL;
        }
    }
}

void GraphicPlane::drawLine(const Vec2D &p1, const Vec2D &p2, CursorAttributes color) {
    double x0 = p1.x;
    double x1 = p2.x;
    double y0 = p1.y;
    double y1 = p2.y;

    int steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }

    double dx = abs(x1 - x0);
    double dy = abs(y1 - y0);
    double error = 0;
    double dErr = dy;
    double x = x0;
    double y = y0;
    drawPixel((Vec2D) {steep ? y : x, steep ? x : y}, color);
    int xstep = (x0 < x1) ? 1 : -1;
    int ystep = (y0 < y1) ? 1 : -1;
    while (abs(x - x1) > 1) {
        x += xstep;
        error += dErr;
        if (2 * error > dx) {
            y += ystep;
            error -= dx;
        }
        drawPixel((Vec2D) {steep ? y : x, steep ? x : y}, color);
    }
}

void GraphicPlane::drawCircle(const Vec2D &center, double radius, CursorAttributes color) {
    double x0 = center.x;
    double y0 = center.y;
    double x = radius;
    double y = 0;
    double err = 0;
    while (x >= y) {
        drawPixel((Vec2D) {x0 + x, y0 + y}, color);
        drawPixel((Vec2D) {x0 + y, y0 + x}, color);
        drawPixel((Vec2D) {x0 - y, y0 + x}, color);
        drawPixel((Vec2D) {x0 - x, y0 + y}, color);
        drawPixel((Vec2D) {x0 - x, y0 - y}, color);
        drawPixel((Vec2D) {x0 - y, y0 - x}, color);
        drawPixel((Vec2D) {x0 + y, y0 - x}, color);
        drawPixel((Vec2D) {x0 + x, y0 - y}, color);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void GraphicPlane::drawPixel(const Vec2D &pos, CursorAttributes color) {
    if (pos.y >= 0 && pos.y < heigth && pos.x >= 0 && pos.x < width) {
        this->userBuffer[(int) pos.y][(int) pos.x].colorBG = color;
        this->userBuffer[(int) pos.y][(int) pos.x].symbol = EMPTY_SYMBOL;
    }
}

void GraphicPlane::redraw() {
    for (int y = 0; y < heigth; y++) {
        for (int x = 0; x < width; x++) {
            if (userBuffer[y][x].colorBG != consoleBuffer[y][x].colorBG ||
                userBuffer[y][x].colorFG != consoleBuffer[y][x].colorFG ||
                userBuffer[y][x].symbol != consoleBuffer[y][x].symbol) {
                Console::setCursorPosition(y + 1, x + 1);
                Console::setCursorAttribute(userBuffer[y][x].colorBG);
                Console::setCursorAttribute(userBuffer[y][x].colorFG);
                putchar(userBuffer[y][x].symbol);
                consoleBuffer[y][x].colorBG = userBuffer[y][x].colorBG;
                consoleBuffer[y][x].colorFG = userBuffer[y][x].colorFG;
                consoleBuffer[y][x].symbol = userBuffer[y][x].symbol;
            }
        }
    }
}

int GraphicPlane::getWidth() const {
    return width;
}

int GraphicPlane::getHeigth() const {
    return heigth;
}

CursorAttributes GraphicPlane::getDefaultColorBG() const {
    return defaultColorBG;
}

CursorAttributes GraphicPlane::getDefaultColorFG() const {
    return defaultColorFG;
}

GraphicPlane::~GraphicPlane() {
    updateConsole.lock();
    clear(pb::BG_DEFAULT, pb::FG_DEFAULT);
    for (int i = 0; i < heigth; i++) {
        delete[] userBuffer[i];
        delete[] consoleBuffer[i];
    }
    delete[] userBuffer;
    delete[] consoleBuffer;
    Console::showCursor();
    Console::reset();
    updateConsole.unlock();
}

void GraphicPlane::fillRect(const Vec2D &left, const Vec2D &right, CursorAttributes color) {
    int x0 = (left.x < right.x) ? left.x : right.x;
    int y0 = (left.y < right.y) ? left.y : right.y;
    int x1 = (left.x > right.x) ? left.x : right.x;
    int y1 = (left.y > right.y) ? left.y : right.y;
    for (int y = y0; y < y1; y++) {
        for (int x = x0; x < x1; x++) {
            drawPixel((Vec2D) {.x=x, .y=y}, color);
        }
    }
}

void GraphicPlane::drawPixel(const Vec2D &pos, CursorAttributes colorBG, CursorAttributes colorFG, char symbol) {
    if (pos.y >= 0 && pos.y < heigth && pos.x >= 0 && pos.x < width) {
        this->userBuffer[(int) pos.y][(int) pos.x].colorBG = colorBG;
        this->userBuffer[(int) pos.y][(int) pos.x].colorFG = colorFG;
        this->userBuffer[(int) pos.y][(int) pos.x].symbol = symbol;
    }
}

void GraphicPlane::print(const std::string &str, CursorAttributes colorBG, CursorAttributes colorFG,
                         const Vec2D &pos) {
    Vec2D posChar{pos.x, pos.y};
    for (auto it = str.begin(); it != str.end(); it++) {
        if (posChar.x > width) {
            posChar.y++;
            if (posChar.y > heigth) break;
            posChar.x = pos.x;
        }
        drawPixel(posChar, colorBG, colorFG, *it.base());
        posChar.x++;
    }
}

void GraphicPlane::end() {
    updateConsole.unlock();
}

void GraphicPlane::begin() {
    updateConsole.lock();
}

CursorAttributes GraphicPlane::getRandomBGColor() {
    switch (rand() % 16) {
        case 0:
            return pb::BG_WHITE;
        case 1:
            return pb::BG_BLUE;
        case 2:
            return pb::BG_GREEN;
        case 3:
            return pb::BG_RED;
        case 4:
            return pb::BG_YELLOW;
        case 5:
            return pb::BG_CYAN;
        case 6:
            return pb::BG_MAGENTA;
        case 7:
            return pb::BG_BLACK;
        case 8:
            return pb::BG_INTENSITY_BLACK;
        case 9:
            return pb::BG_INTENSITY_YELLOW;
        case 10:
            return pb::BG_INTENSITY_WHITE;
        case 11:
            return pb::BG_INTENSITY_BLUE;
        case 12:
            return pb::BG_INTENSITY_CYAN;
        case 13:
            return pb::BG_INTENSITY_GREEN;
        case 14:
            return pb::BG_INTENSITY_MAGENTA;
        default:
            return pb::BG_INTENSITY_RED;
    }
}


CursorAttributes GraphicPlane::getRandomFGColor() {
    return pb::FG_INTENSITY_WHITE;
    switch (rand() % 16) {
        case 0:
            return pb::FG_WHITE;
        case 1:
            return pb::FG_BLUE;
        case 2:
            return pb::FG_GREEN;
        case 3:
            return pb::FG_RED;
        case 4:
            return pb::FG_YELLOW;
        case 5:
            return pb::FG_CYAN;
        case 6:
            return pb::FG_MAGENTA;
        case 7:
            return pb::FG_BLACK;
        case 8:
            return pb::FG_INTENSITY_BLACK;
        case 9:
            return pb::FG_INTENSITY_YELLOW;
        case 10:
            return pb::FG_INTENSITY_WHITE;
        case 11:
            return pb::FG_INTENSITY_BLUE;
        case 12:
            return pb::FG_INTENSITY_CYAN;
        case 13:
            return pb::FG_INTENSITY_GREEN;
        case 14:
            return pb::FG_INTENSITY_MAGENTA;
        default:
            return pb::FG_INTENSITY_RED;
    }
}
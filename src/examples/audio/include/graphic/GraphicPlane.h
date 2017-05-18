//
// Created by zulus on 29.04.17.
//

#ifndef THREADS_CONSOLE_H
#define THREADS_CONSOLE_H

#include <progbase-cpp/console.h>
#include <graphic/GraphUtil.h>
#include <mutex>

using namespace progbase;
using namespace console;

#define DEFAULT_WIDTH 80
#define DEFAULT_HEIGHT 30


class GraphicPlane {
private:
    typedef struct {
        CursorAttributes colorBG;
        CursorAttributes colorFG;
        char symbol;
    } Dot;
    std::mutex updateConsole;
    int width;
    int heigth;
    Dot **userBuffer;
    Dot **consoleBuffer;
    CursorAttributes defaultColorBG;
    CursorAttributes defaultColorFG;
public:
    void clear(CursorAttributes colorBG, CursorAttributes colorFG);

    static CursorAttributes getRandomBGColor();

    int getWidth() const;

    int getHeigth() const;

    CursorAttributes getDefaultColorBG() const;

    void redraw();

    void drawLine(const Vec2D &p1, const Vec2D &p2, CursorAttributes color);

    void drawCircle(const Vec2D &center, double radius, CursorAttributes color);

    GraphicPlane(int width, int heigth, CursorAttributes defaultColorBG = pb::BG_INTENSITY_BLACK,
                 CursorAttributes defaultColorFG = pb::FG_INTENSITY_WHITE);

    void print(const std::string &std, CursorAttributes colorBG, CursorAttributes colorFG, const Vec2D &pos);

    void inline drawPixel(const Vec2D &pos, CursorAttributes color);

    void fillRect(const Vec2D &left, const Vec2D &right, CursorAttributes color);

    virtual ~GraphicPlane();

    void begin();

    void end();

    CursorAttributes getDefaultColorFG() const;

    void drawPixel(const Vec2D &pos, CursorAttributes colorBG, CursorAttributes colorFG, char symbol);

    void clear();

    void prepare();

    static CursorAttributes getRandomFGColor();
};


#endif //THREADS_CONSOLE_H

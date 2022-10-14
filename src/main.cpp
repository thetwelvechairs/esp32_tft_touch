#define LGFX_USE_V1

#include <LovyanGFX.hpp>
#include <random>
#include <map>
#include "setup.hpp"
#include <LGFX_TFT_eSPI.hpp>

static TFT_eSPI tft;

static TFT_eSprite buffer1(&tft);
static TFT_eSprite buffer2(&tft);
static TFT_eSprite *screenBuffers[2] = {&buffer1, &buffer2};

static TFT_eSprite xMark;

static uint32_t sec, psec;
static size_t fps = 0, frame_count = 0;

static uint32_t display_width;
static uint32_t display_height;

static bool collision = false;


void frames(){
    ++frame_count;
    sec = lgfx::millis() / 1000;
    if (psec != sec) {
        psec = sec;
        fps = frame_count;
        frame_count = 0;
    }
    tft.setCursor(2, 2);
    tft.printf("FPS: %d  X: %d  Y: %d", fps);

    if (collision){
        screenBuffers[0]->setCursor(2, 20);
        screenBuffers[0]->printf("COLLISION");
    }
}

void testingLayout(){
    xMark.pushSprite(screenBuffers[0], display_width >> 1, (display_height >> 1) + (display_height >> 2), TFT_BLACK);
    xMark.pushSprite(screenBuffers[0], display_width >> 1, display_height >> 1, TFT_BLACK);
    xMark.pushSprite(screenBuffers[0], display_width >> 1, display_height >> 2, TFT_BLACK);
    xMark.pushSprite(screenBuffers[0], 40, 40, TFT_BLACK);
    xMark.pushSprite(screenBuffers[0], 40, 120, TFT_BLACK);
    xMark.pushSprite(screenBuffers[0], 40, 200, TFT_BLACK);
    xMark.pushSprite(screenBuffers[0], 40, 280, TFT_BLACK);
    xMark.pushSprite(screenBuffers[0], 200, 40, TFT_BLACK);
    xMark.pushSprite(screenBuffers[0], 200, 120, TFT_BLACK);
    xMark.pushSprite(screenBuffers[0], 200, 200, TFT_BLACK);
    xMark.pushSprite(screenBuffers[0], 200, 280, TFT_BLACK);
}

int checkCollision(){
//    for (const auto &each : objects){
//    if (ball.y >= flipperL.y){
//        if (((ball.x >= flipperL.x && ball.x < flipperL.x + flipperL.width) &&
//             ball.y < flipperL.y + flipperL.height) ||
//            ((ball.x >= flipperR.x && ball.x < flipperR.x + flipperR.width) &&
//             ball.y < flipperR.y + flipperR.height)){
//            collision = true;
//            return 1;
//        }
//    }

//    }
    collision = false;
    return 0;
}

void setup(){
    try{
        tft.init();
        tft.setRotation(3);
        tft.setColorDepth(16);
        tft.setSwapBytes(true);
        tft.fillScreen(TFT_RED);

        display_width = tft.width();
        display_height = tft.height();

        screenBuffers[0]->setColorDepth(tft.getColorDepth());
        screenBuffers[0]->setFont(&fonts::Font2);
        screenBuffers[0]->setTextColor(0xFFFFFFU);
        screenBuffers[0]->createSprite(display_width, display_height);
        screenBuffers[1]->setColorDepth(tft.getColorDepth());
        screenBuffers[1]->setFont(&fonts::Font2);
        screenBuffers[1]->setTextColor(0xFFFFFFU);
        screenBuffers[1]->createSprite(display_width, display_height);

        xMark.setSwapBytes(true);
        xMark.createSprite(100, 100);
        xMark.drawLine(0, 0, 99, 99, TFT_WHITE);
        xMark.drawLine(0, 99, 99, 0, TFT_WHITE);

        tft.fillScreen(TFT_BLACK);
        tft.startWrite();
    }
    catch (std::exception const &e){
        tft.print(e.what());
    }
}

void loop(){
    try {
        screenBuffers[0]->clear();

        frames();

        tft.drawLine(0, 0, display_width, display_height, TFT_WHITE);
        tft.drawLine(0, display_height, display_width, 0,  TFT_WHITE);

        screenBuffers[0]->pushSprite(&tft, 0, 0);
        tft.display();
    }
    catch (std::exception const &e){
        tft.print(e.what());
    }
}
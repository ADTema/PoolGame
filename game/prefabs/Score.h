#ifndef PONG_SCORE_H
#define PONG_SCORE_H
#pragma once


#include "../../headers/templates/Text.h"
class Score: public Text{
   public:
    Score(int score);

    void update() override;
    void setScore(int score);

    int m_score = 0;
};


#endif  // PONG_SCORE_H

#include "Score.h"

Score::Score(int score) {
    this->m_score = score;
}

void Score::update() {
    Text::update();

}
void Score::setScore(int score) {
    this->m_score = score;
    setText(std::to_string(score));
}

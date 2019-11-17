//
// Created by Ryan Gurnick on 2019-05-27.
//

#include "heads/Score.h"

Score::Score() {
    score = 0;
}

Score::Score(int initScore) {
    score = initScore;
}

int Score::getPlayerScore() {
    return score;
}

int Score::operator++(int in) {
    score++;
    return this->score;
}

int Score::operator--(int in) {
    score--;
    return this->score;
}
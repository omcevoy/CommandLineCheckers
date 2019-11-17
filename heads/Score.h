//
// Created by Ryan Gurnick on 2019-05-27.
//

#ifndef GAME_SCORE_H
#define GAME_SCORE_H


class Score {
public:
    Score();
    Score(int initScore);

    int getPlayerScore();

    int operator ++(int in);
    int operator --(int in);

private:
    int score;
};


#endif //GAME_SCORE_H

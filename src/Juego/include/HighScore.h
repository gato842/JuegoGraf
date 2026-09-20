#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

struct HighScoreRecord {
    int score;
    char date[30];
};

struct Game;

void LoadHighScores(Game& game);
void SaveHighScores(const Game& game);
void AddHighScore(Game& game, int newScore);
void DrawHighScores(const Game& game);
void UpdateHighScores(Game& game);

#endif

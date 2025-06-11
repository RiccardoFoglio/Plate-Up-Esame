#ifndef RECORDS_H
#define RECORDS_H

#include <string>
#include <vector>

struct ScoreRecord {
    std::string timestamp;
    int score;
};

std::vector<ScoreRecord> getTopRecords(int topN = 10);

#endif // RECORDS_H

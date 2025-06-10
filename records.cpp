#include "records.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>


std::vector<ScoreRecord> getTopRecords(int topN) {
    std::ifstream file("records.txt");
    std::vector<ScoreRecord> records;

    std::string line;
    while (std::getline(file, line)) {
        size_t dashPos = line.find(" - ");
        if (dashPos == std::string::npos) continue;

        std::string timeStr = line.substr(0, dashPos);
        int score = std::stoi(line.substr(dashPos + 3));

        records.push_back({ timeStr, score });
    }

    std::sort(records.begin(), records.end(), [](const ScoreRecord& a, const ScoreRecord& b) {
        return a.score > b.score;
        });

    if (records.size() > topN)
        records.resize(topN);

    return records;
}

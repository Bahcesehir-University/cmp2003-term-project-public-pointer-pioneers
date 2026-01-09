#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <istream>
#include <cctype>

struct ZoneCount {
    std::string zone;
    long long count;
};

struct SlotCount {
    std::string zone;
    int hour;              
    long long count;
};

class TripAnalyzer {
public:
    void ingestFile(const std::string& csvPath);

    std::vector<ZoneCount> topZones(int k = 10) const;
    std::vector<SlotCount> topBusySlots(int k = 10) const;

private:
    std::unordered_map<std::string, long long> zoneTotals_;
    std::unordered_map<std::string, std::array<long long, 24>> zoneHourTotals_;

   
    static inline bool is_space_(unsigned char c) {
        return std::isspace(c) != 0;
    }

    static std::string trim_(const std::string& s);
    static bool splitCSVLine_(const std::string& line, std::vector<std::string>& out);
    static bool parseHourFromTimestamp_(const std::string& raw, int& outHour);
    static bool looksLikeHeader_(const std::vector<std::string>& cols);

    void processRow_(const std::vector<std::string>& cols);
    void ingestStream_(std::istream& in);
};

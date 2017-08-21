#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <map>

#define COMPARE 1 - std::exp(-4)

struct TagStats{
    size_t docs;
    std::unordered_map<std::string, size_t> tagVocab;
    size_t tagVocabSize;
} TTagStats;

std::string inputFile, outputFile, statsFile;
std::unordered_set<std::string> curTags, totalVocab;
std::unordered_map<std::string, struct TagStats> totalTags, classifyTags;
std::unordered_map<std::string, size_t> localVocab;
size_t totalDocs = 0, totalVocabSize = 0, mode = 0;

void Parse(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Error!" << std::endl;
        exit(-1);
    }
    if (!strcmp(argv[1], "learn")) {
        if (!strcmp(argv[2], "--input")) inputFile = argv[3];
        else {
            std::cout << "Error!" << std::endl;
            exit(-1);
        }
        if (!strcmp(argv[4], "--output")) outputFile = argv[5];
        else {
            std::cout << "Error!" << std::endl;
            exit(-1);
        }
        mode = 1;
    } else if (!strcmp(argv[1], "classify")) {
        if (!strcmp(argv[2], "--stats")) statsFile = argv[3];
        else {
            std::cout << "Error!" << std::endl;
            exit(-1);
        }
        if (!strcmp(argv[4], "--input")) inputFile = argv[5];
        else {
            std::cout << "Error!" << std::endl;
            exit(-1);
        }
        if (!strcmp(argv[6], "--output")) outputFile = argv[7];
        else {
            std::cout << "Error!" << std::endl;
            exit(-1);
        }
        mode = 2;
    } else {
        std::cout << "Error!" << std::endl;
        exit(-1);
    }
}

void GetWord(std::string& tmpStr, std::unordered_map<std::string, size_t>& words) {
    std::string word;
    for (int i = 0; i < tmpStr.length(); i++) {
        if (isalnum(tmpStr[i])) word += tolower(tmpStr[i]);
        else {
            if (!word.empty()) {
                if (tmpStr[i] == '#') {
                    word += tolower(tmpStr[i]);
                    continue;
                } else {
                    words[word]++;
                    totalVocab.insert(word);
                    localVocab[word]++;
                }
            }
            word.clear();
        }
    }
    if (!word.empty()) {
        words[word]++;
        totalVocab.insert(word);
        localVocab[word]++;
    }
}

void ParseTags(std::string& tags) {
    std::string tag;
    for (int i = 0; i < tags.length(); i++) {
        if (tags[i] != ',') tag += tolower(tags[i]);
        else {
            curTags.insert(tag);
            tag.clear();
        }
    }
    curTags.insert(tag);
}

void WriteStats() {
    std::ofstream statsF(outputFile);
    statsF << totalVocab.size() << " " << totalDocs << "\n";
    for (auto& it : totalTags) {
        statsF << it.first << " " << it.second.docs << " " << it.second.tagVocabSize << " " << it.second.tagVocab.size() << "\n";
        for (auto& j : it.second.tagVocab) statsF << j.first << " " << j.second << "\n";
    }
}

void ReadStats() {
    std::ifstream statsF(statsFile);
    totalVocabSize = 1, totalDocs = 1;
    statsF >> totalVocabSize >> totalDocs;
    std::string tag, word;
    size_t uniqWords, totalWords;
    while (statsF >> tag) {
        statsF >> classifyTags[tag].docs >> totalWords >> uniqWords;
        classifyTags[tag].tagVocabSize = totalWords;
        while (uniqWords > 0) {
            statsF >> word;
            statsF >> classifyTags[tag].tagVocab[word];
            uniqWords--;
        }
    }
}

int main(int argc, char* argv[]) {
    Parse(argc, argv);
    std::unordered_map<std::string, size_t> words;
    std::ifstream inF(inputFile);
    std::string tmpStr, tags;
    size_t lines = 0;
    if (mode == 1) {
        while (inF >> lines) {
            inF.get();
            while (lines > 0) {
                getline(inF, tmpStr);
                GetWord(tmpStr, words);
                words.clear();
                lines--;
            }
            inF >> tags;
            ParseTags(tags);
            for (auto& it : curTags) totalTags[it].docs++;
            for (auto& it : curTags) {
                for (auto& j : localVocab) {
                    totalTags[it].tagVocab[j.first] += j.second;
                    totalTags[it].tagVocabSize += j.second;
                }
            }
            curTags.clear();
            localVocab.clear();
            totalDocs++;
        }
        WriteStats();
    } else if (mode == 2) {
        ReadStats();
        long double res = 0;
        std::ofstream outF(outputFile);
        words.clear();
        while (inF >> lines) {
            std::multimap<long double, std::string> final;
            inF.get();
            inF.get();
            while (lines > 0) {
                std::string buf;
                getline(inF, buf);
                GetWord(buf, words);
                lines--;
            }
            for (auto& it : classifyTags) {
                res = std::log((double)it.second.docs / (double)totalDocs);
                for (auto& word : words) {
                    std::unordered_map<std::string, size_t>::const_iterator got = it.second.tagVocab.find(word.first);
                    long double denom = (double)totalVocabSize + (double)classifyTags[it.first].tagVocabSize;
                    long double tmp;
                    if (got == it.second.tagVocab.end()) tmp = std::log(1. / denom) * word.second;
                    else tmp = std::log(((double)got->second + 1.) / denom) * word.second;
                    res += tmp;
                }
                final.insert(std::pair<long double, std::string>(res, it.first));
            }
            std::multimap<long double, std::string>::reverse_iterator rit = final.rbegin();            
            if (rit != final.rend()) outF << rit->second;
            while (rit != final.rend()) {
                long double cmp = (double)((rit++)->first) - ((double)rit->first);
                if (cmp >= COMPARE) break;
                auto tmp = (rit--)->second;
                outF << "," << tmp;
                rit++;
            }
            outF << "\n";
            words.clear();
        }
    } else std::cout << "Error!" << std::endl;
}
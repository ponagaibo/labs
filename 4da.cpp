#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
unsigned int pat_len = 0;
bool full = 1;
unsigned int countStr = 1;
unsigned int countWord = 0;

using std::cin; using std::cout; using std::endl; using std::string;

void PrintVect(const std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > >& textBuf) {
	//cout << "*** PRINT VEC ***" << endl;
	//cout << "size of vector: " << textBuf.size() << endl;

	for(unsigned int i = 0; i < textBuf.size(); i++) {
		unsigned int sp;
        //std::cout << "[ " << textBuf[i].first << ", " << (textBuf[i].second).first
		//<< ' ' << (textBuf[i].second).second << " ] ";
		sp = (textBuf[i].second).second;
		if (sp != (textBuf[i + 1].second).second && i < textBuf.size() - 1) {
			sp = (textBuf[i + 1].second).second;
			cout << '\n';
		}
    }
	//cout << endl;
}

void ZFunc(std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > >& vec,
std::vector<std::pair<unsigned int,unsigned int> >& res) {
	unsigned int n;
	if (full) {
		n = 6 * pat_len;
	} else {
		n = vec.size();
	}
    //std::cout << "size: " << n << std::endl;
	std::vector<unsigned int> z (n);
	z[0] = 0;
	unsigned int l = 0;
	unsigned int r = 0;

	for (unsigned int i = 1; i < n; ++i) {
		int min = std::min(r - i, z[i - l]);
		z[i] = std::max( 0, min );
		while (i + z[i] < n && vec[z[i]].first == vec[i + z[i]].first) {
			++z[i];
			//cout << "while equal, z[i] = " << z[i] << endl;
		}

		if (i + z[i] >= r) {
            l = i;
            r = i + z[i];
			//cout << "new border, l = " << i << ", r = " << r << endl;
        }

        if (z[i] >= pat_len && i >= pat_len) {
			//cout << "found inclusion! at i = " << i << endl;
            res.push_back( std::make_pair( (vec[i].second).first, (vec[i].second).second ));
        }
	}

    //std::cout << "print z" << std::endl;
	/*
    for(int i = 0; i < z.size(); i++)
        std::cout << z[i] << ' ';
    std::cout << std::endl;
*/
	//cout << "inclusions: " << endl;
	//cout << "*** PRINT VEC ***" << endl;
/*
	for(int i = 0; i < res.size(); i++) {
		unsigned int sp;
		//std::cout << "[ " << res[i].first << " " << res[i].second << " ] ";
		sp = res[i].second;
		if (sp != res[i + 1].second && i < res.size() - 1) {
			sp = res[i + 1].second;
			cout << '\n';
		}
	}*/
	//cout << endl;
}

void GetPattern(std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > >& pttrn) {
	bool severalSpaces = 0;
	unsigned int word = 0;
	char c;
	scanf("%c", &c);
	while (c != '\n') {
		if (c >= '0' && c <= '9') {
			word *= 10;
			word += (c - '0');
			severalSpaces = 0;
		} else if (c == ' '){
			if (!severalSpaces) {
				pttrn.push_back(std::make_pair(word, std::make_pair(0,0)));
			}
			severalSpaces = 1;
			word = 0;
		}
		scanf("%c", &c);
	}
	if (!severalSpaces) {
		pttrn.push_back(std::make_pair(word, std::make_pair(0,0)));
	}
}

void GetText(std::vector<std::pair<unsigned int,
			 std::pair<unsigned int,unsigned int> > >& textBuf,
			 unsigned int bufferSize) {
	//cout << "max size = " << bufferSize << endl;
	unsigned int word = 0;
	bool severalDelim = 0;
	char c;
	unsigned int size = textBuf.size();
	while (scanf("%c", &c) != EOF && size != bufferSize) {
		//cout << "current size = " << size << ", is full: " << full
		//<< ", max size: " << bufferSize << endl;
		if (c >= '0' && c <= '9') {
			word *= 10;
			word += (c - '0');
			severalDelim = 0;
		} else if (c == ' ' && !severalDelim) {
			++countWord;
			textBuf.push_back(std::make_pair(word, std::make_pair(countWord, countStr)));
			++size;
			word = 0;
			severalDelim = 1;
		} else if (c == '\n') {
			if (!severalDelim) {
				++countWord;
				textBuf.push_back(std::make_pair(word, std::make_pair(countWord, countStr)));
				++size;
				severalDelim = 1;
			}
			++countStr;
			word = 0;
			countWord = 0;
		}
	}
	if (size < bufferSize) {
		full = 0;
	} else {
		ungetc(c, stdin);
	}
	//cout << "full: " << full << endl;
}

int main() {

	std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > > pat;
	GetPattern(pat);
	pat_len = pat.size();
	//cout << "size of pattern is " << pat_len << endl;

	//std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > > textBuf;
	unsigned int bufferSize = 8 * pat.size();
	//GetText(textBuf, bufferSize);
	//cout << "get text " << endl;
	GetText(pat, bufferSize);
	//PrintVect(pat);
	std::vector< std::pair<unsigned int,unsigned int> > res;
	while (full) {
		ZFunc(pat, res);
		pat.erase(pat.begin() + pat_len, pat.begin() + 6 * pat_len);
		//cout << "CUTTED: " << endl;
		//PrintVect(pat);
		//cout << "PROLONGED: " << endl;
		GetText(pat, bufferSize);
		//PrintVect(pat);

	}
	ZFunc(pat, res);
	//cout << "TOTAL: " << endl;
	for(unsigned int i = 0; i < res.size(); i++) {
		std::cout << res[i].second << ", " << res[i].first << endl;
	}
	//cout << endl;

	//PrintVect(textBuf);
	//ZFunc(textBuf);
/*
	cout << "*** PRINT VEC ***" << endl;

	for(int i = 0; i < textBuf.size(); i++) {
		unsigned int sp;
        std::cout << "[ " << textBuf[i].first << ", " << (textBuf[i].second).first
		<< ' ' << (textBuf[i].second).second << " ] ";
		sp = (textBuf[i].second).second;
		if (sp != (textBuf[i + 1].second).second && i < textBuf.size() - 1) {
			sp = (textBuf[i + 1].second).second;
			cout << '\n';
		}
    }
	cout << endl;
*/
    return 0;
}

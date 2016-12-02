#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <ctime>

unsigned int pat_len = 0;
unsigned int RANGE = 48;
unsigned int BUFSIZE = 50;
bool full = 0;
unsigned int countStr = 1;
unsigned int countWord = 0;
unsigned int zf = 0;

using std::cin; using std::cout; using std::endl; using std::string;

void PrintVect(const std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > >& textBuf) {
	cout << "*** PRINT VEC ***" << endl;
	//cout << "size of vector: " << textBuf.size() << endl;
	for(unsigned int i = 0; i < textBuf.size(); i++) {
		unsigned int sp;
        std::cout << "[ " << textBuf[i].first << ", " << (textBuf[i].second).first
		<< ' ' << (textBuf[i].second).second << " ] ";
		sp = (textBuf[i].second).second;
		if (i < textBuf.size() - 1 && sp != (textBuf[i + 1].second).second) {
			sp = (textBuf[i + 1].second).second;
			cout << '\n';
		}
    }
	cout << endl;
}

void ZFunc(std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > >& vec,
std::vector<std::pair<unsigned int,unsigned int> >& res) {
	++zf;
	//cout << "st: " << st << endl;
	unsigned int n;
	if (full) {
		n = (RANGE + 1) * pat_len;
	} else {
		n = vec.size();
	}
	std::vector<unsigned int> z (n);
	z[0] = 0;
	unsigned int l = 0;
	unsigned int r = 0;

	for (unsigned int i = 1; i < n; ++i) {
		int min = std::min(r - i, z[i - l]);
		z[i] = std::max( 0, min );
		while (i + z[i] < n && vec[z[i]].first == vec[i + z[i]].first) {
			++z[i];
		}

		if (i + z[i] <= r) {
            l = i;
            r = i + z[i] - 1;
        }
        if (z[i] >= pat_len && i >= pat_len) {
            res.push_back( std::make_pair( (vec[i].second).first, (vec[i].second).second ));
        }
/*
		if(st == 160 || st == 153) {
			cout << "num: " << vec[i].first << ", st: " << st << endl;
			cout << "size: " << n << ", l = " << l << ", r = " << r
			<< ", i = " << i << ", z[i] = " << z[i] << endl;
			cout << "print z" << endl;
			for(int i = 0; i < z.size(); i++)
				std::cout << z[i] << ' ';
			std::cout << std::endl;
		}
		*/
	}
}

void GetPattern(std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > >& pttrn) {
	bool severalSpaces = 1;
	unsigned int word = 0;
	char c;
	c = getchar_unlocked();
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
		c = getchar_unlocked();
	}
	if (!severalSpaces) {
		pttrn.push_back(std::make_pair(word, std::make_pair(0,0)));
	}
}

void GetText(std::vector<std::pair<unsigned int,
			 std::pair<unsigned int,unsigned int> > >& textBuf,
			 unsigned int bufferSize) {
	unsigned int word = 0;
	full = 0;
	unsigned int size = textBuf.size();
	bool severalDelim = 1;
	char c;
	while ((c = getchar_unlocked()) != EOF) {
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
			if (size == bufferSize) {
				full = 1;
				break;
			}
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
			if (size == bufferSize) {
				full = 1;
				break;
			}
		}
	}
}

int main() {
	unsigned int start = clock();
	std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > > pat;
	GetPattern(pat);
	pat_len = pat.size();
	unsigned int bufferSize = BUFSIZE * pat.size();
	GetText(pat, bufferSize);
	std::vector< std::pair<unsigned int,unsigned int> > res;
	while (full) {
		ZFunc(pat, res);
		unsigned int pos = 1;
		for (unsigned int i = (RANGE * pat_len); i < (BUFSIZE * pat_len); i++) {
			pat[pos++] = pat[i];
		}
		pat.resize(pos);
		pat.reserve(bufferSize);
		GetText(pat, bufferSize);
	}
	/*
	while (full) {
		ZFunc(pat, res);
		//cout << "before " << endl;
		//PrintVect(pat);
		pat.erase(pat.begin() + pat_len, pat.begin() + RANGE * pat_len + 1);
		//cout << "after " << endl;
		//PrintVect(pat);
		GetText(pat, bufferSize);
	}
	*/
	ZFunc(pat, res);
	for(unsigned int i = 0; i < res.size(); i++) {
		std::cout << res[i].second << ',' << res[i].first << endl;
	}
	cout << "zf = " << zf << endl;
	unsigned int end = clock();
	std::cout << "TIME: " << end-start << " ms." << std::endl;
    return 0;
}

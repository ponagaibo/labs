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
	cout << "*** PRINT VEC ***" << endl;
	//cout << "size of vector: " << textBuf.size() << endl;
	for(unsigned int i = 0; i < textBuf.size(); i++) {
		unsigned int sp;
        std::cout << "[ " << textBuf.at(i).first << ", " << (textBuf.at(i).second).first
		<< ' ' << (textBuf.at(i).second).second << " ] ";
		sp = (textBuf.at(i).second).second;
		if (i < textBuf.size() - 1 && sp != (textBuf.at(i + 1).second).second) {
			sp = (textBuf.at(i + 1).second).second;
			cout << '\n';
		}
    }
	cout << endl;
}

void ZFunc(std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > >& vec,
std::vector<std::pair<unsigned int,unsigned int> >& res) {
	unsigned int n;
	if (full) {
		n = 6 * pat_len;
	} else {
		n = vec.size();
	}
	std::vector<unsigned int> z (n);
	z[0] = 0;
	unsigned int l = 0;
	unsigned int r = 0;

	for (unsigned int i = 1; i < n; ++i) {
		//std::cout << "TEXT:" << std::endl;
		//PrintVect(vec);
		//std::cout << std::endl;
		//std::cout << "i = " << i << ", z[i] = " << z.at(i) << ", l = " << l << ", r = " << r << endl;

		int min = std::min(r - i, z.at(i - l));
		z.at(i) = std::max( 0, min );
		while (i + z.at(i) < n && vec.at(z.at(i)).first == vec.at(i + z.at(i)).first) {
			//cout << "while equal, z[i] = " << z[i] << ", i = " << i << endl;
			++z.at(i);
		}

		if (i + z.at(i) <= r) {
            l = i;
            r = i + z.at(i) - 1;
			//cout << "new border, l = " << i << ", r = " << r << endl;
        }
        if (z.at(i) >= pat_len && i >= pat_len) {
			//cout << "found inclusion! at i = " << i << ", z[i] = " << z.at(i) << endl;
            res.push_back( std::make_pair( (vec.at(i).second).first, (vec.at(i).second).second ));
        }
/*
		std::cout << "print z" << std::endl;
		for(int i = 0; i < z.size(); i++)
			std::cout << z[i] << ' ';
		std::cout << std::endl;
*/
	}
}

void GetPattern(std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > >& pttrn) {
	bool severalSpaces = 1;
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
	//cout << "PATTERN: " << endl;
	//PrintVect(pttrn);
}

void GetText(std::vector<std::pair<unsigned int,
			 std::pair<unsigned int,unsigned int> > >& textBuf,
			 unsigned int bufferSize) {
	unsigned int word = 0;
	bool severalDelim = 1;
	char c;
	unsigned int size = textBuf.size();
	while (scanf("%c", &c) != EOF && size != bufferSize) {
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
}

int main() {
	std::vector<std::pair<unsigned int, std::pair<unsigned int,unsigned int> > > pat;
	GetPattern(pat);
	pat_len = pat.size();
	unsigned int bufferSize = 8 * pat.size();
	GetText(pat, bufferSize);
	std::vector< std::pair<unsigned int,unsigned int> > res;
	while (full) {
		ZFunc(pat, res);
		pat.erase(pat.begin() + pat_len, pat.begin() + 6 * pat_len);
		GetText(pat, bufferSize);
	}
	ZFunc(pat, res);
	//cout << "inclusions: " << endl;
	for(unsigned int i = 0; i < res.size(); i++) {
		std::cout << res.at(i).second << ',' << res.at(i).first << endl;
	}
    return 0;
}

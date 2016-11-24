#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
int pat_len = 0;
int words = 1;
/*
std::vector<int> z_functionS (std::string s) {
	int n = (int) s.length();
    std::cout << "length: " << s.length() << std::endl;
    std::vector<int> ress;
	std::vector<int> z (n);
	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r)
			z[i] = std::min(r - i + 1, z[i-l]);
		while (i +z [i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
        if (i > pat_len && s[i] == ' ') {
            ++words;
        }
        if (z[i] == pat_len) {
            ress.push_back(words);
        }
	}
    std::cout << "print inclusions" << std::endl;
    for(int i = 0; i < ress.size(); i++)
        std::cout << ress[i] << ' ';
    std::cout << std::endl;
	return z;
}
*/
/*
std::vector<int> ZFunc (std::vector<int, int>& vec) {
	int n = (int) v.size();
    std::cout << "size: " << n << std::endl;
    std::vector<int> ress;
	std::vector<int> z (n);
	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r)
			z[i] = std::min(r - i + 1, z[i - l]);
		while (i + z[i] < n && vec[z[i]].first == vec[i + z[i]].first)
			++z[i];
		if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }

        if (z[i] == pat_len) {
            ress.push_back(words);
        }
	}
    std::cout << "print inclusions" << std::endl;
    for(int i = 0; i < ress.size(); i++)
        std::cout << ress[i] << ' ';
    std::cout << std::endl;
	return z;
}
*/
using std::cin; using std::cout; using std::endl; using std::string;
int main() {
	int countStr = 0;
	int wd;
/*
    string patt = "cat dog cat dog bird";//"abcaba";
    string text1 = "CAT dog CaT Dog Cat DOG bird CAT\n";
	string text2 = "dog cat dog bird";
	int text3;
	std::getline(cin, text3);
	cout << "*** PRINT STRINGS ***" << endl;
	cout << text1 << text2 << endl;
	if (!text3.compare("\0")) cout << "eof" << endl;
	cout << text3 << text3 << endl;
*/
	std::vector< std::pair<int, int> > vec;
	std::vector<int> pat;
	char c;
	int cc;
	cin >> c;
	while (c != '\n') {
		ungetc(c, stdin);
		cin >> wd;
		pat.push_back(wd);
		cout << "got: " << wd << endl;
		cin >> c;
	}

	while (cin >> c) {
		if (c == '\n') {
			++countStr;
		}
		ungetc(c, stdin);
		cin >> wd;
		vec.push_back( std::make_pair(wd, countStr) );
	}
	cout << "*** PRINT VEC ***" << endl;

	for(int i = 0; i < vec.size(); i++) {
		int s = 1;
        std::cout << "[ " << vec[i].first << " " << vec[i].second << " ] ";
		if (s != vec[i].second) {
			cout << '\n';
			s = vec[i].second;
		}
    }
/*
	//vec.push_back()
    std::transform(text1.begin(), text1.end(), text1.begin(), tolower);
	std::transform(text2.begin(), text2.end(), text2.begin(), tolower);
    pat_len = patt.length();
    patt.push_back('$');
    patt.append(text1, 0, text1.length() - 1);
	patt.push_back(' ');
	patt.append(text2);
    cout << patt << endl;

    std::vector<int> res = z_functionV(vec);
    for(int i = 0; i < res.size(); i++)
        cout << res[i] << ' ';
    cout << endl;
*/
    return 0;
}

/*
디지털미디어학과 2019111253 박서윤 페이지 교체 알고리즘
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int page[10];


int FIFO() {
	vector<int> v1;
	int count = 0;//성공횟수
	for (int i = 0; i < 10; i++) {
		if (i < 3)
			v1.push_back(page[i]);
		else {
			int num = 0; //3칸 돌았는지 확인용
			for (int j = 0; j < 3; j++) {
				if (page[i] == v1[j]) {
					count++;
					break;
				}
				else {
					num++;
					if (num == 3) {
						v1.erase(v1.begin()); //첫번째 원소 제거
						v1.push_back(page[i]);
					}
				}
			}
		}
	}
	
	return count;
}
int LRU() {
	vector<pair<int, int>>v;
	int count = 0;//성공횟수
	int recent = 0;
	for (int i = 0; i < 10; i++) {
		if (i < 3) {
			recent++;
			v.push_back(pair<int, int>(page[i], recent));
		}
		else {
			int num = 0; //3칸 돌았는지 확인용
			int min = 10; //횟수
			int replace = 0; //위치
			for (int j = 0; j < 3; j++) {
				if (page[i] == v[j].first) {
					recent++;
					v[j].second = recent;
					count++;
					break;
				}
				else {
					if (v[j].second <= min) {
						min = v[j].second;
						replace = j;
					}
					num++;
					if (num == 3) {
						v[replace].first = page[i];
						recent++;
						v[replace].second = recent;

					}
				}
			}
		}
	}

	return count;
}
int LFU() {
	vector<pair<int, int>>v;
	int count = 0;//성공횟수
	int frequency = 1;
	for (int i = 0; i < 10; i++) {
		if (i < 3) {
			v.push_back(pair<int, int>(page[i], frequency));
		}
		else {
			int num = 0; //3칸 돌았는지 확인용
			int min = 10; //횟수
			int replace = 0; //위치
			for (int j = 0; j < 3; j++) {
				if (page[i] == v[j].first) {
					v[j].second += 1;
					count++;
					break;
				}
				else {
					if (v[j].second < min) {
						min = v[j].second;
						replace = j;
					}
					num++;
					if (num == 3) {
						v[replace].first = page[i];
						v[replace].second = 1;
					}
				}
			}
		}
	}

	return count;
}
int NUR() {
	vector<pair<int, int>>v;
	int count = 0;//성공횟수
	int bit = 0;
	int a = 0; int b = 0; //각각 참조비트, 변경비트
	for (int i = 0; i < 10; i++) {
		if (i < 3) {
			a = 0 * 10; b = 0;
			bit = a + b;
			v.push_back(pair<int, int>(page[i], bit));
		}
		else {
			int num = 0; //3칸 돌았는지 확인용
			int min = 12; //최대가 11이기에
			int replace = 0; //위치
			for (int j = 0; j < 3; j++) {
				if (page[i] == v[j].first) {
					a = 1 * 10;
					v[j].second = a + b;
					count++;
					break;
				}
				else {
					if (v[j].second < min) {
						min = v[j].second;
						replace = j;
					}
					num++;
					if (num == 3) {
						v[replace].first = page[i];
						v[replace].second = 0;
					}
				}
			}
		}
	}

	return count;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	char c;
	for (int i = 0; i < 10; i++) {
		cin >> c;
		//A B C D B A B A C A
		page[i] = c; //아스키코드
	}

	
	cout << "FIFO의 페이지 성공 횟수 =  " << FIFO() << "회\n";
	cout << "LRU의 페이지 성공 횟수 =  " << LRU() << "회\n";
	cout << "LFU의 페이지 성공 횟수 =  " << LFU() << "회\n";
	cout << "NUR의 페이지 성공 횟수 =  " << NUR() << "회\n";

	return 0;
}
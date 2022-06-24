/*
�����й̵���а� 2019111253 �ڼ��� ������ ��ü �˰���
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int page[10];


int FIFO() {
	vector<int> v1;
	int count = 0;//����Ƚ��
	for (int i = 0; i < 10; i++) {
		if (i < 3)
			v1.push_back(page[i]);
		else {
			int num = 0; //3ĭ ���Ҵ��� Ȯ�ο�
			for (int j = 0; j < 3; j++) {
				if (page[i] == v1[j]) {
					count++;
					break;
				}
				else {
					num++;
					if (num == 3) {
						v1.erase(v1.begin()); //ù��° ���� ����
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
	int count = 0;//����Ƚ��
	int recent = 0;
	for (int i = 0; i < 10; i++) {
		if (i < 3) {
			recent++;
			v.push_back(pair<int, int>(page[i], recent));
		}
		else {
			int num = 0; //3ĭ ���Ҵ��� Ȯ�ο�
			int min = 10; //Ƚ��
			int replace = 0; //��ġ
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
	int count = 0;//����Ƚ��
	int frequency = 1;
	for (int i = 0; i < 10; i++) {
		if (i < 3) {
			v.push_back(pair<int, int>(page[i], frequency));
		}
		else {
			int num = 0; //3ĭ ���Ҵ��� Ȯ�ο�
			int min = 10; //Ƚ��
			int replace = 0; //��ġ
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
	int count = 0;//����Ƚ��
	int bit = 0;
	int a = 0; int b = 0; //���� ������Ʈ, �����Ʈ
	for (int i = 0; i < 10; i++) {
		if (i < 3) {
			a = 0 * 10; b = 0;
			bit = a + b;
			v.push_back(pair<int, int>(page[i], bit));
		}
		else {
			int num = 0; //3ĭ ���Ҵ��� Ȯ�ο�
			int min = 12; //�ִ밡 11�̱⿡
			int replace = 0; //��ġ
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
		page[i] = c; //�ƽ�Ű�ڵ�
	}

	
	cout << "FIFO�� ������ ���� Ƚ�� =  " << FIFO() << "ȸ\n";
	cout << "LRU�� ������ ���� Ƚ�� =  " << LRU() << "ȸ\n";
	cout << "LFU�� ������ ���� Ƚ�� =  " << LFU() << "ȸ\n";
	cout << "NUR�� ������ ���� Ƚ�� =  " << NUR() << "ȸ\n";

	return 0;
}
/*
�����й̵���а� 2019111253 �ڼ��� CPU �����ٸ� ����
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
#include <math.h>
using namespace std;

vector<pair<int, int>>v;
int a, b; //�����ð�, �۾��ð�
const int N = 3; //3���� ���μ���
int timeSlice = 5; //Ÿ�ӽ����̽� 5ms
int totalBurstTime = 0; //��ü ���μ��� �۾��ð� ��

float FCFS() {
	float waitingTime = 0; //��� ���ð�
	int sum = 0;
	int time = 0;

	for (int i = 0; i < N-1; i++) { //2��° ���μ������� ���
		if (i == 0) {
			time = v[i].second - v[i + 1].first;
		}
		else {
			time =  v[i-1].second + v[i].second - v[i + 1].first;
		}
		sum += time;
	}
	waitingTime = (float)sum / N;
	waitingTime *= 10;
	waitingTime = round(waitingTime);
	waitingTime /= 10;
	return waitingTime;
}
float HRN() {
	vector<tuple<float, int, int>>hrn;
	float p; //�켱����
	int aa, bb; 

	for (int i = 1; i < N; i++) { //ù��° ���μ����� �����ð� 0�̱⿡ ����
		p = (float) (v[0].second - v[i].first + v[i].second) / v[i].second;
		aa = v[i].first;
		bb = v[i].second;
		hrn.push_back(make_tuple(p, aa, bb));
	}
	sort(hrn.begin(), hrn.end(), greater<>()); 

	float waitingTime = 0; //��� ���ð�
	int sum = 0;
	int time = 0;

	for (int i = 0; i < N-1; i++) {
		if (i == 0) {
			time = v[0].second - get<1>(hrn[i]);
		}
		else {
			time = v[0].second + get<2>(hrn[i-1]) - get<1>(hrn[i]);
		}
		sum += time;
	}
	waitingTime = (float)sum / N;
	waitingTime *= 10;
	waitingTime = round(waitingTime);
	waitingTime /= 10;
	return waitingTime;
}
float RR(vector<pair<int, int>> v) {
	float waitingTime = 0; //��� ���ð� 
	int tb = totalBurstTime;
	int sum = 0;
	int time = 0;
	int used = 0;
	int self[3] = { 0, };
	int cnt = 0;

	while (tb > 0 ) {
		for (int i = 0; i < N; i++) {
			if (cnt < 3) {
				if (v[i].second > timeSlice-1) {
					time = used - v[i].first;
					v[i].second -= timeSlice;
					tb -= timeSlice;
					used += timeSlice;
					self[i] = timeSlice;
					

				}
				else {
					time = used - v[i].first;
					used += v[i].second;
					tb -= v[i].second;
					self[i] = v[i].second;
					v[i].second = 0;
					
				}
				cnt++;
			}//ù����
			else {
				if (v[i].second > timeSlice-1) {
					time = used - self[i];
					used -= self[i]; 
					v[i].second -= timeSlice;
					tb -= timeSlice;
					used += timeSlice; 
					self[i] = timeSlice;
					

				}
				else if (v[i].second == 0) {
					used -= self[i];
					self[i] = 0;
					time = 0;
				}
				else {
					time = used - self[i];
					used -= self[i];
					tb -= v[i].second;
					used += v[i].second;
					self[i] = v[i].second;
					v[i].second = 0;
					
				}
			}
			sum += time;
			if (tb < 1) {
				break;
			}
		}
	}
	waitingTime = (float)sum / N;
	waitingTime *= 10;
	waitingTime = round(waitingTime);
	waitingTime /= 10;
	return waitingTime;
}
float SRT(vector<pair<int, int>> v) {
	int queue[3] = { 0,1,2 };
	int sum = 0;
	int time = 0;
	int used = 0;
	float waitingTime = 0;

	while (v[queue[0]].second > 0 || v[queue[1]].second > 0 || v[queue[2]].second > 0) {
		if (v[queue[0]].second > timeSlice) {
			used = timeSlice;
		}
		else {
			used = v[queue[0]].second;
		}
		time += used;

		if (time > v[queue[1]].first && v[queue[1]].second > 0) {
			if (v[queue[1]].first > time - timeSlice) {
				sum += time - v[queue[1]].first;
			}
			else if (v[queue[0]].second > timeSlice) {
				sum += timeSlice;
			}
			else if (v[queue[0]].second > 0) {
				sum += v[queue[0]].second;
			}
		}
		if (time > v[queue[2]].first && v[queue[2]].second > 0) {
			if (v[queue[2]].first > time - timeSlice) {
				sum += time - v[queue[2]].first;
			}
			else if (v[queue[0]].second > timeSlice) {
				sum += timeSlice;
			}
			else if (v[queue[0]].second > 0) {
				sum += v[queue[0]].second;
			}
		}
		v[queue[0]].second -= used;

		int temp = queue[0];
		if (v[queue[0]].second == 0) {
			if (v[queue[1]].second > 0 && v[queue[1]].second < v[queue[2]].second) {
				queue[0] = queue[1];
				queue[1] = temp;
			}
			else if (v[queue[2]].second > 0) {
				queue[0] = queue[2];
				queue[2] = temp;
			}
		}
		else if (v[queue[1]].second > 0 
			&& v[queue[1]].second < v[queue[0]].second
			&& v[queue[1]].second < v[queue[2]].second) {
			queue[0] = queue[1];
			queue[1] = temp;
		}
		else if (v[queue[2]].second > 0 
			&& v[queue[2]].second < v[queue[0]].second
			&& v[queue[2]].second < v[queue[1]].second) {
			queue[0] = queue[2];
			queue[2] = temp;
		}
	}


	waitingTime = (float)sum / N;
	waitingTime *= 10;
	waitingTime = round(waitingTime);
	waitingTime /= 10;
	return waitingTime;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		v.push_back(pair<int, int>(a, b));	
		totalBurstTime += b;
	}//�� 3���� ���μ��� �Է�
	sort(v.begin(), v.end()); // �����ð� �������� ����

	cout << "FCFS: ��� ���ð� " << FCFS() << "ms\n";
	cout << "HRN: ��� ���ð� " << HRN() << "ms\n";
	cout << "RR: ��� ���ð� " << RR(v) << "ms\n";
	cout << "SRT: ��� ���ð� " << SRT(v) << "ms\n";

	return 0;
}
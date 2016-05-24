#include <cstdio>
#include <queue>
#include <vector>

#define MAX_NODES 20002
#define INF 300000

using namespace std;

struct edge{
	int end_node;	// ���� ����
	int weight;	// ���� ����ġ
};

struct node{
	int distance;	// ������ '�ִ� �Ÿ�'
	bool selected;	// ���õǾ������� ����
};

struct element{
	int node_number;	// ������ ��ȣ
	int distance;		// ������ '�ִ� �Ÿ�'

	/* ������(<) �������̵�.
	�Ÿ��� ���� element�� PQ�� �� ���� �����ϵ��� ������ش�.*/
	bool operator<(const element &A)const{
		return distance > A.distance;
	}
};

vector<edge> edges[MAX_NODES];
node nodes[MAX_NODES];
priority_queue<element> turn;

void dijkstra(int source){

	// 1. ó���� ��� ������ �ִ� �Ÿ��� '�𸥴�'�� �����Ѵ�.
	for (int i = 0; i < MAX_NODES; i++){
		nodes[i].distance = INF;
		nodes[i].selected = false;
	}

	// 2. �������� �ִ� �Ÿ��� 0���� �����Ѵ�.
	nodes[source].distance = 0;
	turn.push({ source, 0 });

	// PQ�� ����������� �ݺ��Ѵ�.
	while (!turn.empty()){

		// 3. '���� �������� �ʾҰ�, �Ÿ��� �˰� �ִ� ����' �� �Ÿ��� ���� ª�� ������ �����Ѵ�.
		int current_node = turn.top().node_number;
		turn.pop();

		// 4-2. ������ ������ �������� �ƴ϶��, ������ �������κ��� �ֺ��� ������ �Ÿ��� �����Ѵ�.
		int range = edges[current_node].size();

		for (int i = 0; i < range; i++){
			int end_node = edges[current_node][i].end_node;
			int weight = edges[current_node][i].weight;

			if (nodes[end_node].distance > nodes[current_node].distance + weight)
			{
				nodes[end_node].distance = nodes[current_node].distance + weight;
				turn.push({ end_node, nodes[end_node].distance });
			}
		}
	}

	return;
}

/* 4-1. �������� ���� �ϸ� ���ͽ�Ʈ�� ������.
	�� �κ��� ���� ������ '�������� �����Ǿ� �ְ� �ٸ� ��� ������ �ִ� �Ÿ�'�� ���ؾ� �ϱ� �����̴�.
	��, ���� �� ���� �� ���� ���Ϸ��� PQ�� ����� �� ���� �ݺ��ϴ� ��.*/



int main(void){

	int v, e, source;
	scanf("%d %d %d", &v, &e, &source);

	for (int i = 0; i < e; i++){
		int start_node, end_node, weight;
		scanf("%d %d %d", &start_node, &end_node, &weight);
		edges[start_node].push_back({ end_node, weight });
	}

	dijkstra(source);

	for (int i = 1; i <= v; i++){

		// Dijkstra �˰����� ������ �� �Ÿ��� INF�� ��� �����ϴ� ��ΰ� ����.
		if (nodes[i].distance == INF)
			printf("INF\n");
		else
			printf("%d\n", nodes[i].distance);
	}

	return 0;
}
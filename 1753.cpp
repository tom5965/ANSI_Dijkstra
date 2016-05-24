#include <cstdio>
#include <queue>
#include <vector>

#define MAX_NODES 20002
#define INF 300000

using namespace std;

struct edge{
	int end_node;	// 변의 끝점
	int weight;	// 변의 가중치
};

struct node{
	int distance;	// 정점의 '최단 거리'
	bool selected;	// 선택되었는지의 여부
};

struct element{
	int node_number;	// 정점의 번호
	int distance;		// 정점의 '최단 거리'

	/* 연산자(<) 오버라이딩.
	거리가 작은 element가 PQ의 맨 위에 존재하도록 만들어준다.*/
	bool operator<(const element &A)const{
		return distance > A.distance;
	}
};

vector<edge> edges[MAX_NODES];
node nodes[MAX_NODES];
priority_queue<element> turn;

void dijkstra(int source){

	// 1. 처음엔 모든 정점의 최단 거리를 '모른다'고 생각한다.
	for (int i = 0; i < MAX_NODES; i++){
		nodes[i].distance = INF;
		nodes[i].selected = false;
	}

	// 2. 시작점의 최단 거리를 0으로 설정한다.
	nodes[source].distance = 0;
	turn.push({ source, 0 });

	// PQ가 비워질때까지 반복한다.
	while (!turn.empty()){

		// 3. '아직 선택하지 않았고, 거리를 알고 있는 정점' 중 거리가 가장 짧은 정점을 선택한다.
		int current_node = turn.top().node_number;
		turn.pop();

		// 4-2. 선택한 정점이 도착점이 아니라면, 서낵한 정점으로부터 주변의 정점의 거리를 갱신한다.
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

/* 4-1. 도착점에 도달 하면 다익스트라가 끝난다.
	이 부분이 없는 이유는 '시작점이 고정되어 있고 다른 모든 정점의 최단 거리'를 구해야 하기 때문이다.
	즉, 구할 수 있을 때 까지 구하려고 PQ가 비워질 때 까지 반복하는 것.*/



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

		// Dijkstra 알고리즘을 돌렸을 때 거리가 INF인 경우 도달하는 경로가 없다.
		if (nodes[i].distance == INF)
			printf("INF\n");
		else
			printf("%d\n", nodes[i].distance);
	}

	return 0;
}
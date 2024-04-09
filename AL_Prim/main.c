#include <stdio.h>
#include <stdlib.h> // qsrot 함수가 선언된 헤더 파일 (퀵정렬)//랜덤함수 호출
#include <time.h>
#include <limits.h>

#define INF 1000


#define MAX_VERTICES 9



int minD(int key[], int mstSet[]) {//mstSet에 포함되지 않은 정점중에 거리가 가장 가까운 점 구함 
    int min = INF, min_index=0;

    for (int v = 0; v < MAX_VERTICES; v++)
        if (mstSet[v] == 0 && key[v] < min) {//mstSet[v]=0이면 포함되지 않은것 //line 9~12과정 
            printf("debug min_index: %d , v: %d\n", min_index, v);
            min = key[v], min_index = v;
           
        }
    return min_index;
}

void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < MAX_VERTICES; i++) {
        //printf("debug %d \n", parent[i]);
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}

void primMST(int graph[MAX_VERTICES][MAX_VERTICES]) {
    int parent[MAX_VERTICES];
    int D[MAX_VERTICES];//교재에서  D와 같은 역할 
    int mstSet[MAX_VERTICES];//교재에서 TREE에 해당

    for (int i = 0; i < MAX_VERTICES; i++)//초기화 작업 교재 기준 line 2~6 작업 일부 
        D[i] = INF, mstSet[i] = 0;

    D[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < MAX_VERTICES - 1; count++) {
        int u = minD(D, mstSet);//최소 거리 값 찾기 

        mstSet[u] = 1;

        for (int v = 0; v < MAX_VERTICES; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < D[v]) {
                parent[v] = u, D[v] = graph[u][v];
                //printf("debug v:%d parent: %d\n",v, parent[v]);
            }
    }

    printMST(parent, graph);
}

//Random 정점 만들때 사용

int randomPoolOk(int randomPool[]) {
    int flag = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (randomPool[i] != -1) {				//모두 -1이 아니면 아직 덜쓴것  
            flag = 1;
        }


    }
    //printf("RPO : %d\n", flag);
    //다 안썻으면 1반환 
    //다 썻으면 0 반환  .
    return flag;
}

//그래프 출력
void printGraph(int graph[][MAX_VERTICES]) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (graph[i][j] != INF) {
                printf(" %4d", graph[i][j]);
            }
            else {
                printf("  INF");
            }

        }
        printf("\n");
    }
}





//랜덤 트리 만들어줌 
void randomTree(int Graph[][MAX_VERTICES]) {
    //기화배열 초기화
    int edge1 = 0;
    int x, y;

    //Graph 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            Graph[i][j] = 0;

        }

    }


    srand(time(NULL));//랜덤함수 초기화 
    int randomPool[MAX_VERTICES];

    //랜덤 vertex pool// 모두 랜덤으로 하면 간선이 없는 정점이 생길수 있다.
    for (int i = 0; i < MAX_VERTICES; i++) {
        randomPool[i] = i;
    }
    //간선수 고르기 위한 변수  MAX~ Max(Max-1)/2개 ~~~~~~~~~~~~~~~/////////////////

    int EdgeN = (MAX_VERTICES * (rand() % (MAX_VERTICES - 3)+2) / 2);//최솟값이 MaxVertex보다 이상으로
    printf("간선 갯수 %d\n", EdgeN);

    while (edge1 < EdgeN) {


        if (randomPoolOk(randomPool) == 1) {
            do {
                x = randomPool[rand() % MAX_VERTICES];
                y = randomPool[rand() % MAX_VERTICES];

            } while (x == -1 || y == -1);//둘다 사용하지 않은것만 썻을때 가능 
            //printf("debug random (%d, %d) \n",x,y );
            if (x == y) {//이경우는 어차피 못씀
                y = rand() % MAX_VERTICES;
            }
        }
        else {//한 정점씩 다썻을때
            //printf("debug random test\n");
            x = rand() % MAX_VERTICES;
            y = rand() % MAX_VERTICES;

        }

        if (x >= 0 && y >= 0 && Graph[x][y] == 0 && Graph[y][x] == 0 && x != y) {
            int temp = (rand() % 20) + 1;// 1~20 까지의 가중치
            Graph[x][y] = Graph[y][x] = temp;
            edge1++;
            //random;  pool func
            randomPool[x] = randomPool[y] = -1;

            printf("%d. random edge : ( %d , %d), ( %d , %d ), weight: %d\n", edge1, x, y, y, x, Graph[x][y]);
        }



    }
    printf("Number of Vertices : %d\n",MAX_VERTICES);
    printf("Number of Edges : %d\n", EdgeN);
    printGraph(Graph);
}


int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];
    
    randomTree(graph);
     
    primMST(graph);

    return 0;
}

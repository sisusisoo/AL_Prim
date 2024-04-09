#include <stdio.h>
#include <stdlib.h> // qsrot �Լ��� ����� ��� ���� (������)//�����Լ� ȣ��
#include <time.h>
#include <limits.h>

#define INF 1000


#define MAX_VERTICES 9



int minD(int key[], int mstSet[]) {//mstSet�� ���Ե��� ���� �����߿� �Ÿ��� ���� ����� �� ���� 
    int min = INF, min_index=0;

    for (int v = 0; v < MAX_VERTICES; v++)
        if (mstSet[v] == 0 && key[v] < min) {//mstSet[v]=0�̸� ���Ե��� ������ //line 9~12���� 
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
    int D[MAX_VERTICES];//���翡��  D�� ���� ���� 
    int mstSet[MAX_VERTICES];//���翡�� TREE�� �ش�

    for (int i = 0; i < MAX_VERTICES; i++)//�ʱ�ȭ �۾� ���� ���� line 2~6 �۾� �Ϻ� 
        D[i] = INF, mstSet[i] = 0;

    D[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < MAX_VERTICES - 1; count++) {
        int u = minD(D, mstSet);//�ּ� �Ÿ� �� ã�� 

        mstSet[u] = 1;

        for (int v = 0; v < MAX_VERTICES; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < D[v]) {
                parent[v] = u, D[v] = graph[u][v];
                //printf("debug v:%d parent: %d\n",v, parent[v]);
            }
    }

    printMST(parent, graph);
}

//Random ���� ���鶧 ���

int randomPoolOk(int randomPool[]) {
    int flag = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (randomPool[i] != -1) {				//��� -1�� �ƴϸ� ���� ������  
            flag = 1;
        }


    }
    //printf("RPO : %d\n", flag);
    //�� �ț����� 1��ȯ 
    //�� ������ 0 ��ȯ  .
    return flag;
}

//�׷��� ���
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





//���� Ʈ�� ������� 
void randomTree(int Graph[][MAX_VERTICES]) {
    //��ȭ�迭 �ʱ�ȭ
    int edge1 = 0;
    int x, y;

    //Graph �ʱ�ȭ
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            Graph[i][j] = 0;

        }

    }


    srand(time(NULL));//�����Լ� �ʱ�ȭ 
    int randomPool[MAX_VERTICES];

    //���� vertex pool// ��� �������� �ϸ� ������ ���� ������ ����� �ִ�.
    for (int i = 0; i < MAX_VERTICES; i++) {
        randomPool[i] = i;
    }
    //������ ���� ���� ����  MAX~ Max(Max-1)/2�� ~~~~~~~~~~~~~~~/////////////////

    int EdgeN = (MAX_VERTICES * (rand() % (MAX_VERTICES - 3)+2) / 2);//�ּڰ��� MaxVertex���� �̻�����
    printf("���� ���� %d\n", EdgeN);

    while (edge1 < EdgeN) {


        if (randomPoolOk(randomPool) == 1) {
            do {
                x = randomPool[rand() % MAX_VERTICES];
                y = randomPool[rand() % MAX_VERTICES];

            } while (x == -1 || y == -1);//�Ѵ� ������� �����͸� ������ ���� 
            //printf("debug random (%d, %d) \n",x,y );
            if (x == y) {//�̰��� ������ ����
                y = rand() % MAX_VERTICES;
            }
        }
        else {//�� ������ �ٛ�����
            //printf("debug random test\n");
            x = rand() % MAX_VERTICES;
            y = rand() % MAX_VERTICES;

        }

        if (x >= 0 && y >= 0 && Graph[x][y] == 0 && Graph[y][x] == 0 && x != y) {
            int temp = (rand() % 20) + 1;// 1~20 ������ ����ġ
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

#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    char c;
    struct node *link;
} Node;

typedef struct
{
    int v;
    Node **list;
    int **arr;
} Graph;

Node *getNode(char c)
{
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->c = c;
    temp->link = NULL;
    return temp;
}

Graph *getGraph(int v, char ele[])
{
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->v = v;
    g->list = (Node**)malloc(v * sizeof(Node*));
    g->arr = (int**)malloc(v * sizeof(int*));
    for (int i = 0; i < v; i++)
    {
        g->list[i] = getNode(ele[i]);  // Initialize each list with a node
        g->arr[i] = (int*)malloc(v * sizeof(int));
        for (int j = 0; j < v; j++) g->arr[i][j] = 0;
    }
    return g;
}

void addedge(Graph *g, char a, char b)
{
    int i, j;
    for (i = 0; i < g->v; i++)
    {
        if (g->list[i]->c == a) break;
    }
    for (j = 0; j < g->v; j++)
    {
        if (g->list[j]->c == b) break;
    }

    g->arr[i][j] = 1;
    Node *newn = getNode(b);
    if (g->list[i]->link == NULL)
    {
        g->list[i]->link = newn;
    }
    else
    {
        Node *temp = g->list[i]->link;
        while (temp->link) temp = temp->link;
        temp->link = newn;
    }
}


void display(Graph *g)
{
    printf("Adjacency List:\n");
    for (int i = 0; i < g->v; i++)
    {
        Node *temp = g->list[i];
        printf("%c -> ", temp->c);
        while (temp->link)
        {
            temp = temp->link;
            printf("%c -> ", temp->c);
        }
        printf("NULL\n");
    }

    printf("\nAdjacency matrix:\n");
    for (int i = 0; i < g->v; i++)
    {
        for (int j = 0; j < g->v; j++)
        {
            printf("%d\t", g->arr[i][j]);
        }
        printf("\n");
    }
}

void dfs(Graph *g, int *visited, char c, int i)
{
    visited[i] = 1;
    printf("%c\t", c);

    for (Node *temp = g->list[i]; temp != NULL; temp = temp->link)
    {
        int j;
        for (j = 0; j < g->v; j++)
            if (g->list[j]->c == temp->c) break;

        if (!visited[j])
            dfs(g, visited, temp->c, j);
    }
}

void dfsWrapper(Graph *g)
{
    int *visited = (int*)malloc(g->v * sizeof(int));
    for (int i = 0; i < g->v; i++) visited[i] = 0;

    for (int i = 0; i < g->v; i++)
    {
        if (!visited[i])
            dfs(g, visited, g->list[i]->c, i);
    }
    free(visited);
}

int main()
{
    printf("Enter number of vertices: ");
    int v;
    scanf("%d", &v);

    printf("Enter %d vertex names: \n", v);
    char *c = malloc(v * sizeof(char));
    for (int i = 0; i < v; i++)
        scanf(" %c", &c[i]);
    Graph *g = getGraph(v, c);
    printf("1 if edge is present, 0 if not\n");
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            printf("Edge from %c to %c: ", c[i], c[j]);
            int n;
            scanf("%d", &n);
            if (n == 1)
            {
                addedge(g, c[i], c[j]);
            }
        }
    }
    display(g);
    printf("\nDFS traversal :\n");
    dfsWrapper(g);
}

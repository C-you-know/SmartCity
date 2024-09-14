#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define INF INT_MAX

int n = 20; // 20 Different locations in Huballi-Dharwad.

struct city
{
    int Areaid;
    char Areaname[15];
};


struct RoadWasteCollection
{
    int Areaid;         //Primary Key
    int numofDustbins;  //Number of Dustbins in the locality or area
    float wasteproduction; //Production of waste in number of bins per day
    
};

struct DrainageWasteCollection
{
    int Areaid;         //Primary Key
    int openclose;      //Is the draiage open type?(1 -- Yes or 0 -- No)
    int publictoilets; //Does the locality have public toilets? (1 -- Yes or 0 -- No)
};

struct WaterLogistics
{
    int Areaid;         //Primary Key
    int wateravailability;//Is water available 24-7? (1 -- Yes or 0 -- No)
    int typepipeline;     //Is pipeline main? (1 -- Yes or 0 -- No)
};


struct Node {
    int key;
    int Areaid;
    int height;
    struct Node* left;
    struct Node* right;
    struct Node* next;  // Pointer to the next node with the same key
};

//Structures to store data
struct city Hubli_Dharwad[30];
struct RoadWasteCollection Road[30];
struct DrainageWasteCollection Drain[30];
struct WaterLogistics Pipe[30];
      
int RoadWaste[30][30] = {{0,1,2,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
                         {1,0,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {2,2,0,4,2,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,3,4,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0},
                         {3,0,2,0,0,5,3,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
                         {0,0,6,0,5,0,3,0,4,5,0,0,0,0,0,0,0,0,0,0}, 
                         {0,0,0,0,3,3,0,2,1,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,2,0,4,0,0,0,0,0,0,0,0,0,0,0}, 
                         {0,0,0,0,0,4,1,4,0,3,0,0,0,0,0,0,0,0,0,25}, 
                         {0,0,0,7,0,5,0,0,3,0,21,0,0,0,0,0,0,0,0,0}, 
                         {0,0,0,0,0,0,0,0,0,21,0,1,1,0,3,0,0,0,0,0}, 
                         {0,0,0,0,0,0,0,0,0,0,1,0,0,4,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,1,0,0,2,2,1,0,0,0,0}, 
                         {0,0,0,0,0,0,0,0,0,0,0,4,2,0,0,5,0,0,0,0}, 
                         {0,0,0,0,0,0,0,0,0,0,3,0,2,0,0,4,2,0,0,0}, 
                         {0,0,0,0,0,0,0,0,0,0,0,0,1,5,4,0,0,3,1,0}, 
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,7,0,1}, 
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,7,0,2,6}, 
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,0,6}, 
                         {0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,0,1,6,6,0}};

int DrainageWaste[30][30] = {{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
                       {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
                       {0,1,1,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0}, 
                       {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}, 
                       {0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0}, 
                       {0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0}, 
                       {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0}, 
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0}, 
                       {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}, 
                       {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,1}, 
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0}, 
                       {0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0}, 
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0}, 
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}, 
                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0}};

int WaterSupply[30][30] = {{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                                {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0},
                                {0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0}};

        int Relaxation[30][30] = {0};

//SubFuntions
void ViewMatrix(int a[][30])
{
        printf("\nThe matrix is :\n");
        for(int i = 0;i < n; i++)
        {
                for(int j = 0; j < n; j++)
                {
                        printf("%d ", a[i][j]);
                }
                printf("\n");
        }
        printf("\n");
}


//Funtions
void BuildRoad()
{
        printf("Enter the area id of the nodes between which a road should be built and its distance: \n");
        int node1, node2, weight;
        scanf("%d %d %d", &node1, &node2, &weight);

        if(node1 > n || node2 > n)
        {
                printf("Node doesn't exist! \n");
                return;
        }

        node1--;
        node2--;

        //Check if it already exists
        if(RoadWaste[node1][node2]== 0)
        {
                RoadWaste[node1][node2] = weight;
                RoadWaste[node2][node1] = weight;
                printf("Road built between %d to %d \n", node1+1, node2+1);
                return;
        }
        
        printf("Road already exists! \n");       
} 

void BuildDrain()
{
        printf("Enter the area id of the nodes between which a drainage pipe should be built \n");
        int node1, node2, weight = 1;
        scanf("%d %d", &node1, &node2);

        //Check if it already exists
        node1--;
        node2--;

        if(node1 > n || node2 > n)
        {
                printf("Node doesn't exist! \n");
                
        }
        //Check if it already exists
        if(DrainageWaste[node1][node2]== 0)
        {
                DrainageWaste[node1][node2] = weight;
                DrainageWaste[node2][node1] = weight;
                printf("Drain built between %d to %d \n", node1+1, node2+1);
                return;
        }
        
        printf("Drain already exists! \n");       

} 

void BuildPipe()
{
        printf("Enter the area id of the nodes between which a water pipeline should be laid \n");
        int node1, node2, weight = 1;
        scanf("%d %d", &node1, &node2);

       
        node1--;
        node2--;

        if(node1 > n || node2 > n)
        {
                printf("Node doesn't exist! \n");
                
        }

        //Check if it already exists
        if(WaterSupply[node1][node2]== 0)
        {
                WaterSupply[node1][node2] = weight;
                WaterSupply[node2][node1] = weight;
                printf("Pipe built between %d to %d \n", node1+1, node2+1
                );
                return;
        }
        
        printf("Pipe already exists! \n");       

} 

void Displayareas()
{
        for(int i = 0; i < n; i++)
        {
                printf("%d\t%s\n", Hubli_Dharwad[i].Areaid, Hubli_Dharwad[i].Areaname);
        }
}

void addNewArea()
{
        printf("\nEnter the  name of the %dth area :\n", n+1);
        char area[15];
        scanf("%s", Hubli_Dharwad[n].Areaname);

        Hubli_Dharwad[n].Areaid = n+1;
        Road[n].Areaid = n+1;
        Drain[n].Areaid = n+1;
        Pipe[n].Areaid = n+1;

        printf("\nEnter number of dustbins and approx waste production of the area :\n");
        scanf("%d%f", &Road[n].numofDustbins,&Road[n].wasteproduction);
        
        printf("\nEnter if Drainage pipe is closed(1 -- Yes) and if the area has any public toilets(1 -- Yes): \n");
        scanf("%d%d", &Drain[n].openclose, &Drain[n].publictoilets);

        printf("\nIs water avilable 24/7 ? \n");
        scanf("%d",&Pipe[n].wateravailability);

        n++; //Increase the city count which is global

        //Intialise all values for all three matrices a[i][29] == a[29][i]

        for(int i = 0; i < n; i++)
        {
                printf("Enter weight if %d is connected to %d ", n, i+1);
                scanf("%d", &RoadWaste[i][n-1]);
                RoadWaste[n-1][i] = RoadWaste[i][n-1];

        }

        for(int i = 0; i < n; i++)
        {
                printf("Enter weight if %d is connected to %d ", n, i+1);
                scanf("%d", &DrainageWaste[i][n]);
                DrainageWaste[n][i] = DrainageWaste[i][n];

        }

        for(int i = 0; i < n; i++)
        {
                printf("Enter weight if %d is connected to %d ", n, i+1);
                scanf("%d", &WaterSupply[i][n]);
                WaterSupply[n][i] = WaterSupply[i][n];

        }

}

void deletelastArea()
{
        if(n)
        {
                n--;//Ignores all nodes after n
                printf("%s Area deleted from the program\n", Hubli_Dharwad[n].Areaname);
        }
        else
        {
                printf("\nCannot delete anymore nodes \n");
        }
}

int CheckDeficiencies(int i)
{
        int Defciency[3];
        printf("\nDeficiencies in %s area are:\n",Hubli_Dharwad[i].Areaname);

    Drain[2].openclose = 0;
    Drain[2].publictoilets = 1;
    

        if(Road[i].numofDustbins >= (int)(2*Road[i].wasteproduction))
        {
                printf("Number of Dustbins are right in %s\n",Hubli_Dharwad[i].Areaname);
                Defciency[0] = 0;
        }
        else
        {
                Defciency[0] = (int)(2*Road[i].wasteproduction) - Road[i].numofDustbins;
                printf("We require %d number of dustbins in %s.\n", Defciency[0], Hubli_Dharwad[i].Areaname);
        }

        if(Pipe[i].wateravailability == 1)
        {
                printf("Water is available 24/7 in %s\n", Hubli_Dharwad[i].Areaname);
                 Defciency[1] = 0;
        }
        else
        {
                printf("Water is not avaliable 24/7 in %s:(\n", Hubli_Dharwad[i].Areaname);
                Defciency[1] = 1;
        }

        if( Drain[i].publictoilets == 1)
        {
                printf("Public toilets are avaiable in %s\n", Hubli_Dharwad[i].Areaname);
                 Defciency[2] = 0;
        }
        else
        {
                printf("Public toilets are not avaiable in %s\n", Hubli_Dharwad[i].Areaname);
                Defciency[2] = 1;
        }

        int Cost = 10000*Defciency[0]+ 50000*Defciency[1] + 20000*Defciency[2];
        printf("Total cost to fix the %s area : %d\n\n", Hubli_Dharwad[i].Areaname, Cost);

        return(Cost);
}

int TotalCost[30];

void bfs(int RoadWaste[30][30], int n, int src) 
{
    int queue[30];
    int front = -1, rear = -1;
    bool visited[30] = {false};

    queue[++rear] = src;
    visited[src] = true;

    while (front != rear) 
    {
        int temp = queue[++front];
        printf("%d  ", temp+1); 
        
        TotalCost[temp] = CheckDeficiencies(temp);

        for (int i = 0; i < n; i++) 
        {
            if (!visited[i] && RoadWaste[temp][i] != 0) 
            {
                queue[++rear] = i;
                visited[i] = true;
            }
        }
    }
}

void CheckCityFacilities()
{
        int FinalCost = 0;

        bfs(RoadWaste, n, 0);

        for(int i = 0; i < n; i++)
        {
                FinalCost = TotalCost[i] + FinalCost;
        }

        printf("Final Cost to improve city facilities = %d\n\n", FinalCost);
}

void EdgeUnderConstruction()
{
        int node1, node2;

        printf("Enter the AreaID of the nodes on which the edge is incident on : \n");
        scanf("%d%d", &node1, &node2);

        //Convert AreaID to vertexs numbers
        node1--;
        node2--;

        if(node1 > n || node2 > n)
        {
                printf("Node doesn't exist! \n");
                
        }


        if(RoadWaste[node1][node2])
        {
                Relaxation[node1][node2] = RoadWaste[node1][node2];
                Relaxation[node2][node1] = RoadWaste[node2][node1];

                RoadWaste[node1][node2] = 0;
                RoadWaste[node2][node1] = 0;
                printf("Edge between %d and %d now under construction. \n", node1+1, node2+1);
                return;
        }

        printf("Edge doesn't exist! :\n");
        
}

void AllEdgeConstrucrted()
{
        int i, j, flag = 0;
        for(i = 0; i < n; i++)
        {
                for(j = 0; j < n; j++)
                {
                        if(Relaxation[i][j])
                        {
                                RoadWaste[i][j] = Relaxation[i][j];
                                RoadWaste[j][i] = Relaxation[j][i];

                                Relaxation[i][j] = 0;
                                Relaxation[j][i] = 0;

                                flag = 1;
                        }
                }
        }

        if(flag)
                printf("Edge/s Constructed!\n ");
        else
                printf("No Edges under Construction!\n");
}



void dijkstra(int source, int target, int numNodes, int adjacencyMatrix[30][30]) 
{
    int distance[30];
    int visited[30];
    int parent[30];

    
    for (int i = 0; i < numNodes; ++i) 
    {
        distance[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (int count = 0; count < numNodes - 1; ++count) 
    {
        
        int minDistance = INT_MAX;
        int u = -1;

        for (int v = 0; v < numNodes; ++v) 
        {
            if (!visited[v] && distance[v] < minDistance) 
            {
                minDistance = distance[v];
                u = v;
            }
        }

        if (u == -1) 
        {
            
            break;
        }

        
        visited[u] = 1;

        
        for (int v = 0; v < numNodes; ++v)
        {
            if (!visited[v] && adjacencyMatrix[u][v] && distance[u] + adjacencyMatrix[u][v] < distance[v]) 
            {
                distance[v] = distance[u] + adjacencyMatrix[u][v];
                parent[v] = u;
            }
        }
    }


    printf("Alternate route using Dijkstra's algorithm between %d and %d (excluding direct edge):\n", source+1, target+1);

    int currentNode = target;
    while (currentNode != source) 
    {
        printf("%d <- ", currentNode+1);
        currentNode = parent[currentNode];
    }
    printf("%d\n", source +1);
}

void CheckPipeDrainHazard()
{
        int flag = 0;
        int i, j;
        for(i = 0; i < n; i ++)
        {
                for(j = i+1; j < n; j++)
                {
                        if(WaterSupply[i][j] == 1 && DrainageWaste[i][j] == 1)
                        {
                                if(!(Pipe[i].typepipeline && Pipe[j].typepipeline))
                                {
                                        printf("%d->%d\n", i+1, j+1);
                                        flag = 1;
                                        break;
                                }
                        }
                }
                if(flag)
                        break;
        }
        printf("\n");

        if(flag == 0)
                printf("No Harzards :) \n");
        else
        {
                WaterSupply[i][j] = 0;
                WaterSupply[j][i] = 0;    
                dijkstra(i, j, n, WaterSupply);
        }
        
} 


int height(struct Node* node) 
{
    if (node == NULL)
        return 0;
    return node->height;
}

int updateHeight(struct Node* node) 
{
    int leftHeight = (node->left) ? node->left->height : 0;
    int rightHeight = (node->right) ? node->right->height : 0;
    return (node->height = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight));
}


struct Node* rightRotate(struct Node* y) 
{
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = updateHeight(y);
    x->height = updateHeight(x);

    return x;
}


struct Node* leftRotate(struct Node* x) 
{
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = updateHeight(x);
    y->height = updateHeight(y);

    return y;
}

int getBalance(struct Node* node) 
{
    return (node ? ((node->left ? node->left->height : 0) - (node->right ? node->right->height : 0)) : 0);
}


struct Node* newNode(int key, int Areaid) 
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    if (!node) 
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->Areaid = Areaid;
    node->height = 1;
    node->left = node->right = node->next = NULL;
    return node;

}


struct Node* insert(struct Node* root, int key, int Areaid) 
{
    if (root == NULL)
        return newNode(key, Areaid);

    if (key == root->key) 
    {
        struct Node* newNode = insert(root->next, key, Areaid);
        root->next = newNode;
    } else if (key < root->key)
        root->left = insert(root->left, key, Areaid);
    else
        root->right = insert(root->right, key, Areaid);

    updateHeight(root);

    int balance = getBalance(root);

    if (balance > 1) 
    {
        if (key < root->left->key) 
        {
            return rightRotate(root);
        }
    }

    if (balance < -1) 
    {
        if (key > root->right->key) 
        {
            return leftRotate(root);
        }
    }

    return root;
}

struct Node* TreeCreation(struct Node* root)
{

        int Points[30] = {0};

        //Calculate Points

        for(int i = 0; i < n; i++)
        {
                if(Road[i].numofDustbins > (int)(2*Road[i].wasteproduction))
                {
                        Points[i]++;
                }
                else if(Road[i].numofDustbins <= (int)(2*Road[i].wasteproduction))
                {
                        Points[i]--;
                }

                if(Drain[i].openclose == 1)
                {
                        Points[i]--;
                }
                else
                {
                        Points[i]++;
                }

                if(Drain[i].publictoilets == 1)
                {
                        Points[i]++;
                }
                else
                {
                        Points[i]--;
                }

                if(Pipe[i].typepipeline == 1)
                {
                        Points[i]++;
                }
                
                if(Pipe[i].wateravailability == 1)
                {
                        Points[i]++;
                }

                for(int j = 0; j < n; j++)
                {
                        if(RoadWaste[i][j])
                        {
                                Points[i]++;
                                Points[i]++;
                        }

                        if(DrainageWaste[i][j])
                        {
                                Points[i]++;
                        }

                        if(WaterSupply[i][j])
                        {
                                Points[i]++;
                        }
                }
        }

        printf("Points Assigned : \n");

        for(int i = 0; i <n; i++)
        {
                printf("%d %d \n",i+1, Points[i]);
        }

        printf("\nAVL Tree Creation Started!\n");
        for(int k = 0; k < n; k++)
        {
                root = insert(root, Points[k], k);
                printf("%d. %s Node added \n", k+1, Hubli_Dharwad[k].Areaname);
        }
        printf("\nAVL Tree Created!\n");


        return(root);

}


void inorderTraversal(struct Node* root) 
{
    if (root != NULL) 
    {
        inorderTraversal(root->left);
        printf("(%d, %d) ", root->Areaid, root->key);
        struct Node* current = root->next;

        while (current != NULL) 
        {
            printf("(%d, %d) ", current->Areaid, current->key);
            current = current->next;
        }

        inorderTraversal(root->right);
    }
}

void printMaxNode(struct Node* root) 
{
    if (root == NULL) 
    {
        printf("Tree is empty. No maximum node.\n");
        return;
    }

    while (root->right != NULL) 
    {
        root = root->right;
    }

    printf("Maximum Node: (%d, %d)\n",  root->Areaid, root->key);
}

void printMinNode(struct Node* root) 
{
    if (root == NULL) 
    {
        printf("Tree is empty. No minimum node.\n");
        return;
    }

    while (root->left != NULL) 
    {
        root = root->left;
    }

    printf("Minimum Node: (%d, %d)\n", root->Areaid, root->key);
}


int A1[20], A2[50], A3[100];

void intializeTreasury()
{
        srand((unsigned int)time(NULL));

        for (int i = 0; i < 20; i++) 
        {
           A1[i]= rand(); 
        }
        A1[18] = 9448527;

        for (int i = 0; i < 50; i++) 
        {
           A2[i]= rand(); 
        }
        A2[27] = 6363568;

        for (int i = 0; i < 100; i++) 
        {
           A3[i]= rand(); 
        }
        A3[79] = 1000000000; //Billion
}


int HashFuntion(int Passcode, int mod)
{
        int Processing1, Processing2, Processing;

        Processing1 = Passcode/97;

        Processing2 = pow(Passcode, 2);

        Processing = (Processing2) - (Passcode * Processing1);

        return(abs(Processing % mod));
}

void Treasury()
{
        //outputs the amount of gold and reserves that is held treasury!
        int Passcode, Output;

        printf("Enter the correct Passcode please : \n");
        scanf("%d", &Passcode);

        Output = HashFuntion(Passcode, 20); 

        Output = HashFuntion(A1[Output]+Passcode, 50); 

        Output = HashFuntion(A2[Output]+Output, 100); 

        printf("Treasury Monetary Value : %d", A3[Output]);
}

void HashKey()
{
        int Output;
        for(int i = 0; i < 100; i++)
       {

        Output = HashFuntion(i, 20); 

        Output = HashFuntion(A1[Output]+i, 50); 

        Output = HashFuntion(A2[Output]+Output, 100); 

        if(A3[Output] == 1000000000)
        {
            printf("\n%d\n", i);
        }
       }
}

int minKey(int key[], int mstSet[]) 
{
    int min = INF, min_index;

    for (int v = 0; v < n; v++) 
    {
        if (mstSet[v] == 0 && key[v] < min) 
        {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

void printMST(int parent[], int graph[][30]) 
{
    printf("Selected edges in the minimum spanning tree:\n");
    for (int i = 1; i < n; i++) 
    {
        printf("%d - %d : %d\n", parent[i]+1, i+1, graph[i][parent[i]]);
    }
}

void primsAlgorithm(int graph[][30]) 
{
    int parent[30];  
    int key[30];     
    int mstSet[30];

  
    for (int i = 0; i < n; i++) 
    {
        key[i] = INF;
        mstSet[i] = 0;
    }

    
    key[0] = 0;     
    parent[0] = -1;  


    for (int count = 0; count < n - 1; count++) 
    {

        int u = minKey(key, mstSet);


        mstSet[u] = 1;

  
        for (int v = 0; v < n; v++) 
        {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) 
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }


    printMST(parent, graph);
}



int main()
{
        intializeTreasury();
        //HashKey();
 
    // Basic input initlisation
    for(int i = 0; i < n; i++)
    {
        Hubli_Dharwad[i].Areaid = i+1;
        Road[i].Areaid = i+1;
        Drain[i].Areaid = i+1;
        Pipe[i].Areaid = i+1;
        Pipe[i].wateravailability = 0;
    }

    strcpy(Hubli_Dharwad[0].Areaname, "Sampige Nagar");
    Road[0].numofDustbins = 11;
    Road[0].wasteproduction = 4; 
    Drain[0].openclose = 1;
    Drain[0].publictoilets = 0;
    

    strcpy(Hubli_Dharwad[1].Areaname, "Maratha Colony");
    Road[1].numofDustbins = 6;
    Road[1].wasteproduction = 3; 
    Drain[1].openclose = 1;
    Drain[1].publictoilets = 0;

    strcpy(Hubli_Dharwad[2].Areaname, "Central BT");
    Road[2].numofDustbins = 15;
    Road[2].wasteproduction = 6; 
    Drain[2].openclose = 0;
    Drain[2].publictoilets = 1;
    Pipe[2].typepipeline=1;

    strcpy(Hubli_Dharwad[3].Areaname, "Hosayallapur");
    Road[3].numofDustbins = 10;
    Road[3].wasteproduction = 5; 
    Drain[3].openclose = 1;
    Drain[3].publictoilets = 1;

    strcpy(Hubli_Dharwad[4].Areaname, "Srinagar");
    Road[4].numofDustbins = 12;
    Road[4].wasteproduction = 6; 
    Drain[4].openclose = 1;
    Drain[4].publictoilets = 1;
    Pipe[4].wateravailability = 1;

    strcpy(Hubli_Dharwad[5].Areaname, "Malmaddi");
    Road[5].numofDustbins = 8;
    Road[5].wasteproduction = 4; 
    Drain[5].openclose = 0;
    Drain[5].publictoilets = 0;
    Pipe[5].typepipeline=1;

    strcpy(Hubli_Dharwad[6].Areaname, "Saptapur");
    Road[6].numofDustbins = 7;
    Road[6].wasteproduction = 3; 
    Drain[6].openclose = 1;
    Drain[6].publictoilets = 0;
    Pipe[6].wateravailability = 1;

    strcpy(Hubli_Dharwad[7].Areaname, "Kalyan Nagar");
    Road[7].numofDustbins = 4;
    Road[7].wasteproduction = 2; 
    Drain[7].openclose = 0;
    Drain[7].publictoilets = 0;

    strcpy(Hubli_Dharwad[8].Areaname, "Gandhigar");
    Road[8].numofDustbins = 9;
    Road[8].wasteproduction = 4; 
    Drain[8].openclose = 0;
    Drain[8].publictoilets = 0;

    strcpy(Hubli_Dharwad[9].Areaname, "Y.S Colony");
    Road[9].numofDustbins = 6;
    Road[9].wasteproduction = 3; 
    Drain[9].openclose = 0;
    Drain[9].publictoilets = 0;
    Pipe[9].typepipeline=1;

    strcpy(Hubli_Dharwad[10].Areaname, "Vidhya Nagar");
    Road[10].numofDustbins = 9;
    Road[10].wasteproduction = 4; 
    Drain[10].openclose = 0;
    Drain[10].publictoilets = 0;
    Pipe[10].typepipeline=1;

    strcpy(Hubli_Dharwad[11].Areaname, "Anand Nagar");
    Road[11].numofDustbins = 6;
    Road[11].wasteproduction = 3; 
    Drain[11].openclose = 1;
    Drain[11].publictoilets = 0;
    Pipe[11].wateravailability = 1;

    strcpy(Hubli_Dharwad[12].Areaname, "Despande Nagar");
    Road[12].numofDustbins = 13;
    Road[12].wasteproduction = 6; 
    Drain[12].openclose = 1;
    Drain[12].publictoilets = 1;
    Pipe[12].wateravailability = 1;

    strcpy(Hubli_Dharwad[13].Areaname, "Keshwapur");
    Road[13].numofDustbins = 14;
    Road[13].wasteproduction = 6; 
    Drain[13].openclose = 1;
    Drain[13].publictoilets = 1;

    strcpy(Hubli_Dharwad[14].Areaname, "Old Hubli");
    Road[14].numofDustbins = 13;
    Road[14].wasteproduction = 6; 
    Drain[14].openclose = 1;
    Drain[14].publictoilets = 0;
    Pipe[14].typepipeline=1;

    strcpy(Hubli_Dharwad[15].Areaname, "Shirur Park");
    Road[15].numofDustbins = 13;
    Road[15].wasteproduction = 5.5; 
    Drain[15].openclose = 1;
    Drain[15].publictoilets = 0;
    Pipe[15].typepipeline=1;

    strcpy(Hubli_Dharwad[16].Areaname, "Sidharoda Math");
    Road[16].numofDustbins = 5;
    Road[16].wasteproduction = 2.5; 
    Drain[16].openclose = 0;
    Drain[16].publictoilets = 1;
    Pipe[16].wateravailability = 1;
    Pipe[16].typepipeline=1;

    strcpy(Hubli_Dharwad[17].Areaname, "Rajendra Nagar");
    Road[17].numofDustbins = 8;
    Road[17].wasteproduction = 3.5; 
    Drain[17].openclose = 0;
    Drain[17].publictoilets = 0;
    

    strcpy(Hubli_Dharwad[18].Areaname, "Durgad Bail");
    Road[18].numofDustbins = 4;
    Road[18].wasteproduction = 1.5; 
    Drain[18].openclose = 1;
    Drain[18].publictoilets = 0;

    strcpy(Hubli_Dharwad[19].Areaname, "Gabbur Cross");
    Road[19].numofDustbins = 3;
    Road[19].wasteproduction = 1; 
    Drain[19].openclose = 0;
    Drain[19].publictoilets = 1;

    for(int i = 0; i < n; i++)
    {
        if(Pipe[i].typepipeline==1)
                Pipe[i].wateravailability = 1;
        else
                Pipe[i].typepipeline = 0;
    }    


        //Code to verify correct intialisation and intimate the user on its scope.
        printf("\nLocations under Hubli-Dharwad Munipality\n");
        printf("|Aid|\t|AreaName\t|\t|RWaste|    |numDus| |open?| |pubtoi?| |24/7?| |Mains?|\n");
        for(int i = 0; i < n; i++)
        {
                printf("|%d|\t|%s\t|\t|%0.1f|\t\t|%d|\t|%d|\t|%d|\t|%d|\t|%d|\n", Hubli_Dharwad[i].Areaid, Hubli_Dharwad[i].Areaname, Road[i].wasteproduction, Road[i].numofDustbins, Drain[i].openclose, Drain[i].publictoilets, Pipe[i].wateravailability, Pipe[i].typepipeline);
        }




    int choice; // Variable to select a funtion from a list.
    int loopkey = 1; //Variable to exit the loop
    int choiceinfra; //Varable used in function 2
    int EdgeCon = 0;
    int Tree = 0;
    int TreeChoice;

     struct Node* root = NULL; //Root of AVL Tree

    while(loopkey)
    {
        printf("Funtions : \n");

        printf("1 -- List all the areas/localities under the smart city program \n");
        printf("2 -- Build infrastructure between any two nodes \n");
        printf("3 -- Checks City's Public Health Deficiencies\n");
        printf("4 -- Edge under Construction\n");
        printf("5 -- Complete Construction of all Edges\n");
        printf("6 -- Adds a new area to the graph \n");
        printf("7 -- Deletes the last area \n");
        printf("8 -- Check Pipe Drain Hazard\n");
        printf("9 -- Rank areas based on facilities\n");
        printf("10 -- AVL Tree Operations\n");
        printf("11 -- Check Treasury Balence\n");
        printf("12 -- Plan the laying of Optical Cables\n");
        printf("13 -- Exit Program\n");

        scanf("%d", &choice);
        switch(choice)
        {
            case 1: 
                        printf("\n\n");
                        Displayareas();
                        printf("Road\n");
                        ViewMatrix(RoadWaste);
                        printf("Drainage\n");
                        ViewMatrix(DrainageWaste);
                        printf("Water Pipeline\n");
                        ViewMatrix(WaterSupply);
                    break;

            case 2:     
                        printf("\nSelect Infrastructure\n");
                        printf("1--Road\n");
                        printf("2--Drainage pipe\n");
                        printf("3--Water pipe\n");
                        scanf("%d", &choiceinfra);
                        switch(choiceinfra)
                        {
                                case 1: BuildRoad(); break;
                                case 2: BuildDrain();break;
                                case 3: BuildPipe();break;
                                default: printf("Enter correct choice :\n");
                        }
                        
                    break;
            case 3: 
                        CheckCityFacilities();    
                    break;
            case 4: 
                        EdgeUnderConstruction();
                        EdgeCon = 1;
                        Tree = 0;
                    break;
            case 6: 
                        addNewArea();
                        Tree = 0;
                    break;
            case 7: 
                        deletelastArea();
                        Tree = 0;
                    break;
            case 8: 
                        CheckPipeDrainHazard();
                    break;
            case 5: 
                        AllEdgeConstrucrted();
                    break;
            case 9:  root = TreeCreation(root);
                        Tree = 1;
                    break;
           case 10:
                        if(!Tree)
                                printf("Run funtion 9 first \n");
                        else
                        {
                                printf("AVL Tree Funtions : \n");
                                printf("1 -- Inorder Traversal \n");
                                printf("2 -- Max Node(Most Developed Area)\n");
                                printf("3 -- Min Node(Least Developed Area)\n");

                                scanf("%d", &TreeChoice);
                                switch (TreeChoice)
                                {
                                        case 1: printf("Inorder traversal of the AVL tree: ");
                                                inorderTraversal(root);
                                                printf("\n");
                                                break;
                                        case 2: printMaxNode(root); break;
                                        case 3: printMinNode(root); break;

                                        default: printf("Enter correct choice :\n");
                                }
                        }
                    break;

            case 11:
                    Treasury();
                    printf("\n");
                    break;

                case 12:
                        primsAlgorithm(RoadWaste);
                    break;

                case 13:
                    loopkey = 0; 
                    break;
            default: printf("Enter correct choice :\n");   
        } 
    }  

    return(0);
}
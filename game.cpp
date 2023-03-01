#include "bits/stdc++.h"
#define V 10
#define INF 1000000007
using namespace std;

//graph to store basic structure of cities and distances
vector<pair<int, int>> graph[V];

//map to store distances between cities
map<pair<int, int>, int> m;

//helper function to fill our map and graph
void set_graph_util(int u, int v, int distance){
   //set distance between u and v as dist
   graph[u].push_back({v, distance});
   graph[v].push_back({u, distance});
   m[{u, v}] = distance;
   m[{v, u}] = distance;
}

//function to generate random cities and distances  
void set_graph(int edges){
    for(int i=0; i<edges; i++){
        int v1 = (rand() % 10);
        int v2 = (rand() % 10);
        int dist = (rand() % 10);
       
        //if rand() function fetches same value for both v1 and v2 then we'll ignore
        if(v1 == v2){
            --i;
            continue;
        }
        set_graph_util(v1, v2, dist);
    }
}

//function to print the desired graph
void show_graph(){
    for(int i=0; i<V; i++){
        for(auto it : graph[i]){
            cout << i <<"     ->   "<< it.first << "   =   " << it.second << " KM\n";
        }
        cout << "\n";
    }
}

//function to find the shortest distance from city 0 to city 9 and store it in original_path vector
bool dijkstra(vector<int> &original_path){
   vector<int> dist(V, INF);
   vector<int> parent(V, -1);
   dist[0] = 0;
   
   //dijkstra via set implementation
   set<pair<int, int>> s;
   s.insert({0, 0});
   while(!s.empty()){
       pair<int, int> tmp = *(s.begin());
       s.erase(s.begin());
       int curr = tmp.second;
       
       //calculate the shortst distance betwen city 0 to city 9
       for(int i=0; i<graph[curr].size(); i++){
           int x = graph[curr][i].first;
           int wt = graph[curr][i].second;
           if(dist[curr] + wt < dist[x]){
               dist[x] = dist[curr] + wt;
               parent[x] = curr;
               s.insert({dist[x], x});
           }
       }
   }
   
   //if no path exists then return false otherwise store the path in priginal_path vector
   if(dist[V-1] == INF) return false;
   else{
       int x = V-1;
       original_path.push_back(V-1);
       while(x != 0){
           original_path.push_back(parent[x]);
           x = parent[x];
       }
   }
   reverse(original_path.begin(), original_path.end());
   return true;
}

//function to print starting message
void welcome_note(){
    cout << "*GUESS THE SHORTEST PATH !*\n";
    cout <<"\nRULE : SIMRAN IS LOST ON AN ABONDONED ISLAND,\n       FORTUNATELY, SHE HAS HER BOAT WITH HER BUT SHE HAS\n       VERY LIMITED RESOURCES TO KEEP HER ALIVE. ALSO SHE\n       HAS A WORLD MAP WHICH SHOWS THE DISTANCE TO\n       THE NEAREST CITIES. CURRENTLY SHE IS AT CITY\n       NUMBER 0 (CITIES ARE NUMBERED FROM 0 TO 9), \n       HELP SIMRAN TO FIND A ROUTE TO CITY 10 WITH\n       LEAST DISTANCE COVERED IF ITS POSSIBLE.\n";
}

//function to print the title of graph structure
void table_format(){
    cout << "\nCITY1    CITY2    DISTANCE\n";
}
int main(){
    //srand to set the seeding of rand() function to NULL so that it gives different random values at each execution
    srand(time(NULL));
   
    //show table
    welcome_note();
    table_format();
   
    //vector to store our original answer
    vector<int> original_path;
   
    //get random numbeer of edges in the range 10 - 15
    int edges = (rand() % 15) + 10;
   
    //boolean variable to check if a definite path exist between city 0 to city 9 or not
    bool flag = true;
   
    //setting up the graph
    set_graph(edges);
    show_graph();
   
    if(dijkstra(original_path) == false) flag = false; // path doesnt exist
   
    cout << "\n\n";
    int lifeline = 3, idx = 1;
    cout << "\nIS IT POSSIBLE TO REACH CITY 10 (Y/N) :";
    char ch; cin >> ch;
   
    //if user enters wrong answer
    if((ch == 'Y' && flag == false) || (ch == 'N' && flag == true)){
        cout << "* SORRY ! YOU LOSE ! *";
        exit(0);
    }
   
    //main game mechanics
    while(idx < original_path.size() && lifeline > 0){
        int city;
        cout << "\nCURRENT LIFELINE :  "<<lifeline << " ,  GUESS CURRENT CITY : ";
        cin >> city;
       
        //if user's guess is right
        if(city == original_path[idx]){
            cout << "\n -----CORRECT !-----\n" << endl;
            idx++;
            continue;
        }
        //if user's guess is wrong
        else{
            lifeline--;
            if(lifeline == 0) break;
            cout << "\n-----OOPS ! TRY AGAIN-----\n" <<  endl;
            continue;
        }
    }
   
    //if user has used up all of his lifeline
    if(idx != original_path.size()) {
        cout << "\n\n** SORRY, YOU RAN OUT OF LIFELINE ! **\n";
        cout << "\nCORRECT PATH : ";
        for(auto it : original_path) cout << it << " ";
    }
   
    //if user got all correct answer
    else cout << "\n\n** YOU WON ! **";
}

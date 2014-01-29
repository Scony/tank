#include <cstdio>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <vector>
#include <utility>

#define X 25
#define Y 25

using namespace std;

int map[X][Y];
int vis[X][Y];
vector<pair<int,int> > first;
vector<pair<int,int> > powerups;

void dfs(int x, int y){
	if(x < 0) return;
	if(y < 0) return;
	if(x >= X) return;
	if(y >= Y) return;
	if(vis[x][y]) return;
	if(map[x][y]) return;
	vis[x][y] = 1;
	dfs(x,y-1);
	dfs(x,y+1);
	dfs(x-1,y);
	dfs(x+1,y);
}

int main(){
	srand (time(NULL));
	for(int i=0;i<X;i++){
		for(int j=0;j<Y;j++){
		if(i%5 == 0 && j%5 == 0) continue;
			int rnd = rand()%15;
			if(rnd == 1){
				map[i][j] = 2;
            }else if(!rnd){
            	map[i][j] = 5;
            }
        }
    }
	for(int i=0;i<X;i++)
	for(int j=0;j<Y;j++){
		if(!vis[i][j] && !map[i][j]){
			first.push_back(make_pair(i,j));
			dfs(i,j);
		}
	}
	for(int i=0;i<first.size()-1;i++){
		int x1 = first[i].first < first[i+1].first ? first[i].first : first[i+1].first;
		int y1 = first[i].second < first[i+1].second ? first[i].second : first[i+1].second;
		int x2 = first[i].first > first[i+1].first ? first[i].first : first[i+1].first;
		int y2 = first[i].second > first[i+1].second ? first[i].second : first[i+1].second;
		for(int j=x1;j<=x2;j++)
			map[j][y1] = 0;
		for(int j=y1;j<=y2;j++)
			map[x1][j] = 0;
	}
	for(int i=0;i<X;i++){
		for(int j=0;j<Y;j++){
			if(map[i][j]) continue;
			int rnd = rand()%5;
			if(i%5 == 0 && j%5 == 0) rnd = 0;
			if(rnd == 2 || rnd == 3) rnd = 0;
			map[i][j] = rnd;
			if(rnd != 1 && rand()%50 == 0)
				powerups.push_back(make_pair(i,j));
        }
    }
    printf("%d %d\n", 2*X+2, 2*Y+2);
    for(int i=0;i<2*X+2;i++){
    for(int j=0;j<=2*Y+2;j++){
    	if(i==0 || j == 0 || i == 2*X+1 || j == 2*Y+1)
    		printf("2 ");
    	else
    		printf("%d ", map[(i-1)/2][(j-1)/2]);
    }
    printf("\n");
    }
    
    printf("%d\n", powerups.size());
    for(int i=0;i<powerups.size();i++){
    	int type = rand()%5;
    	if(type > 2) type = 2;
    	int amm;
    	int x = powerups[i].first;
    	int y = powerups[i].second;
    	if(type==0) amm = 20; if(type==1) amm = 100; if(type==2) amm = 1000; 
    		printf("%d %d %d %d\n",2*x + 1, 2*y + 1, type, amm/2 + rand()%amm);
    }
    	
}
		
	
	
            

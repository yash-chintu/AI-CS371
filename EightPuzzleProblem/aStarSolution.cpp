#include<bits/stdc++.h>
using namespace std;
typedef pair<int,vector<vector<int>>> pi;

vector<vector<int>> goal,start;

//priority queue min heap
priority_queue<pi,vector<pi>,greater<pi>>open_list;

vector<pair<int,vector<vector<int>>>>closed_list;

//function for checking whether the current state is goal state
bool is_equal(vector<vector<int>> matrix){
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        if(matrix[i][j]!=goal[i][j])
        return false;
    }
  }
  return true;
}


//function for calculating manhatten distance
int calculate_manhatten_distance(int data,int x,int y){

    for(int i=0;i<3;i++){
      for(int j=0;j<3;j++)
      {
        if(goal[i][j]==data){
            return abs(x-i)+abs(y-j);
        }
      }
    }
return 0;
}

//function for calculating f(n)
int get_distance(vector<vector<int>> s,int g_n){

  int distance = 0;
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      distance+=calculate_manhatten_distance(s[i][j],i,j);
    }

  } 
  return distance+g_n;
}

//function for moving the empty space
vector<vector<int>> modify(vector<vector<int>>matrix , int x, int y , int x2 , int y2){
  int temp = matrix[x2][y2];
  matrix[x2][y2]=matrix[x][y];
  matrix[x][y]=temp;
  return matrix;
}


//checks whether the node is explored of not
bool is_explored(vector<vector<int>> matrix){
  for(int i=0;i<closed_list.size();i++){
    auto item = closed_list[i].second;
    int count=0;
    for(int j=0;i<3;i++){
      for(int k=0;i<3;i++){
          if(matrix[j][k]==item[j][k])
          count++;
      }
    }
    if(count==9)
    return true;
  }
  return false;
}

//generates all possible moves ( left , right, up, down )
void create_array(vector<vector<int>> matrix,int g_n){
  int x,y;
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      if(matrix[i][j]==-1){
        x=i,y=j;
      }
    }
  }
  vector<pair<int,int>> point_list;
  if(x-1>=0)
  point_list.push_back(make_pair(x-1,y));
  if(y-1>=0)
  point_list.push_back(make_pair(x,y-1));
  if(x+1<3)
  point_list.push_back(make_pair(x+1,y));
  if(y+1<3)
  point_list.push_back(make_pair(x,y+1));

  for(int i=0;i<point_list.size();i++){
    auto temp=matrix;
    temp=modify(temp,x,y,point_list[i].first,point_list[i].second);
    int f_n = get_distance(temp,g_n);
    if(!is_explored(temp)){
    open_list.push(make_pair(f_n,temp));
    
    }
  }

}

//returns the count of number of moves
int process_fun(){

  open_list.push(make_pair(0,start));
  int flag = 1,count = 0;
  while(flag>0){
    auto explore_matrix = open_list.top().second;
    closed_list.push_back(open_list.top());
    open_list.pop();

    if(is_equal(explore_matrix)){
      flag=0;
      break;
    }
    else{
      create_array(explore_matrix,count);
    }
    count++;


  }
  return count;

}

//prints a state
void print_matrix(vector<vector<int>>matrix){
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      if(matrix[i][j]==-1)
      cout<<" "<<" ";
      else
      cout<<matrix[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<"--------"<<endl;
}

//calls the function print_matrix for multiple states
void print_states(){
  int n=closed_list.size();
  for(int i=0;i<n;i++){
    print_matrix(closed_list[i].second);
  }
}


int main(){

  cout<<"Example Input : 1 2 3 4 5 6 7 8 -1"<<endl;
  cout<<"Enter Goal State :"<<endl;
  
  for(int i=0;i<3;i++){
    vector<int> temp_;
    for(int j=0;j<3;j++){
      int temp;
      cin>>temp;
      temp_.push_back(temp);
    }
    goal.push_back(temp_);
  }

  cout<<"Enter Start State :"<<endl;
  for(int i=0;i<3;i++){
    vector<int> temp_;
    for(int j=0;j<3;j++){
      int temp;
      cin>>temp;
      temp_.push_back(temp);
    }
    start.push_back(temp_);
  }
  cout<<"--------"<<endl;
  cout<<"Start State :"<<endl;

  int count = process_fun();

  print_states();

  cout<<"Count:"<<count<<endl;


  return 0;
}

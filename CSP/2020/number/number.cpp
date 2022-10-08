#include <cassert>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <climits>

using namespace std;

const int N = 1010;
int grid[N][N];
int n, m;

inline bool isStartPoint(int x, int y) {
  return x==0 && y==0;
}

inline bool isEndPoint(int x, int y) {
  return (x==m-1) && (y==n-1);
}

bool isInGrid(int x, int y) {
  return x >= 0 && x < m && y >= 0 && y < n;
}

bool isValid(int x, int y, int succX, int succY) {
  if(! isInGrid(x, y)) return false;
  if(x==succX && y==succY) return false; // can't go back
  return true;
}

bool canGoLeft(int x, int y, int succX, int succY) {
  return isValid(x-1, y, succX, succY);
}
bool canGoUp(int x, int y, int succX, int succY) {
  return isValid(x, y-1, succX, succY);
}
bool canGoDown(int x, int y, int succX, int succY) {
  // can't go down on first and last column
  return isValid(x,y+1,succX,succY) && !(x==0 || x==m-1);
}

int path(int x, int y, int succX, int succY) {
  if(isStartPoint(x, y)) return grid[0][0];

  int prevPath = INT_MIN;
  if(canGoLeft(x, y, succX, succY)) prevPath = max(prevPath, path(x-1,y, x, y));
  if(canGoUp(x, y, succX, succY)) prevPath = max(prevPath, path(x, y-1, x, y));
  if(canGoDown(x, y, succX, succY)) prevPath = max(prevPath, path(x, y+1, x, y));

  int result = prevPath + grid[y][x];

  return result;
}

void uat() {
  scanf("%d%d", &n, &m);
  for(int i=0; i < n; i++) {
    for(int j=0; j < m; j++) {
      scanf("%d", &grid[i][j]);
    }
  }

  printf("%d\n", path(m-1,n-1, m-1, n));
}

void run(string name, bool withTest=false) {
  string inFile = name + ".in";
  string outFile = name + ".out";
  freopen(inFile.c_str(), "r", stdin);
  freopen(outFile.c_str(), "w", stdout);

  uat();

  fclose(stdin);
  fclose(stdout);

  if(withTest) {
    string diff = "diff 1>&2 -B ";
    diff += outFile + " " + name + ".ans";
    int i = system(diff.c_str());
    assert(i==0);
    fprintf(stderr, "Test %s passed.\n", name.c_str());
  }
}

int main() {
  // run("number");
  run("number10", true);
  return 0;
}

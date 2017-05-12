#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int  Status;

#define  MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535

typedef struct {
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
}MGraph;


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

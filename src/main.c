#include "../include/graph.h"


int main(int argc, const char * argv[]) {
    FILE *fp;
    if ((fp = fopen("vertexlist.txt", "r")) != NULL) {
        rungraphalgorithms(fp);
    } else {
        printf("Something went wrong opening your file.");
        exit(1);
    }
    fclose(fp);
    return 0;
}
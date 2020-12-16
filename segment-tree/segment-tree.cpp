#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

const int MAXN = 1e3 + 50;

// arr{1, 3, 5, 7, 9, 11}
// tree{36, 9, 27, 4, 5, 16, 11, 1, 3, 0, 0, 7, 9, 0, 0}

int arr[] = {1, 3, 5, 7, 9, 11};
int tree[MAXN]; // 节点中的每个值等于儿子节点之和

// 创建线段树
void buildTree(int node, int start, int end){
    if (start == end){
        tree[node] = arr[start];
        return ;
    }

    // 算出中心点
    int mid = (start + end) >> 1;
    int lnode = (node << 1) + 1;
    int rnode = (node << 1) + 2;

    // 左右分别建树
    buildTree(lnode, start, mid);
    buildTree(rnode, mid + 1, end);
    tree[node] = tree[lnode] + tree[rnode];
}

// 更新数组中的节点
void updateTree(int node, int start, int end, int ids, int val){
    if (start == end){
        arr[ids] = val;
        tree[node] = val;
        return ;
    }

    // 算出中心点
    int mid = (start + end) >> 1;
    int lnode = (node << 1) + 1;
    int rnode = (node << 1) + 2;

    // 左右分别建树
    if (ids <= mid) updateTree(lnode, start, mid, ids, val);
    if (ids > mid) updateTree(rnode, mid + 1, end, ids, val);
    tree[node] = tree[lnode] + tree[rnode];
}

// 对 L--R 求和
int queryTree(int node, int start, int end, int L, int R){
    printf("start = %d\n", start);
    printf("end   = %d\n", end);
    printf("\n");
    if (end < L || R < start) return 0;
    if (L <= start && R >= end) return tree[node];
    if (start == end) return tree[node];

    // 算出中心点
    int mid = (start + end) >> 1;
    int lnode = (node << 1) + 1;
    int rnode = (node << 1) + 2;

    return queryTree(lnode, start, mid, L, R) + queryTree(rnode, mid + 1, end, L, R);
}

int main(){
    memset(tree, 0, sizeof(tree));
    int arr_size = sizeof(arr) / sizeof(int);
    // printf("%d\n", arr_size);
    buildTree(0, 0, arr_size - 1);
    updateTree(0, 0, arr_size - 1, 4, 6);
    int tmp = queryTree(0, 0, arr_size - 1, 2, 5);

    // for (int i = 0; i < 15; i++) printf("tree[%d] = %d\n", i, tree[i]);
    printf("%d\n", tmp);

    return 0;
}

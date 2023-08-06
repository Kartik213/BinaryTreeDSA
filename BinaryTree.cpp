#include<bits/stdc++.h>
using namespace std;

void io() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

class Node{
public:
    int data;
    Node* left;
    Node* right;
    Node(int d){
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};
void inorder(Node* root){
    if(!root)
        return ;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}
void preorder(Node* root) {
    if (!root)
        return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(Node* root) {
    if (!root)
        return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}
void levelOrder(Node* root){
    queue<Node*>q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        if(temp == NULL){
            cout<<endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
        else{
            cout<<temp->data<<" ";
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
        }
    }
}
void buildLevelOrder(Node* &root){
    queue<Node*>q;
    int data;
    cin>>data;
    root = new Node(data);
    q.push(root);
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        cin>>data;
        if(data != -1){
            temp->left = new Node(data);
            q.push(temp->left);
        }
        cin>>data;
        if (data != -1) {
            temp->right = new Node(data);
            q.push(temp->right);
        }
    }
}
void countLeaf(Node* root, int &count){
    if(!root)
        return ;
    countLeaf(root->left, count);
    if(!root->left && !root->right)
        count++;
    countLeaf(root->right, count);
}
int heightOfTree(Node* node){
    if(!node)
        return 0;
    int leftHeight = heightOfTree(node->left);
    int rightHeight = heightOfTree(node->right);
    return max(leftHeight, rightHeight) + 1;
}
pair<int, int> diameter(Node* node){
    if(!node){
        pair<int, int> p = make_pair(0,0);
        return p;
    }
    pair<int, int> left = diameter(node->left);
    pair<int, int> right = diameter(node->right);
    int leftDiameter = left.first;
    int rightDiameter = right.first;
    int rootDiameter = left.second + right.second + 1;
    pair<int, int>ans;
    ans.first = max(rootDiameter, max(leftDiameter, rightDiameter));
    ans.second = max(left.second, right.second) + 1;
    return ans;
}
int diameterSlow(Node* node){
    if(!node)
        return 0;
    int leftDiameter = diameterSlow(node->left);
    int rightDiameter = diameterSlow(node->right);
    int rootDiameter = heightOfTree(node->left) + heightOfTree(node->right) +1;
    int diameter = max(leftDiameter, max(rightDiameter, rootDiameter));
    return diameter;
}
int balanced(Node* node){
    if(!node)
        return 0;
    int lh = balanced(node->left);
    int rh = balanced(node->right);
    if(abs(lh-rh) > 1)
        return -1;
    if(lh == -1 || rh == -1)
        return -1;
    return (max(lh, rh) + 1);
}
pair<bool, int> sumTree(Node* node){
    if(!node){
        pair<bool, int>p = make_pair(true, 0);
        return p;
    }
    if(!node->left || !node->right){
        pair<bool, int>p = make_pair(true, node->data);
        return p;
    }
    pair<bool, int> left = sumTree(node->left);
    pair<bool, int> right = sumTree(node->right);
    bool sum = node->data == left.second + right.second;
    pair<bool, int> ans;
    if(left.first && right.first && sum){
        ans.first = true;
        ans.second = 2*node->data;
    }else{
        ans.first = false;
    }
    return ans;
}
void zigzag(Node* node){
    vector<vector<int>>zz;
    if(node == NULL)
        return ;
    queue<Node*>q;
    q.push(node);
    int num = 0;
    while(!q.empty()){
        int n = q.size();
        vector<int>v;
        for(int i=0;i<n;i++){
            Node* temp = q.front();
            q.pop();
            if(temp->left != NULL)
                q.push(temp->left);
            if(temp->right != NULL)
                q.push(temp->right);
            v.push_back(temp->data);
        }
        num++;
        if(num%2 == 0)
            reverse(v.begin(), v.end());
        for(auto i: v)
            cout<<i<<" ";
        cout<<endl;
    }
}
void traverseLeft(Node* node, vector<int>&ans){
    if(!node || (!node->left && !node->right))
        return ;
    // ans.push_back(node->data);
    cout<<node->data<<" ";
    if(node->left)
        traverseLeft(node->left, ans);
    else
        traverseLeft(node->right, ans);
}
void traverseRight(Node* node, vector<int>&ans){
    if(!node || (!node->left && !node->right))
        return ;
    if(node->right)
        traverseRight(node->right, ans);
    else
        traverseRight(node->left, ans);
    // ans.push_back(node->data);
    cout<<node->data<<" ";
}
void traverseLeaf(Node* node, vector<int>&ans){
    if(!node)
        return ;
    if(!node->left && !node->right){
        // ans.push_back(node->data);
        cout<<node->data<<" ";
        return ;
    }
    traverseLeaf(node->left, ans);
    traverseLeaf(node->right, ans);
}
void boundaryTraversal(Node* node){
    vector<int> ans;
    // ans.push_back(node->data);
    cout<<node->data<<" ";
    traverseLeft(node->left, ans);
    traverseLeaf(node, ans);
    traverseRight(node->right, ans);
    // for(auto i:ans){
    //     cout<<i<<" ";
    // }
    cout<<endl;
}
void verticalOrderTraversal(Node* node){
    if(!node)
        return ;
    map<int, map<int, vector<int>>> nodes;
    queue<pair<Node* , pair<int, int>>> q;
    q.push(make_pair(node, make_pair(0,0)));
    while(!q.empty()){
        pair<Node*, pair<int, int>> temp = q.front();
        q.pop();
        Node* nodef = temp.first;
        int horizontalDis = temp.second.first;
        int lvl = temp.second.second;
        nodes[horizontalDis][lvl].push_back(nodef->data);
        if(nodef->left){
            q.push(make_pair(nodef->left, make_pair(horizontalDis-1, lvl+1)));
        }
        if(nodef->right){
            q.push(make_pair(nodef->right, make_pair(horizontalDis+1, lvl+1)));
        }
    }
    for(auto i:nodes){
        for(auto j:i.second){
            for(auto k:j.second){
                cout<<k<<" ";
            }
        }
    }
    cout<<endl;
}
void topView(Node* node){
    if(!node)
        return ;
    map<int, int>tView;
    queue<pair<Node*, int>>q;
    q.push(make_pair(node, 0));
    while(!q.empty()){
        pair<Node*, int> temp = q.front();
        q.pop();
        int horizontalDis = temp.second;
        Node* nodef = temp.first;
        if(tView.find(horizontalDis) == tView.end()){
            tView[horizontalDis] = nodef->data;
        }
        if(nodef->left){
            q.push(make_pair(nodef->left, horizontalDis-1));
        }
        if(nodef->right){
            q.push(make_pair(nodef->right, horizontalDis+1));
        }
    }
    for(auto i:tView){
        cout<<i.second<<" ";
    }
    cout<<endl;
}
void bottomView(Node* node) {
    if (!node)
        return;
    map<int, int>bView;
    queue<pair<Node*, int>>q;
    q.push(make_pair(node, 0));
    while (!q.empty()) {
        pair<Node*, int> temp = q.front();
        q.pop();
        int horizontalDis = temp.second;
        Node* nodef = temp.first;
        bView[horizontalDis] = nodef->data;
        if (nodef->left) {
            q.push(make_pair(nodef->left, horizontalDis - 1));
        }
        if (nodef->right) {
            q.push(make_pair(nodef->right, horizontalDis + 1));
        }
    }
    for (auto i : bView) {
        cout << i.second << " ";
    }
    cout << endl;
}
void leftViewLevelOrder(Node* node) {
    if (!node)
        return;
    map<int, int>lView;
    queue<pair<Node*, int>>q;
    q.push(make_pair(node, 0));
    while (!q.empty()) {
        pair<Node*, int> temp = q.front();
        q.pop();
        int lvl = temp.second;
        Node* nodef = temp.first;
        if (lView.find(lvl) == lView.end()) {
            lView[lvl] = nodef->data;
        }
        if (nodef->left) {
            q.push(make_pair(nodef->left, lvl + 1));
        }
        if (nodef->right) {
            q.push(make_pair(nodef->right, lvl + 1));
        }
    }
    for (auto i : lView) {
        cout << i.second << " ";
    }
    cout << endl;
}
void leftViewRecursive(Node* node, vector<int>&left, int lvl){
    if(!node)
        return ;
    if(lvl == left.size())
        left.push_back(node->data);
    leftViewRecursive(node->left, left, lvl+1);
    leftViewRecursive(node->right, left, lvl+1);
}
void rightViewRecursive(Node* node, vector<int>&right, int lvl){
    if(!node)
        return ;
    if(lvl == right.size())
        right.push_back(node->data);
    rightViewRecursive(node->right, right, lvl+1);
    rightViewRecursive(node->left, right, lvl+1);
}
void sumofLongestPath(Node* node, int sum, int &maxSum, int len, int &maxLen){
    if(!node){
        if(len > maxLen){
            maxSum = sum;
        }
        if(len == maxLen){
            maxSum = max(maxSum, sum);
        }
        return ;
    }
    sum += node->data;
    sumofLongestPath(node->left, sum, maxSum, len+1, maxLen);
    sumofLongestPath(node->right, sum, maxSum, len+1, maxLen);
}
Node* lca(Node* node, int n1, int n2){
    if(!node)
        return NULL;
    if(node->data == n1 || node->data == n2)
        return node;
    Node* left = lca(node->left, n1, n2);
    Node* right = lca(node->right, n1, n2);
    if(left != NULL && right != NULL)
        return node;
    else if(left != NULL && right == NULL)
        return left;
    else if(left == NULL && right != NULL)
        return right;
    else
        return NULL;
}
void kSumPath(Node* node, int sum, int k, int& count){
    if(!node){
        return ;
    }
    if(node->data == k){
        count++;
    }
    sum += node->data;
    kSumPath(node->left, sum, k, count);
    kSumPath(node->right, sum, k, count);
    if(sum == k){
        count++;
    }
}
void printvec(vector<int>v){
    for(auto i:v){
        cout<<i<<" ";
    }
    cout<<endl;
}
void findpath(Node* node, vector<int>& path, int check){
    if(!node){
        return ;
    }
    path.push_back(node->data);
    findpath(node->left, path, check);
    findpath(node->right, path, check);
    if(node->data == check){
        printvec(path);
    }
    path.pop_back();
}
Node* kthancestor(Node* node, int &k, int check){
    if(!node)
        return NULL;
    if(node->data == check)
        return node;
    Node* left = kthancestor(node->left, k, check);
    Node* right = kthancestor(node->right, k, check);
    if(left != NULL && right == NULL){
        k--;
        if(k<=0){
            k = INT_MAX;
            return node;
        }
        return left;
    }
    if(left == NULL && right != NULL){
        k--;
        if(k<=0){
            k = INT_MAX;
            return node;
        }
        return right;
    }
    return NULL;
}
pair<int, int> maxSumNonAdjacent(Node* node){
    if(!node){
        pair<int, int> p = make_pair(0,0);
        return p;
    }
    pair<int, int> left = maxSumNonAdjacent(node->left);
    pair<int, int> right = maxSumNonAdjacent(node->right);

    pair<int, int> ans;
    ans.first = node->data + left.second + right.second;
    ans.second = max(left.first, right.first) + max(left.second, right.second);
    return ans;
}
int findIndex(int arr[], int n, int key){
    for(int i=0;i<n;i++){
        if(arr[i] == key)
            return i;
    }
    return -1;
}
Node* treeInPre(int in[], int pre[], int &index, int inStart, int inEnd, int n){
    if(index >= n || inStart > inEnd){
        return NULL;
    }
    Node* node = new Node(pre[index]);
    int pos = findIndex(in, n, pre[index]);
    index++;
    node->left = treeInPre(in, pre, index, inStart, pos-1, n);
    node->right = treeInPre(in, pre, index, pos+1, inEnd, n);
    return node;
}
Node* treeInPost(int in[], int post[], int &index, int inStart, int inEnd, int n){
    if(index < 0 || inStart > inEnd){
        return NULL;
    }
    Node* node = new Node(post[index]);
    int pos = findIndex(in, n, post[index]);
    index--;
    node->right = treeInPost(in, post, index, pos+1, inEnd, n);
    node->left = treeInPost(in, post, index, inStart, pos-1, n);
    return node;
}
void parentMapping(Node* root, map<Node*, Node*>& childToParent) {
    queue<Node*>q;
    q.push(root);
    childToParent[root] = NULL;
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        if(temp->left){
            childToParent[temp->left] = temp;
            q.push(temp->left);
        }
        if(temp->right){
            childToParent[temp->right] = temp;
            q.push(temp->right);
        }
    }
}
void findTarget(Node* node, int target, Node* &ans){
    if(!node)
        return ;
    findTarget(node->left, target, ans);
    if(node->data == target)
        ans = node;
    findTarget(node->right, target, ans);
}
int burnTree(Node* targetNode, map<Node*, Node*>childToParent){
    map<Node*, bool>vis;
    queue<Node*>q;
    int ans = 0;
    q.push(targetNode);
    vis[targetNode] = true;
    while(!q.empty()){
        bool flag = false;
        int n = q.size();
        for(int i=0;i<n;i++){
            Node* temp = q.front();
            q.pop();
            if(temp->left && !vis[temp->left]){
                flag = true;
                vis[temp->left] = true;
                q.push(temp->left);
            }
            if(temp->right && !vis[temp->right]){
                flag = true;
                vis[temp->right] = true;
                q.push(temp->right);
            }
            if(childToParent[temp] && !vis[childToParent[temp]]){
                flag = true;
                vis[childToParent[temp]];
                q.push(childToParent[temp]);
            }
        }
        if(flag){
            ans++;
        }
    }
    return ans;
}
int main(){
    io();
    Node* root = NULL;
    buildLevelOrder(root);
    cout<<"Level Order\n";
    levelOrder(root);
    cout<<"Inorder: ";
    inorder(root);
    cout<<"\nPreorder: ";
    preorder(root);
    cout<<"\nPostorder: ";
    postorder(root);
    int count = 0;
    countLeaf(root, count);
    cout<<"\nNumber of Leaf Node: "<<count<<"\n";
    int height = heightOfTree(root);
    cout<<"Height of Binary Tree: "<<height<<endl;
    cout<<"Diameter of Binary Tree: "<<diameter(root).first<<endl;
    cout<<"Slow method for Diameter of Binary Tree: "<<diameterSlow(root)<<endl;
    balanced(root) == -1 ? cout<<"Tree is not balanced\n":cout<<"Tree is balanced\n";
    sumTree(root).first ? cout<<"Sum Tree\n":cout<<"Not a sum tree\n";
    cout<<"Zig Zag traversal: \n";
    zigzag(root);
    cout<<"Boundary Traversal: ";
    boundaryTraversal(root);
    cout<<"Vertical order Traversal: ";
    verticalOrderTraversal(root);
    cout<<"Top view of Binary Tree: ";
    topView(root);
    cout<<"Bottom view of Binary Tree: ";
    bottomView(root);
    cout<<"Left view of Binary Tree using level order: ";
    leftViewLevelOrder(root);
    cout<<"Left view of Binary Tree using recursion: ";
    vector<int>left;
    leftViewRecursive(root, left, 0);
    for(auto i:left)
        cout<<i<<" ";
    cout<<endl;
    cout<<"Right view of Binary Tree using recursion: ";
    vector<int>right;
    rightViewRecursive(root, right, 0);
    for(auto i:right)
        cout<<i<<" ";
    cout<<endl;
    cout<<"Sum of nodes on the longest path of the binary tree: ";
    int sum = 0;
    int maxSum = INT_MIN;
    int len = 0;
    int maxLen = INT_MIN;
    sumofLongestPath(root, sum, maxSum, len, maxLen);
    cout<<maxSum<<endl;
    Node* ans = lca(root, 1, 20);
    if(ans == NULL){
        cout<<-1<<endl;
    }else{
        cout<<"Lowest common ancestor of 4 amd 14: "<<ans->data<<endl;
    }
    count = 0;
    kSumPath(root, 0, 28, count);
    cout<<count<<endl;
    vector<int>path;
    cout<<"Path: ";
    findpath(root, path, 4);
    int k = 2;
    cout<<k<<"nd Ancestor of 12: ";
    ans = kthancestor(root, k, 12);
    if(!ans || ans->data == 12){
        cout<<-1<<endl;
    }else{
        cout<<ans->data<<endl;
    }
    cout<<"Maximum sum of nom adjacent nodes: ";
    pair<int, int>res = maxSumNonAdjacent(root);
    cout<<max(res.first, res.second)<<endl;
    cout<<"Build tree using Inorder and Preorder then printing its Postorder: ";
    //for further optimization instead of finding the index of preorder element
    //in inoder we can store the index and value in map then access them directly.
    int n = 8;
    int in[n] = {4, 8, 10, 12, 14, 20, 22, 25};
    int pre[n] = {20, 8, 4, 12, 10, 14, 22, 25};
    //inorder, preorder, preorderIndex, inorderStart, inorderEnd, size
    int preIndex = 0;
    root = treeInPre(in, pre, preIndex, 0, n-1, n);
    postorder(root);
    cout<<"\nBuild tree using Inorder and Postorder then printing its Preorder: ";
    int post[n] = {4, 10, 14, 12, 8, 25, 22, 20};
    int postIndex = n-1;
    root = treeInPost(in, post, postIndex, 0, n-1, n);
    preorder(root);
    cout<<endl;
    cout<<"Child to Parent mapping: \n";
    map<Node*, Node*> childToParent;
    parentMapping(root, childToParent);
    for(auto it:childToParent){
        Node* child = it.first;
        Node* parent = it.second;
        if(parent && child){
            cout<<child->data<<" -> "<<parent->data<<"\n";
        }
    }
    cout<<"Time to burn the entire tree: ";
    Node* targetNode = NULL;
    findTarget(root, 4, targetNode);
    cout<<burnTree(targetNode, childToParent);
    // 20 8 22 4 12 -1 25 -1 -1 10 14 -1 -1
    // 1 2 3 4 5 -1 6 -1 -1 7 8 -1 9 -1 -1 -1 -1 -1 10
    return 0;
}

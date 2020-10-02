#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;

class Node{
    public:
     int data=0;
     Node* left=NULL;
     Node* right=NULL;

     Node(int data){
         this->data=data;
     }
     Node(int data,Node* left,Node*right){
         this->data=data;
         this->left=left;
         this->right=right;
     }
};


Node*create(vector<int>&arr,int si,int ei){
    if(si>ei){
        return nullptr;
    }
    if(si==ei){
        Node*node=new Node(arr[si]);
        return node;
    }
    int mid=(si+ei)>>1;   //mid=(si+ei)/2
    Node* node=new Node(arr[mid]);
    node->left=create(arr,si,mid-1);
    node->right=create(arr,mid+1,ei);
    return node;
}
void display(Node*node){
    if(node==NULL){
        return;
    }
    string str="";
    str+=(node->left!=NULL?to_string(node->left->data):".");
    str+="->" + to_string(node->data) + "<-";
    str+=(node->right!=NULL?to_string(node->right->data):".");
    cout<<str<<endl;
    display(node->left);
    display(node->right);
}
int minimum(Node*node){
    if(node==NULL){
        return INT_MAX;
    }
    int minl=minimum(node->left);
    int minr=minimum(node->right);
    int minroot=min(minl,minr);
    return min(node->data,minroot);
}
int maximum(Node*node){
    if(node==NULL){
        return INT_MIN;
    }
    int maxl=maximum(node->left);
    int maxr=maximum(node->right);
    int maxroot=max(maxl,maxr);
    return max(maxroot,node->data);
}
// int min(Node*node){
//     if(node->left==NULL){
//         return node->data;
//     }
//     int res=min(node->left);
//     return res;
// }
bool find(Node*node,int data){
    if(node==NULL){
        return false; 
    }
    if(node->data==data){
        return true;
    }
    return find(node->left,data) || find(node->right,data);
}
int height(Node*node){
    if(node==NULL){
        return 0;
    }
    int l=0;
    int r=0;
    l+=height(node->left);
    r+=height(node->right);
    return max(l,r)+1;
}
int size(Node*node){
    if(node==NULL){
        return 0;
    }
    int s=0;
    s+=size(node->left);
    s+=size(node->right);
    return s+1;
}
int lca(Node*node,int n1,int n2){
    if(node==NULL){
       return -1;
    }
    if(node->data<n1){
        return lca(node->right,n1,n2);
    }
    else if(node->data>n2){
        return lca(node->left,n1,n2);
    }
    else{
        return node->data;
    }
}

// void add(Node* node,Node*par,int data,bool isleft){
//     if(node->data==NULL){
//         Node*child=new Node(data);
//         if(isleft==true){
//             par->left=data;
//         }
//         else{
//             par->right=data;
//         }
//     }
//     if(data<node->data){
//         add(node->left,node,data,true);
//     }
//     if(data>node->data){
//         add(node->right,node,data,false);
//     }
// }
Node*addNode(Node*node,int data){
    if(node==NULL){
        return new Node(data);
    }
    if(data>node->data){
        node->right=addNode(node->right,data);
    }
    if(data<node->data){
        node->left=addNode(node->left,data);
    }
    return node;
}

Node*delNode(Node*node,int data){
    if(node==NULL){
        
    }
}



// Node* pred=NULL;
// Node* succ=NULL;
// Node* pre=NULL;
// void presucc_01(Node*node,int data){
//     if(node==NULL){
//         return ;
//     }
//     presucc_01(Node->left,data);
//     if(node->data==data){
//         pred=pre;
//     }
//     if(pre!=NULL&& pre->data==data){
//         succ=node;
//     }
//     pre=node;
//     presucc_01(node->right,data);
// }



void solve(){
vector<int>arr={10,20,30,40,50,60,70,80,90,100,110,120};
Node*root=create(arr,0,arr.size()-1);
//display(root);
cout<<minimum(root)<<endl;
cout<<maximum(root)<<endl;;
cout<<(boolalpha)<<find(root,140)<<endl;
cout<<height(root)<<endl;
cout<<size(root)<<endl;
cout<<lca(root,10,20)<<endl;
addNode(root,21);
display(root);
}
int main(int args, char** argv){
solve();
return 0;
}
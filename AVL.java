import java.util.Scanner;
public class AVL{
    public static void main(String[] args){
        int [] arr={10,20,30,40,50,60,70,80,90,100,110,120};
        Node root=create(arr,0,arr.length-1);
        Display(root);
    }
    public static class Node{
        int data=0;
        Node left=null;
        Node right=null;
        int height=-1;
        int balance=0;
        Node(int data){
            this.data=data;
        }
        Node(int data,Node left,Node right,int height,int balance){
            this.data=data;
            this.left=left;
            this.right=right;
            this.height=height;
            this.balance=balance;
        }    
    }
    public static Node create(int [] arr,int si,int ei){
        if(si>ei){
            return null;
        }
        int mid=(si+ei)>>1;
        Node node=new Node(arr[mid]);
        node.left=create(arr,si,mid-1);
        node.right=create(arr,mid+1,ei);
        node.height=getHeight(node);
        node.balance=getblance(node);
        return node;
    }
    public static void Display(Node node){
        if(node==null){
            return;
        }
        StringBuilder sb=new StringBuilder();
        sb.append(node.left!=null?node.left.data:".");
        sb.append("->" + node.data+ "<-");
        sb.append(node.right!=null?node.right.data:".");

        System.out.println(sb.toString());
        System.out.println("Height: "+node.height+" Balance: "+node.balance);
        Display(node.left);
        Display(node.right);  
    }
    public static int getblance(Node node){
        if(node==null){
            return 0;
        }
        int lh=-1;
        int rh=-1;
        if(node.left!=null){
            lh=node.left.height;
        }
        if(node.right!=null){
            rh=node.right.height;
        }
            return lh-rh;
    }
    public static int getHeight(Node node){
        if(node==null){
            return -1;
        }
        int lh=-1;
        int rh=-1;
        if(node.left!=null){
            lh=node.left.height;
        }
        if(node.right!=null){
            rh=node.right.height;
        }
            return Math.max(lh,rh)+1;
    }
    public static void updateFactors(Node node){
        node.height=getHeight(node);
        node.balance=getblance(node);
    }
    public static Node rightRotation(Node node){
        Node newnode=node.left;
        Node temp=newnode.right;
        
        newnode.right=node;
        node.left=temp;
        
        updateFactors(node);
        updateFactors(newnode);
        return newnode;
    }
    public static Node leftRotation(Node node){
        Node newnode=node.right;
        Node temp=newnode.left;
        newnode.left=node;
        node.right=temp;
        updateFactors(node);
        updateFactors(newnode);
        return newnode;
    }
    Node newFactors(Node node){
        if(getblance(node)>1){ //ll,lr
            if(getblance(node.left)>0){ //ll
                node=rightRotation(node);
            }
            else{   //lr
                node.left=leftRotation(node.left);
                node.right=rightRotation(node);
            }
        }
        else if(getHeight(node)<-1){ //rr,rl
            if(getblance(node.right)<0){ //rr
                node=leftRotation(node);
            }
            else{  //rl
                node.right=rightRotation(node.right);
                node.left=leftRotation(node);
            }
        }
        return node;
    }
    
}
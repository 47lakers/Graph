//
//  main.cpp
//  Graphs
//
//  Created by Ira Xavier Porchia on 6/30/20.
//  Copyright © 2020 Ira Xavier Porchia. All rights reserved.
//

#include <iostream>
using namespace std;

//For LL
const int MAX = 5;
//For queue
const int MAX1 = 100;

template<class T>
class Queue{
private:
    int _head;
    int _tail;
public:
    T _arr[MAX1];
    
    Queue():
    _head(0), _tail(0){}
    
    bool isFull(){
        if((_tail + 1) % MAX1 == _head){
            return true;
        }
        return false;
    }
    
    bool isEmpty(){
        if(_tail == _head){
            return true;
        }
        return false;
    }
    
    void enqueue(T data){
        if(isFull()){
            cout << "Error" << endl << endl;
            return;
        }
        _arr[_tail] = data;
        _tail = (_tail + 1) % MAX1;
    }
    
    T dequeue(){
        if(isEmpty()){
            cout << "Error" << endl << endl;
            return -1;
        }
        T temp = _arr[_head];
        _head = (_head + 1) % MAX1;
        return temp;
    }
    
    void print(){
        for(int i = 0; i < MAX1; i++){
            cout << _arr[i] << " ";
        }
        cout << endl << endl;
    }
    
    T front(){
        return _arr[_head];
    }
};

class Stack{
    private:
        int _top;
    public:
        int _data[MAX1];
    
        Stack():
        _top(-1){}
    
        bool push(int value){
            if(_top >= (MAX1 - 1)){
                cout << "Stack Overflow" << endl;
                return false;
            }
            _data[++_top] = value;
            return true;
        }
    
        int pop(){
            if(_top < 0){
                cout << "Stack Underflow" << endl;
                return 0;
            }
            int value = _data[_top--];
            return value;
        }
    
        int peek(){
            if (_top < 0) {
                cout << "Stack is Empty";
                return 0;
            }
            else {
                int value = _data[_top];
                return value;
            }
        }
    
        bool isEmpty(){
            return (_top < 0);
        }
};

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

class MatrixGraph{
private:
    int _vertex;
    int _edge;
    int **adj;
public:
    MatrixGraph(int v, int e){
        _vertex = v;
        _edge = e;
        adj = new int *[v];
        for(int row = 0; row < v; row++){
            adj[row] = new int [v];
            for(int col = 0; col < v; col++){
                adj[row][col] = 0;
            }
        }
    }
    
    void addEdge(int start, int e){
        adj[start][e] = 1;
        adj[e][start] = 1;
    }
    
    void print(){
        for(int i = 0; i < _vertex; i++){
            for(int j = 0; j < _vertex; j++){
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void BFS(int start){
        Queue<int> queue;
        int v = _vertex;
        //Create an array that shows whether something is visited or not
        bool visited[v];
        for(int i = 0; i < v; i++){
            visited[i] = false;
        }
        //Enqueue the first value and set that it's visited
        queue.enqueue(start);
        visited[start] = true;
        int vis;
        while(!queue.isEmpty()){
            //cout the number in the queue and then dequeue it
            vis = queue.front();
            cout << vis << " ";
            queue.dequeue();
            //For every adjacent vertex to the current vertex
            for(int i = 0; i < v; i++){
                if(adj[vis][i] == 1 && (!visited[i])){
                    //Push the adjacent node to the queue
                    queue.enqueue(i);
                     // Set
                    visited[i] = true;
                }
            }
        }
        cout << endl << endl;
    }
    
    void DFS(int start){
        Stack stack;
        int v = _vertex;
        //Create an array that shows whether something is visited or not
        bool visited[v];
        for(int i = 0; i < v; i++){
            visited[i] = false;
        }
        //Push the first value and set that it's visited
        stack.push(start);
        visited[start] = true;
        int vis;
        while(!stack.isEmpty()){
            //cout the number in the stack and then dequeue it
            vis = stack.peek();
            cout << vis << " ";
            stack.pop();
            //For every adjacent vertex to the current vertex
            for(int i = 0; i < v; i++){
                if(adj[vis][i] == 1 && (!visited[i])){
                    //Push the adjacent node to the queue
                    stack.push(i);
                     // Set
                    visited[i] = true;
                }
            }
        }
        cout << endl << endl;
    }
    
};

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

class node{
    friend class linkedList;
    friend class LLGraph;
private:
    int _data;
    node *_next;
public:
    node(int data):
    _data(data), _next(nullptr){}
};

class linkedList{
    friend class LLGraph;
private:
    node *_head;
public:
    linkedList():
    _head(nullptr){}
    
    ~linkedList(){
        clear();
    }
    
    void clear(){
        if(_head == nullptr){
            return;
        }
        node *temp;
        while(_head != nullptr){
            temp = _head;
            _head = _head->_next;
            temp->_next = nullptr;
            delete temp;
        }
    }
    
    void append(int data){
        if(_head == nullptr){
            _head = new node(data);
            return;
        }
        node *temp = _head;
        while(temp->_next != nullptr){
            temp = temp->_next;
        }
        temp->_next = new node(data);
    }
    
    void remove(int data){
        if(_head == nullptr){
            return;
        }
        if(_head->_data == data){
            node *temp = _head->_next;
            _head->_next = nullptr;
            _head = temp;
        }
        node *p = _head->_next;
        node *q = _head;
        while(p != nullptr){
            if(p->_data == data){
                q->_next = p->_next;
            }
            q = p;
            p = p->_next;
        }
    }
    
    void traverse(){
        node *temp = _head;
        while(temp != nullptr){
            cout << temp->_data << " ";
            temp = temp->_next;
        }
        cout << endl << endl;
    }
    
    
};

class LLGraph{
private:
    int _vertex;
    
    linkedList *adj;
public:
    LLGraph(int v){
        adj = new linkedList[v];
        _vertex = v;
    }
    
    void addEdge(int v, int w){
        adj[v].append(w);
        adj[w].append(v);
    }
    
//    void inOrder(int i){
//        node *head = adj[i]._head;
//        node *p = head->_next;
//        node *q = head;
//        if(p == nullptr){
//            return;
//        }
//        while(p != nullptr){
//            if(p->_data < q->_data){
//                int temp = p->_data;
//                p->_data = q->_data;
//                q->_data = temp;
//            }
//            q = p;
//            p = p->_next;
//        }
//    }
    
    void print(){
        for(int i = 0; i < MAX; i++){
            cout << i;
            node *temp = adj[i]._head;
            if(temp != nullptr){
                cout << " ---> ";
            }
            while(temp != nullptr){
                cout << temp->_data;
                if(temp->_next != nullptr){
                    cout << " ---> ";
                }
                temp = temp->_next;
            }
            cout << endl;
        }
        cout << endl << endl;
    }
    
    void BFS(int start){
        Queue<int> queue;
        int v = _vertex;
        //Create an array that shows whether something is visited or not
        bool visited[v];
        for(int i = 0; i < v; i++){
            visited[i] = false;
        }
        //Enqueue the first value and set that it's visited
        queue.enqueue(start);
        visited[start] = true;
        int vis;
        while(!queue.isEmpty()){
            //cout the number in the queue and then dequeue it
            vis = queue.front();
            cout << vis << " ";
            queue.dequeue();
            //For every adjacent vertex to the current vertex
            node *temp = adj[vis]._head;
            if(temp == nullptr){
                cout << endl << endl;
                return;
            }
            int i;
            while(temp != nullptr){
                i = temp->_data;
                if((!visited[i])){
                    //Push the adjacent node to the queue
                    queue.enqueue(i);
                     // Set
                    visited[i] = true;
                }
                temp = temp->_next;
            }
        }
        cout << endl << endl;
    }
    
    void DFS(int start){
        Stack stack;
        int v = _vertex;
        //Create an array that shows whether something is visited or not
        bool visited[v];
        for(int i = 0; i < v; i++){
            visited[i] = false;
        }
        //Push the first value and set that it's visited
        stack.push(start);
        visited[start] = true;
        int vis;
        while(!stack.isEmpty()){
            //cout the number in the stack and then dequeue it
            vis = stack.peek();
            cout << vis << " ";
            stack.pop();
            //For every adjacent vertex to the current vertex
            node *temp = adj[vis]._head;
                if(temp == nullptr){
                    cout << endl << endl;
                    return;
                }
                int i;
                while(temp != nullptr){
                    i = temp->_data;
                    if((!visited[i])){
                        //Push the adjacent node to the queue
                        stack.push(i);
                         // Set
                        visited[i] = true;
                    }
                    temp = temp->_next;
                }
            }
        cout << endl << endl;
    }
    
};

int main(int argc, const char * argv[]) {
    MatrixGraph graph(5, 5);
    graph.print();
    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.print();
    graph.BFS(3);
    graph.DFS(3);
    cout << endl << endl;
    LLGraph graph2(5);
    graph2.print();
    graph2.addEdge(0, 1);
    graph2.addEdge(0, 4);
    graph2.addEdge(1, 2);
    graph2.addEdge(1, 3);
    graph2.addEdge(1, 4);
    graph2.addEdge(2, 3);
    graph2.addEdge(3, 4);
    graph2.print();
    graph2.BFS(3);
    graph2.DFS(3);
    return 0;
}

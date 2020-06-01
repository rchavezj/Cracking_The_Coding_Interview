Kahn Algorithm
//Input : adj_list ->Adjacency list; indegree : indegrees of all nodes .....
void top_sort(vector<list<int> > & adj_list, vector<int> &indegree) {
      queue<int> tsort_queue;
      vector<int> sorted;
     
      //If a node is not present in the graph , its indegree is -1.....
      for(int i = 0; i < (signed)indegree.size(); i++) {
            if(indegree[i] == -1)
                  continue;
            if(indegree[i] == 0)
            tsort_queue.push(i);
      }
     
      while(!tsort_queue.empty()) {
            int front = tsort_queue.front();
            tsort_queue.pop();
            sorted.push_back(front);
            list<int>::iterator it;
            for(it = adj_list[front].begin();
                        it != adj_list[front].end(); it++) {
                  indegree[*it] -= 1;
                  if(indegree[*it] == 0)
                        tsort_queue.push(*it);
            }
      }
      cout<<"Top Sorted Order : ";
      for(int i = 0; i < (signed)sorted.size(); i++)
            cout<<sorted[i]<<" ";
      cout<<endl;
}
#include <iostream>
#include <conio.h>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <set>
using namespace std;



class Vertex
{

public:
	int vertexid ;
	int distance ;
	int positioninheap;
	
};

class Edge
{
 public:
	Vertex source; /// Source vertex of the edge 
	Vertex destination ; /// Destination vertex of the edge
	int weight ;  /// Weight of the edge 
	Edge(Vertex isource,  Vertex idestination , int iweight)
	{
		source = isource;
		destination = idestination;
		weight = iweight ;
	}
};




class Graph
{
	public:
	
		vector<Vertex>VerticesList;
		vector<Vertex>SpannedVerticesList;
		list<Edge>Edgeslist;
		map<int,vector<Edge>>AdjacencyList ;
		int vertices;
		int edges ;
	
		void InitializeGraph(int numvertices ,int numedges)
		{
			vertices = numvertices;
			edges = numedges;
		}	


	  void AddEdge(Vertex source ,Vertex destination ,int weight)
	  {
		  Edge  e1(source , destination , weight);
		  Edgeslist.push_back(e1);
	  }

	  void SetVertices()
	  {
		 cout<<"EdgesListSize"<<Edgeslist.size();
		 getch();
		 set<int>vertexids;
		 for(list<Edge>::iterator itr = Edgeslist.begin() ;itr != Edgeslist.end();++itr)
		  {

			  Vertex source = itr->source ;
			  Vertex destination = itr->destination ;
			  vector<Vertex>::iterator sourcevertexitr = VerticesList.begin();
			  vertexids.insert(source.vertexid);
			  vertexids.insert(destination.vertexid);
		  }

		  for(set<int>::iterator it=vertexids.begin(); it!=vertexids.end(); ++it)
		  {
			  Vertex vertex ;
			  vertex.vertexid =  *it;
			  VerticesList.push_back(vertex);	
		  }

		 
	  }

	  void SetAdjacencyListForEachVertex()
	  {
		  
		  
		  for(int i = 0 ;i<VerticesList.size() ;++i)
		  {

			  
			    for (list<Edge>::iterator itr = Edgeslist.begin();itr != Edgeslist.end();++itr)
				{

					Vertex src;
					src.vertexid = 0;
					Vertex destn;
					destn.vertexid = 0;
					if(VerticesList[i].vertexid == itr->source.vertexid || VerticesList[i].vertexid == itr->destination.vertexid)
					{

						src = itr->source; 
						destn = itr->destination;
						Edge tempedge(src,destn,itr->weight);
						AdjacencyList[VerticesList[i].vertexid].push_back(tempedge);
					    
					}
				  

					

				}

			

	      }

		    for(map<int,vector<Edge>>::iterator itr = AdjacencyList.begin() ;itr != AdjacencyList.end();++itr)
			  {
				  cout<<endl<<"Adjacency List "<<endl;
				  cout<<"Vertex=" <<itr->first<<endl ;
				  for(vector<Edge>::iterator itr2 =itr->second.begin();itr2 !=itr->second.end();++itr2)
				  {
					  cout<<itr2->source.vertexid<<"  "<<itr2->destination.vertexid<<"  "<<itr2->weight<<endl;
				  }
				   getch();
			  }
	  }


};


class MinHeap
{

public:
	
	vector<Vertex>m_pMinHeap; /// This is used to represent the Heap Data Structure 
	                           
	int m_NumElementsInHeap; ///Size of the heap
	
public:
	MinHeap()
	:m_pMinHeap(),
	m_NumElementsInHeap(0)
	{
		


	}

	void insert(Vertex newvertex)
	{
		int pos = m_NumElementsInHeap;
		newvertex.positioninheap = pos ;
		m_pMinHeap.push_back(newvertex);
		cout<<"insert"<<endl ;
		heapifyup(pos);
		m_NumElementsInHeap++;
	}

	Vertex extract_min()
	{
		//First element in the heap is to be returned 
		Vertex ret = m_pMinHeap[0] ;

		//Last element in the Heap is being set as the first element
		m_pMinHeap[0] = m_pMinHeap[m_NumElementsInHeap -1] ;

		//update the position of the above inserted vertex in heap to be  0
		m_pMinHeap[0].positioninheap = 0;

		//Decrease the size of heap by 1
		m_NumElementsInHeap-- ;

		if(m_NumElementsInHeap>0)
		{
			heapifydown(0);

		}

		return ret;
		
	}

	void decrease_key(Vertex vertex ,int newdistance)
	{
		vertex.distance = newdistance ;
		heapifyup(vertex.positioninheap);
	}

public:
	
	void heapifyup(int i)
	{
		int j = 0; 
		 cout<<"heapifyup"<<endl  ;
		while(i>=0)
		{
		    cout<<"Enter while"<<endl  ;
			j =i/2;

			if(m_pMinHeap[i].distance < m_pMinHeap[j].distance)
			{
				Vertex temp ;

				//Sapping the elements 
				temp = m_pMinHeap[i];
				m_pMinHeap[i] = m_pMinHeap[j];
				m_pMinHeap[j] = temp ;

				m_pMinHeap[i].positioninheap = i ;
				m_pMinHeap[j].positioninheap = j ;
				i = j ;
			}
			else
			{
				break ;
			}



		}
	}

    void heapifydown(int i)
	{
		int j = 0 ;
		while(2*i < m_NumElementsInHeap)
		{
			if(2*i == m_NumElementsInHeap -1 || m_pMinHeap[2*i].distance <=   m_pMinHeap[2*i +1].distance)
			{

				j =  2*i ;

			}
			else
			{
				j =2*i + 1 ;

			}

			if(m_pMinHeap[j].distance < m_pMinHeap[i].distance )
			{
				Vertex temp ;
				temp = m_pMinHeap[j];
				m_pMinHeap[j]  = m_pMinHeap[i] ;
			    m_pMinHeap[i] =  temp ;

				m_pMinHeap[i].positioninheap = i ;
				m_pMinHeap[j].positioninheap = j ;
				i = j ;
			}
			else
			{
				break;
			}
		}


	}

};

int main()
{




	int numvertices =0 ; 
	int numedges = 0;

	ifstream ifobj;
	ifobj.open("input.txt");
	Graph objgraph;
	if (ifobj.is_open())
	{
		
		ifobj>>numvertices>>numedges;

		objgraph.InitializeGraph(numvertices,numedges);
		
		
		int weight=0,sourcevertexid=0,destinationvertexid=0 ;	

		while (ifobj>>sourcevertexid>>destinationvertexid>>weight)
		{
			
			Vertex tempsourcevertex,tempdestinationvertex ;	 		
			tempsourcevertex.vertexid = sourcevertexid ;
			tempdestinationvertex.vertexid = destinationvertexid;
			objgraph.AddEdge(tempsourcevertex,tempdestinationvertex,weight);
		}
		
		ifobj.close();
	}
	

	objgraph.SetVertices();
	objgraph.SetAdjacencyListForEachVertex();

	vector<Edge> MST;

	//below steps yields a random vertex in the graph
	int randomvertexid =  rand() % objgraph.vertices +1 ;
	cout<<"randomvertexid"<<randomvertexid<<endl;
	cout<<"check"<<endl;
	cout<<objgraph.VerticesList.size()<<endl;
	getch();
	Vertex objfirstvertex = objgraph.VerticesList[randomvertexid];

	
	MinHeap objheap;
	
	for(int i =0 ; i< objgraph.VerticesList.size() ; ++i)
	{
		if(objgraph.VerticesList[i].vertexid == randomvertexid)
		{
			//Assigning the distance value for the first vertex in MST to be 1 
			objgraph.VerticesList[i].distance =  0;
		}
		else
		{
			//Assigning the distance value for remaining vertices to be infinity which is represented by value 10^7
			objgraph.VerticesList[i].distance = 10000000;
		}
	
		//Inserting every vertex into  minheap which is the priority queue
		objheap.insert(objgraph.VerticesList[i]);
	}
	
	
	while(objgraph.SpannedVerticesList.size() != objgraph.VerticesList.size())
	{
		for(int i = 0 ;i<objheap.m_pMinHeap.size();++i)
		{
			cout<<objheap.m_pMinHeap[i].vertexid<<":"<<objheap.m_pMinHeap[i].distance<<endl;

		}

		Vertex u  =  objheap.extract_min();
		cout<<endl<<"u.vertexid="<<u.vertexid<<endl;
		getch();
		objgraph.SpannedVerticesList.push_back(u); 

		vector<Edge>templist = objgraph.AdjacencyList[u.vertexid]; 

		for(vector<Edge>::iterator itr =  templist.begin() ; itr != templist.end(); ++itr)
		{
			cout<<"for loop main"<<endl;
			Vertex v =  itr->destination ;
			cout<<"v.vertexid"<<v.vertexid<<" ";	
		
			bool bIsVertexInSpannedVerticesList =  false;
			for(vector<Vertex>::iterator itr2 =  objgraph.SpannedVerticesList.begin() ; itr2 != objgraph.SpannedVerticesList.end(); ++itr2)
			{

				//	cout<<"2nd for loop"<<endl;
				if(v.vertexid == (*itr2).vertexid)
				{
					bIsVertexInSpannedVerticesList = true;
					break;
				}

			}
			
			
			//the destination vertex being considered shouldnt be in the spanned vertices list 
			if(!bIsVertexInSpannedVerticesList)
			{	

				if((*itr).weight < v.distance)
				{

					v.distance = (*itr).weight;
					//distance value is updated 
					objheap.decrease_key(v,v.distance);

								
				}

					
			}

			
		}

		if(!templist.empty())
		{
			Vertex d1 ;
			d1.vertexid = 0;
			Vertex d2 ;
			d2.vertexid = 0;
			Edge minedge(d1,d2,10000000) ;
			for( vector<Edge>::iterator edgeitr2 = templist.begin(); edgeitr2 != templist.end() ; ++edgeitr2)
			{
						
				if(edgeitr2->weight < minedge.weight)
				{
							
					minedge = *edgeitr2;
								
				}

			}
			cout<<endl<<"minedge w="<<minedge.weight<<":"<<minedge.source.vertexid<<":"<<minedge.destination.vertexid<<endl;
			getch();
			MST.push_back(minedge);
		}		
	}
	
	
	int totweight = 0 ;
	for(vector<Edge>::iterator edgeitr =  MST.begin() ; edgeitr != MST.end(); ++edgeitr)
	{

		totweight +=(*edgeitr).weight; 

	}
	cout<<totweight<<endl;
	
	cout<<"MST.size="<<MST.size()<<endl;
	


	ofstream ofobj;
	ofobj.open("output.txt");
	if (ofobj.is_open())
	{

		ofobj<<totweight<<endl;
		
		for(vector<Edge>::iterator edgeitr =  MST.begin() ; edgeitr != MST.end(); ++edgeitr)
		{
			int v1 = (*edgeitr).source.vertexid;
			cout<<v1;
			int v2 = (*edgeitr).destination.vertexid;
			cout<<v2;
			ofobj << v1 <<" "<<v2<<endl; 
		}
		ofobj.close();
	}

	
	return 0 ;

}
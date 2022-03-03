#include<iostream>

#include<cstdlib>
#include<cstring>
#include<stdio.h>
#include <vector>
#include <list>
// #include <utility>//
#include <bits/stdc++.h> 
using namespace std;
typedef pair<int,int> P;
//int c = 0;
vector< vector<int> > m;///////新的

int total_edges_weight = 0;







void solve_dir(vector<int>& w,vector<int>& out,vector<int>& in, list<int>& node, const int& V,FILE* fpout)
{
    bool source_state = false;
    bool sink_state = false;
    
    fprintf(fpout,"            \n");
    // list<int>::iterator ittt;//for final list
    // list<int>::iterator ittt1;
    while (!node.empty())
    {
        list<int>::iterator i; 
        list<int>::iterator it1;
        for (i = node.begin(); i != (node.end()); ++i) 
            {
                //cout<<(*i)<<endl;
                if (sink_state==true)//有砍sink
                {
                    i=node.begin();
                    sink_state=false;
                }
                
                if( ( out[(*i)]==0 ) && ( in[(*i)]!=0 ) )//sink
                {
                    //cerr<< (*i) <<" is a sink "<<endl;
                    int thisnode=(*i);
                    for (int j=0; j<V ; ++j) 
                    {
                        if (m[j][thisnode]!=(-110))
                        {
                            w[j]-=m[j][thisnode];
                            out[j]-=1;
                            //cerr << j << " " << thisnode << " " << m[j][thisnode]   << "is removed" << endl;
                            m[j][thisnode]=(-110);

                        }
                    }
                    
                    w[thisnode]=(-214748364);
                    it1=node.erase(i);
                    in[thisnode]=0;
                    i=it1;
                    i--;
                    sink_state=true;
                    // after.push_front(thisnode);
                }
            }//for
        for (i = node.begin(); i != (node.end()); ++i) 
            {
                
                if (source_state==true)//有砍source
                {
                    i=node.begin();
                    source_state=false;
                }
                if( ( out[(*i)]!=0 ) && ( in[(*i)]==0 ) )//source
                {
                    //cerr<< (*i) <<" is a source "<<endl;
                    int thisnode=(*i);
                    for (int j=0; j<V ; ++j) 
                    {
                        if (m[thisnode][j]!=(-110))
                        {
                            w[j]+=m[thisnode][j];
                            in[j]-=1;
                            //cerr << thisnode << " " << j << " " << m[thisnode][j]  << "is removed" << endl;
                            m[thisnode][j]=(-110);
                            

                        }
                    }
                    
                    out[thisnode]=0;
                    w[thisnode]=(-214748364);
                    it1=node.erase(i);
                    i=it1;
                    i--;
                    source_state=true;
                    //cerr<<"the source "<<thisnode<<" is push to vector "<<endl;
                    // pre.push_back(thisnode);
                }
            }
        for (i = node.begin(); i != (node.end()); ++i)
            {    
                if( ( out[(*i)]==0 ) && ( in[(*i)]==0 ) )
                {
                    // pre.push_back( (*i) );
                    it1=node.erase(i);
                    i=it1;
                    i--;
                    w[ (*i) ]=(-214748364);

                }
            }
        
                   
                    

            //for source sink
        int max= (-214748364);
        int max_index=(-1);
        for(int k=0; k<V ; ++k)
        {
            if (w[k]>max)
            {
                max=w[k];
                max_index=k;
            }
        }
        //cerr<<"max_index= "<< max_index << endl;
        //cerr<<"max= "<<max <<endl;
        // cerr<<"node is empty: "<<node.empty()<<endl;
        if (node.empty()) {break;}
        w[max_index]= (-214748364);
        if (max_index==(-1))
        {
            for ( i=node.begin(); i!=node.end(); ++i )
                {cerr<<"the node "<<(*i)<<" is not canceled";}
            exit(-1);
        }
        for (int j=0; j<V ; ++j) //max_index is sink
        {
            if (m[j][max_index]!= (-110))
            {
                //cerr << j << " " << max_index << " " << m[j][max_index] << "is removed" << endl;
                total_edges_weight+=m[j][max_index];
                char str1 [100];
                sprintf (str1, "%d %d %d\n",j,max_index,m[j][max_index]);
                fputs(str1 ,fpout);

                w[j]-=m[j][max_index];
                out[j]-=1;
                m[j][max_index]=(-110);

            }
        }
        //cerr<<"V: "<<V<<endl;
        for (int z=0; z<V ; ++z) //max_index is source
        {
            if (m[max_index][z]!=(-110))
            {
                //cerr << max_index << " " << z << " " << m[max_index][z] << "is removed (source)" << endl;
                w[z]+=m[max_index][z];
                in[z]-=1;
                m[max_index][z]=(-110);

            }
        }
        // pre.push_back( max_index );
        //cerr<<"the max_index "<<max_index<<" is push to vector "<<endl;
        for ( i=node.begin(); i!=node.end(); ++i )
        {
            if ( (*i) == max_index )
            {
                it1=node.erase(i);
                i=it1;
                break;   
            }
        }
        
    }//while
    
    fseek(fpout, 0, SEEK_SET);
    fprintf(fpout,"%d",total_edges_weight);
    
}



void Prim(priority_queue<P,vector<P>,greater<P> >& Q , vector<bool>& bool_black, vector<P>& pre, vector< list< pair<int, int> > >& adjacencyList ,FILE* fpout )
{
    
    //initialize at outside
    // cout << "here" << endl;
    fprintf(fpout,"            \n");
    // cout << "fff" << endl;
    Q.push(make_pair(0,0));
    // cout << "there" << endl;
    while(!Q.empty())
    {
        /*c+=1;
        if (c==100)
        {
            cout<<"something went wrong at outer";
            exit(-1);
        }*/
        P u = Q.top();
        //cout<<"u.first: "<<u.first<<endl;
        // cout<<"u.second: "<<u.second<<endl;
        Q.pop();
        if (bool_black[u.second]==true)
        {
            continue;
        }
        else
        {
            bool_black[u.second] = true;
            //can do MST here

            list< pair<int, int> >::iterator itr = adjacencyList[u.second].begin();
            while (itr != adjacencyList[u.second].end()) 
            {
                /*c+=1;
                if (c==100)
                {
                    cout<<"something went wrong at inner";
                    exit(-1);
                }*/
                if ( bool_black[ (*itr).first] == true )
                {
                    //cout<<"連到black node"<<endl;
                    ++itr;
                    continue;
                }
                else
                {
                    if (pre[(*itr).first].second >= (*itr).second )//weight<=key
                    {
                        // cout<<"use edge:"<<u.second<<" "<<(*itr).first<<" "<<(*itr).second<<" replace ";
                        if ( pre[(*itr).first].first!= -1)//old edge eliminated and add to answer if the edge exists
                        {
                            // cout<< pre[(*itr).first].first << " " << (*itr).first <<" "<<pre[(*itr).first].second <<endl;//change to fout
                            // cout<<"removed edge: "<<pre[(*itr).first].first << " " << (*itr).first <<" "<<-pre[(*itr).first].second <<endl;
                            // fout<<pre[(*itr).first].first << " " << (*itr).first <<" "<<-pre[(*itr).first].second <<endl;//weight correct!
                            char str1 [100];
                            sprintf (str1, "%d %d %d\n", pre[(*itr).first].first , (*itr).first , -pre[(*itr).first].second );
                            fputs(str1 ,fpout);
                            // output(pre[(*itr).first].first , (*itr).first , -pre[(*itr).first].second,fpout);
                            total_edges_weight +=(-pre[(*itr).first].second) ;
                        }

                        pre[(*itr).first].first=u.second;//node_pi=u
                        pre[(*itr).first].second=(*itr).second;//node_key=weight
                        Q.push(make_pair((*itr).second,(*itr).first));
                        
                    }
                    else//weight > key
                    {
                        // cout<<"weight>key"<<endl;
                        // cout<< u.second << " " <<(*itr).first<<" "<<(*itr).second<<endl;//this edge is eliminated
                        // cout<<"removed edge: "<<u.second << " " <<(*itr).first<<" "<<-(*itr).second<<endl;
                        // fout<<u.second << " " <<(*itr).first<<" "<<-(*itr).second<<endl;
                        char str1 [100];
                        sprintf (str1, "%d %d %d\n", u.second , (*itr).first , -(*itr).second );
                        fputs(str1 ,fpout);
                        // output(u.second , (*itr).first , -(*itr).second,fpout);
                        total_edges_weight += (-(*itr).second);
                    }
                }
                
                ++itr;
            }
        }
    }
    //Q ended(empty)
    
    // fout.seekp(0,ios::beg);
    // fout<<total_edges_weight;
    fseek(fpout, 0, SEEK_SET);
    fprintf(fpout,"%d",total_edges_weight);
}


int main(int argc, char *argv[]) {
    if (argc!=3) {
        cout <<"wrong number of arguments: "<< argc  << endl;
        return 0;
    }
    // cerr<<"correct"<<endl;
    FILE* fpin;
    FILE* fpout;
    fpin=fopen(argv[1], "r");
    // cout << "filename: " << argv[2] << endl;
    fpout=fopen(argv[2], "w");
    char  graphtype;
    char buffer[100];
    char ch;
    int integer;
    int state=0;
    std::ios::sync_with_stdio(false);
    
    fscanf(fpin,"%s",&graphtype);
    // cerr<<"correct"<<endl;
    
    // cerr<<graphtype<<endl;////////////////////////
    fscanf(fpin,"%s",&buffer);
    // cout<<"buffer: "<<buffer<<endl;////
    const int V=atoi(buffer);
    fscanf(fpin,"%s",&buffer);
    const int E=atoi(buffer);
    // cout<<"V= "<<V<<", E="<<E<<endl;
    //adjacencyList
    vector< list< pair<int, int> > > adjacencyList(V);
    int start,end, weight;
    if (graphtype=='u')
    {
        // cout<<"undirected";
        for (int i = 1; i <= E; ++i) {


            integer=0;
            state=0;
            bool minus=false;
        while( (ch=fgetc(fpin)) !=EOF){
            //cerr<<ch<<endl;
            if(ch=='\n') 
            {
                if (state==0)
                {
                    // if (start==0) {cerr<<"only one component";}
                }
                else if(state==2)
                {
                    if (minus==true)
                    {weight=-integer;}
                    else 
                    {weight=integer;}
                    minus=false;
                    integer=0;
                    state=0;
                    break;
                }
                else 
                {
                    cerr<<"wrong";
                }
            }
            else if(isdigit(ch)) integer = integer*10 + (ch & 0x0f);
            else if(ch==' ') /*printf("%d ", integer),*/ 
            {
                if (state==0) {start=integer; integer=0;state+=1;}
                else if (state==1){end=integer; integer=0;state+=1;}
                else {cerr<<"state wrong";}       
            }
            else if(ch=='-')
            {
                //cerr<<" - is readed"<<endl;
                minus=true;
            }
        }
            
        state=0;
        // cerr << start << " " << end << " " << weight <<endl; 

        // Adding Edge to the undirected graph
        adjacencyList[start].push_back(make_pair(end, -weight));
        adjacencyList[end].push_back(make_pair(start, -weight));
        // cerr << "pushed" << endl;
        
        }

        /*cout<<"\nThe Adjacency List-\n";
        // Printing Adjacency List
        for (int i = 0; i < adjacencyList.size(); ++i) {
            cout<<"adjacencyList["<<i<<"]";
         
            list< pair<int, int> >::iterator itr = adjacencyList[i].begin();
         
            while (itr != adjacencyList[i].end()) {
                cout<<" -> "<<(*itr).first<<(*itr).second;
                ++itr;
            }
            cout<<"\n";
        }*/
        // cerr<<"the end of the read in";

        priority_queue<P,vector<P>,greater<P> > Q;
        // Q.push(make_pair(0,0));
        vector<bool> bool_black;
        bool_black.assign(V,false);
        vector<P> pre;
        pre.assign(V,make_pair(-1,1000));
        Prim( Q ,  bool_black,  pre,  adjacencyList,fpout);//
    }
    else if (graphtype == 'd')
    {
        vector<int> row;
        row.assign(V,-110);//配置一個 row 的大小
        m.assign(V,row);//配置2維
        // vector<int> row2;
        // row2.assign(V,-110);//配置一個 row 的大小
        // m_for_test.assign(V,row2);//配置2維
        vector<int> w;
        vector<int> in;
        vector<int> out;
        w.assign(V,0);
        in.assign(V,0);
        out.assign(V,0);

        list<int> node;
        for (int i=0;i<V;++i) 
        {
            node.push_back(i);
        }

        for (int i = 1; i <= E; ++i) 
        {


            integer=0;
            state=0;
            bool minus=false;
            while( (ch=fgetc(fpin)) !=EOF)
            {
            //cerr<<ch<<endl;
                if(ch=='\n') 
                {
                    if (state==0)
                    {
                        //if (start==0) {cerr<<"only one component";}
                    }
                    else if(state==2)
                    {
                        if (minus==true)
                        {weight=-integer;}
                        else 
                        {weight=integer;}
                        minus=false;
                        integer=0;
                        state=0;
                        break;
                    }
                    else 
                    {
                        cerr<<"wrong";
                    }
                }
                else if(isdigit(ch)) integer = integer*10 + (ch & 0x0f);
                else if(ch==' ') /*printf("%d ", integer),*/ 
                {
                    if (state==0) {start=integer; integer=0;state+=1;}
                    else if (state==1){end=integer; integer=0;state+=1;}
                    else {cerr<<"state wrong";}       
                }
                else if(ch=='-')
                {
                    //cerr<<" - is readed"<<endl;
                    minus=true;
                }
            }
            
        state=0;
        
        
        // cerr<<start<<" "<<end<<" "<<weight<<"ya"<<endl;
        m[start][end]=weight;
        // m_for_test[start][end]=weight;
        w[start]+=weight;
        w[end]-=weight;
        out[start]+=1;
        in[end]+=1;
        //cerr <<"out of " <<start << " is " << out[start] << endl;
        


        }//for的部分
        //cerr<<"is in?";
        /*for (int i=0; i<V ; i++)
        {cerr <<"weight of " << i << " is " << w[i] << endl;}*/
        
        
        solve_dir(w,out,in,node,V,fpout);

    
    
    }
    else
    {cerr<<"unvalid graph type";}
    
    // cerr<<total_edges_weight;
    fclose(fpin);
    fclose(fpout);
    
    
    
    
    return 0;



}
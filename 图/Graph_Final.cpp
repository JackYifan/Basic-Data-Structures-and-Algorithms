#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<limits.h>
#include<queue>
#include<set>
using namespace std;


class Graph {
protected:
	int nv;
	bool directed;
	vector<string>vertices;
	map<string, int>iov;
	vector<bool>visited;
	virtual void dfs(int v) = 0;
public:
	Graph(bool dir = false) {
		directed = dir;
		nv = 0;
	}
	Graph(vector<string>v, bool dir = false) {
		directed = dir;
		nv = (int)v.size();
		vertices = v;
		for (int i = 0; i < nv; i++) {
			iov[v[i]] = i;
		}
	}
	Graph(int n, bool dir = false) {
		directed = dir;
		nv = n;
		vertices.resize(n);
		for (int i = 0; i < n; i++) {
			vertices[i] = to_string(i);
			iov[to_string(i)] = i;
		}
	}
	virtual void print() = 0;
	virtual void insertV() { insertV(to_string(nv)); }
	virtual bool insertV(string v);
	virtual bool insertE(string src, string dst, int weight = 1) {
		insertV(src);
		insertV(dst);
		return insertE(iov[src], iov[dst], weight);
	}
	virtual bool insertE(int src, int dst, int weight = 1) = 0;
	virtual bool removeE(string src, string dst) {
		if (iov.find(src) == iov.end() || iov.find(dst) == iov.end()) return false;
		removeE(iov[src], iov[dst]);
		return true;
	}
	virtual bool removeE(int src, int dst) = 0;
	virtual void dfs(string v) {
		if (iov.find(v) == iov.end()) return;
		visited.resize(nv);
		for (int i = 0; i < nv; i++) visited[i] = false;
		dfs(iov[v]);
	}
	virtual void bfs(string v) = 0;

};


class MGraph :public Graph {
protected:
	vector<vector<int>> adjM;
	void setAdjM();
	void dfs(int v) {
		cout << vertices[v] << " ";
		visited[v] = true;
		for (int i = 0; i < nv; i++) {
			if (adjM[v][i] != INT_MAX && !visited[i]) {
				dfs(i);
			}
		}
	}
public:
	MGraph(bool dir = false) : Graph(dir) {}
	MGraph(vector<string> v, bool dir = false) :Graph(v, dir) { setAdjM(); }
	MGraph(int n, bool dir = false) :Graph(n, dir) { setAdjM(); }
	void print();
	void insertV();
	bool insertV(string v);
	virtual bool insertE(string src, string dst, int weight = 1) {
		return Graph::insertE(src, dst, weight);
	}
	virtual bool insertE(int src, int dst, int weight = 1) {
		if (src < 0 || dst < 0 || src >= nv || dst >= nv) return false;
		if (adjM[src][dst] != INT_MAX) return false;
		adjM[src][dst] = weight;
		if (!directed) adjM[dst][src] = weight;
		return true;
	}
	bool removeE(string src, string dst) {
		return Graph::removeE(src, dst);
	}
	bool removeE(int src, int dst) {
		if (src < 0 || dst < 0 || src >= nv || dst >= nv) return false;
		if (adjM[src][dst] == INT_MAX) return false;
		adjM[src][dst] = INT_MAX;
		if (!directed) adjM[dst][src] = INT_MAX;
		return true;
	}
	void dfs(string s) {
		Graph::dfs(s);
	}

	virtual void bfs(string v) {
		if (iov.find(v) == iov.end()) return;
		int iv = iov[v];
		visited.resize(nv);
		for (int i = 0; i < nv; i++) visited[i] = false;
		queue<int>q;
		cout << v << " ";//对访问的结点做一系列操作
		visited[iv] = true;
		q.push(iv);
		while (!q.empty()) {
			int front = q.front();
			q.pop();
			for (int i = 0; i < nv; i++) {
				if (visited[i] == false && adjM[front][i] != INT_MAX) {
					cout << vertices[i] << " ";
					visited[i] = true;
					q.push(i);
				}
			}

		}
	}

	void dijkstra(string src) {
		if (iov.find(src) == iov.end()) return;
		vector<int>d(nv, INT_MAX);//结点距离src的距离
		vector<int>from(nv, -1);
		vector<int>known(nv, false);//已经确定最短距离的结点
		d[iov[src]] = 0;
		//在d中寻找没有访问过的最小的距离 known[i]=false
		int minDis, minIndex;//默认值不能是第零项，因为可能已经被访问过
		for (int t = 0; t < nv; t++) {
			minDis = INT_MAX;
			minIndex = -1;//可能所有点都是INT_MAX
			for (int i = 0; i < nv; i++) {
				if (known[i] == false && d[i] < minDis) {
					minDis = d[i];
					minIndex = i;
				}
			}
			if (minIndex == -1) break;
			known[minIndex] = true;
			for (int i = 0; i < nv; i++) {
				if (adjM[minIndex][i] != INT_MAX && known[i] == false && d[minIndex] + adjM[minIndex][i] < d[i]) {
					d[i] = d[minIndex] + adjM[minIndex][i];
					from[i] = minIndex;
				}
			}

		}
		for (int i = 0; i < nv; i++) cout << i << "\t"; cout << endl;
		for (int i = 0; i < nv; i++) cout << vertices[i] << "\t"; cout << endl;
		for (int i = 0; i < nv; i++) cout << d[i] << "\t"; cout << endl;
		for (int i = 0; i < nv; i++) cout << (from[i] >= 0 ? vertices[i] : "-") << "\t"; cout << endl;
	}


    void weightedShortest(string src){
        if (iov.find(src) == iov.end()) return;
		vector<int>d(nv, INT_MAX);//结点距离src的距离
		vector<int>from(nv, -1);
        queue<int>q;//元素的最短路径一旦更改就加入到队列中，可以已经在队列中的无需操作，可以多次入队
		vector<int>inqueue(nv, false);//已经确定最短距离的结点
		d[iov[src]] = 0;
        q.push(iov[src]);
        inqueue[iov[src]]=true;
        int v; 
        while(!q.empty()){
            v=q.front();q.pop();
            inqueue[v]=false ;
            for(int w=0;w<nv;w++){
                if(adjM[v][w]!=INT_MAX&&d[v]+adjM[v][w]<d[w]){
                    d[w]=d[v]+adjM[v][w];
                    from[w]=v;
                    if(!inqueue[w]){
                        q.push(w);
                        inqueue[w]=true;
                    }
                }
            }
        }		
		for (int i = 0; i < nv; i++) cout << i << "\t"; cout << endl;
		for (int i = 0; i < nv; i++) cout << vertices[i] << "\t"; cout << endl;
		for (int i = 0; i < nv; i++) cout << d[i] << "\t"; cout << endl;
		for (int i = 0; i < nv; i++) cout << (from[i] >= 0 ? vertices[i] : "-") << "\t"; cout << endl;
    }

    void prim(string src){
        if (iov.find(src) == iov.end()) return;
		vector<int>d(nv, INT_MAX);//结点距离树的距离
		vector<int>from(nv, -1);
		vector<int>known(nv, false);//已经加入了生成树
		d[iov[src]] = 0;
		//在d中寻找没有访问过的最小的距离 known[i]=false
		int minDis, minIndex;//默认值不能是第零项，因为可能已经被访问过
		for (int t = 0; t < nv; t++) {
			minDis = INT_MAX;
			minIndex = -1;//可能所有点都是INT_MAX
			for (int i = 0; i < nv; i++) {
				if (known[i] == false && d[i] < minDis) {
					minDis = d[i];
					minIndex = i;
				}
			}
			if (minIndex == -1) break;
			known[minIndex] = true;
			for (int i = 0; i < nv; i++) {
				if (adjM[minIndex][i] != INT_MAX && known[i] == false && adjM[minIndex][i] < d[i]) {
					d[i] = adjM[minIndex][i];
					from[i] = minIndex;
				}
			}
			//找到距离树的距离最短的点，加入树中并更新其他点距离树的距离

		}
		for (int i = 0; i < nv; i++) cout << i << "\t"; cout << endl;
		for (int i = 0; i < nv; i++) cout << vertices[i] << "\t"; cout << endl;
		for (int i = 0; i < nv; i++) cout << d[i] << "\t"; cout << endl;
		for (int i = 0; i < nv; i++) cout << (from[i] >= 0 ? vertices[i] : "-") << "\t"; cout << endl;
    }
};



class LGraph : public Graph {
protected:
	vector<map<int, int>>adjL;
	void setAdjL();
	void dfs(int v) {
		cout << vertices[v] << " ";
		visited[v] = true;
		for (auto x : adjL[v]) {
			if (!visited[x.first]) dfs(x.first);
		}
	}
public:
	LGraph(bool dir = false) :Graph(dir) {}
	LGraph(vector<string>v, bool dir = false) :Graph(v, dir) { setAdjL(); }
	LGraph(int n, bool dir = false) :Graph(n, dir) { setAdjL(); }
	void print();
	void insertV();
	bool insertV(string v);
	virtual bool insertE(string src, string dst, int weight = 1) {
		return Graph::insertE(src, dst, weight);
	}
	virtual bool insertE(int src, int dst, int weight = 1) {
		if (src < 0 || dst < 0 || src >= nv || dst >= nv) return false;
		if (adjL[src].find(dst) != adjL[src].end()) return false;
		adjL[src].insert(pair<int, int>(dst, weight));
		if (!directed) adjL[dst].insert(pair<int, int>(src, weight));
		return true;
	}
	bool removeE(string src, string dst) {
		return Graph::removeE(src, dst);
	}
	bool removeE(int src, int dst) {
		if (src < 0 || dst < 0 || src >= nv || dst >= nv) return false;
		if (adjL[src].find(dst) == adjL[src].end()) return false;
		adjL[src].erase(dst);
		if (!directed) adjL[dst].erase(src);
		return true;
	}
	void dfs(string s) {
		Graph::dfs(s);
	}
	virtual void bfs(string v) {
		if (iov.find(v) == iov.end()) return;
		int iv = iov[v];
		visited.resize(nv);
		for (int i = 0; i < nv; i++) visited[i] = false;
		queue<int>q;
		cout << v << " ";//对访问的结点做一系列操作
		visited[iv] = true;
		q.push(iv);
		while (!q.empty()) {
			int front = q.front();
			q.pop();
			for (auto x : adjL[front]) {
				int i = x.first;
				if (visited[i] == false) {
					cout << vertices[i] << " ";
					visited[i] = true;
					q.push(i);
				}
			}

		}
	}
	void dfs(int v, set<int>&school) {
		visited[v] = true;
		school.insert(v);
		for (auto x : adjL[v]) {
			if (!visited[x.first]) dfs(x.first, school);
		}
	}

	void findSchool() {
		set<int>school;//school集合，用于存储该学校的学生
		vector<set<int>>schoolList;
		visited.resize(nv);
		for (int i = 0; i < nv; i++) visited[i] = false;
		for (int i = 0; i < nv; i++) {
			//每次访问一个新学校的学生，清空school 
			school.clear();
			if (!visited[i]) dfs(i, school);
			schoolList.push_back(school);
		}
		int max = schoolList[0].size();
		int maxi = 0;
		for (int i = 1; i < schoolList.size(); i++) {
			if (max < schoolList[i].size()) {
				max = schoolList[i].size();
				maxi = i;
			}
		}
		cout << max << endl;
		for (auto x : schoolList[maxi]) cout << vertices[x] << " ";
	}
	void findSchoolBFS() {
		queue<int>q;
		vector<int>inschool(nv, -1);//-1表示还没有归到学校中 用于存储i号学生的学校编号
		int school, cnt, max, maxschool;
		school = cnt = max = maxschool = 0;
		//i号学生
		for (int i = 0; i < nv; i++) {
			if (inschool[i] != -1) continue;
			school++;
			cnt = 1;//本学校的第一个学生
			inschool[i] = school;
			q = queue<int>();//新的空队列
			q.push(i);
			int w;
			while (!q.empty()) {
				w = q.front();
				q.pop();
				for (auto x : adjL[w]) {
					//adjL[w]是Map,存储的是Entry
					if (inschool[x.first] == -1) {
						inschool[x.first] = school;
						cnt++;
						q.push(x.first);
					}
				}
			}
			if (max < cnt) {
				max = cnt;
				maxschool = school;
			}
		}
		cout << max << " " << endl;
		for (int i = 0; i < nv; i++) {
			if (inschool[i] == maxschool) cout << vertices[i] << " ";
		}

	}
	bool topSort() {
		vector<int> inDegree(nv, 0);//记录各点的入度
		for (auto vl : adjL) {
			//每个map
			for (auto w : vl) {
				//每个entry w.first是指向的结点编号
				inDegree[w.first]++;
			}
		}
		queue<int>q;
		for (int i = 0; i < nv; i++) {
			//没有入度的点进入队列
			if (inDegree[i] == 0) q.push(i);
		}
		int cnt = 0, v;
		while (!q.empty()) {
			//弹出的结点全是入度为0的结点
			v = q.front(); q.pop();
			cout << vertices[v] << " ";
			cnt++;
			for (auto w : adjL[v]) {
				inDegree[w.first]--;//指向的结点入度-1
				if (inDegree[w.first] == 0) q.push(w.first);//减了以后如果没有入度就加入队列
			}
		}
		if (cnt != nv) return false;
		return true;
	}
	void shortest(string src) {
		if (iov.find(src) == iov.end()) return;
		vector<int>d(nv, INT_MAX);//每个点距离src的最短路径
		vector<int>from(nv, -1);//上一个点的Index,进而记录一条路径
		d[iov[src]] = 0;//初始化
		queue<int>q;
		q.push(iov[src]);
		int v;
		while (!q.empty()) {
			int front = q.front();
			q.pop();
			for (auto x : adjL[front]) {
				if (d[x.first] == INT_MAX) {
					d[x.first] = d[front] + 1;
					from[x.first] = front;
					q.push(x.first);
				}
			}
		}
		for (int i = 0; i < nv; i++) {
			cout << vertices[i] << "(" << d[i] << ","
				<< (from[i] >= 0 ? vertices[from[i]] : "-")
				<< ")" << " ";
		}
		cout << endl;
	}
};




bool Graph::insertV(string v) {
	if (iov.find(v) != iov.end()) return false;
	vertices.push_back(v);
	iov[v] = nv++;
	return true;
}
void LGraph::setAdjL() {
	adjL.resize(nv);
	for (auto x : adjL) x.clear();

}

void LGraph::print() {
	//    adjL[0].insert(pair<int,int>(1,90));
	//    adjL[0].insert(pair<int,int>(2,80));
	for (int i = 0; i < nv; i++) {
		cout << vertices[i] << "[" << i << "]" << "-->";
		for (auto x : adjL[i]) {
			cout << vertices[x.first] << "(" << x.second << ")  ";
		}
		cout << endl;
	}

}

void LGraph::insertV()
{
	insertV(to_string(nv));
}

bool LGraph::insertV(string v)
{
	bool r = Graph::insertV(v);
	if (!r) return false;
	adjL.push_back(map<int, int>());
	return true;
}
void MGraph::setAdjM() {
	adjM.resize(nv);
	for (int i = 0; i < nv; i++) {
		adjM[i].resize(nv);
		for (int j = 0; j < nv; j++) {
			adjM[i][j] = INT_MAX;
		}
	}


}

void MGraph::print() {
	cout << "\t";
	for (int i = 0; i < nv; i++)   cout << vertices[i] << "\t";
	cout << endl;
	for (int i = 0; i < nv; i++) {
		cout << vertices[i] << ":\t";
		for (int j = 0; j < nv; j++) {
			if (adjM[i][j] == INT_MAX) cout << "-\t";
			else cout << adjM[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void MGraph::insertV() {
	insertV(to_string(nv));
}

bool MGraph::insertV(string v) {
	bool r = Graph::insertV(v);
	if (!r) return false;
	for (int i = 0; i < nv - 1; i++) {
		adjM[i].push_back(INT_MAX);
	}
	adjM.push_back(vector<int>(nv, INT_MAX));

	return true;
}
int main() {
	// vector<string>v = { "AA","BB","CC","DD","EE" };
	// LGraph g(v);
	// g.insertE("AA","CC");
	// g.insertE("BB","CC");
	// g.insertE(1,3);
	// g.insertE("DD","EE");
	// g.insertE("EE","BB");
	// g.print();
	// g.dfs("AA");
	// cout<<endl<<"-------------------"<<endl;
	// g.bfs("AA");
	// int n;cin>>n;
	// vector<string>v(n);
	// for(int i=0;i<n;i++){
	//     cin>>v[i];
	// }
	MGraph g;
	int m; cin >> m;
	for (int i = 0; i < m; i++) {
		string x, y; int weight;
		cin >> x >> y >> weight;
		g.insertE(x, y, weight);
	}
	// g.print();
	// g.findSchoolBFS();
	// g.print();
	// g.topSort();
	//g.weightedShortest("A");
    g.prim("A");
	return 0;
}
/*
5
C03 C04
C04 C05
C01 C02
C05 C06
C02 C06
*/
/*
12
A B 2
C A 4
A D 1
B D 3
B E 10
D C 2
D E 7
C F 5
D F 8
D G 4
E G 6
G F 1

*/
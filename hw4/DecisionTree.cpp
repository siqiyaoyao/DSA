#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<double,int> mypair;

bool mycompare(const mypair &a, const mypair &b){
	return get<0>(a) < get<0>(b);
}

struct node{
	node(){
		left=NULL;
		right=NULL;
	}
	int dim;
	double cut;
	int label;
	node * left;
	node * right;
};

class DecisionTree{
public:
	DecisionTree(){num_inst=0;num_feature=0;Y=NULL;X=NULL;root=NULL;epsilon=-1;}
	DecisionTree(vector<int> &,vector < vector<double> > &,double);
	~DecisionTree();
	node * train(vector<int> v){root=trainTree(v); return root;}
	node * getTree(){return root;}
	int getNumInst(){return num_inst;}
	int getNumFeature(){return num_feature;}
	void printTree(string);
	void clearTree();
	void setData(vector<int> &,vector < vector<double> > &);
	void setEpsilon(double);

private:
	void clear(node *);
	void ptree(node *,string);
	double confusion(int,int);
	double total_confusion(int,int,int,int);
	node * trainTree(vector<int> v);

	node *root;
	int num_inst;
	int num_feature;
	vector <int> *Y;
	vector < vector<double> > *X;
	double epsilon;
};

DecisionTree::DecisionTree(vector<int> &label,vector < vector<double> > &attr,double ep){
	Y=&label;
	X=&attr;
	num_inst=Y->size();
	num_feature=X[0][0].size();
	root=NULL;
	epsilon=ep;
}

DecisionTree::~DecisionTree(){
	clear(root);
}

void DecisionTree::clearTree(){
	clear(root);
}

void DecisionTree::clear(node * p){
	if(p!=NULL){
		clear(p->left);
		clear(p->right);
		delete []p;	
	}
}

void DecisionTree::setData(vector<int> &label,vector < vector<double> > &attr){
	Y=&label;
	X=&attr;
	num_inst=Y->size();
	num_feature=X[0].size();
}

void DecisionTree::setEpsilon(double ep){
	epsilon=ep;
}

double DecisionTree::confusion(int a,int b){
	if(a+b==0)
		return 0;
	double tmp1=(double)a/(a+b);
	double tmp2=(double)b/(a+b);
	return 1-tmp1*tmp1-tmp2*tmp2;
	
}

double DecisionTree::total_confusion(int a,int b,int c,int d){
	double total= (double)a+b+c+d;
	return (a+b)/total*confusion(a,b)+(c+d)/total*confusion(c,d);
}

node * DecisionTree::trainTree(vector<int> v){
	node *decision=new node();
	vector<mypair> candidate;
	int P=0,N=0,best_f;
	int size=v.size();
	double min_confusion=1,best_cut;

	for(int i=0;i<size;i++){
		if((*Y)[v[i]]==1)
			P++;
		else
			N++;
	}
	
	if(confusion(P,N)<=epsilon){
		decision->label=P>N?1:-1;
		return decision;
	}

	for(int f=0;f<num_feature;f++){
		//get data in f-th dim
		for(int i=0;i<size;i++){
			candidate.push_back(make_pair((*X)[v[i]][f],(*Y)[v[i]]));
		}
		//sort data
		sort(candidate.begin(),candidate.end(),mycompare);	
		//get best cut
		int left_y=0,left_n=0,right_y=P,right_n=N;
		double best_m=0,confusion=1;
		for(int m=0;m<=size;m++){
			if(m>0 && m<size && get<0>(candidate[m-1])==get<0>(candidate[m])){
				int y=get<1>(candidate[m]);
				if(y==1){
					left_y++;
					right_y--;
				}else{
					left_n++;
					right_n--;
				}
				continue;
			}
			double conf=total_confusion(left_y,left_n,right_y,right_n);
			if(conf<confusion){
				confusion=conf;
				best_m=m;
			}
			if(m==size)
				break;
			int y=get<1>(candidate[m]);
			if(y==1){
				left_y++;
				right_y--;
			}else{
				left_n++;
				right_n--;
			}
		}
		if(confusion<min_confusion){
			best_f=f;
			if(best_m==0){
				best_cut=get<0>(candidate[best_m])-1;
			}
			else if(best_m==size){
				best_cut=get<0>(candidate[best_m])+1;
			}
			else{
				best_cut=(get<0>(candidate[best_m-1])+get<0>(candidate[best_m]))*0.5;
			}
			min_confusion=confusion;
		}
		candidate.clear();
	}
	//condition that can't branch anymore
	if(min_confusion==confusion(P,N)){
		decision->label=P>N?1:-1;
		return decision;
	}

	decision->cut=best_cut;
	decision->dim=best_f;

	//cut and deal with left_subset and right_subset
	vector<int> left_index;
	vector<int> right_index;
	for(int i=0;i<size;i++){
		if((*X)[v[i]][best_f]<best_cut)
			left_index.push_back(v[i]);
		else
			right_index.push_back(v[i]);
	}

	decision->left=trainTree(left_index);
	decision->right=trainTree(right_index);
	return decision;
}


void DecisionTree::ptree(node * decision,string t){
	t=t+"\t";
	if(!decision->left || !decision->right){
		cout<<t+"return "<<decision->label<<";\n";
	}
	else{
		cout<<t+"if(attr["<<decision->dim<<"]<"<<decision->cut<<"){\n";
		ptree(decision->left,t);
		cout<<t+"}else{\n";
		ptree(decision->right,t);
		cout<<t+"}\n";
	}
}
void DecisionTree::printTree(string func_name){
	cout<<"int "<<func_name<<"(double * attr){\n";
	ptree(root,"");
	cout<<"}\n";
}


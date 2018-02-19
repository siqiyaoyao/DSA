#include "DecisionTree.cpp"
#include <string>

vector <int> total_index;
vector <int> Y;
vector < vector<double> > X;
int T;
int num_inst;
int num_feature;

void readData(char* datafile){
	ifstream in;
	in.open(datafile);
	if(!in.is_open()){
		cout<<"can't open input file "<<datafile<<endl;
		exit(-1);
	}
	string line;
	int max_dim=0;
	while(getline(in,line)){
		istringstream iss(line);
		if(!iss.str().length())
			break;
		//read y
		int y; iss>>y; Y.push_back(y);
		//read x
		int i=0,idx,col;
		double value;
		string tmp;
		vector<double> x;
		while(iss>>tmp){
			idx=tmp.find(':');
			col=stoi(tmp.substr(0,idx));
			value=stod(tmp.substr(idx+1));
			for(int j=i;j<col;j++){
				x.push_back(0);
			}
			x.push_back(value);
			i=col+1;
		}
		X.push_back(x);
		if(col>max_dim){
			max_dim=col;
		}
	}
	num_inst=Y.size();
	num_feature=max_dim+1;
	in.close();
	for(int i=0;i<num_inst;i++){
		total_index.push_back(i);
		int mx=X[i].size();
		for(int j=mx;j<num_feature;j++){
			X[i].push_back(0);
		}
	}
}
int main(int argc, char * argv[]){
	if(argc!=3){
		cout<<"./forest trainfile num_tree"<<endl;
		exit(1);
	}
	T=stod(argv[2]);
	readData(argv[1]);
	DecisionTree dtree(Y,X,0);
	int m=num_inst/3;

	for(int t=0;t<T;t++){
		random_shuffle(total_index.begin(), total_index.end());
		vector <int> sub_index(&total_index[0],&total_index[m]);
		dtree.train(sub_index);
		string tree_name="tree"+to_string(t+1)+"_predict";
		cout<<"//"<<tree_name<<":\n";
		dtree.printTree(tree_name);	
		cout<<"\n";
	}
	cout<<"int forest_predict(double *attr){\n"<<"int pred=0;\n";
	for(int t=0;t<T;t++){
		string tree_name="tree"+to_string(t+1)+"_predict";
		cout<<"pred+="<<tree_name<<"(attr);\n";
	}
	cout<<"return pred>=0?1:-1;\n}\n";

	return 0;
}
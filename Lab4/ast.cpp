#include <typeinfo>
#include "ast.h"
#include <stack>
#include <map>
#ifndef ASTCPP

string curFuncName;
localSymbolTable curLocal;
vector<type> parameterTypes;
stack<vector<type> > parameterStack;
bool isPrintf;
stack<bool> isPrintfStack;

map<int, string> globalStrings;
int sid=0;
string curStruct;
bool hasReturn;

int tempOffsets;

globalSymbolTable gst;

vector<stmt_astnode*> functions;

int labelsAllotted=0;

string getLabel(){

	string s = "LABEL"+to_string(labelsAllotted++);
	return s;
}

int getSize(variable v){
	string type = v.vtype.base.type;
	int baseSize=0;
	if(type == "int") baseSize=4;
	else if(type == "float") baseSize=4;
	else if(type == "void") baseSize=0;
	else if(v.vtype.base.pointers!=0) baseSize=4;
	else if(type[0]=='s'){
		int sum = 0;
		localSymbolTable lst = gst.symboltables[type];
		for(auto l: lst.symbols){
			variable vv = l.second.v;
			sum+=getSize(vv);
		}
		baseSize=sum;
	}
	int mul = 1;
	for(auto i: v.vtype.sizes){
		mul*=i;
	}

	return baseSize*mul;
}

bool isBasic(type t){
	if(t.sizes.size() == 0 && t.base.pointers == 0 && t.base.type != "void")
		return true;
	return false;
}

void showError(string s, int lineNumber = -1){
	cerr<<"Error in line number: "<<lineno<<": "<<s<<endl;
	exit(0);
}

void showWarning(string s, int lineNumber = -1){

	cerr<<"Warning in line number: "<<lineno<<": "<<s<<endl;
}

bool operator == (const type& t1, const type& t2){
	if(t1.sizes!=t2.sizes) return false;
	if(t1.base.type!=t2.base.type) return false;
	if(t1.base.pointers!=t2.base.pointers) return false;
	return true;
}

void binaryTypeCheck(exp_astnode *e1, exp_astnode *e2){
	type t1 = e1->expType;
	type t2 = e2->expType;
		
	string s1 = t1.base.type;
	string s2 = t2.base.type;
	if(isBasic(t1) && isBasic(t2)){
		if(s1 == "string" && s2 != "string" || s2 == "string" && s1 != "string")
			showError("Incompatible types", -1);
		if(s1[0]=='s' || s2[0]=='s'){
			showError("Cannot operate on struct types");
		}
		if(s1 == "float" && s2 == "int"){
			e2->expType.base.type = "float";
			e2->typeCasted = true;
		}
		if(s1 == "int" && s2 == "float"){
			e1->expType.base.type = "float";
			e1->typeCasted = true;
		}
		return;
	}

	if(t1.sizes.size() == 0 && t2.sizes.size() == 0 && t1.base.pointers == 1 && t2.base.pointers == 1){
		if(t1.base.type == "void" || t2.base.type == "void")
			return;
	}

	// array type check
	if(t1.base.pointers ==  t2.base.pointers && t1.sizes.size() == t2.sizes.size()){
		if(t1.base.type != t2.base.type)
			showError("Incompatible types");
		for(int i=1;i<t1.sizes.size();++i){
			if(t1.sizes[i] != t2.sizes[i]){
				showError("Incompatible types!");
			}
		}
		return;
	}
	
	if(!(t1.sizes.size() == 0 && t1.base.pointers == 1+t2.base.pointers && t2.sizes.size() == 1) || t1.base.type != t2.base.type){
		showError("Incompatible array types!");
		return;
	}

	if(!(t2.sizes.size() == 0 && t2.base.pointers == 1+t1.base.pointers && t1.sizes.size() == 1) || t1.base.type != t2.base.type){
		showError("Incompatible array types!");
		return;
	}
}

void unaryTypeCheck(type t1, exp_astnode* e){
	type t2 = e->expType;
	
	if(isBasic(t1) && isBasic(t2)){
		if(t1.base.type == "string" && t2.base.type != "string" ||
			t2.base.type == "string" && t1.base.type != "string"){
			showError("Incompatible types!", -1);
		}
		if(t2==t1) return;
		if(t1.base.type[0]=='s' || t2.base.type[0]=='s')
			showError("Incompatible types!");

		e->expType = t1;
		e->typeCasted=true;
		
		return;
	}



	if(t1.sizes.size() == 0 && t2.sizes.size() == 0 && t1.base.pointers == 1 && t2.base.pointers == 1){
		if(t1.base.type == "void" || t2.base.type == "void")
			return;
	}

	// if(t2.base.type == "void" && t1.base.type != "void")
		// showError("Can't cast void to non-void type");

	// array type check
	if(t1.base.pointers ==  t2.base.pointers && t1.sizes.size() == t2.sizes.size()){
		if(t1.base.type != t2.base.type)
			showError("Incompatible types");
		for(int i=1;i<t1.sizes.size();++i){
			if(t1.sizes[i] != t2.sizes[i]){
				showError("Incompatible types!");
			}
		}
		return;
	}
	
	if(!(t1.sizes.size() == 0 && t1.base.pointers == 1+t2.base.pointers && t2.sizes.size() == 1) || t1.base.type != t2.base.type){
		showError("Incompatible array types!");
		return;
	}

	//if(e->expType.base.type=="void") showError("Incompatible type!");
}

void copyStruct(int s){
	// assumes destination in $t0, source in $t1
	for(int i=0; i<s; i+=4){
		int x = -i;
		cout<<"lw $t2 "<<x<<"($t1)"<<endl;
		cout<<"sw $t2 "<<x<<"($t0)"<<endl;
	}
}

void stmt_astnode::print(int l){
	std::cout<<"This should never be called; stmt_astnode"<<std::endl;
}

void stmt_astnode::gencode(int accessType){
	cout<<"This should never be called; gencode stmt_astnode"<<endl;
	;
}

void exp_astnode::print(int l){

	std::cout<<"This should never be called; exp_astnode"<<std::endl;
}

void exp_astnode::gencode(int accessType){

	std::cout<<"This should never be called; gencode exp_astnode"<<std::endl;
}

void ref_astnode::print(int l){

	std::cout<<"This should never be called; ref_astnode"<<std::endl;
}

void ref_astnode::gencode(int accessType){

	std::cout<<"This should never be called; gencode ref_astnode"<<std::endl;
}

empty_astnode::empty_astnode(){

}

void empty_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Empty)";
}

void empty_astnode::gencode(int accessType){
	
}

seq_astnode::seq_astnode(std::vector<stmt_astnode*> n){

    nodes = n;
}

void seq_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Block [";
	for(unsigned int i = 0; i<nodes.size(); i++)
		nodes[i]->print(0);
	std::cout<<"])\n";
}

void seq_astnode::gencode(int accessType){
	tempOffsets -= 4;
	for(unsigned int i=0; i<nodes.size(); i++){
		int defaultOffset = tempOffsets;
		nodes[i]->gencode(1);
		tempOffsets=defaultOffset;
	}
	if(isFunction){
		cout<<"# default return statement"<<endl;
		cout<<"lw $ra, 4($sp)"<<endl;
		cout<<"lw $sp, 0($sp)"<<endl;
		cout<<"jr $ra"<<endl;
	}
}

assign_stmt_astnode::assign_stmt_astnode(exp_astnode* n2){
    r = n2;
}

void assign_stmt_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	r->print(0);
}

void assign_stmt_astnode::gencode(int accessType){
	r->gencode(1);
}

assign_exp_astnode::assign_exp_astnode(exp_astnode* n1, exp_astnode* n2){
    l = n1;
    r = n2;
}

void assign_exp_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Ass ";
	this->l->print(0);
	std::cout<<" ";
	if(r->typeCasted) cout<<"(to_"+r->expType.base.type<<" ";
	r->print(0);
	if(r->typeCasted) cout<<") ";
	std::cout<<")\n";
}

void assign_exp_astnode::gencode(int accessType){
	// TODO: assigning for structs and floats
	
	l->gencode(2);
	r->gencode(1);

	if(isBasic(l->expType) && isBasic(r->expType) && l->expType.base.type=="int" && r->expType.base.type=="int" && r->typeCasted){
		cout<<"l.s $f0, "<<r->tempOffset<<"($sp)"<<endl;
		cout<<"cvt.w.s $f0, $f0"<<endl;
		cout<<"mfc1 $t0, $f0"<<endl;
		cout<<"lw $t1, "<<l->tempOffset<<"($sp)"<<endl;
		cout<<"sw $t0, 0($t1)"<<endl;
		tempOffset=tempOffsets;
		tempOffsets-=4;
		cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
		return;
	}

	if(isBasic(l->expType) && isBasic(r->expType) && l->expType.base.type=="float" && r->expType.base.type=="float" && r->typeCasted){
		cout<<"lw $t0, "<<r->tempOffset<<"($sp)"<<endl;
		cout<<"lw $t1, "<<l->tempOffset<<"($sp)"<<endl;
		cout<<"mtc1 $t0, $f0"<<endl;
		cout<<"cvt.s.w $f0, $f0"<<endl;
		cout<<"s.s $f0, 0($t1)"<<endl;
		tempOffset=tempOffsets;
		tempOffsets-=4;
		cout<<"s.s $f0, "<<tempOffset<<"($sp)"<<endl;
		return;
	}

	if(isBasic(l->expType) && isBasic(r->expType) && l->expType.base.type=="float" && r->expType.base.type=="float"){
		cout<<"l.s $f0, "<<r->tempOffset<<"($sp)"<<endl;
		cout<<"lw $t1, "<<l->tempOffset<<"($sp)"<<endl;
		cout<<"s.s $f0, 0($t1)"<<endl;
		tempOffset=tempOffsets;
		tempOffsets-=4;
		cout<<"s.s $f0, "<<tempOffset<<"($sp)"<<endl;
		return;
	}

	if(expType.base.type[0]=='s' && expType.base.pointers==0 && expType.sizes.size()==0){
		int size = getSize(variable(l->expType, "", 0, 0));

		cout<<"addi $t1, $sp, "<<r->tempOffset<<endl;
		cout<<"lw $t0, "<<l->tempOffset<<"($sp)"<<endl;
		copyStruct(size);
		//cerr<<size<<endl;
		tempOffset=tempOffsets;
		tempOffsets-=size;
		cout<<"addi $t0, $sp, "<<tempOffset<<endl;
		copyStruct(size);
		return;
	}

	cout<<"# assignment"<<endl;
	cout<<"lw $t0, "<<r->tempOffset<<"($sp)"<<endl;
	cout<<"lw $t1, "<<l->tempOffset<<"($sp)"<<endl;
	cout<<"sw $t0, 0($t1)"<<endl;
	tempOffset=tempOffsets;
	tempOffsets-=4;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
}

return_astnode::return_astnode(exp_astnode* n){
    node = n;
}

void return_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Return ";
	if(node->typeCasted) cout<<"(to_"+node->expType.base.type<<" ";
	node->print(0);
	if(node->typeCasted) cout<<") ";
	std::cout<<") ";

}

void return_astnode::gencode(int accessType){
	node->gencode(1);
	// TODO: struct copying
	variable v=variable(node->expType, "", 0, 0);
	int retsize = getSize(v);
	//cerr<<retsize<<endl;
	int rlocation = 4+retsize + gst.getTotalArgsSize("function "+curFuncName);
	
	cout<<"# copying to RV"<<endl;
	
	if(isBasic(node->expType) && node->typeCasted){
		if(node->expType.base.type == "float"){
			// original type was int now changed to float
			cout<<"lw $t0, "<<node->tempOffset<<"($sp)"<<endl;
			cout<<"mtc1 $t0, $f0"<<endl;
			cout<<"cvt.s.w $f0, $f0"<<endl;
			cout<<"s.s $f0, "<<rlocation<<"($sp)"<<endl;
		}
		else{
			// original type was float now changed to int
			cout<<"l.s $f0, "<<node->tempOffset<<"($sp)"<<endl;
			cout<<"cvt.w.s $f0, $f0"<<endl;
			cout<<"mfc1 $t0, $f0"<<endl;
			cout<<"sw $t0, "<<rlocation<<"($sp)"<<endl;
		}
	}
	else{
		cout<<"# rlocation here "<<rlocation<<endl;
		cout<<"addi $t0, $sp, "<<rlocation<<endl;
		cout<<"addi $t1, $sp, "<<node->tempOffset<<endl;
		copyStruct(retsize);

		//cout<<"lw $t0, "<<node->tempOffset<<"($sp)"<<endl;
		//cout<<"sw $t0, "<<rlocation<<"($sp)"<<endl;
		//cout<<"add $v0, $t0, $0"<<endl;
	}

	cout<<"# returning"<<endl;
	cout<<"lw $ra, 4($sp)"<<endl;
	cout<<"lw $sp, 0($sp)"<<endl;
	cout<<"jr $ra"<<endl;
}

if_astnode::if_astnode(exp_astnode* n1, stmt_astnode** n2){
    node = n1;
    nodes[0] = n2[0];
    nodes[1] = n2[1];
}

void if_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(If ";
	node->print(0);
	std::cout<<" \n";
	nodes[0]->print(l+4);
	std::cout<<" \n";
	nodes[1]->print(l+4);
	std::cout<<") \n";
}

void if_astnode::gencode(int accessType){
	// TODO: everything
	node->gencode(1);
	string label1 = getLabel();
	string label2 = getLabel();

	cout<<"lw $t0, "<<node->tempOffset<<"($sp)"<<endl;
	cout<<"beq $t0, $0, "<<label1<<endl;
	nodes[0]->gencode(1);
	cout<<"j "<<label2<<endl;
	cout<<label1<<":"<<endl;
	nodes[1]->gencode(1);
	cout<<label2<<":"<<endl;

}

while_astnode::while_astnode(exp_astnode* n1, stmt_astnode* n2){
    node = n1;
    node2 = n2;
}

void while_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(While ";
	node->print(0);
	std::cout<<" ";
	node2->print(0);
	std::cout<<") ";
}

void while_astnode::gencode(int accessType){
	
	string label1 = getLabel();
	string label2 = getLabel();
	cout<<label1<<":";
	node->gencode(1);
	cout<<"lw $t0, "<<node->tempOffset<<"($sp)"<<endl;
	cout<<"beq $t0, $0, "<<label2<<endl;
	node2->gencode(1);
	cout<<"j "<<label1<<endl;
	cout<<label2<<":"<<endl;

}

for_astnode::for_astnode(exp_astnode** n1, stmt_astnode* n2){
	nodes[0]=n1[0];
	nodes[1]=n1[1];
	nodes[2]=n1[2];
	node=n2;
}

void for_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(For\n";
	for(int i=0; i<3; i++){
		nodes[i]->print(l + 4);
		std::cout<<" \n";
	}
	node->print(l+4);
	std::cout<<")\n";
}

void for_astnode::gencode(int accessType){
	string label1=getLabel(), label2=getLabel();
	nodes[0]->gencode(1);
	cout<<label1<<":"<<endl;
	nodes[1]->gencode(1);
	cout<<"lw $t0, "<<nodes[1]->tempOffset<<"($sp)"<<endl;
	cout<<"beq $t0, $0, "<<label2<<endl;
	node->gencode(1);
	nodes[2]->gencode(1);
	cout<<"j "<<label1<<endl;
	cout<<label2<<":"<<endl;

}

op_astnode2::op_astnode2(exp_astnode** n1, std::string n2){
	nodes[0]=n1[0];
	nodes[1]=n1[1];
	op=n2;
}

void op_astnode2::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	bool toCast = true;
	if(op=="OR" || op=="AND")
		toCast=false;
	std::cout<<"("<<op;
	if(nodes[0]->expType.base.type == "int" && toCast)
		std::cout<<"-INT ";
	if(nodes[0]->expType.base.type == "float" && toCast)
		std::cout<<"-FLOAT ";
	
	if(nodes[0]->typeCasted && toCast)
		cout<<"(to_" + nodes[0]->expType.base.type;
	nodes[0]->print(0);
	if(nodes[0]->typeCasted && toCast)
		cout<<") ";
	
	if(nodes[1]->typeCasted && toCast)
		cout<<"(to_" + nodes[1]->expType.base.type;
	nodes[1]->print(0);
	if(nodes[1]->typeCasted && toCast)
		cout<<") ";
	std::cout<<") ";
}

void op_astnode2::gencode(int accessType){
	// TODO: type casting
	if(nodes[0]->typeCasted || nodes[1]->typeCasted || nodes[0]->expType.base.type=="float" || nodes[1]->expType.base.type=="float"){

		// since in op_astnode2, so the cast must have
		// promoted the type of the variable to float
		
		// both base types would be the same here
		if(op=="AND"){
			nodes[0]->gencode(1);
			string label = getLabel();
			string l1 = getLabel();
			string l2 = getLabel();
			string l3 = getLabel();
			string l4 = getLabel();

			if(nodes[0]->typeCasted){
				cout<<"lw $t0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
				cout<<"mtc1 $t0, $f0"<<endl;
				cout<<"cvt.s.w $f0, $f0"<<endl;
			}
			else{
				cout<<"l.s $f0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
			}

			cout<<"li.s $f2, 0.0"<<endl;
			cout<<"c.eq.s $f0, $f2"<<endl;
			cout<<"bc1t "<<l1<<endl;
			cout<<"addi $t0, $0, 1"<<endl;
			cout<<"j "<<l2<<endl;
			cout<<l1<<":"<<endl;
			cout<<"addi $t0, $0, 0"<<endl;
			cout<<l2<<":"<<endl;

			cout<<"beq $t0, $0, "<<label<<endl;

			nodes[1]->gencode(1);			
			if(nodes[1]->typeCasted){
				cout<<"lw $t1, "<<nodes[1]->tempOffset<<"($sp)"<<endl;
				cout<<"mtc1 $t1, $f1"<<endl;
				cout<<"cvt.s.w $f1, $f1"<<endl;
			}
			else{
				cout<<"l.s $f1, "<<nodes[1]->tempOffset<<"($sp)"<<endl;
			}

			cout<<"li.s $f2, 0.0"<<endl;
			cout<<"c.eq.s $f1, $f2"<<endl;
			cout<<"bc1t "<<l3<<endl;
			cout<<"addi $t1, $0, 1"<<endl;
			cout<<"j "<<l4<<endl;
			cout<<l3<<":"<<endl;
			cout<<"addi $t1, $0, 0"<<endl;
			cout<<l4<<":"<<endl;

			cout<<label<<":"<<endl;
			cout<<"and $t0, $t0, $t1"<<endl;
			tempOffset = tempOffsets;
			tempOffsets -= 4;
			cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
			return;		
		}

		if(op=="OR"){
			nodes[0]->gencode(1);
			string label = getLabel();
			string l1 = getLabel();
			string l2 = getLabel();
			string l3 = getLabel();
			string l4 = getLabel();

			if(nodes[0]->typeCasted){
				cout<<"lw $t0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
				cout<<"mtc1 $t0, $f0"<<endl;
				cout<<"cvt.s.w $f0, $f0"<<endl;
			}
			else{
				cout<<"l.s $f0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
			}

			cout<<"li.s $f2, 0.0"<<endl;
			cout<<"c.eq.s $f0, $f2"<<endl;
			cout<<"bc1t "<<l1<<endl;
			cout<<"addi $t0, $0, 1"<<endl;
			cout<<"j "<<l2<<endl;
			cout<<l1<<":"<<endl;
			cout<<"addi $t0, $0, 0"<<endl;
			cout<<l2<<":"<<endl;

			cout<<"bne $t0, $0, "<<label<<endl;

			nodes[1]->gencode(1);			
			if(nodes[1]->typeCasted){
				cout<<"lw $t1, "<<nodes[1]->tempOffset<<"($sp)"<<endl;
				cout<<"mtc1 $t1, $f1"<<endl;
				cout<<"cvt.s.w $f1, $f1"<<endl;
			}
			else{
				cout<<"l.s $f1, "<<nodes[1]->tempOffset<<"($sp)"<<endl;
			}

			cout<<"li.s $f2, 0.0"<<endl;
			cout<<"c.eq.s $f1, $f2"<<endl;
			cout<<"bc1t "<<l3<<endl;
			cout<<"addi $t1, $0, 1"<<endl;
			cout<<"j "<<l4<<endl;
			cout<<l3<<":"<<endl;
			cout<<"addi $t1, $0, 0"<<endl;
			cout<<l4<<":"<<endl;

			cout<<label<<":"<<endl;
			cout<<"or $t0, $t0, $t1"<<endl;
			cout<<"addi $t3, $0, 1"<<endl;
			cout<<"movn $t0, $t3, $t0"<<endl;
			tempOffset = tempOffsets;
			tempOffsets -= 4;
			cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
			return;		
		}

		nodes[0]->gencode(1);
		nodes[1]->gencode(1);
				
		if(nodes[0]->typeCasted){
			cout<<"lw $t0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
			cout<<"mtc1 $t0, $f0"<<endl;
			cout<<"cvt.s.w $f0, $f0"<<endl;
		}
		else{
			cout<<"l.s $f0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
		}

		if(nodes[1]->typeCasted){
			cout<<"lw $t1, "<<nodes[1]->tempOffset<<"($sp)"<<endl;
			cout<<"mtc1 $t1, $f1"<<endl;
			cout<<"cvt.s.w $f1, $f1"<<endl;
		}
		else{
			cout<<"l.s $f1, "<<nodes[1]->tempOffset<<"($sp)"<<endl;
		}

		tempOffset = tempOffsets;
		tempOffsets -= 4;

		if(op == "PLUS"){
			cout<<"add.s $f0, $f0, $f1"<<endl;
			cout<<"s.s $f0, "<<tempOffset<<"($sp)"<<endl;
		}
		else if(op == "MINUS"){
			cout<<"sub.s $f0, $f0, $f1"<<endl;
			cout<<"s.s $f0, "<<tempOffset<<"($sp)"<<endl;
		}
		else if(op == "MULT"){
			cout<<"mul.s $f0, $f0, $f1"<<endl;
			cout<<"s.s $f0, "<<tempOffset<<"($sp)"<<endl;
		}
		else if(op == "DIV"){
			cout<<"div.s $f0, $f0, $f1"<<endl;
			cout<<"s.s $f0, "<<tempOffset<<"($sp)"<<endl;
		}
		else if(op=="LT"){
			cout<<"c.lt.s $f0, $f1"<<endl;
			string l1 = getLabel();
			string l2 = getLabel();
			cout<<"bc1t "<<l1<<endl;
			cout<<"add $t0, $0, $0"<<endl;
			cout<<"j "<<l2<<endl;
			cout<<l1<<":"<<endl;
			cout<<"addi $t0, $0, 1"<<endl;
			cout<<l2<<":"<<endl;
			cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
		}
		else if(op=="GT"){
			cout<<"c.lt.s $f1, $f0"<<endl;
			string l1 = getLabel();
			string l2 = getLabel();
			cout<<"bc1t "<<l1<<endl;
			cout<<"add $t0, $0, $0"<<endl;
			cout<<"j "<<l2<<endl;
			cout<<l1<<":"<<endl;
			cout<<"addi $t0, $0, 1"<<endl;
			cout<<l2<<":"<<endl;
			cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
		}
		else if(op=="LE_OP"){
			cout<<"c.le.s $f0, $f1"<<endl;
			string l1 = getLabel();
			string l2 = getLabel();
			cout<<"bc1t "<<l1<<endl;
			cout<<"add $t0, $0, $0"<<endl;
			cout<<"j "<<l2<<endl;
			cout<<l1<<":"<<endl;
			cout<<"addi $t0, $0, 1"<<endl;
			cout<<l2<<":"<<endl;
			cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
		}
		else if(op=="GE_OP"){
			cout<<"c.le.s $f1, $f0"<<endl;
			string l1 = getLabel();
			string l2 = getLabel();
			cout<<"bc1t "<<l1<<endl;
			cout<<"add $t0, $0, $0"<<endl;
			cout<<"j "<<l2<<endl;
			cout<<l1<<":"<<endl;
			cout<<"addi $t0, $0, 1"<<endl;
			cout<<l2<<":"<<endl;
			cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
		}
		else if(op=="EQ_OP"){
			cout<<"c.eq.s $f0, $f1"<<endl;
			string l1 = getLabel();
			string l2 = getLabel();
			cout<<"bc1t "<<l1<<endl;
			cout<<"add $t0, $0, $0"<<endl;
			cout<<"j "<<l2<<endl;
			cout<<l1<<":"<<endl;
			cout<<"addi $t0, $0, 1"<<endl;
			cout<<l2<<":"<<endl;
			cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
		}
		else if(op=="NE_OP"){
			cout<<"c.eq.s $f0, $f1"<<endl;
			string l1 = getLabel();
			string l2 = getLabel();
			cout<<"bc1f "<<l1<<endl;
			cout<<"add $t0, $0, $0"<<endl;
			cout<<"j "<<l2<<endl;
			cout<<l1<<":"<<endl;
			cout<<"addi $t0, $0, 1"<<endl;
			cout<<l2<<":"<<endl;
			cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
		}

		return;
	}


	if(op=="AND"){
		nodes[0]->gencode(1);
		string label = getLabel();
		cout<<"lw $t0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
		cout<<"beq $t0, $0, "<<label<<endl;
		nodes[1]->gencode(1);
		cout<<label<<":"<<endl;
		cout<<"lw $t0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
		cout<<"lw $t1, "<<nodes[1]->tempOffset<<"($sp)"<<endl;
		cout<<"and $t0, $t0, $t1"<<endl;
		tempOffset = tempOffsets;
		tempOffsets -= 4;
		cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
		return;		
	}

	if(op=="OR"){
		nodes[0]->gencode(1);
		string label = getLabel();
		cout<<"lw $t0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
		cout<<"bne $t0, $0, "<<label<<endl;
		nodes[1]->gencode(1);
		cout<<label<<":"<<endl;
		cout<<"lw $t0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
		cout<<"lw $t1, "<<nodes[1]->tempOffset<<"($sp)"<<endl;
		cout<<"or $t0, $t0, $t1"<<endl;
		cout<<"addi $t3, $0, 1"<<endl;
		cout<<"movn $t0, $t3, $t0"<<endl;
		tempOffset = tempOffsets;
		tempOffsets -= 4;
		cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
		return;		
	}

	nodes[0]->gencode(1);
	nodes[1]->gencode(1);
	cout<<"# Load values onto registers"<<endl;
	cout<<"lw $t0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
	cout<<"lw $t1, "<<nodes[1]->tempOffset<<"($sp)"<<endl;
	
	cout<<"# generate op code"<<endl;
	if(op == "PLUS"){
		cout<<"add $t0, $t0, $t1"<<endl;
	}
	else if(op == "MINUS"){
		cout<<"sub $t0, $t0, $t1"<<endl;
	}
	else if(op == "MULT"){
		cout<<"mul $t0, $t0, $t1"<<endl;
	}
	else if(op == "DIV"){
		cout<<"div $t0, $t0, $t1"<<endl;
	}
	else if(op=="LT"){
		cout<<"slt $t0, $t0, $t1"<<endl;
	}
	else if(op=="GT"){
		cout<<"slt $t0, $t1, $t0"<<endl;
	}
	else if(op=="LE_OP"){
		cout<<"slt $t0, $t1, $t0"<<endl;
		cout<<"addi $t1, $0, 1"<<endl;
		cout<<"sub $t0, $t1, $t0"<<endl;
	}
	else if(op=="GE_OP"){
		cout<<"slt $t0, $t0, $t1"<<endl;
		cout<<"addi $t1, $0, 1"<<endl;
		cout<<"sub $t0, $t1, $t0"<<endl;
	}
	else if(op=="EQ_OP"){
		cout<<"sub $t2, $t0, $t1"<<endl;
		cout<<"addi $t1, $0, 1"<<endl;
		cout<<"add $t0, $0, $0"<<endl;
		cout<<"movz $t0, $t1, $t2"<<endl;
	}
	else if(op=="NE_OP"){
		cout<<"sub $t2, $t0, $t1"<<endl;
		cout<<"addi $t1, $0, 0"<<endl;
		cout<<"addi $t0, $0, 1"<<endl;
		cout<<"movz $t0, $t1, $t2"<<endl;	
	}

	tempOffset = tempOffsets;
	tempOffsets -= 4;
	cout<<"# store the value back into memory"<<endl;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;

}

op_astnode1::op_astnode1(exp_astnode* n1, std::string n2){
	node=n1;
	op=n2;
}

void op_astnode1::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"("<<op<<" ";
	node->print(0);
	std::cout<<") ";
}

void op_astnode1::gencode(int accessType){
	


	if(op=="ADDRESSOF"){
		node->gencode(2);
		cout<<"lw $t0, "<<node->tempOffset<<"($sp)"<<endl;
		tempOffset=tempOffsets;
		tempOffsets-=4;
		cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;	
	}
	else if(op=="DEREF"){
		node->gencode(1);
		cout<<"lw $t0, "<<node->tempOffset<<"($sp)"<<endl;
		if(accessType==1) cout<<"lw $t0, 0($t0)"<<endl;
		tempOffset=tempOffsets;
		tempOffsets-=4;
		cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
	}
	else if(op=="NOT"){
		node->gencode(1);
		cout<<"lw $t0, "<<node->tempOffset<<"($sp)"<<endl;
		tempOffset=tempOffsets;
		cout<<"addi $t1, $0, 0"<<endl;
		cout<<"addi $t2, $0, 1"<<endl;
		cout<<"movz $t1, $t2, $t0"<<endl;
		tempOffsets-=4;
		cout<<"sw $t1, "<<tempOffset<<"($sp)"<<endl;			
	}
	else if(op=="UMINUS"){
		node->gencode(1);
		if(node->expType.base.type == "float"){
			cout<<"l.s $f0, "<<node->tempOffset<<"($sp)"<<endl;
			cout<<"neg.s $f0, $f0"<<endl;
			tempOffset = tempOffsets;
			tempOffsets-=4;
			cout<<"s.s $f0, "<<tempOffset<<"($sp)"<<endl;
		}
		else{
			cout<<"lw $t0, "<<node->tempOffset<<"($sp)"<<endl;
			cout<<"sub $t0, $0, $t0"<<endl;
			tempOffset=tempOffsets;
			tempOffsets-=4;
			cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
		}
	}
	else if(op=="PP"){
		if(node->expType.base.type == "float"){
			node->gencode(2);
			cout<<"lw $t0, "<<node->tempOffset<<"($sp)"<<endl;
			tempOffset=tempOffsets;
			cout<<"l.s $f1, 0($t0)"<<endl;
			cout<<"li.s $f2, 1.0"<<endl;
			cout<<"add.s $f2, $f1, $f2"<<endl;
			cout<<"s.s $f2, 0($t0)"<<endl;
			tempOffsets-=4;
			cout<<"s.s $f1, "<<tempOffset<<"($sp)"<<endl;
		}
		else{
			node->gencode(2);
			cout<<"lw $t0, "<<node->tempOffset<<"($sp)"<<endl;
			tempOffset=tempOffsets;
			cout<<"lw $t1, 0($t0)"<<endl;
			cout<<"addi $t2, $t1, 1"<<endl;
			cout<<"sw $t2, 0($t0)"<<endl;
			tempOffsets-=4;
			cout<<"sw $t1, "<<tempOffset<<"($sp)"<<endl;			
		}
	}

}

funcall_astnode::funcall_astnode(std::string n1, std::vector<exp_astnode*> n2){
	funcName=n1;
	nodes=n2;
}

void funcall_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"( "<<funcName<<" (";
	for(int i=0;i<nodes.size();++i){
		if(nodes[i]->typeCasted) cout<<"(to_"<<nodes[i]->expType.base.type;
		nodes[i]->print(0);	
		if(nodes[i]->typeCasted) cout<<") ";
	}
	std::cout<<") ) ";
}

void funcall_astnode::gencode(int accessType){
	if(funcName=="printf"){
		for(auto v: nodes){
			v->gencode(1);
			if(v->expType.base.type == "float" && v->expType.base.pointers==0){
				cout<<"l.s $f12, "<<v->tempOffset<<"($sp)"<<endl;
				cout<<"li $v0, 2"<<endl;
				cout<<"syscall"<<endl;
				cout<<"li $v0 4"<<endl;
				cout<<"la $a0, space"<<endl;
				cout<<"syscall"<<endl;
			}
			else if(v->expType.base.type != "string" || v->expType.base.pointers!=0){
				cout<<"lw $t0, "<<v->tempOffset<<"($sp)"<<endl;
				cout<<"li $v0, 1"<<endl;
				cout<<"add $a0, $0, $t0"<<endl;
				cout<<"syscall"<<endl;
				cout<<"li $v0 4"<<endl;
				cout<<"la $a0, space"<<endl;
				cout<<"syscall"<<endl;
			}
			else if(v->expType.base.type == "string"  && v->expType.base.pointers==0){
				cout<<"li $v0, 4"<<endl;
				stringconst_astnode* s = (stringconst_astnode*)v;
				cout<<"la $a0, "<<s->sname<<endl;
				cout<<"syscall"<<endl;
				cout<<"li $v0 4"<<endl;
				cout<<"la $a0, space"<<endl;
				cout<<"syscall"<<endl;
			}
		}
		cout<<"addi $v0, $0, 4"<<endl;
		cout<<"la $a0, newl"<<endl;
		cout<<"syscall"<<endl;
		return;
	}
	if(funcName=="printn"){
		cout<<"addi $v0, $0, 4"<<endl;
		cout<<"la $a0, newl"<<endl;
		cout<<"syscall"<<endl;
        return;
	}

	
	// tempOffsets-=4; // buffer for some reason
	auto args = gst.symbols[funcName].args;
	for(unsigned int i=0; i<args.size(); i++){
		//variable v = args[i];
		if(nodes[i]->expType.sizes.size()==0)
			nodes[i]->gencode(1);
		else nodes[i]->gencode(2);	
	}
	int sizet = abs(gst.symbols[funcName].v.size);
	tempOffset=tempOffsets;
	tempOffsets-=sizet; // RV
	
	for(auto e: nodes){
		type t = e->expType;
		// tempOffsets-=4; // buffer
		int argsize = abs(getSize(variable(t, "", 0, 0)));
		if(t.sizes.size()!=0) argsize=4;

		//cerr<<argsize<<endl;
		if(isBasic(t) && e->typeCasted){
			if(t.base.type == "float"){
				// original type was int now changed to float
				cout<<"lw $t0, "<<e->tempOffset<<"($sp)"<<endl;
				cout<<"mtc1 $t0, $f0"<<endl;
				cout<<"cvt.s.w $f0, $f0"<<endl;
				cout<<"s.s $f0, "<<tempOffsets<<"($sp)"<<endl;
			}
			else{
				// original type was float now changed to int
				cout<<"l.s $f0, "<<e->tempOffset<<"($sp)"<<endl;
				cout<<"cvt.w.s $f0, $f0"<<endl;
				cout<<"mfc1 $t0, $f0"<<endl;
				cout<<"sw $t0, "<<tempOffsets<<"($sp)"<<endl;
			}
		}
		else if(t.base.type[0]=='s' && t.base.pointers==0 && t.sizes.size()==0){
			cout<<"addi $t0, $sp, "<<tempOffsets<<endl;
			cout<<"addi $t1, $sp, "<<e->tempOffset<<endl;
			copyStruct(argsize);
			//cout<<"lw $t0, "<<e->tempOffset<<"($sp)"<<endl;
			//cout<<"sw $t0, "<<tempOffsets<<"($sp)"<<endl;	
		}
		else{
			cout<<"lw $t0, "<<e->tempOffset<<"($sp)"<<endl;
			cout<<"sw $t0, "<<tempOffsets<<"($sp)"<<endl;
		}
		
		tempOffsets-=argsize; // param
	}
	tempOffsets-=4; // RA
	
	cout<<"sw $sp, "<<tempOffsets<<"($sp)"<<endl;
	cout<<"addi $sp, $sp, "<<tempOffsets<<endl;
	//tempOffsets-=4;
	cout<<"jal ";
	if(funcName!="main") cout<<"F_";
	cout<<funcName<<endl;
}

floatconst_astnode::floatconst_astnode(float n){
	val=n;
}

void floatconst_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(FloatConst "<<val<<") ";
}

void floatconst_astnode::gencode(int accessType){
	// TODO: everything
	if((int)val == val)
		cout<<"li.s $f0, "<<val<<".0"<<endl;
	else
		cout<<"li.s $f0, "<<val<<endl;
	tempOffset = tempOffsets;
	tempOffsets-=4;
	cout<<"s.s $f0, "<<tempOffset<<"($sp)"<<endl;
}

intconst_astnode::intconst_astnode(int n){
	val=n;
}

void intconst_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(IntConst "<<val<<") ";
}

void intconst_astnode::gencode(int accessType){
	cout<<"# loading intconst"<<endl;
	cout<<"addi $t0, $0, "<<val<<endl;
	tempOffset = tempOffsets;
	tempOffsets-=4;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
}

stringconst_astnode::stringconst_astnode(std::string n, int s){
	val=n;
	sname = "S_" + to_string(s);
}

void stringconst_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(StringConst "<<val<<") ";
}

void stringconst_astnode::gencode(int accessType){
	// can only be used in printf, so put special
	// consideration for that here

}

identifier_astnode::identifier_astnode(std::string n){
	name=n;
}

void identifier_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Id \""<<name<<"\") ";
}

void identifier_astnode::gencode(int accessType){
	localSymbolTable lst = gst.symboltables["function "+curFuncName];
	int variableOffset = lst.symbols[name].v.offset;
	if(accessType==0){
		cerr<<"Should never happen"<<endl;
	}
	//cerr<<name<<" "<<variableOffset<<endl;
	cout<<"addi $t1, $sp, "<<variableOffset<<endl;
	if(expType.base.type[0]=='s' && expType.base.pointers==0 && expType.sizes.size()==0){
		if(accessType==1){
			int size = abs(lst.symbols[name].v.size);
			tempOffset=tempOffsets;
			tempOffsets-=size;
			cout<<"addi $t0, $sp, "<<tempOffset<<endl;
			copyStruct(size);
			return;
		}
	}
	else if(expType.sizes.size()==0){
		if(accessType==1) cout<<"lw $t1, 0($t1)"<<endl;
	}
	else if(variableOffset>0 && expType.sizes.size()!=0){
		cout<<"lw $t1, 0($t1)"<<endl;
	}
	tempOffset=tempOffsets;
	tempOffsets-=4;
	cout<<"sw $t1, "<<tempOffset<<"($sp)"<<endl;		
}

arrayref_astnode::arrayref_astnode(exp_astnode* b, exp_astnode* o){
	base = b;
	offset = o;
	this->lvalue = true;
}

void arrayref_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"( arrayRef";
	base->print(0);
	std::cout<<" [";
	offset->print(0);
	std::cout<<"] ";
	std::cout<<") ";
}

void arrayref_astnode::gencode(int accessType){
	if(accessType==0) cerr<<"Should never happen"<<endl;
	
	if(base->expType.sizes.size()==0){
		base->gencode(1);
	}
	else {
		base->gencode(2);
	}
	offset->gencode(1);
	
	int t;
	type tempType = base->expType;
	if(tempType.sizes.size()!=0){
		type tt = tempType;
		tt.sizes.erase(tt.sizes.begin());
		t = getSize(variable(tt, "", 0, 0));
	}
	else{
		type tt = tempType;
		tt.base.pointers--;
		t = getSize(variable(tt, "", 0, 0));
	}

	cout<<"lw $t0, "<<offset->tempOffset<<"($sp)"<<endl;
	cout<<"addi $t1, $0, "<<t<<endl;
	cout<<"mul $t0, $t0, $t1"<<endl;
	cout<<"lw $t1, "<<base->tempOffset<<"($sp)"<<endl;
	cout<<"sub $t1, $t1, $t0"<<endl;

	// $t1 now holds address of to be found
	// t holds size of element, since we must be at the last [ ]
	if(accessType==1){
		cout<<"addi $t0, $sp, "<<tempOffsets<<endl;
		tempOffset=tempOffsets;
		tempOffsets-=t;
		copyStruct(t);
		return;
	}
	
	tempOffset=tempOffsets;
	tempOffsets -= 4;
	cout<<"sw $t1, "<<tempOffset<<"($sp)"<<endl;
}

member_astnode::member_astnode(exp_astnode* n, identifier_astnode* i){
	node=n;
	id=i;
	this->lvalue = true;
}

void member_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(DOT ";
	node->print(0);
	std::cout<<" ";
	id->print(0);
	std::cout<<") ";
}

void member_astnode::gencode(int accessType){
	
	if(accessType==1){
		node->gencode(1);
		int offset = node->tempOffset;
		localSymbolTable lst = gst.symboltables[node->expType.base.type];
		int varOffset = lst.symbols[id->name].v.offset;
		// TODO for struct
		int size = lst.symbols[id->name].v.size;
		cout<<"addi $t0, $sp, "<<tempOffsets<<endl;
		cout<<"addi $t1, $sp, "<<offset+varOffset<<endl;
		copyStruct(size);
		tempOffset=tempOffsets;
		tempOffsets-=size;
		return;
	}
	node->gencode(2);
	int offset = node->tempOffset;
	localSymbolTable lst = gst.symboltables[node->expType.base.type];
	int varOffset = lst.symbols[id->name].v.offset;
	cout<<"lw $t0, "<<offset<<"($sp)"<<endl;
	cout<<"addi $t0, $t0, "<<(varOffset)<<endl;
	tempOffset=tempOffsets;
	tempOffsets-=4;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;

}

arrow_astnode::arrow_astnode(exp_astnode* n, identifier_astnode* i){
	node=n;
	id=i;
	this->lvalue = true;
}

void arrow_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Arrow ";
	node->print(0);
	std::cout<<" ";
	id->print(0);
	std::cout<<") ";
}

void arrow_astnode::gencode(int accessType){
	
	node->gencode(1);
	int offset = node->tempOffset;
	localSymbolTable lst = gst.symboltables[node->expType.base.type];
	int varOffset = lst.symbols[id->name].v.offset;
		

	if(accessType==1){
		// cout<<"lw $t0, "<<offset<<"($sp)"<<endl;	// address of struct base
		// cout<<"lw $t0, "<<(varOffset)<<"($t0)"<<endl;	// offset to member
		// TODO for struct
		int size = lst.symbols[id->name].v.size;
		
		cout<<"addi $t0, $sp, "<<tempOffsets<<endl;
		cout<<"lw $t1, "<<offset<<"($sp)"<<endl;
		cout<<"addi $t1, $t1, "<<varOffset<<endl;
		copyStruct(size);
		tempOffset=tempOffsets;
		tempOffsets-=size;
	

		// tempOffset=tempOffsets;
		// tempOffsets-=4;
		// cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
		return;
	}

	cout<<"lw $t0, "<<offset<<"($sp)"<<endl;
	cout<<"addi $t0, $t0, "<<(varOffset)<<endl;
	tempOffset=tempOffsets;
	tempOffsets-=4;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
}

#define ASTCPP
#endif
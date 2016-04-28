// int main(){
// 	float a[5], temp;
// 	int i,j;

// 	a[0]=5;
// 	a[1]=1;
// 	a[2]=3.0;
// 	a[3]=3.1;
// 	a[4]=2.1;

// 	for(i=0;i<5;i++){
// 		for(j=i+1;j<5;j++){
// 			if(a[i] > a[j]){
// 				temp=a[i];
// 				a[i]=a[j];
// 				a[j]=temp;
// 			}
// 			else ;
// 		}
// 	}

// 	for(i=0;i<5;i++){
// 		printf(a[i]);
// 	}
// 	return 0;
// }

// float func(int x){
// 	float begin, end, mid;
// 	int i;
// 	i=0;
// 	begin=0;
// 	end=x;
// 	while(i<10000){
// 		mid=(begin+end)/2;
// 		if(mid*mid < x){
// 			begin=mid;
// 		}
// 		else{
// 			end=mid;
// 		}
// 		i++;
// 	}
// 	return mid;
// }

struct inner{
	int val;
};

struct outer{
	struct inner a;
};

struct inner unwrap(struct outer* o){
	return o->a;
}

int main(){
	struct inner i;
	struct outer o;
	i.val=5;
	o.a=i;
	print(unwrap(&o).val);

	return 0;
}
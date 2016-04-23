
int main(){

	int array[10];
	int i, j, temp;

	array[0]=5;
	array[1]=6;
	array[2]=7;
	array[3]=1;
	array[4]=-7;
	array[5]=0;
	array[6]=12;
	array[7]=9;
	array[8]=2;
	array[9]=-3;

	for(i=0; i<10; i++){
		for(j=i+1; j<10; j++){
			if(array[i]>array[j]){
				temp=array[i];
				array[i]=array[j];
				array[j]=temp;
			}
			else{
				;
			}
		}
	}

	for(i=0; i<10; i++){
		printf(array[i]);
		print();
	}
	return 0;
	
}
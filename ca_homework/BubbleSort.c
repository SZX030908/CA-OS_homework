#define NUM 10
int array[NUM] = {5,7,2,4,0,1,8,9,6,3};
int main(){
    int i,j;
    int temp;

    for(i = 0;i < NUM-1;i++){
        for(j = NUM-2;j >= 0;j--){
            if(array[j] < array[j+1]){
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }   
}
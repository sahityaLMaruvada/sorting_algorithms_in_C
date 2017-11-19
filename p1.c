/*
The project aims to familiarize the student with the sorting algorithms and the usage of pointers
Bubble Sort, Insertion Sort, Counting Sort, Merge Sort, Quick Sort
Execution is done by passing the input and output files
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
The function writes the number of comparision and copies in each sorting algorithm to a file
input take the file pointer, number of comparisions, copies  and the name of sorting algorithm as input and writes them
into the target file
*/
void print_comparisions(FILE *comparision_op_file, int comparisions, int copies, char *sorting_algorithm){
    fprintf(comparision_op_file, "%s:%d comparisions %d copies\n",sorting_algorithm, comparisions,copies);
}




int * bubble_sort(int *a, FILE *comparision_op_file, int n){
    int copies=0,comparisions=0;
    int i,j,tmp;
    for(i=0;i<n;i++){
        for (j = n-1; j >= i+1 ; j--)
        {
            comparisions++;
            if (a[j]<a[j-1])
            {
                tmp=a[j];
                a[j]=a[j-1];
                a[j-1]=tmp;
                copies +=3;
            }

        }
    }
    print_comparisions(comparision_op_file,comparisions,copies,"Bubble Sort");
    
    return &a[0];

}

int *insertion_sort(int *a,FILE *comparision_op_file, int n){
    int key,i,j,copies=0,comparisions=1;
    for (i = 1; i < n; i++)
    {
        key=a[i];copies++;
        j=i-1;
        while (j>=0 && key < a[j]) 
        {
            comparisions++;
            a[j+1]=a[j];copies++;
            j--;
        }
        a[j+1]=key;copies++;
    }
    print_comparisions(comparision_op_file,comparisions,copies,"Insertion Sort");
    return &a[0];
}


int *counting_sort (int *arr, int min, int max, int length, int *b,FILE *comparision_op_file)
{

  int i,copies=0,comparisions=0;
  int c_length = max - min + 1;
  int c[c_length];
  for (i = 0; i < c_length; i++)
    c[i] = 0;
  for (i = 0; i < length; i++)
    c[arr[i] - min] += 1;
  for (i = 1; i < c_length; i++)
    {
      c[i] = c[i] + c[i - 1];
      copies++;
    }

  for (i = length - 1; i >= 0; i--)
    {
      b[c[arr[i] - min] - 1] = arr[i]; copies++;
      c[arr[i] - min] = c[arr[i] - min] - 1;
    }
  print_comparisions(comparision_op_file,comparisions,copies,"Counting Sort");
  return &b[0];
}

void merge(int a[], int left, int middle, int right,int *comparision_ptr,int *copy_ptr){
    int n1=middle-left+1;
    int n2=right-middle;
    int l[n1],r[n2];
    int i=0;
    for(;i<n1;i++)
    {
        l[i]=a[left+i];
        (*copy_ptr)++;
    } 
    for(i=0;i<n2;i++)
    {    
        r[i]=a[middle+1+i];
        (*copy_ptr)++;
    }
    i=0;int j=0;int k=left;
    //Compares values in left and right arrays and merges them to the main array
    while(i<n1&&j<n2){
        
        if(l[i]<=r[j]){
            a[k]=l[i];
            i++;
        }
        else{
            a[k]=r[j];
            j++;
        }
        (*comparision_ptr)++;
        (*copy_ptr)++;
        k++;
    }
    //Adds the extra values in l to the main array(unequal count of numbers in l and i)
    while(i<n1){
        a[k]=l[i];
        (*copy_ptr)++;
        i++;
        k++;
    }
    //Adds the extra values in r to the main array(left over numbers in the right array)
    while(j<n2){
        a[k]=r[j];
        (*copy_ptr)++;
        j++;
        k++;
    }
}



int *merge_sort(int arr[], int left, int right,int *comparision_ptr, int *copy_ptr, FILE *comparision_op_file ){
    int middle, final_comparisions;
    if(left<right){
        middle=(left+right)/2;
        merge_sort(arr,left,middle,comparision_ptr,copy_ptr,comparision_op_file);
        merge_sort(arr,middle+1,right,comparision_ptr,copy_ptr,comparision_op_file);
        merge(arr,left,middle,right,comparision_ptr,copy_ptr);
    }
    return &arr[0];
}


int partition_func(int *arr,int first,int last, int *comparision_ptr, int *copy_ptr){
    printf("%d\n",*comparision_ptr );
    int partition=arr[first],temp,i=0;
    (*copy_ptr)++;
    int left=first+1;
    int right=last;
    while(left<=right){
        
        while(partition>=arr[left]){
            (*comparision_ptr) ++;
            left++;
            printf("%d\n",*comparision_ptr );
        }
        while(partition<arr[right]){
            (*comparision_ptr) ++;
            right--;
            printf("%d\n",*comparision_ptr);
           
        }
        (*comparision_ptr)+=2;
        if(left<=right)
        {
            (*copy_ptr) +=3;
            temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
    }
    (*copy_ptr)+=3;
    temp=arr[first];
    arr[first]=arr[right];
    arr[right]=temp;
    return right;

}


void quick_sort(int *arr,int left,int right,int *comparision_ptr,int *copy_ptr){
    
    if(left<right){
        int partition=partition_func(arr,left,right,comparision_ptr,copy_ptr);
        quick_sort(arr,left,partition-1,comparision_ptr,copy_ptr);
        quick_sort(arr,partition+1,right,comparision_ptr,copy_ptr);
    }
    
}


void print_values(FILE *output_file, int count, int *bubble_sort, int *insertion_sort,int *counting_sort_ptr, int *merge_sort_ptr,int *quick_array ) 
{   
    fprintf(output_file, "%s\n","Bubble Sort  Insertion Sort  Counting Sort  Merge Sort  Quick Sort" );
    for (int i = 0; i < count; i++)
    {
        fprintf(output_file, "%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n",*(bubble_sort +i), *(insertion_sort+i),*(counting_sort_ptr+i),*(merge_sort_ptr+i),quick_array[i]);

    }
}

int main(int argc, char const *argv[]) 
{
    FILE *input_file = fopen(argv[1],"r");
    FILE *output_file=fopen(argv[2],"w");
    FILE *comparision_op_file=fopen("comparisions.txt","w");

    int count=0,min=0,max=0,comparisions=0,copies=0;
    int *comparision_ptr=&comparisions;
    int *copy_ptr=&copies;
    fscanf(input_file,"%d",&count);
    fscanf(input_file,"%d",&min);
    fscanf(input_file,"%d",&max);
    int array[count],bubble_array[count],insertion_array[count],counting_array[count],merge_array[count],quick_array[count], count_op_array[count], *bubble_sort_ptr,*insertion_sort_ptr,*counting_sort_ptr, *merge_sort_ptr, *quick_sort_ptr;
    for (int i = 0; i < count; i++) {
        fscanf(input_file, "%d", &array[i]);
    }
    for (int i = 0; i < count; i++)
    {
        bubble_array[i]=array[i];
        insertion_array[i]=array[i];
        counting_array[i]=array[i];
        merge_array[i]=array[i];
        quick_array[i]=array[i];
          
    }
    bubble_sort_ptr=bubble_sort(bubble_array,comparision_op_file,count);
    insertion_sort_ptr=insertion_sort(insertion_array,comparision_op_file,count);
    counting_sort_ptr=counting_sort(counting_array,min,max,count,count_op_array,comparision_op_file);
    merge_sort_ptr=merge_sort(merge_array,0,count-1,comparision_ptr,copy_ptr, comparision_op_file);
    print_comparisions(comparision_op_file,*comparision_ptr,*copy_ptr,"Merge Sort");
    *comparision_ptr=0;*copy_ptr=0;
    quick_sort(quick_array,0,count-1,comparision_ptr,copy_ptr);
    print_comparisions(comparision_op_file,*comparision_ptr,*copy_ptr,"Quick Sort");

   print_values(output_file,count,bubble_sort_ptr,insertion_sort_ptr,counting_sort_ptr,merge_sort_ptr,quick_array);

 
    fclose(input_file);
    fclose(output_file);
    fclose(comparision_op_file);
    return 0;
}


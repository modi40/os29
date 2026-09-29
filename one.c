#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int binary_search(int arr[], int n, int key) {
int low = 0, high = n - 1;
while(low <= high) {
int mid = (low + high) / 2;
if(arr[mid] == key) return mid;
if(arr[mid] < key) low = mid + 1;
else high = mid - 1;
}
return -1;
}
int main(int argc, char *argv[]) {
int i, j;
if(argc > 1) {
int n = argc - 1;
int *arr = (int *)malloc(n * sizeof(int));
for(i = 0; i < n; i++) arr[i] = atoi(argv[i + 1]);
printf("\n[Child Process loaded via execve] PID = %d\n", getpid());
printf("Received sorted array: ");
for(i = 0; i < n; i++) printf("%d ", arr[i]);
printf("\nEnter element to search: ");
int key;
if(scanf("%d", &key) == 1) {
int pos = binary_search(arr, n, key);
if(pos != -1) printf("Element %d found at position %d (0-indexed).\n", key, pos);
else printf("Element %d not found in the array.\n", key);
}
free(arr);
return 0;
}
int n;
printf("Enter number of elements in array: ");
if(scanf("%d", &n) != 1) return 0;
int arr[100];
printf("Enter %d integers: ", n);
for(i = 0; i < n; i++) scanf("%d", &arr[i]);
for(i = 0; i < n - 1; i++) {
for(j = 0; j < n - i - 1; j++) {
if(arr[j] > arr[j + 1]) {
int t = arr[j];
arr[j] = arr[j + 1];
arr[j + 1] = t;
}
}
}
printf("Parent sorted the array: ");
for(i = 0; i < n; i++) printf("%d ", arr[i]);
printf("\n");
pid_t pid = fork();
if(pid < 0) {
perror("Fork failed");
exit(1);
}
if(pid == 0) {
char *new_argv[110];
new_argv[0] = argv[0];
for(i = 0; i < n; i++) {
new_argv[i + 1] = (char *)malloc(16);
sprintf(new_argv[i + 1], "%d", arr[i]);
}
new_argv[n + 1] = NULL;
execve(argv[0], new_argv, NULL);
perror("execve failed");
exit(1);
} else {
wait(NULL);
printf("Parent Process: Child binary search finished.\n");
}
return 0;
}

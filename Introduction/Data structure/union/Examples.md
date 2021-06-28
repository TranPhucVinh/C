### Example 1

``struct`` inside a ``union``

```c
union data_frame {
    struct header {
        char id[1];
        char command[3];
        char check_sum[1];
    } header;//must give the name for struct header
    char data[5];
};

int main(){
    union data_frame data;

    strcpy(data.data, "12345");
    printf("data: %s\n", data.data);
    strcpy(data.header.id, "6");
	printf("header.id: %s\n", data.header.id);
    strcpy(data.header.command, "789");
	printf("header.command: %s\n", data.header.command);
    strcpy(data.header.check_sum, "0");
	printf("header.check_sum: %s\n", data.header.check_sum);
}
```
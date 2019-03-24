
``g++ -o test test.cpp -lpthread``

```c
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void *func_thread_1(void *ptr);// khai bao ham luong 1
void *func_thread_2(void *ptr);// khai bao ham luong 2

main() {
	pthread_t thread_1;// pointer luong 1
	pthread_t thread_2;// ponter luong 2

	int iret_1;//bien ket qua tra ve thuc thi luong 1
	int iret_2;//bien ket qua tra ve thuc thi luong 2

	iret_1 = pthread_create(&thread_1, NULL, func_thread_1, NULL);//khoi tao luong 1
	iret_2 = pthread_create(&thread_2, NULL, func_thread_2, NULL);//khoi tao luong 2

	cout << "Ket qua tao luong 1 " << iret_1 <<"\n";
	cout << "Ket qua tao luong 2 " << iret_2 << "\n";

	pthread_join(thread_1, NULL);// gắn luồng 1 vao main va wait until thread end
	pthread_join(thread_2, NULL);// gắn luồng 2 vao main va wait until thread end
}

void *func_thread_1(void *ptr){
	int count1 = 0;
	while(1){
		cout << "this is thread 1" <<count1 << "\n";
		count1++;
		sleep(1); //delay 1 second
	}
}

void *func_thread_2(void *ptr){
	int count2 = 0;
	while(1){
		cout << "thread 2 is running" << count2 << "\n";
		count2++;
		sleep(1);
	}
}
```

**pthread_create() with variable**

```c
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void *func_thread_1(void *ptr);// khai bao ham luong 1
void *func_thread_2(void *ptr);// khai bao ham luong 2

main() {
	pthread_t thread_1;// pointer luong 1
	pthread_t thread_2;// ponter luong 2

	int iret_1;//bien ket qua tra ve thuc thi luong 1
	int iret_2;//bien ket qua tra ve thuc thi luong 2

	char msg1[] = "First thread";
	char msg2[] = "Second thread";

	iret_1 = pthread_create(&thread_1, NULL, func_thread_1, (void *) msg1);//khoi tao luong 1
	iret_2 = pthread_create(&thread_2, NULL, func_thread_2, (void *) msg2);//khoi tao luong 2

	cout << "Ket qua tao luong 1 " << iret_1 <<"\n";
	cout << "Ket qua tao luong 2 " << iret_2 << "\n";

	pthread_join(thread_1, NULL);// gắn luồng 1 vao main va wait until thread end
	pthread_join(thread_2, NULL);// gắn luồng 2 vao main va wait until thread end
}

void *func_thread_1(void *variable){
	char *message;
	message = (char *) variable;
	int count1 = 0;
	while(1){
		cout << "this is " << message  << count1 << "\n";
		count1++;
		sleep(1); //delay 1 second
	}
}

void *func_thread_2(void *variable){
	char *message;
	message = (char *) variable;
	int count2 = 0;
	while(1){
		cout << "this is " << message << count2 << "\n";
		count2++;
		sleep(1);
	}
}
```

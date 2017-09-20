// tư vấn học ngôn ngữ lập trình
#include <stdio.h>
#include <string.h>
main () 
{ int n;
printf(" BẠN THEO HƯƠNG LAP TRÌNH NÀO ? \n " );
printf(" (Nhập vào số tương ứng với định hướng bạn chọn) \n
1. Web \n
2. Desktop \n
3. Mobile \n
4. Embedded \n
5. Khác \n" );


scanf("%d",&n);
int a;
char s1;

switch (n)
{
	case 1:
	printf(" các hướng lập trình web \n
	       1. Thiết kế web \n
	       2. Server \n
	       bạn chọn hướng nào ? (Nhập vào số tương ứng \n" );
	scanf("%d",&a);
	if (a == 1)
	{
    printf( " Đầu tiên học HTML, sau đó học CSS, JavaScript, JQuerry \n" );
    printf ("Bạn nên ưu tiên học JavaScript để có thể vừa lập trình giao diện và server. Đồng thời có thể test trực tiếp giao diện bằng localhost với JavaScript" );

	}
	else 
	{
	printf(" bạn cần server cho các ứng dụng real-time không ? \n" );
	printf("có (y) \n" );
	printf("không (n) \n");
	s1 = getchar();
	// so sánh s1
	// nếu đúng
	// printf (" học Node JS (JavaScript) ")
	// printf( " bạn cần tìm hiểu sâu hơn vể server ?")
	// yes no
	// yes : học cơ sở dữ liệu: Oracle, Mongol DB, SQLite, My SQL
	// no : Cảm ơn bạn đã sử dụng chương trình.

	// nếu sai: 
	case 2:
	printf("on going \n" ); 
	case 3:
	printf("Bạn cần lập trình cho hệ điều hành nào ? (Chọn số thứ tự tương ứng) \n" );
    printf ("1. Android" );
    printf ("2. IOS" );
    printf ("3. Windows Phone" );
    scanf();
    case 4:
    printf (" Mỗi vi điều khiển có một ngôn ngữ riêng. Bạn cần học 3 ngôn ngữ C, C++ để làm nền tảng (Đây là 2 ngôn ngữ thông dụng nhất");
    printf(" Bạn cũng có thể học thêm ngôn ngữ Assembly" );
    case 5:
        
	}

}


}
 
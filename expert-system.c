// tư vấn học ngôn ngữ lập trình
#include <stdio.h>

main () 
{ int n;
printf(" BẠN THEO HƯƠNG LAP TRÌNH NÀO ? \n " );
printf(" (Nhập vào số tương ứng với định hướng bạn chọn) \n\
1. Web \n\
2. Desktop \n\
3. Mobile \n\
4. Embedded \n\
5. Khác \n " );


scanf("%d",&n);
int a;
char s0, s1;

switch (n)
{
	case 1:
	printf(" các hướng lập trình web \n
		(Nhập vào số tương ứng) \n
	       1. Front End \n
	       2. Back End: App \n
	       3. Back End: Database \n
	       bạn chọn hướng nào ?  \n" );
	scanf("%d",&a);
	if (a == 1)
	{
    printf( " Bạn cần ưu tiên học theo thứ tự sau: \n
    1/ HTML: Thiết kế giao diện web. Bạn cũng có thể học XHTML, cũng có khả năng như HTML như có cấu trúc chặt chẽ hơn HTML \n 
    2/ CSS : Ngôn ngữ để định dạng trang web \n
    3/ JavaScript: Là ngôn ngữ lập trình cho HTML và Web. JavaScript hỗ trợ tạo các web động và hỗ trợ phía client của web tương tác \n
    với người dùng. Đoạn code JavaScript sẽ được chèn vào phần script của đoạn code HTML \n
    Bấm một phím bất kì để tiếp tục \n" );
    s1 = getchar();
    if ( (s0 >= 'a' && s0 <= 'z') || (s0 >= '0' && s0 <= '9'))
    {
    	printf("Bạn chỉ quan tâm tới Front end thôi sao ?" );
    }
	}
 WORK0:
 	else 
 {
	printf(" bạn cần server cho các ứng dụng real-time không ? \n
	         có (y) \n
	         không (n) \n");
	s1 = getchar();
	if (s1 = 'y')
	{
	printf("học Nodejs"); 	
	}
 }
 break;
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
	break;
	case 3:
	printf("Bạn cần lập trình cho hệ điều hành nào ? (Chọn số thứ tự tương ứng) \n
          1. Android \n
          2. IOS \n
          3. Windows Phone" );
    scanf();
    break;
    case 4:
    printf (" Mỗi vi điều khiển có một ngôn ngữ riêng. Bạn cần học 2 ngôn ngữ C, C++ để làm nền tảng (Đây là 2 ngôn ngữ thông dụng nhất \n
              Bạn cũng có thể học thêm ngôn ngữ Assembly" );
    break;
    case 5:
    printf("Có thể bạn quan tâm tới các hướng sau: \n
    	1. Internet of Things \n
    	2. Bảo mật - An ninh mạng \n
    	Nếu đúng, hãy nhập vào số tương ứng ở trên, nếu không, hãy nhấn phím "n" trên bàn phím ");
    break;
        
}	

}



 
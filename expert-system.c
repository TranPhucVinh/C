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
	int a,b,b1,b2;
	char s0[1], s1[1],s2[1],s3[1];

	switch (n)
	{
		case 1:
		printf(" các hướng lập trình web \n\
			(Nhập vào số tương ứng) \n\
		       1. Front End \n\
		       2. Back End: App \n\
		       3. Back End: Database \n\
		       bạn chọn hướng nào ?  \n" );
		scanf("%d",&a);
		if (a == 1)
		{
	    printf( " Bạn cần ưu tiên học theo thứ tự sau: \n\
	    1/ HTML: Thiết kế giao diện web. Bạn cũng có thể học XHTML, cũng có khả năng như HTML như có cấu trúc chặt chẽ hơn HTML \n\ 
	    2/ CSS : Ngôn ngữ để định dạng trang web \n\
	    3/ JavaScript: Là ngôn ngữ lập trình cho HTML và Web. JavaScript hỗ trợ tạo các web động và hỗ trợ phía client của web tương tác với người dùng. Đoạn code JavaScript sẽ được chèn vào phần script của đoạn code HTML \n\
	    Bạn muốn tìm hiểu thêm về lập trình web ? \n\
	    Bấm phím 'y' nếu muốn, hoặc bấm phím 'n' để từ chối. \n" );
	    scanf("%s",s0);
	    if ((strcmp(s0,"y")) ==0 )
    {
	    	printf("Bạn chỉ quan tâm tới Front end thôi sao ? \n\
	    	        Vâng: Nhấn phím 'y'	\n\
	    	        Không, tôi cần tự tay phát triển cả một website, cả front end và back end: Nhấn phím 'n' \n " );

	    	    scanf("%s",s1);
	         if ((strcmp(s1,"y")) ==0)
	         {
	    	   printf("Cảm ơn bạn đã sử dụng chương trình \n");
	    	   break;
	          }
	    else
	    { printf("Bạn quan tâm đến: \n\
	     1. Back End - App \n\
	     2. Back End - Database  \n\
	     3. Khác \n\
	     Nhập số tương ứng \n" );
	    	scanf("%d",&b1);
	        if ((b1 ==1))
	        {goto WORK0;}
	        else if  (b1 ==2)
	        {}
	        else {printf("Xin lỗi, chúng tôi không thể hỗ trợ bạn được. Có thể bạn nên học các kiến thức căn bản về mạng trước. \n\
	        	          Cảm ơn bạn đã sử dụng chương trình. \n" );
	              break; }

	    } 
	}
	    else {
	    if ((strcmp(s0,"n")) ==0 )
	    {
	    	printf("Cảm ơn bạn đã sử dụng chương trình" );
	    	break;
	    }

	    }
       }
	    
		
	 	else if (a ==2)
	 {  WORK0:
		printf(" Ưng dụng web của bạn thuộc loại nào: \n\
			     (Nhập vào số tương ứng) \n\
		         1. Nhẹ: Bán hàng, thanh toán, quản lí nội dung phạm vi nhỏ, xử lí văn bản, ... \n\
		         2. Nặng, chú trọng tính năng real-time, độ bảo mật cao: Games online, Phim online, báo điện tử, Quản lí nội dung rất lớn, ...  \n");
		scanf("%d",&b);
		if (b==1)
		{
			printf("Với các ứng dụng qui mô nhỏ như thế này, các vấn đề chính bạn cần quan tâm là xử lí nghiệp vụ: sale, makerting \n\
			thanh toán, thuế, bản quyền nội dung, quản lí sinh viên/nhân viên,.... Do đó, về mặt lí thuyết thì bạn có thể chọn bất cứ ngôn ngữ lập trình hướng đối tượng \n\
			nào cũng được, vì khi đó mỗi một lớp (class) sẽ đại diện cho một đối tượng ví dụ như: lớp khách hàng, lớp sinh viên, lớp nhân viên,... \n\
			Ban nên ưu tiên lựa chọn 3 ngôn ngữ: PHP, Python, Ruby vì tính đơn gỉan, gọn nhẹ, dễ học \n" );
			printf(" ");
			printf("Bạn quan tâm đến định hướng tìm hiểu chung cho Lập trình Web ? \n\
	 		        Nhấn phím 'y' nếu bạn quan tâm hoặc nhấn 'n' nếu bạn không quan tâm. \n");
			scanf("%s",s2);
	         if ((strcmp(s2,"y")) ==0)
	         {goto EXTRÁ0;}
	         else
	         	{goto EXTRA1;}
		}
	    else
	    {
	    	printf("Bạn cần học một trong các ngôn ngữ sau: Java, C#, JavaScript. \n\
	    	Với ứng dụng cần tính bảo mật cao, bạn nên ưu tiên học Java vì Java hỗ trợ tốt các thuộc tính truy cập: public, private,...\n\
	    	Với ứng dụng đòi hòi tính năng real-time, bạn nên học JavaScript với NodeJS vì NodeJS với npm hỗ trợ hàng ngàn package với vô số tính năng hữu ích. \n " );
	    	printf(" ");
			printf("Bạn quan tâm đến định hướng tìm hiểu chung cho Lập trình Web ? \n\
	 		        Nhấn phím 'y' nếu bạn quan tâm hoặc nhấn 'n' nếu bạn không quan tâm. \n");
			scanf("%s",s3);
	         if ((strcmp(s3,"y")) ==0)
	         {goto EXTRÁ0;}
	         else
	         	{goto EXTRA1;}
	    }
	 } 
	 else 
	 {
	 	printf(" Bạn cần tương tác với Database như thế nào ? \n\
	 		(Nhập vào số tương ứng) \n\
	 		1. Truy vấn dữ liệu \n\
	 		2. Quản trị cơ sở dữ liệu \n" );
	 	scanf("%d",&b2);
	 	if (b2==1)
	 	{
	 		printf("Bạn cần học SQL");
	 		printf("Bạn quan tâm đến định hướng tìm hiểu chung cho Lập trình Web chứ ? \n\
	 		        Nhấn phím 'y' nếu bạn quan tâm hoặc nhấn 'n' nếu bạn không quan tâm. \n");

	 	}
	 	else {printf("Bạn cần học các ngôn ngữ sau: MySQL, SQL Server, DB2, Oracle \n\
	 		 Trong đó, nếu chỉ mới bắt đầu học, bạn nên ưu tiên học MySQL để dễ tiếp cận hơn. \n");
	          printf("Bạn quan tâm đến định hướng tìm hiểu chung cho Lập trình Web chứ ? \n\
	 		        Nhấn phím 'y' nếu bạn quan tâm hoặc nhấn 'n' nếu bạn không quan tâm. \n");


	  }

	 }
	
	
		case 2:
		printf("on going \n" ); 
		break;
		case 3:
		printf("Bạn cần lập trình cho hệ điều hành nào ? (Chọn số thứ tự tương ứng) \n\
	          1. Android \n\
	          2. IOS \n\
	          3. Windows Phone" );
	    break;
	    case 4:
	    printf (" Mỗi vi điều khiển có một ngôn ngữ riêng. Bạn cần học 2 ngôn ngữ C, C++ để làm nền tảng (Đây là 2 ngôn ngữ thông dụng nhất \n\
	              Bạn cũng có thể học thêm ngôn ngữ Assembly" );
	    break;
	    case 5:
	    printf("Có thể bạn quan tâm tới các hướng sau: \n\
	    	1. Internet of Things \n\
	    	2. Bảo mật - An ninh mạng \n\
	    	Nếu đúng, hãy nhập vào số tương ứng ở trên, nếu không, hãy nhấn phím 'n' trên bàn phím ");
	    break;
	 }
	 EXTRA0:
	 printf("Để trở thành một lập trình viên Web chuyên nghiệp, bạn cần có kỹ năng ở 3 phần Front End, Back End, Database. \n\
	 	Bạn có thể tham khảo hướng nghiên cứu  theo các bước sau: \n\
	 	1/ HTML, CSS \n\
        2/ JavaScript \n\
        3/ Database: MySQL, SQL Server, DB2, Oracle (nếu mới bắt đầu bạn nên chọn MySQL hoặc SQL Server để dễ tiếp cận hơn) \n\
        4/ Back End: Bạn nên chọn một trong các ngôn ngữ Java, C#, PHP, Python, Ruby để trang bị kỹ năng này. \n");
	 EXTRA1:
	 printf("Cảm ơn bạn đã sử dụng chương trình \n");
	}



	 
// tư vấn học ngôn ngữ lập trình
#include <stdio.h>

main ()
{	int n;
	printf("CÂU HỎI:" );
	printf(" BẠN THEO HƯƠNG LAP TRÌNH NÀO ? \n " );
	printf(" (Nhập vào số tương ứng với định hướng bạn chọn) \n\
	1. Web \n\
	2. Desktop \n\
	3. Mobile \n\
	4. Embedded \n\
	5. Khác \n " );


	scanf("%d", &n);
	int a, b, b1, b2, c, c1, d, d1;
	char s0[1], s1[1], s2[1], s3[1], s4[1], s5[1], s6[1], s7[1], s8[1];

	switch (n)
	{
	case 1:
		printf(" CÂU HỎI: \n\
		    Các hướng lập trình web \n\
			(Nhập vào số tương ứng) \n\
		       1. Front End \n\
		       2. Back End: App \n\
		       3. Back End: Database \n\
		       \n\
		       bạn chọn hướng nào ?  \n" );
		scanf("%d", &a);
		printf("\n");
		if (a == 1)
		{
			printf( " TRẢ LƠI: \n\
	    	Bạn cần ưu tiên học theo thứ tự sau: \n\
	    1/ HTML: Thiết kế giao diện web. Bạn cũng có thể học XHTML, cũng có khả năng như HTML như có cấu trúc chặt chẽ hơn HTML \n\
	    \n\
	    2/ CSS : Ngôn ngữ để định dạng trang web \n\
	    \n\
	    3/ JavaScript: Là ngôn ngữ lập trình cho HTML và Web. JavaScript hỗ trợ tạo các web động và hỗ trợ phía client của web tương tác với người dùng. Đoạn code JavaScript sẽ được chèn vào phần script của đoạn code HTML \n\
	    \n\
	    Bạn muốn tìm hiểu thêm về lập trình web ? \n\
	    \n\
	    Bấm phím 'y' nếu muốn, hoặc bấm phím 'n' để từ chối. \n\
	    \n " );
			scanf("%s", s0);
			printf("\n");
			if ((strcmp(s0, "y")) == 0 )
			{
				printf(" GƠI Ý: \n\
	    		\n\
	    		Bạn chỉ quan tâm tới Front end thôi sao ? \n\
	    	        Vâng: Nhấn phím 'y'	\n\
	    	        Không, tôi cần tự tay phát triển cả một website, cả front end và back end: Nhấn phím 'n' \n" );

				scanf("%s", s1);
				printf("\n");
				if ((strcmp(s1, "y")) == 0)
				{
					printf("Cảm ơn bạn đã sử dụng chương trình \n");
					break;
				}
				else
				{	printf(" CÂU HỎI: \n\
	    	\n\
	    	Bạn quan tâm đến: \n\
	     1. Back End - App \n\
	     2. Back End - Database  \n\
	     3. Khác \n\
	     Nhập số tương ứng \n" );
					scanf("%d", &b1);
					printf("\n");
					if ((b1 == 1))
					{goto WORK0;}
					else if  (b1 == 2)
					{goto WORK1;}
					else {
						printf("Xin lỗi, chúng tôi không thể hỗ trợ bạn được. Có thể bạn nên học các kiến thức căn bản về mạng trước. \n\
	        	          Cảm ơn bạn đã sử dụng chương trình. \n" );
						break;
					}

				}
			}
			else {
				if ((strcmp(s0, "n")) == 0 )
				{
					printf("Cảm ơn bạn đã sử dụng chương trình \n" );
					break;
				}

			}
		}


		else if (a == 2)
		{	WORK0:
			printf(" CÂU HỎI: \n\
	\n\
Ưng dụng web của bạn thuộc loại nào: \n\
(Nhập vào số tương ứng) \n\
			     \n\
1. Nhẹ: Bán hàng, thanh toán, quản lí nội dung phạm vi nhỏ, xử lí văn bản, ... \n\
2. Nặng, chú trọng tính năng real-time, độ bảo mật cao: Games online, Phim online, báo điện tử, Quản lí nội dung rất lớn, ...  \n\
		         \n");
			scanf("%d", &b);
			printf("\n");
			if (b == 1)
			{
				printf(" TRẢ LƠI: \n\
Với các ứng dụng qui mô nhỏ như thế này, các vấn đề chính bạn cần quan tâm là xử lí nghiệp vụ: sale, makerting \n\
thanh toán, thuế, bản quyền nội dung, quản lí sinh viên/nhân viên,.... Do đó, về mặt lí thuyết thì bạn có thể chọn bất cứ ngôn ngữ lập trình hướng đối tượng \n\
nào cũng được, vì khi đó mỗi một lớp (class) sẽ đại diện cho một đối tượng ví dụ như: lớp khách hàng, lớp sinh viên, lớp nhân viên,... \n\
			\n\
Ban nên ưu tiên lựa chọn 3 ngôn ngữ: PHP, Python, Ruby vì tính đơn gỉan, gọn nhẹ, dễ học \n\
			\n" );

				printf(" GƠI Ý: \n\
Bạn quan tâm đến định hướng tìm hiểu chung cho Lập trình Web ? \n\
Nhấn phím 'y' nếu bạn quan tâm hoặc nhấn 'n' nếu bạn không quan tâm. \n\
	 		        \n");
				scanf("%s", s2);
				printf("\n");
				if ((strcmp(s2, "y")) == 0)
				{goto EXTRA0;}
				else
				{
					printf("Cảm ơn bạn đã sử dụng chương trình \n");
				}
			}
			else
			{
				printf(" TRẢ LƠI : \n\
Bạn cần học một trong các ngôn ngữ sau: Java, C#, JavaScript. \n\
Với ứng dụng cần tính bảo mật cao, bạn nên ưu tiên học Java vì Java hỗ trợ tốt các thuộc tính truy cập: public, private,...\n\
Với ứng dụng đòi hòi tính năng real-time, bạn nên học JavaScript với NodeJS vì NodeJS với npm hỗ trợ hàng ngàn package với vô số tính năng hữu ích. \n\
	    	\n " );

				printf(" GƠI Ý: \n\
Bạn quan tâm đến định hướng tìm hiểu chung cho Lập trình Web ? \n\
Nhấn phím 'y' nếu bạn quan tâm hoặc nhấn 'n' nếu bạn không quan tâm. \n\
	 		        \n");
				scanf("%s", s3);
				printf("\n");
				if ((strcmp(s3, "y")) == 0)
				{goto EXTRA0;}
				else
				{ printf("Cảm ơn bạn đã sử dụng chương trình \n");}
			}
		}
		else
		{	WORK1:
			printf(" CÂU HỎI: \n\
        \n\
	    Bạn cần tương tác với Database như thế nào ? \n\
	 		(Nhập vào số tương ứng) \n\
	 		1. Truy vấn dữ liệu \n\
	 		2. Quản trị cơ sở dữ liệu \n\
	 		\n" );
			scanf("%d", &b2);
			printf("\n");
			if (b2 == 1)
			{
				printf(" TRẢ LƠI: \n\
Bạn cần học SQL \n\
\n\
GƠI Ý: \n\
\n\
Bạn quan tâm đến định hướng tìm hiểu chung cho Lập trình Web chứ ? \n\
Nhấn phím 'y' nếu bạn quan tâm hoặc nhấn 'n' nếu bạn không quan tâm. \n\
\n");
				scanf("%s", s4);
				printf("\n");
				if ((strcmp(s4, "y")) == 0)
				{goto EXTRA0;}
				else
				{
					printf("Cảm ơn bạn đã sử dụng chương trình \n");
				}

			}
			else {
				printf(" TRÀ LƠI: \n\
Bạn cần học các ngôn ngữ sau: MySQL, SQL Server, DB2, Oracle \n\
Trong đó, nếu chỉ mới bắt đầu học, bạn nên ưu tiên học MySQL để dễ tiếp cận hơn. \n\
\n\
GƠI Ý: \n\
Bạn quan tâm đến định hướng tìm hiểu chung cho Lập trình Web chứ ? \n\
	          	\n\
Nhấn phím 'y' nếu bạn quan tâm hoặc nhấn 'n' nếu bạn không quan tâm. \n");
				scanf("%s", s5);
				printf("\n");
				if ((strcmp(s5, "y")) == 0)
				{goto EXTRA0;}
				else
				{	printf("Cảm ơn bạn đã sử dụng chương trình \n");
					break;
				}


			}
EXTRA0:
			printf("TRÀ LƠI: \n\
\n\
Để trở thành một lập trình viên Web chuyên nghiệp, bạn cần có kỹ năng ở 3 phần Front End, Back End, Database. \n\
Bạn có thể tham khảo hướng nghiên cứu  theo các bước sau: \n\
1/ HTML, CSS \n\
2/ JavaScript \n\
3/ Database: MySQL, SQL Server, DB2, Oracle (nếu mới bắt đầu bạn nên chọn MySQL hoặc SQL Server để dễ tiếp cận hơn) \n\
4/ Back End: Bạn nên chọn một trong các ngôn ngữ Java, C#, PHP, Python, Ruby để trang bị kỹ năng này. \n");
			break;


		}


	case 2:
		printf(" CÂU HỎI: \n\
\n\
Bạn cần lập trình Desktop với hệ điều hành nào ? (Nhập vào số thứ tự tương ứng) \n\
			    1. Windows (x86 và x 64) \n\
			    2. Linux (64-bit Intel) \n\
			    3. OS (32 bit) \n\
			    4. iOS (32 bit và 64 bit) \n\
			    5. Android (64 bit Intel) \n " );
		scanf("%d", &c);
		printf("\n");
		if (c == 1)
		{
			printf(" TRẢ LƠI: \n\
			Bạn có thể lựa chọn một trong các ngôn ngữ sau: C++, Java SE, Python, Delphi, Visual Basic.net. \n\
			Trong đó, C++ và Java SE là lựa chọn tốt nhất cho Windows Desktop \n");
			break;
		}
		else if ((c == 2) || (c == 3) || (c == 4) || (c == 5) )
		{
			printf(" TRẢ LƠI : \n\
Bạn cần học ngôn ngữ Delphi. Ngôn ngữ Delphi hỗ trợ cho cả 5 hệ điều hành: Windows, Linux, OS, iOS và Android. \n");
			break;
		}

	case 3:
		printf("Bạn cần lập trình cho hệ điều hành nào ? (Nhập vào số thứ tự tương ứng) \n\
	          1. Android \n\
	          2. IOS \n\
	          3. Windows Phone\n\
	          \n" );
		scanf("%d", &c1);
		printf("\n");
		if (c1 == 1)
		{	printf("Bạn đã thông thạo ít nhất một ngôn ngữ lập trình hướng đối tượng chưa ? \n\
	    	 Nếu có, ấn phím 'y', nếu không, ấn phím 'n' \n ");
			scanf("%s", s6);
			printf("\n");
			if (strcmp(s6, "y") == 0)
			{
				printf(" Bạn cần học lập trình Android với trình biên dịch Android Studio \n\
				 Bạn cũng có thể học lập trình Kotlin hoặc React Native. Lưu ý React Native hỗ trợ cả 2 hệ điều hành Android và IoS \n\
				 \n");

			}
			else {
				printf("Bạn cần học 1 trong 2 ngôn ngữ Java, C# để làm nền tảng, vì lập trình Mobile cần nền tảng kiến thức lập trình \n\
	    	hướng dối tượng trước khi bắt đầu. \n\
	    	\n");
			}
		}
		else if (c1 == 2)
		{
			printf("Bạn đã thông thạo ít nhất một ngôn ngữ lập trình hướng đối tượng chưa ? \n\
	    	 Nếu có, ấn phím 'y', nếu không, ấn phím 'n' \n\
	    	 \n ");
			scanf("%s", s7);
			printf("\n");
			if (strcmp(s7, "y") == 0)
			{
				printf(" Bạn cần học lập trình Swift \n\
				 Bạn cũng có thể React Native. React Native hỗ trợ cả 2 hệ điều hành Android và IoS \n\
				 \n");

			}
			else {
				printf("Bạn cần học 1 trong 2 ngôn ngữ Java, C# để làm nền tảng, vì lập trình Mobile cần nền tảng kiến thức lập trình \n\
	    	hướng dối tượng trước khi bắt đầu. \n");
			}
		}
		else
		{
			printf(" Bạn cần học lập trình C#. Việc thiết kế giao diện app và viết code sẽ thực hiện đồng bộ trên trình biên dịch Visual Studio. \n");
		}
	case 4:
		printf (" Mỗi vi điều khiển có một ngôn ngữ riêng. Bạn cần học 2 ngôn ngữ C, C++ để làm nền tảng (Đây là 2 ngôn ngữ thông dụng nhất) \n\
	              Bạn cũng có thể học thêm ngôn ngữ Assembly \n" );
		break;
	case 5:
		printf("Có thể bạn quan tâm tới các hướng sau: \n\
	    	1. Internet of Things \n\
	    	2. Bảo mật - An ninh mạng \n\
	    	3. Không phải 2 hướng trên \n\
	    	Nhập vào số tương ứng \n\
	    	\n");
		scanf("%d", &d);
		printf("\n");
		if (d == 1)
		{
			printf(" Bạn cần lập trình theo hướng nào ? \n\
	    		     (Nhập vào số tương ứng) \n\
	    		     1. Thao tác với các cảm biến \n\
	    		     2. Server \n\
	    		     3. Cơ sở dữ liệu \n\
	    		     \n" );
			scanf("%d", &d1);
			printf("\n");
			if (d1 == 1)
			{
				printf("Bạn cần học lập trình Arduino cho với chip ESP8266 hoặc ESP32. Chip ESP8266 và ESP32 hỗ trợ mạnh các giao tiếp WiFi. ");
			}
			else if (d1 == 2)
			{
				printf(" Bạn cần học JavaScript với NodeJS cho server và HTML cho thao tác giao diện.");
			}
			else {goto WORK1;}

		}
		else if (d == 2)
		{
			printf(" Bạn đã có kiến thức trước về lập trình và bảo mật chưa ? \n\
	     Nhập vào phím tương ứng: \n\
	     'y' nếu đã có kiến thức, 'n' nếu chưa. \n\
	     \n");

			scanf("%s", s8);
			printf("\n");
			if ((strcmp(s8, "y")) == 0)
			{
				printf("Bạn cần sử dụng tốt các công cụ tích hợp trên Kali Linux. \n");
			}
			else
			{
				printf(" Bạn cần học kỹ về các kiến thức mạng,sử dụng tốt hệ điều hành Linux, đặc biệt là Linux Shell. \n\
			Bạn cũng cần học thông thạo một vài ngôn ngữ lập trình như C#, Java, JavaScript với NodeJS \n ");
			}
		}
		else {
			printf("Xin lỗi, chương trình chúng tôi không thể hỗ trợ bạn được \n");
		}

	}
}




#include "description.h"

char introduction[] = "Programming language to build softwares";
char main_option[] = "What kind of software do you want to build ?";
char enter_the_following_number[] = "Enter the following number with your chosen option";
char enter_wrong_number_option[] = "Sorry, you have enter the wrong number option. Please try again.";
char enter_wrong_yes_no_option[] = "Sorry, you have enter the wrong Yes/No option. Please try again.";
char yes_no_option_confirm[] = "Yes or No ";
char thanks_for_using[] = "Thanks for using the program";
char thanks_and_cannot_help[] = "Sorry, our program can't help you. Thanks for using the program";

//Web programming options
char web_programming_options[] = "Web programming options: ";
char front_end_tutorial[] = "You can become a front-end developer with the following skills: ";
char front_end_html[] = "HTML: Help you design the web interface. You can also learn XHTML, which acts like HTML but has more concise architecture";
char front_end_css[] = "CSS: a style sheet language used for describing the presentation of a document written in a markup language like HTML.";
char front_end_javscript[] = "CSS: enables interactive web pages";
char further_web_programming_suggestion[] = "You wanna learn more about Web programming ?";
char front_end_further_sugestion[] = "You only care about front end programming ? ";

char back_end_app[] = "Back-end: App";
char back_end_database[] = "Back-end: Database";
char back_end_others[] = "Others";
char kind_of_website_chosen[] = "What kind of web application that you want to build ?";
char light_web_application[] = "1. Light web application: Sales, small content management, text document storage,...";
char heavy_load_web_application[] = "2. Heavy load web application: Real-time and high-security: Game online, online payment, online movies,...";
char light_web_application_solution[] = "With light web application, it's better to care on the technical aspect like sales, content management,... So in theory, any oriented object language can be chosen.";
char light_web_application_programming_solution[] = "You can refer to these 3 language for their easy-to-learn: Python, PHP and Ruby";
char heavy_load_web_application_solution[] = "You can choose one among those language: Java, C#, JavaScript";
char high_security_web_application[] = "For high security web application, you can choose Java as it supports the access method with public, private, protected";
char real_time_web_application[] = "For real-time web application, you should prefer Node.js with JavaScript";

char database_interaction[] = "How do you want to interact with the Database ?";
char database_query[] = "You should learn SQL";

char desktop_application_options[] = "Which OS do you want to choose to build the desktop application ?";
char mobile_application_options[] = "Which OS do you want to choose to build the mobile application ?";

char oop_language_suggestion[] = "You should choose one language among Java and C# to learn, as mobile application require knowledge of object oriented language to start";
char windows_phone_solution[] = "You should learn C# language. The Windows phone app's source code and interface can be implemented synchronously in Visual Studio code";

char embedded_programming_solution[] = "All MCUs has their own compiler and API but most base on C and C++. So you should learn C and C++ at first, you can also learn the Assembly language of the specific MCU chosen in your project";
char iot_embedded_software_solution[] = "You can take a look at 2 MCU ESP8266 and ESP32 which supports TCP/IP for IoT embedded software application";

char programming_knowledge[] = "Did you have any progamming knowledge previously";
char kali_linux[] = "You should learn to work with Kali Linux";

void print_programming_options(){
    puts("1. Website");
    puts("2. Desktop");
    puts("3. Mobile");
    puts("4. Embedded");
    puts("5. Others");
    printf("%s: ", enter_the_following_number);
}

void print_web_programming_options(){
    puts("1. Front End");
    puts("2. Back End: App");
    puts("3. Back End: Database");
    printf("%s: ", enter_the_following_number);
}

void print_front_end_tutorial(){
    puts(front_end_tutorial);
    puts(front_end_html);
    puts(front_end_css);
    puts(front_end_javscript);
    puts(further_web_programming_suggestion);
}

void print_front_end_further_sugestion(){
    puts(front_end_further_sugestion);
   
}

void print_back_end_suggestion(){
    puts("You can take a look on our back-end application solutions: ");
    puts("1. Back-end: App");
    puts("2. Back-end: Database");
    puts("3. Others");
}

void print_further_web_application_suggestion(){
    puts("You want further research on Web application ?");
    printf("%s: ", yes_no_option_confirm); //Yes No options put in the same line
}

void print_web_application_options(){
    puts(kind_of_website_chosen);
    puts(light_web_application);
    puts(heavy_load_web_application);
    printf("%s: ", enter_the_following_number);
}

void print_light_web_application_solution(){
    puts(light_web_application_solution);
    puts(light_web_application_programming_solution);
}

void print_heavy_load_web_application_solution(){
    puts(light_web_application_programming_solution);
    puts(high_security_web_application);
    puts(real_time_web_application);
}

void print_other_suggestion_with_database(){
    puts(database_interaction);
    puts("1. Database query ");
    puts("2. Database management");
    printf("%s: ", enter_the_following_number);
}

void print_database_query_solution(){
    puts(database_query);
}

void print_database_management_solution(){
    printf("You should learn those languages: My SQL, SQL Server, DB2, Oracle");
}

void print_fullstack_developer_roadmap(){
    puts("To become a fullstack developer, you need to have skill in Front-end, Back-end and Database.");
    puts("You can refer to the following roadmap:");
	puts("1. Front-end: HTML, CSS");
	puts("2. Front-end: JavaScript");
	puts("3. Database: MySQL, SQL Server, DB2, Oracle (It's easier for beginner to choose MySQL or SQL Server)");
	puts("4. Back-end: Choose one among those Java, C#, PHP, Python, Ruby");
}

void print_desktop_application_options(){
    puts(desktop_application_options);
    puts("1. Windows (x86 and x 64)");
	puts("2. Linux (64-bit Intel)");
	puts("3. OS (32 bit)");
	puts("4. iOS (32 bit và 64 bit)");
	puts("5. Android (64 bit Intel)");
    printf("%s: ", enter_the_following_number);
}

void print_windows_application_solution(){
    puts("You can choose one among those languages: C++, Java SE, Python, Delphi and Visual Basic.net");
	puts("Among them, C++ and Java SE are the best choices for Windows Desktop");
} 

void print_not_windows_application_solution(){
    puts("You should learn Delphi, which supports all 5 OS: Windows, Linux, OS, iOS và Android");
}

void print_mobile_application_options(){
    puts(mobile_application_options);
    puts("1. Android");
	puts("2. iOS ");
	puts("3. Windows Phone");
    printf("%s: ", enter_the_following_number);
}

void print_mobile_application_with_android_solution(){
    puts("You should learn Android with Android Studio");
    puts("You can also learn Kotlin or React Native. Notice that React Native suuports both Android and iOS");
}

void print_mobile_application_with_iOS_solution(){
    puts("You should learn Swift language");
    puts("You can also learn React Native as it suuports both Android and iOS");
}

void ask_for_object_oriented_language_familiar(){
    puts("Have you familiar which an Object Oriented language ?");
    printf("%s: ", yes_no_option_confirm); //Yes No options put in the same line
}

void print_other_suggestions(){
    puts("You may interested in those fields:");
	puts("1. Internet of Things");
	puts("2. Cybersecurity");
	puts("3. Not among those");
    printf("%s: ", enter_the_following_number);
}

void print_iot_application_option(){
    puts("What kind of IoT application do you want to build ?");
    puts("1. IoT embedded software");
	puts("2. Cloud system for IoT with website");
	puts("3. IoT database storage");
    printf("%s: ", enter_the_following_number);
}

void iot_webpage_suggestion(){
    puts("You can take a look to the webpage suggestion");
	printf("%s ", "Proceed with webpage suggestion ? Y or N: ");
}

void print_cybersecurity_solutions(){
    puts("You should have skills on network and Linux");
	puts("You should also know at least one programming language like Javascript, Python, C/C++ and Shell Script");
}
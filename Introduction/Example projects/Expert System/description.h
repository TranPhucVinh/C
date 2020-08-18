#include <string.h>
#include <stdio.h>

extern char introduction[], main_option[], enter_the_following_number[], yes_no_option_confirm[], enter_wrong_number_option[], enter_wrong_yes_no_option[], thanks_for_using[], thanks_and_cannot_help[];

//Web programming options
extern char web_programming_options[], front_end_tutorial[], front_end_html[], front_end_css[], front_end_javscript[], further_web_programming_suggestion[], front_end_further_sugestion[];

//Back-end app solutions
extern char back_end_app[], back_end_database[], back_end_others[], kind_of_website_chosen[], light_web_application[], heavy_load_web_application[], light_web_application_solution[], light_web_application_programming_solution[], heavy_load_web_application_solution[], high_security_web_application[], real_time_web_application[];

//Back-end database solutions
extern char database_interaction[], database_query[];

//Desktop application
extern char desktop_application_options[];
extern char oop_language_suggestion[], windows_phone_solution[];
extern char embedded_programming_solution[], iot_embedded_software_solution[];
extern char programming_knowledge[], kali_linux[];

void constant_char_init();
void print_programming_options();
void print_web_programming_options();
void print_front_end_tutorial();
void print_front_end_further_sugestion();
void print_back_end_suggestion();
void print_further_web_application_suggestion();
void print_web_application_options();
void print_light_web_application_solution();
void print_heavy_load_web_application_solution();
void print_other_suggestion_with_database();
void print_database_query_solution();
void print_database_management_solution();
void print_fullstack_developer_roadmap();

void print_desktop_application_options();
void print_windows_application_solution();
void print_not_windows_application_solution();

void print_mobile_application_options();
void print_mobile_application_with_android_solution();
void print_mobile_application_with_iOS_solution();
void ask_for_object_oriented_language_familiar();

void print_other_suggestions();
void print_cybersecurity_solutions();
void print_iot_application_option();
void iot_webpage_suggestion();
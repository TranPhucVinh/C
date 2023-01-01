#include "description.h"

char programming_option[1];
char web_option[1], back_end_option[1], desktop_option[1], mobile_option[1], other_suggestion_option[1];
char yes_no_option[1];

int main ()
{		
	puts(introduction);
	puts(main_option);

	print_programming_options();

	fgets(programming_option, 2, stdin);
	while ((getchar()) != '\n');  
	
	switch (programming_option[0])
	{
		case '1':
			WEB_PROGRAMMING_OPTIONS:
				puts(web_programming_options);
				print_web_programming_options();

				fgets(web_option, 2, stdin);
				while ((getchar()) != '\n');   

				if (web_option[0] == '1') //Front-end option handler
				{
					print_front_end_tutorial();
					FRONT_END_YES_NO_OPTION:
						printf("%s: ", yes_no_option_confirm); //Yes No options put in the same line
						fgets(yes_no_option, 2, stdin);

						while ((getchar()) != '\n');						
						if (yes_no_option[0] == 'Y')
						{
							FRONT_END_SUGGESTION_YES_NO_OPTION:
								print_front_end_further_sugestion();
								printf("%s: ", yes_no_option_confirm); //Yes No options put in the same line
								fgets(yes_no_option, 2, stdin);
								while ((getchar()) != '\n');

								if (yes_no_option[0] == 'Y')
								{
									puts(thanks_for_using);
									break;
								} else if (yes_no_option[0] == 'N')
								{	
									print_back_end_suggestion();
									BACK_END_FURTHER_SUGGESTION_YES_NO_OPTION:
										printf("%s: ", enter_the_following_number);
										fgets(web_option, 2, stdin);
										while ((getchar()) != '\n');

										if (web_option[0] == '1') goto BACK_END_APPLICATION;
										else if (web_option[0] == '2') goto BACK_END_DATABASE;
										else {
											puts(enter_wrong_yes_no_option);
											goto BACK_END_FURTHER_SUGGESTION_YES_NO_OPTION;
										}
								} else {
									puts(enter_wrong_yes_no_option);
									goto FRONT_END_SUGGESTION_YES_NO_OPTION;
								}	
						} else if (yes_no_option[0] == 'N'){
								puts(thanks_for_using);
								break;
						} else {
							puts(enter_wrong_yes_no_option);
							goto FRONT_END_YES_NO_OPTION;
						}	
				} else if (web_option[0] == '2')
				{
					BACK_END_APPLICATION: 
						print_web_application_options();
						fgets(back_end_option, 2, stdin);
						while ((getchar()) != '\n');

						if (back_end_option[0] == '1')
						{
							print_light_web_application_solution();

							BACK_END_SUGGESTION_YES_NO_OPTION:
								print_further_web_application_suggestion();
								
								fgets(yes_no_option, 2, stdin);
								while ((getchar()) != '\n');

								if (yes_no_option[0] == 'Y') goto FULL_STACK_DEVELOPER;
								else if (yes_no_option[0] == 'N')
								{
									puts(thanks_for_using);
									break;
								} else {
									puts(enter_wrong_yes_no_option);
									goto BACK_END_SUGGESTION_YES_NO_OPTION;
								}
						}
						else if (back_end_option[0] == '2')
						{
							print_heavy_load_web_application_solution();
							print_further_web_application_suggestion();

							fgets(yes_no_option, 2, stdin);
							while ((getchar()) != '\n');

							if (yes_no_option[0] == 'Y') goto FULL_STACK_DEVELOPER;
							else if (yes_no_option[0] == 'N')
							{
								puts(thanks_for_using);
								break;
							} else
							{
								puts(enter_wrong_yes_no_option);
								goto BACK_END_SUGGESTION_YES_NO_OPTION;
							}
						} else {
							puts(enter_wrong_number_option);
							goto BACK_END_APPLICATION;
						}
				}
				else if (web_option[0] == '3')
				{	
					BACK_END_DATABASE:
						print_other_suggestion_with_database();

						fgets(back_end_option, 2, stdin);
						while ((getchar()) != '\n');

						if (back_end_option[0] == '1')
						{
							print_database_query_solution();
							DATABASE_QUERY_YES_NO_OPTION:
								print_further_web_application_suggestion();

								fgets(yes_no_option, 2, stdin);
								while ((getchar()) != '\n');

								if (yes_no_option[0] == 'Y') goto FULL_STACK_DEVELOPER;
								else if (yes_no_option[0] == 'N')
								{
									puts(thanks_for_using);
									break;
								} else
								{
									puts(enter_wrong_yes_no_option);
									goto DATABASE_QUERY_YES_NO_OPTION;
								}
						}	else if (back_end_option[0] == '2') {
								print_database_management_solution();

								DATABASE_MANAGEMENT_YES_NO_OPTION:
									print_further_web_application_suggestion();

									fgets(yes_no_option, 2, stdin);
									while ((getchar()) != '\n');

									if (yes_no_option[0] == 'Y') goto FULL_STACK_DEVELOPER;
									else if (yes_no_option[0] == 'N')
									{
										puts(thanks_for_using);
										break;
									} else
									{
										puts(enter_wrong_yes_no_option);
										goto DATABASE_MANAGEMENT_YES_NO_OPTION;
									}
						}	else {
								puts(enter_wrong_number_option);
								goto BACK_END_DATABASE;
						}
						FULL_STACK_DEVELOPER:
							print_fullstack_developer_roadmap();
							break;
				} else {
					puts(enter_wrong_number_option);
					goto WEB_PROGRAMMING_OPTIONS;
				}
		case '2':
			DESKTOP_APPLICATION_OPTIONS:
				print_desktop_application_options();

				fgets(desktop_option, 2, stdin);
				while ((getchar()) != '\n');

				if (desktop_option[0] == '1')
				{
					print_windows_application_solution();
					break;
				}
				else if ((desktop_option[0] == '2') || (desktop_option[0] == '3') || (desktop_option[0] == '4') || (desktop_option[0] == '5'))
				{
					print_not_windows_application_solution();
					break;
				} else {
					puts(enter_wrong_number_option);
					goto DESKTOP_APPLICATION_OPTIONS;
				}

		case '3':
			MOBILE_APPLICATION_OPTIONS:
				print_mobile_application_options();

				fgets(mobile_option, 2, stdin);
				while ((getchar()) != '\n');

				if (mobile_option[0] == '1')
				{	
					ANDROID_YES_NO_OPTION:
						ask_for_object_oriented_language_familiar();
						fgets(yes_no_option, 2, stdin);
						while ((getchar()) != '\n');

						if (yes_no_option[0] == 'Y')
						{
							print_mobile_application_with_android_solution();
							break;
						}
						else if (yes_no_option[0] == 'N') {
							puts(oop_language_suggestion);
							break;
						} else {
							puts(enter_wrong_number_option);
							goto ANDROID_YES_NO_OPTION;
						}
				}
				else if (mobile_option[0] == '2')
				{
					iOS_YES_NO_OPTION:
						ask_for_object_oriented_language_familiar();
						fgets(yes_no_option, 2, stdin);
						while ((getchar()) != '\n');

						if (yes_no_option[0] == 'Y')
						{
							print_mobile_application_with_iOS_solution();
							break;
						}
						else if (yes_no_option[0] == 'N') {
							puts(oop_language_suggestion);
							break;
						} else {
							puts(enter_wrong_number_option);
							goto iOS_YES_NO_OPTION;
						}
				}
				else if (mobile_option[0] == '3')
				{
					puts(windows_phone_solution);
					break;
				}
				else {
					puts(enter_wrong_number_option);
					goto MOBILE_APPLICATION_OPTIONS;
				}
		case '4':
			puts(embedded_programming_solution);
			break;
		case '5':
			OTHER_SUGGESTION_OPTIONS:
				print_other_suggestions();
				fgets(other_suggestion_option, 2, stdin);
				while ((getchar()) != '\n');

				if (other_suggestion_option[0] == '1')
				{
					IOT_APPLICATION_OPTIONS:
						print_iot_application_option();
						fgets(other_suggestion_option, 2, stdin);
						while ((getchar()) != '\n');

						if (other_suggestion_option[0] == '1')
						{
							puts(iot_embedded_software_solution);
							break;
						}
						else if (other_suggestion_option[0] == '2')
						{
							IOT_WEBPAGE_SUGGESTION:
								iot_webpage_suggestion();
								fgets(yes_no_option, 2, stdin);
								while ((getchar()) != '\n');

								if (yes_no_option[0] == 'Y') goto WEB_PROGRAMMING_OPTIONS;
								else if (yes_no_option[0] == 'N') {
									puts(thanks_for_using);
									break;
								} else {
									puts(enter_wrong_number_option);
									goto IOT_WEBPAGE_SUGGESTION;
								}		
						}
						else if (other_suggestion_option[0] == '3') goto BACK_END_DATABASE;
						else {
							puts(enter_wrong_number_option);
							goto IOT_APPLICATION_OPTIONS;
						}
				}
				else if (other_suggestion_option[0] == '2')
				{
					CYBERSECURITY_OPTIONS:
						puts(programming_knowledge);
						printf("%s: ", yes_no_option_confirm);
						fgets(yes_no_option, 2, stdin);
						while ((getchar()) != '\n');

						if (yes_no_option[0] == 'Y')
						{
							puts(kali_linux);
							break;
						} else if (yes_no_option[0] == 'N')
						{
							print_cybersecurity_solutions();
							break;
						} else {
							puts(enter_wrong_number_option);
							goto CYBERSECURITY_OPTIONS;
						}
				}
				else if (other_suggestion_option[0] == '3'){
					puts(thanks_and_cannot_help);
					break;
				}
				else {
					puts(enter_wrong_number_option);
					goto OTHER_SUGGESTION_OPTIONS;
				}
		default:
			puts(enter_wrong_number_option);
			break;	
		}		
}
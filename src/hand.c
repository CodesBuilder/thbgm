/**
 * @file hand.c
 * @author CodesBuilder (2602783536@qq.com)
 * @brief JU57 A J0K3.
 * @version 0.1
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022 CodesBuilder and contributors
 *
 */
#include <stdio.h>
#include <string.h>

int cmdop_hand(int argc, char** argv) {
	const char* s =
	"\
########             #                  #             ########\n\
        #           #    #    #          #           #\n\
         #         #      #    #          #         #\n\
          #        #       #    #   #     #        #\n\
           #       #              ##      #       #\n\
            #       #          ###       #       #\n\
             ####### #     ####         # #######";
	char* s2 = "?thgir ,siht dnif ot yrt dna secruos eht nees evah uoY";
	for(size_t i=0;i<strlen(s2)/2;i++)
	{
		char tmp = s2[i];
		s2[i] = s2[strlen(s2)-i - 1];
		s2[strlen(s2)-i - 1] = tmp;
	}
	puts(s);
	puts(s2);
	return 0;
}

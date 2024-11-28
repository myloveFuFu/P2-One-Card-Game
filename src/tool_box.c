#include "tool_box.h"

void game_start(bool if_demo, FILE* f) {
	printf("-------Game Start-------\n");
	printf("Press enter to start the game!\n\n");
	fprintf(f, "-------Game Start-------\n");
	fprintf(f, "Press enter to start the game!\n\n");
	if (!if_demo) {
#ifdef _WIN32
		getchar();
		system("cls");
#else
		getchar();
		system("clear");
#endif
	}
}

void clean_screen(bool if_demo, FILE* f) {
	printf("Press enter to switch to the next player\n\n");
	fprintf(f, "Press enter to switch to the next player\n\n");
	if (!if_demo) {
#ifdef _WIN32
		getchar(); 
		getchar();
		system("cls");
#else
		getchar();
		getchar();
		system("clear");
#endif
	}
}

// void check_memory(const void* p){
//     if(p == NULL){
//         fprintf(stderr, "Error: memory allocation failed\n");
//         exit(-1);
//     }
// }

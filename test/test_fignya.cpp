
#include <iostream>
int value(){
    
    return 0;
}
int menu() {
	int choice = -1;

	while (choice != 0) {
		std::cout << "\n=== Game Menu ===\n"
				  << "1. Start game\n"
				  << "2. Instructions\n"
				  << "3. Credits\n"
				  << "0. Exit\n"
				  << "Choose an option: ";

		if (!(std::cin >> choice)) {
			std::cout << "Invalid input.\n";
			return 1;
		}

		switch (choice) {
		case 1:
			std::cout << "Starting game...\n";
			break;
		case 2:
			std::cout << "Use the controls to play and reach the goal.\n";
			break;
		case 3:
			std::cout << "Created by the game team.\n";
			break;
		case 0:
			std::cout << "Goodbye!\n";
			break;
		default:
			std::cout << "Invalid option.\n";
			break;
		}
	}

	return 0;
}

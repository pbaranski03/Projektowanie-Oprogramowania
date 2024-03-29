#include "User.h"

bool User::login(string role) {

	// Logowanie do systemu na podstawie podanej nazwy
	std::cout << "Type your name: "; std::cin >> username;
    std::cout << "Type your password: "; std::cin >> password;
	

    // Otwarcie pliku z danymi użytkowników
    std::ifstream file("users.txt");

    if (!file.is_open()) {
        std::cout << "ERROR while trying to access database." << std::endl;
        return false;
    }

    // Sprawdzenie, czy użytkownik istnieje w pliku
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string stored_username, stored_password, stored_role;

        if (iss >> stored_username >> stored_password >> stored_role) {
            if (stored_username == username && stored_password == password && stored_role == role) {
                std::cout << "Succes" << std::endl;
                file.close();

                return true;
            }
        }
    }

    std::cout << "Failure into finding user" << std::endl;
    file.close();
    return false;
}

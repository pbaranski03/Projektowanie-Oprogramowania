#ifndef MENAGER_H
#define MENAGER_H

#include "workers.h"

#include "Reception.h"
#include "websiteData.h"

class Menager : public Reception {

private:
	std::vector<workers*> worker;
	// Dodawanie nowych pracownik�w, w vectorze bo mo�e by� ich wi�cej ni� 1
	void addWorker();

	// Zmiana pensji pracownika i ewentualna zmiana czy dostanie pieni�dze w tym miesi�cu
	void changeWorkerSalary();

	// Zmiana opisu pracownika
	void changeWorkerReview();

	// Usuwa pracownika
	void deleteWorker();

	bool getFromFile();

	bool writeToFile();

public:
	Menager();
	~Menager();
	void menageWorkers();

	void editWebpage();
};

#endif

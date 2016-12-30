#include "stdafx.h"


#define CURRENT_LANGUAGE 3 
						   // 1 - english
						   // 2 - deutsch
						   // 3 - русский

map<string, string> languageMap;

HANDLE createFile(string filename) {

	HANDLE hFile, hStream;
	DWORD dwRet;

	hFile = CreateFileA(filename.c_str(),
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_OVERLAPPED,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		printf("Cannot open file");

	return hFile;
}

string getTranslation(string text, int languageNumber) {

	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
	if ((languageMap.find(text) != languageMap.end()) && (languageNumber != 3))
		return languageMap.at(text);
	else
		return text;
}

void readFile(string filename, int languageNumber) {

	map<string, string> fileLanguageMap;
	string str = "";
	int pos = 0;
	ifstream fin(filename); // открыли файл для чтения
	if (fin.is_open()) {
		while (!fin.eof()) {
			getline(fin, str);
			std::transform(str.begin(), str.end(), str.begin(), ::tolower); //lowercase
			int position = str.find('-', pos);
			fileLanguageMap.insert(pair<string, string>(str.substr(pos, position), str.substr(position + 1, str.size())));
		}

		for (map<string, string>::iterator it = fileLanguageMap.begin(); it != fileLanguageMap.end(); ++it)
			cout << it->first << " => " << it->second << endl;
	}
	else {
		cout << getTranslation("Ошибка! Файл с таким именем отсутствует.", languageNumber) << endl;
	}
	system("pause");
}

void fillLanguageMap(int languageNumber) {

	string str = "";
	string lang = "";

	int pos = 0;
	languageMap.clear();

	if (languageNumber == 1) {
		lang = "localization:english";
	}
	else if (languageNumber == 2) {
		lang = "localization:deutsch";
	}

	ifstream fin(lang);
	if (fin.is_open()) {
		while (!fin.eof()) {
			getline(fin, str);
			std::transform(str.begin(), str.end(), str.begin(), ::tolower); //lowercase
			int position = str.find('-', pos);
			languageMap.insert(pair<string, string>(str.substr(pos, position), str.substr(position + 1, str.size())));
		}

		for (map<string, string>::iterator it = languageMap.begin(); it != languageMap.end(); ++it)
			cout << it->first << " => " << it->second << endl;
	}
	else {
		cout << getTranslation("Ошибка! Файл с таким именем отсутствует.", languageNumber) << endl;
	}
}

void writeToFile(string filename, string record, int languageNumber) {
	ofstream fout(filename, ios::app);
	if (fout.is_open()) {
		fout << record << endl;
		fout.close();
	}
	else {
		cout << getTranslation("Ошибка! Файл с таким именем отсутствует.", languageNumber) << endl;
		
	}
}


//Меню выбора языка
int chooseLanguage(int currentLanguageNumber) {

	int languageNumber = currentLanguageNumber;
	int menuSelected = 25;
	while (menuSelected != 4)
	{
		system("cls");
		cout << " [1] - English" << endl;
		cout << " [2] - Deutsch" << endl;
		cout << " [3] - Русский" << endl;
		cout << endl;
		cout << " [4] - " << getTranslation("Назад", languageNumber) << endl;

		cin >> menuSelected;
		switch (menuSelected)
		{
		case 1:
			languageNumber = 1;
			fillLanguageMap(1);
			menuSelected = 4;
			break;
		case 2:
			languageNumber = 2;
			fillLanguageMap(2);
			menuSelected = 4;
			break;
		case 3:
			languageNumber = 3;
			menuSelected = 4;
			break;
		}
	}

	return languageNumber;
}

bool checkFileExistence(string fileName) {
	bool existance = false;
	ifstream fin(fileName);
	if (fin.is_open()) {
		existance = true;
	}
	fin.close();
	return existance;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "russian");

	HANDLE hFile, hStream;

	int menuSelected = 0;
	int languageNumber = CURRENT_LANGUAGE; //язык - русский
	
	if(languageNumber!=3)
		fillLanguageMap(languageNumber);

	string fileName = "";
	string streamName = "";
	string fileStreamName = "";
	string selectedFileName = "";
	string selectedFileStreamName = "";
	string record = "";

	while (menuSelected != 9)
	{
		system("cls");

		cout << getTranslation("Выбранный файл", languageNumber) << ": " << selectedFileName << endl;
		cout << getTranslation("Выбранный поток", languageNumber) << ": " << selectedFileStreamName << endl;
		cout << endl;
		cout << " [1] - " << getTranslation("Создать файл", languageNumber) << endl;
		cout << " [2] - " << getTranslation("Выбрать файл", languageNumber) << endl;
		cout << endl;
		cout << " [3] - " << getTranslation("Добавить поток", languageNumber) << endl;
		cout << " [4] - " << getTranslation("Выбрать поток", languageNumber) << endl;
		cout << " [5] - " << getTranslation("Удалить поток", languageNumber) << endl;
		cout << endl;
		cout << " [6] - " << getTranslation("Добавить в текущий поток фразы с переводом", languageNumber) << endl;
		cout << " [7] - " << getTranslation("Вывести содержимое файла", languageNumber) << endl;
		cout << endl;
		cout << " [8] - " << getTranslation("Выбрать язык", languageNumber) << endl;
		cout << endl;
		cout << " [9] - " << getTranslation("Выход", languageNumber) << endl;

		cin >> menuSelected;
		system("cls");

		switch (menuSelected)
		{
		case 1: //Создать файл
		
			cout << getTranslation("Введите имя файла", languageNumber) << endl;
			cin.ignore();
			getline(cin, fileName);
						
			if (checkFileExistence(fileName)) {
				cout << getTranslation("Файл с таким именем уже существует", languageNumber) << endl;
				system("pause");
			}
			else {
				hFile = createFile(fileName);
			}
			
			break;
		
		case 2: //Выбрать файл
		
			cout << getTranslation("Введите имя файла", languageNumber) << endl;
			cin.ignore();
			getline(cin, selectedFileName);
			
			if (!checkFileExistence(selectedFileName)) {
				selectedFileName = "";
				selectedFileStreamName = "";
				cout << getTranslation("Ошибка! Файл с таким именем отсутствует.", languageNumber) << endl;
				system("pause");
			}
			
			break;
		
		case 3://Добавить поток
		
			if (selectedFileName == "")
			{
				cout << getTranslation("Файл не выбран", languageNumber) << endl;
				system("pause");
				break;
			}
			cin.ignore();
			cout << getTranslation("Введите имя потока", languageNumber) << endl;
			getline(cin, streamName);
			fileStreamName = selectedFileName + ":" + streamName;
			cout << fileStreamName << endl;
						
			if (checkFileExistence(fileStreamName)) {
				cout << getTranslation("Поток с таким именем уже существует", languageNumber) << endl;
				system("pause");
			}
			else {
				hStream = createFile(fileStreamName);
			}
		
			break;
		
		case 4: //Выбрать поток
		
			if (selectedFileName == "")
			{
				cout << getTranslation("Файл не выбран", languageNumber) << endl;
				system("pause");
				break;
			}
			cout << getTranslation("Введите имя потока", languageNumber) << endl;
			cin.ignore();
			getline(cin, streamName);
			
			if (checkFileExistence(selectedFileName + ":" + streamName)) {
				selectedFileStreamName = selectedFileName + ":" + streamName;
			}
			else {
				cout << getTranslation("Ошибка! Файл с таким именем отсутствует.", languageNumber) << endl;
				system("pause");
			}
			
		
			break;
		
		case 5: //Удалить поток
		
			if (selectedFileName == "")
			{
				cout << getTranslation("Файл не выбран", languageNumber) << endl;
				system("pause");
				break;
			}
			cout << getTranslation("Введите имя потока", languageNumber) << endl;
			cin.ignore();
			getline(cin, streamName);

			if (checkFileExistence(selectedFileName + ":" + streamName)) {

				selectedFileStreamName = selectedFileName + ":" + streamName;
				remove(selectedFileStreamName.c_str());
				selectedFileStreamName = "";
			}
			else {
				cout << getTranslation("Ошибка! Файл с таким именем отсутствует.", languageNumber) << endl;
				system("pause");
			}
			
			break;
		
		case 6: //Добавить в текущий поток фразы с переводом
			if (selectedFileStreamName == "")
			{
				cout << getTranslation("Поток не выбран", languageNumber) << endl;
				system("pause");
				break;
			}

			cout << getTranslation("Вводите фразы с переводом", languageNumber) << endl;
			cout << getTranslation("Для завершения введите 'stop'", languageNumber) << endl;

			cin.ignore();
			while (true) {
				getline(cin, record);
				if (record == "stop")
					break;
				writeToFile(selectedFileStreamName, record, languageNumber);
			}

			break;

		case 7: //Вывести содержимое файла

			cout << getTranslation("Введите имя файла, содержимое которого следует вывести", languageNumber) << endl;
			cin.ignore();
			getline(cin, fileName);
			readFile(fileName,languageNumber);

			break;

		case 8: //Выбрать язык

			languageNumber = chooseLanguage(languageNumber);
			break;

		default:
			break;

		}
	}
}

